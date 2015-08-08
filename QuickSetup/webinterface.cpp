#include "webinterface.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);


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


bool WEBINTERFACE_CLASS::WebServer()
{
  // Routing Table
  server.on("/wifi.html", handleWifi);
  server.on("/", handleRoot);

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void WEBINTERFACE_CLASS::handleClient()
{
  server.handleClient();
}


