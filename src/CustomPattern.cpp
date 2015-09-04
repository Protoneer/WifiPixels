#include <ESP8266WiFi.h>
#include "CustomPattern.h"
#include "pixel_helper.h"


struct CUSTOMPATTERN {
  RgbColor Patterns[255][16];
  int PatternIntervals[255];
  int Index;			// Current position in the Animation array
};

CUSTOMPATTERN cp;


void ParseCustomPattern(String input, PIXEL_HELPER_CLASS* p_helper) {
	p_helper->LEDMode = CustomPattern_Mode;
 /*
  // Red
  cp.Patterns[0][0] = new RgbColor(0,0,0);
  cp.Patterns[0][1] = new RgbColor(30,0,0);
  cp.Patterns[0][2] = new RgbColor(0,0,0);
  cp.Patterns[0][3] = new RgbColor(30,0,0);
  cp.Patterns[0][4] = new RgbColor(0,0,0);
  cp.Patterns[0][5] = new RgbColor(30,0,0);
  cp.Patterns[0][6] = new RgbColor(0,0,0);
  cp.Patterns[0][7] = new RgbColor(30,0,0);
  cp.Patterns[0][8] = new RgbColor(0,0,0);
  cp.Patterns[0][9] = new RgbColor(30,0,0);
  cp.Patterns[0][10] = new RgbColor(0,0,0);
  cp.Patterns[0][11] = new RgbColor(30,0,0);
  cp.Patterns[0][12] = new RgbColor(0,0,0);
  cp.Patterns[0][13] = new RgbColor(30,0,0);
  cp.Patterns[0][14] = new RgbColor(0,0,0);
  cp.Patterns[0][15] = new RgbColor(30,0,0);

  //Blue
  cp.Patterns[0][0] = new RgbColor(0,0,30);
  cp.Patterns[0][1] = new RgbColor(0,0,0);
  cp.Patterns[0][2] = new RgbColor(0,0,30);
  cp.Patterns[0][3] = new RgbColor(0,0,0);
  cp.Patterns[0][4] = new RgbColor(0,0,30);
  cp.Patterns[0][5] = new RgbColor(0,0,0);
  cp.Patterns[0][6] = new RgbColor(0,0,30);
  cp.Patterns[0][7] = new RgbColor(0,0,0);
  cp.Patterns[0][8] = new RgbColor(0,0,30);
  cp.Patterns[0][9] = new RgbColor(0,0,0);
  cp.Patterns[0][10] = new RgbColor(0,0,30);
  cp.Patterns[0][11] = new RgbColor(0,0,0);
  cp.Patterns[0][12] = new RgbColor(0,0,30);
  cp.Patterns[0][14] = new RgbColor(0,0,0);
  cp.Patterns[0][15] = new RgbColor(0,0,30);
  
	// Set Intervals between changes.
	cp.PatternIntervals[0] = 1000;
	cp.PatternIntervals[1] = 1000;
	
	cp.Index = 0;*/
}

void DoCustomPatternMode(PIXEL_HELPER_CLASS* p_helper) {
    p_helper->SetAll({0,0,0});
    p_helper->strip.Show();	
}

