#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <PubSubClient.h>     // MQTT
#include "eeprom_lib.h"
#include "config.h"
#include "webserver_setup.h"
#include "wifi_setup.h"
#include <NeoPixelBus.h>      // Pixels

ESP8266WebServer server(webserver_port);
NeoPixelBus strip = NeoPixelBus(pixel_count, pixel_pin);


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

  
  // Setup Wifi
  wifi_setup();

  // Setup Webserver
  webserver_url_routing(&server);
  server.begin();
  Serial.println("HTTP server started");


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
  server.handleClient();
  
 /*
  mqtt_helper->mqttLoop();
  pixel_helper->pixelLoop();
  */
}
