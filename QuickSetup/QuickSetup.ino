#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>


#include <EEPROM.h> // Needed to give config.h access
#include "quick_setup.h"
#include "wifi_helper.h"



void setup()
{
  quick_setup = new QUICK_SETUP_CLASS();

  // Set basic settings
  quick_setup->AP_SSID = "WifiPixels";
  quick_setup->AP_Password = ""; // Open network
  
  quick_setup->Start();
  
  // Serial
  Serial.begin(115200);
  Serial.println("");

  // Wifi
  //wifiSetup();

}

void loop()
{
  quick_setup->Handle_Requests();
 
}
