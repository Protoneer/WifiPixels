#ifndef PIXEL_HELPER_H
#define PIXEL_HELPER_H

#include <ESP8266WiFi.h>
#include <NeoPixelBus.h>

#define RGBMode_Blank 0
#define RGBMode_BLEND 1

#define pixelPin 2
#define pixelCount 16

struct RGBBLEND {
  RgbColor RGB1;    // Start Color
  RgbColor RGB2;    // End Color
  int Cycles;       // Blend Cycles. 0=continuous
  int Interval;     // Delay between each loop cycle
  int CycleNumber;  // Current cycle // TO-DO
  int Direction;    // RGB1->RGB2 or RGB2->RGB1
  int Progress;     // 0-255 0=RGB1 255=RGB2 
  int ProgressSteps; // Rate of progress // TO-DO 
};

class PIXEL_HELPER_CLASS
{
  public:
    PIXEL_HELPER_CLASS();
    void pixelLoop();
    void ProcessCommand(String command);
    int LEDMode = RGBMode_Blank;
    bool ProcessSerial = false;

    RgbColor RGBStringToRGB(String input);
    void SetAll(RgbColor colour);
    
    NeoPixelBus strip = NeoPixelBus(pixelCount, pixelPin);

    RGBBLEND BlendModeSettings;
    long previousMillis = 0;
};

extern PIXEL_HELPER_CLASS * pixel_helper;

#endif
