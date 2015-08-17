#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>


#include <EEPROM.h> // Needed to give config.h access
#include "quick_setup.h"
#include "wifi_helper.h"
#include "mqtt_helper.h"

#include <NeoPixelBus.h>

int Counter = 0;
int direction = 1;
String LedColor = "";

void callback(const MQTT::Publish& pub) {
  LedColor = pub.payload_string();  
  Serial.println(pub.payload_string());
  Counter = 0;
  direction =1;
}

#define pixelCount 16
NeoPixelBus strip = NeoPixelBus(pixelCount, 2);

void SetAll(RgbColor colour){
  for(int K=0;K<pixelCount;K++){
    strip.SetPixelColor(K, colour);
  }
}

long previousMillis = 0; 
long interval = 50;
 
void CyclePixels(){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis; 
    
    Counter = Counter + direction;
    if(Counter > 30){
      direction = -1;
    }
    if(Counter < 10){
      direction = 1;
    }
    
    if(LedColor == "RED"){
      SetAll(RgbColor(Counter,0, 0));
    } else if(LedColor == "GREEN"){
      SetAll(RgbColor(0,Counter, 0));
    } else {
      SetAll(RgbColor(0,0, 0));
    }
    strip.Show();
 
  }
}

void setup()
{
  // Clear pixels
  CyclePixels();
  
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
  //pinMode(0, OUTPUT);
  mqtt_helper = new MQTT_HELPER_CLASS();
  //void mqttSetup(server,port,user,password,clientID,callbackFunction,topic);
  mqtt_helper->mqttSetup(xxx,xxx,xxx,xxx,xxx,callback,"/test/buttonPressed");
}

void loop()
{
  quick_setup->Handle_Requests();
  mqtt_helper->mqttLoop();
  CyclePixels();
}
