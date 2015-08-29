#ifndef Q_SETUP_H
#define Q_SETUP_H

#include <ESP8266WiFi.h>
#define AP_MODE      1
#define CLIENT_MODE   2

#define DISCONNECTED  0
#define CONNECTED  1

#define EEPROM_SIZE 512

class QUICK_SETUP_CLASS
{
  public:
    void Start();
    void Handle_Requests();
    void LoadClientSettings();
    void SaveClientSettings();
    
    String AP_SSID = "WifiPixels";
    String AP_Password = "";
    IPAddress AP_IP;
    int AP_State = DISCONNECTED;

    String CLIENT_SSID = "";
    String CLIENT_Password = "";
    int CLIENT_State = DISCONNECTED;
    IPAddress CLIENT_IP;

    int Mode = AP_MODE;

};

extern QUICK_SETUP_CLASS * quick_setup;

#endif
