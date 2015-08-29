#include <ESP8266WiFi.h>
#include "BlendRGB.h"
#include "pixel_helper.h"

void ParseRGBBLEND(String input, PIXEL_HELPER_CLASS* p_helper) {
  p_helper->LEDMode = RGBMode_BLEND;
  
  input.remove(0, 9);
  p_helper->BlendModeSettings.RGB1 = p_helper->RGBStringToRGB(input.substring(0, input.indexOf(',')));

  input.remove(0, input.indexOf(',') + 1);
  p_helper->BlendModeSettings.RGB2 = p_helper->RGBStringToRGB(input.substring(0, input.indexOf(',')));

  input.remove(0, input.indexOf(',') + 1);
  p_helper->BlendModeSettings.Cycles = input.substring(0, input.indexOf(',')).toInt();

  input.remove(0, input.indexOf(',') + 1);
  p_helper->BlendModeSettings.Interval = input.toInt();

  p_helper->BlendModeSettings.CycleNumber = 0;
  p_helper->BlendModeSettings.Progress = 0;
  p_helper->BlendModeSettings.Direction = 1;
  p_helper->previousMillis = millis() - p_helper->BlendModeSettings.Interval;

}

void DoBlendMode(PIXEL_HELPER_CLASS* p_helper) {
  unsigned long currentMillis = millis();

  if (currentMillis - p_helper->previousMillis > p_helper->BlendModeSettings.Interval) {
    p_helper->previousMillis = currentMillis;

    // Step Progress and control direction on Min and max
    p_helper->BlendModeSettings.Progress = p_helper->BlendModeSettings.Progress + p_helper->BlendModeSettings.Direction;

    if (p_helper->BlendModeSettings.Progress > 254) {
      p_helper->BlendModeSettings.Direction = -1;
    }
    if (p_helper->BlendModeSettings.Progress < 1) {
      p_helper->BlendModeSettings.Direction = 1;
    }

    RgbColor rgb;
    rgb = rgb.LinearBlend(p_helper->BlendModeSettings.RGB1, p_helper->BlendModeSettings.RGB2, p_helper->BlendModeSettings.Progress);
    p_helper->SetAll(rgb);


    p_helper->strip.Show();
  }

}
