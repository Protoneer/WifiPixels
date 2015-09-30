#ifndef config_h
#define config_h
#include <ESP8266WiFi.h>
#include <NeoPixelBus.h>

#define EEPROM_SIZE   512
#define pixel_count   16      // Number of RRG led's hooked-up in the chain
#define pixel_pin     2       // MCU Pin used to drive the LED's
#define webserver_port 80
#define maxFrames 128
#define animationCount 2

#define AP_MODE      1
#define CLIENT_MODE   2

struct wifi_settings_struct{
    // Access Point
    String AP_SSID      = "WifiPixels";
    String AP_Password    = "";       // Open Access point
    IPAddress AP_IP     = IPAddress(192,168,4,1);  // Default Access point ip
  
    // Wifi Client
    String CLIENT_SSID    = "";
    String CLIENT_Password  = "";
    IPAddress CLIENT_IP   = IPAddress(127,0,0,1);    // Default assigned by Wifi router.
  
    // Client mode or mixed mode
    int Mode        = AP_MODE;      // Start of as an access point and swithc to client mode if connection has been made.
};

struct mqtt_settings_struct{
    String mqttServer     = "m11.cloudmqtt.com";    // MQTT Server Name
    int mqttPort      = 0;            // MQTT Server Port
    String mqttUser     = "xxx";          // MQTT Username
    String mqttPassword   = "xxx";          // MQTT Password
    String mqttClientID   = "Client1234";       // MQTT Client id. This ID can only be used by one client at time
    String mqttSubTopic   = "/test/buttonPressed";    // MQTT subject to subscribe to.
};

struct pixels_settings_struct{
    //int LEDMode       = RGBMode_Blank;  
    bool ProcessSerial    = false;      // Accept serial commands
    long previousMillis   = 0;        // Last time the pixel process was run
	int currentAnimation	= 0;	// Zero based selected animation
};

struct ANIMATION{
  RgbColor Frames[maxFrames][pixel_count];
  int FrameIntervals[maxFrames] = {0};
  int Index = 0;			// Current position in the Animation array
  int Cycles = 0;
};

extern ANIMATION 				animations[animationCount];
extern wifi_settings_struct     wifi_settings;
extern mqtt_settings_struct     mqtt_settings;
extern pixels_settings_struct   pixels_settings;


#endif
