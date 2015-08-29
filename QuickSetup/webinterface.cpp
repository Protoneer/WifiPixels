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
    quick_setup->SaveClientSettings();

    quick_setup->Mode = CLIENT_MODE;
    wifi_helper->wifiSetup();
  }  
  
  String body = wifi_html;
    
  body.replace("$Network$",String(quick_setup->Mode == CLIENT_MODE ? quick_setup->CLIENT_SSID : quick_setup->AP_SSID));
  body.replace("$Status$",String(quick_setup->Mode == CLIENT_MODE ? quick_setup->CLIENT_State : quick_setup->AP_State));
  body.replace("$IP$",String(wifi_helper->IPtoString(quick_setup->Mode == CLIENT_MODE ? quick_setup->CLIENT_IP : quick_setup->AP_IP)));
  body.replace("$Mode$",String(quick_setup->Mode == CLIENT_MODE ? "Wifi Client" : "Access Point"));

  server.send(200, "text/html", body);
}

void handleScan(){
  String body = wifi_helper->GetAPList();
  server.send(200, "application/json", body);
}


void WEBINTERFACE_CLASS::WebServer()
{
  // Routing Table
  server.on("/wifisetup.html", handleWifi);
  server.on("/scan.json",handleScan);
  server.on("/", handleWifi);

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void WEBINTERFACE_CLASS::handleClient()
{
  server.handleClient();
}


