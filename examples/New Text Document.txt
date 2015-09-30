/**************************************************************************
    Souliss - RGB LED Strip Hack

    Control and RGB LED or a Strip using the PWM, fade in/out and flash 
    effects are available as the Android interface or openHAB.

    Run this code on one of the following boards:
      - RGBW Led Strip Driver based on ESP8266

***************************************************************************/

// Configure the framework
#include "bconf/MCU_ESP8266.h"              // Load the code directly on the ESP8266
#include "conf/Gateway.h"                   // The main node is the Gateway, we have just one node

// **** Define the WiFi name and password ****
#define WIFICONF_INSKETCH
#define WiFi_SSID               xx
#define WiFi_Password           xx

// Include framework code and libraries
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include "Souliss.h"

#define LEDCONTROL        0
#define LEDRED            1
#define LEDGREEN          2
#define LEDBLUE           3
#define LEDSTRIP1         4
#define LEDWHITE1         5
#define LEDSTRIP2         6
#define LEDWHITE2         7

void setup()
{   
    Initialize();

    // Get the IP address from DHCP
    GetIPAddress();                          
    SetAsGateway(myvNet_dhcp);                  // Set this node as gateway for SoulissApp                        

    Set_LED_Strip(LEDCONTROL);                  // Set a logic to control a LED strip
    //Set_DimmableLight(LEDSTRIP1);
    //Set_DimmableLight(LEDSTRIP2);

    // Define inputs, outputs pins
    //pinMode(12, OUTPUT);                 // Power the LED
    //pinMode(13, OUTPUT);                 // Power the LED
    //pinMode(15, OUTPUT);                 // Power the LED    
    //pinMode(14, OUTPUT);                 // Power the LED
    //pinMode(4,  OUTPUT);                 // Power the LED 
    Serial.begin(115200);
}

void loop()
{ 
    // Here we start to play
    EXECUTEFAST() {                     
        UPDATEFAST();   

        // Execute the code every 1 time_base_fast      
        FAST_10ms() {

            // Execute the logic that handle the LED
            Logic_LED_Strip(LEDCONTROL);
            //Logic_DimmableLight(LEDWHITE1);
            //Logic_DimmableLight(LEDWHITE2);

            // Use the output values to control the PWM
            //analogWrite(12, mOutput(LEDRED)*4);
            //analogWrite(13, mOutput(LEDGREEN)*4);
            //analogWrite(15, mOutput(LEDBLUE)*4);

            Serial.println(mOutput(LEDBLUE)*4);
            //analogWrite(14, mOutput(LEDWHITE1)*4);
            //analogWrite(4, mOutput(LEDWHITE2)*4);

            // Just process communication as fast as the logics
            ProcessCommunication();
        } 

        // Process the other Gateway stuffs
        FAST_GatewayComms();

    }
    EXECUTESLOW()
    {   
        UPDATESLOW();

        SLOW_10s()  {

            // The timer handle timed-on states
            Timer_LED_Strip(LEDCONTROL); 
            //Timer_DimmableLight(LEDWHITE1);
            //Timer_DimmableLight(LEDWHITE2);                       
        }     
    }       
}