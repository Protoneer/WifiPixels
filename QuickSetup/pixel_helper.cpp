#include <NeoPixelBus.h>
#include "pixel_helper.h"




PIXEL_HELPER_CLASS * pixel_helper;

#define pixelPin 2
#define pixelCount 16
NeoPixelBus strip = NeoPixelBus(pixelCount, pixelPin);

RgbColor RGBStringToRGB(String input) {
  int index = 0;
  int R = input.substring(0, input.indexOf('.')).toInt();

  index = input.indexOf('.');
  int G = input.substring(index + 1, input.indexOf('.', index + 1)).toInt();

  index = input.indexOf('.', index + 1);
  int B = input.substring(index + 1).toInt();

  return (RgbColor) { R , G , B };
}

void SetAll(RgbColor colour){
  for(int K=0;K<pixelCount;K++){
    strip.SetPixelColor(K, colour);
  }
}
void PIXEL_HELPER_CLASS::ProcessCommand(String input){
  if (input.startsWith("RGBBLEND")) {
    LEDMode = RGBMode_BLEND;
    input.remove(0, 9);
    BlendModeSettings.RGB1 = RGBStringToRGB(input.substring(0, input.indexOf(',')));

    input.remove(0, input.indexOf(',')+1);
    BlendModeSettings.RGB2 = RGBStringToRGB(input.substring(0, input.indexOf(',')));
    
    input.remove(0, input.indexOf(',')+1);
    BlendModeSettings.Cycles = input.substring(0, input.indexOf(',')).toInt();

    input.remove(0, input.indexOf(',')+1);
    BlendModeSettings.Interval = input.toInt();

    BlendModeSettings.CycleNumber = 0;
    BlendModeSettings.Progress = 0;  
    BlendModeSettings.Direction = 1;
  }
}

void DoBlendMode(){
  unsigned long currentMillis = millis();
  
  if(currentMillis - pixel_helper->previousMillis > pixel_helper->BlendModeSettings.Interval) {
    pixel_helper->previousMillis = currentMillis;   

    // Step Progress and control direction on Min and max
    pixel_helper->BlendModeSettings.Progress = pixel_helper->BlendModeSettings.Progress + pixel_helper->BlendModeSettings.Direction;

    if(pixel_helper->BlendModeSettings.Progress > 254){
      pixel_helper->BlendModeSettings.Direction = -1;
    }
    if(pixel_helper->BlendModeSettings.Progress < 1){
      pixel_helper->BlendModeSettings.Direction = 1;
    }
    
    RgbColor rgb;    
    rgb = rgb.LinearBlend(pixel_helper->BlendModeSettings.RGB1,pixel_helper->BlendModeSettings.RGB2,pixel_helper->BlendModeSettings.Progress);
    SetAll(rgb);

    /*
    if(pixel_helper->LedColor == "RED"){
      SetAll(RgbColor(Counter,0, 0));
    } else if(LedColor == "GREEN"){
      SetAll(RgbColor(0,Counter, 0));
    } else if(LedColor == "BLUE"){
      SetAll(RgbColor(0,0,Counter));
    } else {
      SetAll(RgbColor(0,0, 0));
    }
    */

    
    strip.Show(); 
  }

}

void PIXEL_HELPER_CLASS::pixelLoop(){
  if(LEDMode == RGBMode_BLEND){
    DoBlendMode();
  }
}

