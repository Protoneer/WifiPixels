#include <ESP8266WiFi.h>
#include "CustomPattern.h"
#include "pixel_helper.h"

/*
struct CUSTOMPATTERN {
  int Patterns[255][16][3];
  int PatternIntervals[255];
  int Index;			// Current position in the Animation array
  int NumberOfPattern;  // Set the number of animations
};

CUSTOMPATTERN cp;
*/

void ParseCustomPattern(String input, PIXEL_HELPER_CLASS* p_helper) {
	p_helper->LEDMode = CustomPattern_Mode;
	/*
	// Set Patterns
	cp.Patterns[0] = {{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,}};
	cp.Patterns[1] = {{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0}};
	cp.Patterns[2] = {{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,},{0,0,0,}};
	cp.Patterns[3] = {{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0},{10,0,0}};
	
	// Set Intervals between changes.
	cp.PatternIntervals[0] = 1000;
	cp.PatternIntervals[1] = 1000;
	cp.PatternIntervals[2] = 1000;
	cp.PatternIntervals[3] = 1000;	
	
	cp.NumberOfPattern = 4;
	cp.Index = 0;
	*/
}

void DoCustomPatternMode(PIXEL_HELPER_CLASS* p_helper) {
    p_helper->SetAll({0,0,0});
    p_helper->strip.Show();	
}

