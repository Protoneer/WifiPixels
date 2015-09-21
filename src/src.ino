#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <PubSubClient.h>     // MQTT
#include <NeoPixelBus.h>      // Pixels
#include "eeprom_lib.h"
#include "config.h"

wifi_settings_struct      wifi_settings;
mqtt_settings_struct      mqtt_settings;
pixels_settings_struct    pixels_settings;

ESP8266WebServer server(webserver_port);
NeoPixelBus strip = NeoPixelBus(pixel_count, pixel_pin);

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

/*
void callback(const MQTT::Publish& pub) {
  pixel_helper->ProcessCommand(pub.payload_string());
}
*/

void setup()
{
  // Serial
  Serial.begin(115200);
  Serial.println("");
  Serial.println("System Starting Up....");

  // EEPROM
  EEPROM.begin(EEPROM_SIZE);
  
  /*
  //Pixels
  pixel_helper = new PIXEL_HELPER_CLASS();
  pixel_helper->ProcessSerial = true;
  */

  //wifi_helper->wifiSetup();
  //web_interface->WebServer();

  /*
  // Set basic settings
  quick_setup->AP_SSID = "WifiPixels";
  quick_setup->AP_Password = ""; // Open network
  quick_setup->Mode = AP_MODE;
  //quick_setup->AP_IP = "192.168.1.1"; // To-Do  
  //quick_setup->AP_Channel = 7; // To-Do  

  quick_setup->LoadClientSettings();
  
  quick_setup->Start();  


  // MQTT  
  mqtt_helper = new MQTT_HELPER_CLASS();
  mqtt_helper->mqttSetup("m11.cloudmqtt.com",0,"xxx","xxx","Client3451",callback,"/test/buttonPressed");
  */
}

void loop()
{
  //web_interface->handleClient();
  
 /*
  mqtt_helper->mqttLoop();
  pixel_helper->pixelLoop();
  */
}
