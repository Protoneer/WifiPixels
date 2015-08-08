#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "webinterface.h"
#include "config.h"
#include "wifi_helper.h"



void setup()
{
  config();
  
  // Serial
  Serial.begin(115200);
  Serial.println("");

  // Wifi
  wifiSetup();

  web_interface = new WEBINTERFACE_CLASS(); 
  web_interface->WebServer();
}

void loop()
{
  web_interface->handleClient();
 
}
