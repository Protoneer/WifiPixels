#include <ESP8266WiFi.h>

String GetAPList(){
  int n = WiFi.scanNetworks();
  String result = "";
  if(n==0){
    result = "<a>No networks found</a>";
  } else{
    for (int i = 0; i < n; ++i)
    {
      result += "<input type=""radio"" name=""ap"" value=""" + String(WiFi.SSID(i)) + """ checked=""checked"">" + String(WiFi.SSID(i)) + "<br>";
      delay(10);
    }

  }
  return result;
}

String IPtoString(IPAddress IPaddr){
  return String(IPaddr[0]) + '.' + String(IPaddr[1])  + '.' + String(IPaddr[2])  + '.' + String(IPaddr[3]);
}

bool WifiClient(){
  
  char ssid_buff[ssid.length()+1];
  char password_buff[password.length()+1];
  ssid.toCharArray(ssid_buff,ssid.length()+1);
  password.toCharArray(password_buff,password.length()+1);

  Serial.println("Connecting with...");
  Serial.print('[');
  Serial.print(ssid_buff);
  Serial.println(']');
  Serial.print('[');
  Serial.print(password_buff);
  Serial.println(']');

  WiFi.begin((const char*)ssid_buff, (const char*)password_buff);
  int retries = 5;  
  while (WiFi.status() != WL_CONNECTED && retries >= 0) {
    delay(500);
    Serial.print(".");
    retries--;
  }

  if(WiFi.status() == WL_CONNECTED){
    Mode = "WifiClient";
    Status = "Connected";
    Mode = "WifiClient";
    Network = ssid;
    IP = IPtoString(WiFi.localIP());
  
    Serial.println("");
    Serial.println("WiFi Client connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());    
    return true;
  } else{
    Mode = "n/a";
    Status = "n/a";
    Network = "n/a";

    Serial.println("WiFi Client not connected!!!");  
    return false;
  }

}

void WifiAP(){
  char apssid_buff[APSSID.length()+1];
  char appassword_buff[APPassword.length()+1];
  APSSID.toCharArray(apssid_buff,APSSID.length()+1);
  APPassword.toCharArray(appassword_buff,APPassword.length()+1);
  
  WiFi.softAP((const char*)apssid_buff, (const char*)appassword_buff, 7); // Open connection  

  //Stop Client
  WiFi.disconnect(true);

  Serial.println("WiFi AP Started");  
  
  Mode = "Access Point";
  Status = "Running";
  Network = APSSID;
  IP = IPtoString(WiFi.softAPIP());

  
}

void wifiSetup(){
  if(!WifiClient()){
    WifiAP();  
  }    
}
