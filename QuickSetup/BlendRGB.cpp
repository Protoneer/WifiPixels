#include <ESP8266WiFi.h>
#include "BlendRGB.h"
#include "pixel_helper.h"

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

RGBBLEND BlendModeSettings;

void ParseRGBBLEND(String input, PIXEL_HELPER_CLASS* p_helper) {
  p_helper->LEDMode = RGBMode_BLEND;
  
  input.remove(0, 9);
  BlendModeSettings.RGB1 = p_helper->RGBStringToRGB(input.substring(0, input.indexOf(',')));

  input.remove(0, input.indexOf(',') + 1);
  BlendModeSettings.RGB2 = p_helper->RGBStringToRGB(input.substring(0, input.indexOf(',')));

  input.remove(0, input.indexOf(',') + 1);
  BlendModeSettings.Cycles = input.substring(0, input.indexOf(',')).toInt();

  input.remove(0, input.indexOf(',') + 1);
  BlendModeSettings.Interval = input.toInt();

  BlendModeSettings.CycleNumber = 0;
  BlendModeSettings.Progress = 0;
  BlendModeSettings.Direction = 1;
  p_helper->previousMillis = millis() - BlendModeSettings.Interval;

}

void DoBlendMode(PIXEL_HELPER_CLASS* p_helper) {
  unsigned long currentMillis = millis();

  if (currentMillis - p_helper->previousMillis > BlendModeSettings.Interval) {
    p_helper->previousMillis = currentMillis;

    // Step Progress and control direction on Min and max
    BlendModeSettings.Progress = BlendModeSettings.Progress + BlendModeSettings.Direction;

    if (BlendModeSettings.Progress > 254) {
      BlendModeSettings.Direction = -1;
    }
    if (BlendModeSettings.Progress < 1) {
      BlendModeSettings.Direction = 1;
    }

    RgbColor rgb;
    rgb = rgb.LinearBlend(BlendModeSettings.RGB1, BlendModeSettings.RGB2, BlendModeSettings.Progress);
    p_helper->SetAll(rgb);


    p_helper->strip.Show();
  }

}
