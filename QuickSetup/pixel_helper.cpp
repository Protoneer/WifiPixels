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
void PIXEL_HELPER_CLASS::ProcessCommand(String command){
  LedColor = command;  
  Counter = 0;
  direction =1;
}

void PIXEL_HELPER_CLASS::pixelLoop(){
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis; 
    
    Counter = Counter + direction;
    if(Counter > 30){
      direction = -1;
    }
    if(Counter < 10){
      direction = 1;
    }
    
    if(pixel_helper->LedColor == "RED"){
      SetAll(RgbColor(Counter,0, 0));
    } else if(LedColor == "GREEN"){
      SetAll(RgbColor(0,Counter, 0));
    } else if(LedColor == "BLUE"){
      SetAll(RgbColor(0,0,Counter));
    } else {
      SetAll(RgbColor(0,0, 0));
    }
    strip.Show(); 
  }
}

