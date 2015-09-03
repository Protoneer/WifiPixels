#include <ESP8266WiFi.h>
#include "CustomPattern.h"
#include "pixel_helper.h"

struct CUSTOMPATTERN {
  // int[255][16][3] Patterns;
  // int[255] PatternIntervals;
  int Index;			// Current position in the Animation array
  int NumberOfPattern;  // Set the number of animations
};

CUSTOMPATTERN cp;

void ParseCustomPattern(String input, PIXEL_HELPER_CLASS* p_helper) {
	p_helper->LEDMode = CustomPattern_Mode;
}

void DoCustomPatternMode(PIXEL_HELPER_CLASS* p_helper) {
    p_helper->SetAll({0.0.0});
    p_helper->strip.Show();	
}

