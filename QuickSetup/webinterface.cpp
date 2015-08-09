#include "webinterface.h"
#include "html_static_resources.h"
#include "quick_setup.h"
#include "wifi_helper.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

WEBINTERFACE_CLASS * web_interface;

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
      quick_setup->CLIENT_SSID = temp;
    }else{
      quick_setup->CLIENT_SSID = "";
    }

    temp = server.arg("pw");
    if(temp.length() > 0){
      quick_setup->CLIENT_Password = temp;
    }else{
      quick_setup->CLIENT_Password = "";
    }

    // Save Settings
    //writeEEPROMSettings();

    //quick_setup->Mode = CLIENT_MODE;
    //wifi_helper->wifiSetup();
  }  
  
  String body = wifi_html;

    
  body.replace("$Network$",String(quick_setup->Mode == CLIENT_MODE ? quick_setup->CLIENT_SSID : quick_setup->AP_SSID));
  body.replace("$Status$",String(quick_setup->Mode == CLIENT_MODE ? quick_setup->CLIENT_State : quick_setup->AP_State));
  body.replace("$IP$",String(wifi_helper->IPtoString(quick_setup->Mode == CLIENT_MODE ? quick_setup->CLIENT_IP : quick_setup->AP_IP)));
  body.replace("$Mode$",String(quick_setup->Mode == CLIENT_MODE ? "Wifi Client" : "Access Point"));

  body.replace("$APs$", wifi_helper->GetAPList());
  
  
    
  server.send(200, "text/html", body);
}


void WEBINTERFACE_CLASS::WebServer()
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


