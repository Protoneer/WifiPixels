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

void FillFrame(RgbColor *frame, RgbColor fill){
  for(int K=0;K<leds;K++){
    frame[K] = fill;
  }
}

void TestPatternInjector2(){
  FillFrame(A1.Frames[0],RgbColor(0,0,0));
  A1.Frames[0][0] = RgbColor(30,0,0);
  FillFrame(A1.Frames[1],RgbColor(0,0,0));
  A1.Frames[1][1] = RgbColor(30,0,0);
  FillFrame(A1.Frames[2],RgbColor(0,0,0));
  A1.Frames[2][2] = RgbColor(30,0,0);
  FillFrame(A1.Frames[3],RgbColor(0,0,0));
  A1.Frames[3][3] = RgbColor(30,0,0);
  FillFrame(A1.Frames[4],RgbColor(0,0,0));
  A1.Frames[4][4] = RgbColor(30,0,0);
  FillFrame(A1.Frames[5],RgbColor(0,0,0));
  A1.Frames[5][5] = RgbColor(30,0,0);
  FillFrame(A1.Frames[6],RgbColor(0,0,0));
  A1.Frames[6][6] = RgbColor(30,0,0);
  FillFrame(A1.Frames[7],RgbColor(0,0,0));
  A1.Frames[7][7] = RgbColor(30,0,0);
  FillFrame(A1.Frames[8],RgbColor(0,0,0));
  A1.Frames[8][8] = RgbColor(30,0,0);
  FillFrame(A1.Frames[9],RgbColor(0,0,0));
  A1.Frames[9][9] = RgbColor(30,0,0);
  FillFrame(A1.Frames[10],RgbColor(0,0,0));
  A1.Frames[10][10] = RgbColor(30,0,0);
  FillFrame(A1.Frames[11],RgbColor(0,0,0));
  A1.Frames[11][11] = RgbColor(30,0,0);
  FillFrame(A1.Frames[12],RgbColor(0,0,0));
  A1.Frames[12][12] = RgbColor(30,0,0);
  FillFrame(A1.Frames[13],RgbColor(0,0,0));
  A1.Frames[13][13] = RgbColor(30,0,0);
  FillFrame(A1.Frames[14],RgbColor(0,0,0));
  A1.Frames[14][14] = RgbColor(30,0,0);
  FillFrame(A1.Frames[15],RgbColor(0,0,0));
  A1.Frames[15][15] = RgbColor(30,0,0);

  A1.FrameIntervals[0] = 50;
  A1.FrameIntervals[1] = 45;
  A1.FrameIntervals[2] = 41;
  A1.FrameIntervals[3] = 35;
  A1.FrameIntervals[4] = 29;
  A1.FrameIntervals[5] = 21;
  A1.FrameIntervals[6] = 14;
  A1.FrameIntervals[7] = 6;
  A1.FrameIntervals[8] = 2;
  A1.FrameIntervals[9] = 6;
  A1.FrameIntervals[10] = 14;
  A1.FrameIntervals[11] = 21;
  A1.FrameIntervals[12] = 29;
  A1.FrameIntervals[13] = 35;
  A1.FrameIntervals[14] = 41;
  A1.FrameIntervals[15] = 45;
  
  A1.Index = maxFrames;

  A1.Cycles = 0;
}

void SetBaseAndFillRest(RgbColor *frame,RgbColor base, RgbColor fill, int fillCount){
  for (int K = 0; K < leds; K++) {
    frame[K]=base;
  }
  for (int K = 0; K < fillCount; K++) {
    frame[K]=fill;
  }
  
  
}

void TestPatternInjector3(){
  for(int K=0; K < leds; K++){
    SetBaseAndFillRest(A1.Frames[K],RgbColor(0,0,0),RgbColor(30,0,0),K+1);    
  }
  for(int K=16; K < 16+leds; K++){
    SetBaseAndFillRest(A1.Frames[K],RgbColor(30,0,0),RgbColor(0,0,0),K-15);    
  }
  for(int K=32; K < 32+leds; K++){
    SetBaseAndFillRest(A1.Frames[K],RgbColor(0,0,0),RgbColor(0,30,0),K-31);    
  }
  for(int K=48; K < 48+leds; K++){
    SetBaseAndFillRest(A1.Frames[K],RgbColor(0,30,0),RgbColor(0,0,0),K-47);    
  }
  for(int K=64; K < 64+leds; K++){
    SetBaseAndFillRest(A1.Frames[K],RgbColor(0,0,0),RgbColor(0,0,30),K-63);    
  }
  for(int K=76; K < 76+leds; K++){
    SetBaseAndFillRest(A1.Frames[K],RgbColor(0,0,30),RgbColor(0,0,0),K-75);    
  }

  for(int K=0; K < 88; K++){
    A1.FrameIntervals[K]=30;
  }
  
  
  A1.Index = maxFrames;
  A1.Cycles = 0;
 
}

void TestPatternInjector4(){
  FillFrame(A1.Frames[0], RgbColor(30,0,0));
  FillFrame(A1.Frames[1], RgbColor(0,30,0));
  FillFrame(A1.Frames[2], RgbColor(0,0,30));
  FillFrame(A1.Frames[3], RgbColor(0,0,0));
  FillFrame(A1.Frames[4], RgbColor(30,30,30));
  
  for(int K=0; K < 5; K++){
    A1.FrameIntervals[K]=1000;
  }
  
  
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
  //TestPatternInjector();
  //TestPatternInjector2();
  TestPatternInjector3();
  //TestPatternInjector4();
}

void DoCustomPatternMode(PIXEL_HELPER_CLASS* p_helper) {
  unsigned long currentMillis = millis();

  if (currentMillis - p_helper->previousMillis > A1.FrameIntervals[A1.Index]) {
    p_helper->previousMillis = currentMillis;
    
    A1.Index = IncrementIndex(A1.Index,A1.FrameIntervals,maxFrames+20);
    
    SetPixels(p_helper,A1.Frames[A1.Index]);    

    p_helper->strip.Show();
  }	
}

