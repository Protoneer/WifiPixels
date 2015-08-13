#include <ESP8266WiFi.h>
#include "quick_setup.h"
#include "wifi_helper.h"

WIFI_HELPER_CLASS * wifi_helper;

String WIFI_HELPER_CLASS::GetAPList(){
  int n = WiFi.scanNetworks();
  String result = "";
  if(n==0){
    result = "[]";
  } else{
    result="[";
    for (int i = 0; i < n; ++i)
    {
      result += "\"" + String(WiFi.SSID(i)) + "\"";
      if(i!=n-1)
        result += ",";
    }
    result+="]";
  }
  return result;
}

String WIFI_HELPER_CLASS::IPtoString(IPAddress IPaddr){
  return String(IPaddr[0]) + '.' + String(IPaddr[1])  + '.' + String(IPaddr[2])  + '.' + String(IPaddr[3]);
}

void WifiClient(){
  
  char ssid_buff[quick_setup->CLIENT_SSID.length()+1];
  char password_buff[quick_setup->CLIENT_Password.length()+1];
  quick_setup->CLIENT_SSID.toCharArray(ssid_buff,quick_setup->CLIENT_SSID.length()+1);
  quick_setup->CLIENT_Password.toCharArray(password_buff,quick_setup->CLIENT_Password.length()+1);

  
  Serial.println("Connecting with...");
  Serial.print('[');
  Serial.print(ssid_buff);
  Serial.println(']');
  Serial.print('[');
  Serial.print(password_buff);
  Serial.println(']');
  

  
  WiFi.mode(WIFI_STA);
  WiFi.begin((const char*)ssid_buff, (const char*)password_buff);

  if (WiFi.waitForConnectResult() == WL_CONNECTED){
    quick_setup->Mode = CLIENT_MODE;
    quick_setup->CLIENT_State = CONNECTED;
    quick_setup->CLIENT_IP = WiFi.localIP();

    Serial.println("");
    Serial.println("WiFi Client connected");  
    Serial.println("IP address: ");
    Serial.println(quick_setup->CLIENT_IP);    
  } else{
    quick_setup->Mode = AP_MODE;
    quick_setup->CLIENT_State = DISCONNECTED;

    Serial.println("WiFi Client not connected!!!");  
    wifi_helper->wifiSetup();
  }
}


void WifiAP(){
  char apssid_buff[quick_setup->AP_SSID.length()+1];
  char appassword_buff[quick_setup->AP_Password.length()+1];
  quick_setup->AP_SSID.toCharArray(apssid_buff,quick_setup->AP_SSID.length()+1);
  quick_setup->AP_Password.toCharArray(appassword_buff,quick_setup->AP_Password.length()+1);

  //Stop Client
  WiFi.disconnect(true);

  WiFi.mode(WIFI_AP);  
  WiFi.softAP((const char*)apssid_buff, (const char*)appassword_buff, 7); // Open connection  

  Serial.println("WiFi AP Started...");  

  quick_setup->Mode = AP_MODE;
  quick_setup->AP_State = CONNECTED;
  quick_setup->AP_IP = WiFi.softAPIP();
  quick_setup->CLIENT_State = DISCONNECTED;

  
  Serial.println("IP address: ");
  Serial.println(quick_setup->AP_IP); 
  
}


void WIFI_HELPER_CLASS::wifiSetup(){

  if (quick_setup->Mode == CLIENT_MODE){
    WifiClient();
  } else {
    WifiAP();
  }  
}

