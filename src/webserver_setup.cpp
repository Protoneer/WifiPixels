#include "webserver_setup.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer * webServer;


void webserver_url_routing(ESP8266WebServer * webserver){
  webServer = webserver;
  webserver->onNotFound(NotFound);
  
  // Setup URL's
  webserver->on("/wifisetup.html", WifiSetup);
  webserver->on("/", WifiSetup);
  
  // API URL'scan
  webserver->on("/api/v1/access_points.json",  HTTP_GET,  GetAccessPoints);   // List of available Wifi Networks
  
  webserver->on("/api/v1/current_animation",   HTTP_GET,  GetCurrentAnimation); // Get the selected animation 0-3
  webserver->on("/api/v1/current_animation",   HTTP_POST, SetCurrentAnimation); // Set the selected animation 0-3 [0=disabled]

  webserver->on("/api/v1/animation_frame",   HTTP_GET,  GetAnimationFrame);   // Get frame , frame=???
  webserver->on("/api/v1/animation_frame",   HTTP_POST,   SetAnimationFrame);   // Set frame , post data -> frameNumber=0;frameData="???";
};

void NotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += webServer->uri();
  message += "\nMethod: ";
  message += (webServer->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webServer->args();
  message += "\n";
  for (uint8_t i = 0; i < webServer->args(); i++) {
    message += " " + webServer->argName(i) + ": " + webServer->arg(i) + "\n";
  }
  webServer->send(404, "text/plain", message);
}

void GetAccessPoints(){
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
  webServer->send(200, "application/json", result);
};

void WifiSetup(){
  webServer->send(200, "text/plain", "wifisetup.html");
};
void GetCurrentAnimation(){
    webServer->send(200, "text/plain", "api/v1/current_animation");
};

void SetCurrentAnimation(){    
  webServer->send(200, "text/plain", "api/v1/current_animation");
};

void GetAnimationFrame(){
    webServer->send(200, "text/plain", "/api/v1/animation_frame");
};

void SetAnimationFrame(){
  webServer->send(200, "text/plain", "/api/v1/animation_frame");
};

