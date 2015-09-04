#include <ESP8266WiFi.h>
#include "CustomPattern.h"
#include "pixel_helper.h"

#define maxFrames 255
#define leds 16

struct ANIMATION{
  RgbColor Frames[maxFrames][16];
  int FrameIntervals[maxFrames] = {0};
  int Index;			// Current position in the Animation array
  int Cycles;
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
  A1.Frames[1][0] = RgbColor(0,0,30);
  A1.Frames[1][1] = RgbColor(0,0,0);
  A1.Frames[1][2] = RgbColor(0,0,30);
  A1.Frames[1][3] = RgbColor(0,0,0);
  A1.Frames[1][4] = RgbColor(0,0,30);
  A1.Frames[1][5] = RgbColor(0,0,0);
  A1.Frames[1][6] = RgbColor(0,0,30);
  A1.Frames[1][7] = RgbColor(0,0,0);
  A1.Frames[1][8] = RgbColor(0,0,30);
  A1.Frames[1][9] = RgbColor(0,0,0);
  A1.Frames[1][10] = RgbColor(0,0,30);
  A1.Frames[1][11] = RgbColor(0,0,0);
  A1.Frames[1][12] = RgbColor(0,0,30);
  A1.Frames[1][13] = RgbColor(0,0,0);
  A1.Frames[1][14] =  RgbColor(0,0,30);
  A1.Frames[1][15] = RgbColor(0,0,0);
  
  // Set Intervals between changes.
  A1.FrameIntervals[0] = 1000;
  A1.FrameIntervals[1] = 1000;
  
  A1.Index = maxFrames;

  A1.Cycles = 0;
}


int IncrementIndex(int index,int *intervals,int maxTries ){
    index++;
    maxTries--;
    if(index >= maxFrames){
      index = 0;
    }

    // Prevent circular increments finding the next non zero frame.
    if(intervals[index] == 0 && maxTries >= 0){
      index = IncrementIndex(index,intervals,maxTries);
    }
    return index;
}

void SetPixels(PIXEL_HELPER_CLASS* p_helper,RgbColor *frame){
  for (int K = 0; K < leds; K++) {
    p_helper->strip.SetPixelColor(K,frame[K]);
  }
}


void ParseCustomPattern(String input, PIXEL_HELPER_CLASS* p_helper) {
  p_helper->LEDMode = CustomPattern_Mode;
  TestPatternInjector();
}

void DoCustomPatternMode(PIXEL_HELPER_CLASS* p_helper) {
  unsigned long currentMillis = millis();

  if (currentMillis - p_helper->previousMillis > A1.FrameIntervals[A1.Index]) {
    p_helper->previousMillis = currentMillis;
    
    A1.Index = IncrementIndex(A1.Index,A1.FrameIntervals,maxFrames+20);
    Serial.println(A1.Index); 
    
    SetPixels(p_helper,A1.Frames[A1.Index]);    

    p_helper->strip.Show();
  }	
}

