#include <ESP8266WiFi.h>
#include "CustomPattern.h"
#include "pixel_helper.h"

#define maxFrames 255
#define leds 16

struct ANIMATION{
  RgbColor Frames[maxFrames][16];
  int FrameIntervals[maxFrames];
  int Index;			// Current position in the Animation array
};

ANIMATION A1;

void TestPatternInjector(){
  // Red
  A1.Frames[0][0] = RgbColor(0,0,0);
  A1.Frames[0][1] = RgbColor(30,0,0);
  A1.Frames[0][2] = RgbColor(0,0,0);
  A1.Frames[0][3] = RgbColor(30,0,0);
  A1.Frames[0][4] = RgbColor(0,0,0);
  A1.Frames[0][5] = RgbColor(30,0,0);
  A1.Frames[0][6] = RgbColor(0,0,0);
  A1.Frames[0][7] = RgbColor(30,0,0);
  A1.Frames[0][8] = RgbColor(0,0,0);
  A1.Frames[0][9] = RgbColor(30,0,0);
  A1.Frames[0][10] = RgbColor(0,0,0);
  A1.Frames[0][11] = RgbColor(30,0,0);
  A1.Frames[0][12] = RgbColor(0,0,0);
  A1.Frames[0][13] = RgbColor(30,0,0);
  A1.Frames[0][14] = RgbColor(0,0,0);
  A1.Frames[0][15] = RgbColor(30,0,0);

  //Blue
  A1.Frames[0][0] = RgbColor(0,0,30);
  A1.Frames[0][1] = RgbColor(0,0,0);
  A1.Frames[0][2] = RgbColor(0,0,30);
  A1.Frames[0][3] = RgbColor(0,0,0);
  A1.Frames[0][4] = RgbColor(0,0,30);
  A1.Frames[0][5] = RgbColor(0,0,0);
  A1.Frames[0][6] = RgbColor(0,0,30);
  A1.Frames[0][7] = RgbColor(0,0,0);
  A1.Frames[0][8] = RgbColor(0,0,30);
  A1.Frames[0][9] = RgbColor(0,0,0);
  A1.Frames[0][10] = RgbColor(0,0,30);
  A1.Frames[0][11] = RgbColor(0,0,0);
  A1.Frames[0][12] = RgbColor(0,0,30);
  A1.Frames[0][14] = RgbColor(0,0,0);
  A1.Frames[0][15] =  RgbColor(0,0,30);
  
  // Set Intervals between changes.
  A1.FrameIntervals[0] = 1000;
  A1.FrameIntervals[1] = 1000;
  
  A1.Index = 0;
}


int IncrementIndex(int index,int *intervals,int maxTries ){
    index++;
    maxTries--;
    if(index > maxFrames){
      index = 0;
    }

    // Prevent circular increments finding the next non zero frame.
    if(intervals[index] == 0 && maxFrames >= 0){
      index = IncrementIndex(index,intervals,maxTries);
    }
    return index;
}

void SetPixels(NeoPixelBus strip,RgbColor *frame){
  for (int K = 0; K < leds; K++) {
    strip.SetPixelColor(K,frame[K]);
  }
}


void ParseCustomPattern(String input, PIXEL_HELPER_CLASS* p_helper) {
  p_helper->LEDMode = CustomPattern_Mode;
  TestPatternInjector();
  Serial.println("Injected"); 
  A1.Index = 255;
}

void DoCustomPatternMode(PIXEL_HELPER_CLASS* p_helper) {
    A1.Index = IncrementIndex(A1.Index,A1.FrameIntervals,maxFrames);
    Serial.println(A1.Index); 
    
    SetPixels(p_helper->strip,A1.Frames[A1.Index]);    

    p_helper->strip.Show();	
}

