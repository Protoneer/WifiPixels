#ifndef WIFI_HELPER_H
#define WIFI_HELPER_H

#include <ESP8266WiFi.h>
class WIFI_HELPER_CLASS
{
  public:
    void wifiSetup();
    String GetAPList();
    String IPtoString(IPAddress IPaddr);
};

extern WIFI_HELPER_CLASS * wifi_helper;

#endif
