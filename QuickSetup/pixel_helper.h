#include <ESP8266WiFi.h>
#include <NeoPixelBus.h>

#define RGBMode_Blank 0
#define RGBMode_BLEND 1

struct RGBBLEND {
  RgbColor RGB1;    // Start Color
  RgbColor RGB2;    // End Color
  int Cycles;       // Blend Cycles. 0=continuous
  int Interval;     // Delay between each loop cycle
  int CycleNumber;  // Current cycle
  int Progress;     // 0-255 0=RGB1 255=RGB2  
};

class PIXEL_HELPER_CLASS
{
  public:
    void pixelLoop();
    void ProcessCommand(String command);
    int LEDMode = RGBMode_Blank;

    
    String LedColor = "";
    long previousMillis = 0; 
    long interval = 50;
    int Counter = 0;
    int direction = 1;
};

extern PIXEL_HELPER_CLASS * pixel_helper;
