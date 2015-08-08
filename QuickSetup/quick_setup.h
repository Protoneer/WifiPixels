#include <ESP8266WiFi.h>
class QUICK_SETUP_CLASS
{
  public:
    void Start();
    void Handle_Requests();
    String AP_SSID = "WifiPixels";
    String AP_Password = "";
    
};

extern QUICK_SETUP_CLASS * quick_setup;
