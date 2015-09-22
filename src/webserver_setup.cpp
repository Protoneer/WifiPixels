#include "webserver_setup.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

void handleNotFound(){}; 
void handleWifi(){};
void GetAccessPoints(){};
void GetCurrentAnimation(){};
void SetCurrentAnimation(){};
void GetAnimationFrame(){};
void SetAnimationFrame(){};

void webserver_url_routing(ESP8266WebServer * webserver){
  webserver->onNotFound(handleNotFound);
  
  // Setup URL's
  webserver->on("/wifisetup.html", handleWifi);
  webserver->on("/", handleWifi);
  
  // API URL'scan
  webserver->on("/api/v1/access_points.json",  HTTP_GET,  GetAccessPoints);   // List of available Wifi Networks
  
  webserver->on("/api/v1/current_animation",   HTTP_GET,  GetCurrentAnimation); // Get the selected animation 0-3
  webserver->on("/api/v1/current_animation",   HTTP_POST, SetCurrentAnimation); // Set the selected animation 0-3 [0=disabled]

  webserver->on("/api/v1/animation_frame",   HTTP_GET,  GetAnimationFrame);   // Get frame , frame=???
  webserver->on("/api/v1/animation_frame",   HTTP_POST,   SetAnimationFrame);   // Set frame , post data -> frameNumber=0;frameData="???";
};


