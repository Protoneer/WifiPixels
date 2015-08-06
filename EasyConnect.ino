#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

MDNSResponder mdns;
ESP8266WebServer server(80);

// Wifi Settings
//const char* ssid = "xxxx";
//const char* password = "xxxx";

String ssid ="";
String password="";

String APSSID = "WifiPixels";
String APPassword = "";
String Mode = "";
String Status = "";
String Network ="";
String IP ="";


void handleRoot() {

  String body =
    "<!DOCTYPE html>"
    "<html>"
    "<body>"
    "<form action=""index.html"">"
    "Red:<br><input type=""text"" name=""red"" value=""$R$""><br>"
    "Green:<br><input type=""text"" name=""green"" value=""$G$""><br>"
    "Blue:<br><input type=""text"" name=""blue"" value=""$B$""><br>"
    "<input type=""submit"" value=""Set"">"
    "</form>"
    "</body>"
    "</html>";
  /*
    body.replace("$R$",String(red));
    body.replace("$G$",String(green));
    body.replace("$B$",String(blue));
  */

  server.send(200, "text/html", body);
}

void handleWifi() {
  // Check for args with connection settings
  if(server.args() > 0){
    String temp = "";
    
    temp = server.arg("ap");
    if(temp.length() > 0){
      ssid = temp;
    }else{
      ssid="";
    }

    temp = server.arg("pw");
    if(temp.length() > 0){
      password = temp;
    }else{
      password="";
    }
    writeEEPROMSettings();

    wifiSetup();
  }  
  
  String body =
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "  <meta charset=""UTF-8"">"
    " <meta name=""viewport"" content=""width=310px"">"
    " <title>Wifi Setup</title>"
    "<style>"
    "table, th, td {"
    "    border: 1px solid black;"
    "    border-collapse: collapse;"
    "}"
    "th, td {"
    "    padding: 5px;"
    "}"
    "</style>"
    "<script type=""text/javascript"">"
    "</script>"
    "</head>"
    "<body>"
    " <table border=""1"" style=""width:300px"">"
    "   <tr>"
    "   <th colspan=""2"" bgcolor=""black""><font color=""white"">WIFI Settings</font></td>"
    "   </tr>"
    "   <tr><td>Network:</td><td>$Network$</td><tr>"
    "   <tr><td>Status:</td><td>$Status$</td><tr>"
    "   <tr><td>IP:</td><td>$IP$</td><tr>"
    "   <tr><td>Mode:</td><td>$Mode$</td><tr>"
    "   <tr><td colspan=""2""><input type=""Button"" value=""Turn Hotspot ON"" /></td><tr>"
    " </table>"
    " <br>"
    " <form  action=""wifi.html"">"
    " <table border=""1"" style=""width:300px"">"
    "   <tr>"
    "   <th colspan=""2"" bgcolor=""black""><font color=""white"">WIFI Connections</font></td>"
    "   </tr>"
    "   <tr><td>$APs$</td>"
    "   <tr>"
    "   <tr><td colspan=""2"">Password: <input name=""pw"" type=""password"" value="""" style=""width: 100px;"" /></td><tr>"
    "   <tr><td colspan=""2""><button onclick=""location.href='wifi.html';"">Refresh</button> <input type=""submit"" value=""Connect"" /></td><tr>"
    " </table>"
    " </form>"
    "</body>"
    "</html>";
    
  body.replace("$Network$",Network);
  body.replace("$Status$", Status);

  body.replace("$IP$",    IP);
  body.replace("$Mode$",  Mode);

  body.replace("$APs$",    GetAPList());

  
    
  server.send(200, "text/html", body);
}

String IPtoString(IPAddress IPaddr){
  return String(IPaddr[0]) + '.' + String(IPaddr[1])  + '.' + String(IPaddr[2])  + '.' + String(IPaddr[3]);
}



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

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
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

void WebServer(){
  // Routing Table
  server.on("/wifi.html", handleWifi);
  server.on("/", handleRoot);

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void wifiSetup(){
  // Stop AP
  //WiFi.softAPdisconnect(true);
  //WiFi.disconnect(true);

  if(!WifiClient()){
    WifiAP();  
  }    
}

void readEEPROMSettings(){
  Serial.println("Reading EEPROM");
  Serial.println(EEPROM.read(0));
  
  ssid = "";
  for(int K=0;K<32;K++){
    char temp = EEPROM.read(K);
    if(temp != 0){
      Serial.print(temp);
      ssid += char(EEPROM.read(K));      
    } else{
      break;
    }      
  }

  password = "";
  for(int K=32;K<96;K++){
    char temp = EEPROM.read(K);
    if(temp != 0){
      Serial.print(temp);
      password += char(EEPROM.read(K));      
    } else{
      break;
    }      
  }
  Serial.print('[');
  Serial.print(ssid);
  Serial.println(']');
  Serial.print('[');
  Serial.print(password);
  Serial.println(']');
  
}
void writeEEPROMSettings(){
  Serial.println("Writing EEPROM");
  Serial.print('[');
  Serial.print(ssid);
  Serial.println(']');
  Serial.print('[');
  Serial.print(password);
  Serial.println(']');


  
  for(int K=0;K<ssid.length();K++)  {
    EEPROM.write(K,ssid[K]);
  }
  EEPROM.write(ssid.length(),0);
  
  for(int K=0;K<+password.length();K++)  {
    EEPROM.write(32+K,password[K]);
  }
  EEPROM.write(32+password.length(),0);
}

void setup()
{
  EEPROM.begin(512);
  readEEPROMSettings();
  
  // Serial
  Serial.begin(115200);
  Serial.println("");

  // Wifi
  wifiSetup();

  WebServer();
}

void loop()
{
  server.handleClient();
}
