#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

// Wifi Settings
const char* ssid = "xxxx";
const char* password = "xxxx";

MDNSResponder mdns;
ESP8266WebServer server(80);

String Mode = "";
String Status = "";
String Network ="";


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
  String body =
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "  <meta charset=""UTF-8"">"
    " <meta name=""viewport"" content=""width=device-width"">"
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
    " <table border=""1"" style=""width:200px"">"
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
    " <table border=""1"" style=""width:200px"">"
    "   <tr>"
    "   <th colspan=""2"" bgcolor=""black""><font color=""white"">WIFI Connections</font></td>"
    "   </tr>"
    "   <tr><td>$APs$"
    "   <tr>"
    "   <tr><td colspan=""2"">Password: <input type=""password"" value="""" style=""width: 100px;"" /></td><tr>"
    "   <tr><td colspan=""2""><button onclick=""location.href='wifi.html';"">Refresh</button> <input type=""Button"" value=""Connect"" /></td><tr>"
    " </table>"
    "</body>"
    "</html>";
    
  body.replace("$Network$",Network);
  body.replace("$Status$", Status);

  body.replace("$IP$",    LocalIP());
  body.replace("$Mode$",  Mode);

  body.replace("$APs$",    GetAPList());

  
    
  server.send(200, "text/html", body);
}

String LocalIP(){
  return String(WiFi.localIP()[0]) + '.' + String(WiFi.localIP()[1])  + '.' + String(WiFi.localIP()[2])  + '.' + String(WiFi.localIP()[3]);
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

void WifiClient(){
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Status = "Connected";
  Mode = "WifiClient";
  Network = ssid;

  Serial.println("");
  Serial.println("WiFi Client connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void WifiAP(){
  WiFi.softAP(ssid, password, 7); // Open connection  
}

void WebServer(){
  // Routing Table
  server.on("/wifi.html", handleWifi);
  server.on("/", handleRoot);

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void setup()
{
  EEPROM.begin(512);

  // Serial
  Serial.begin(115200);
  Serial.println("");

  // Wifi
  WifiClient();
  //WifiAP();

  WebServer();
}

void loop()
{
  server.handleClient();
}

