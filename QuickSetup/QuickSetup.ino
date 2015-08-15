#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>


#include <EEPROM.h> // Needed to give config.h access
#include "quick_setup.h"
#include "wifi_helper.h"
#include "mqtt_helper.h"

#define BUFFER_SIZE 100
void callback(const MQTT::Publish& pub) {
  Serial.print(pub.topic());
  Serial.print(" => ");
  if (pub.has_stream()) {
    uint8_t buf[BUFFER_SIZE];
    int read;
    while (read = pub.payload_stream()->read(buf, BUFFER_SIZE)) {
      Serial.write(buf, read);
    }
    pub.payload_stream()->stop();
    Serial.println("");
  } else
    Serial.println(pub.payload_string());
}

void setup()
{
  // Serial
  Serial.begin(115200);
  Serial.println("");
  Serial.println("System Starting Up....");

  // EEPROM
  EEPROM.begin(EEPROM_SIZE);

  quick_setup = new QUICK_SETUP_CLASS();

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
  mqtt_helper->mqttSetup(xxx,xxx,xxx,xxx,xxx,callback);
}

void loop()
{
  quick_setup->Handle_Requests();
  mqtt_helper->mqttLoop();
}
