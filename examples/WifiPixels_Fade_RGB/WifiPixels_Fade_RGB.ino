#include <NeoPixelBus.h>

#define pixelCount 16
#define pixelPin 2

RgbColor Red   = {128,   0,   0};
RgbColor Green = {0  , 128,   0};
RgbColor Blue  = {0  ,   0, 128};
RgbColor Black = {0  ,   0,   0};

NeoPixelBus strip = NeoPixelBus(pixelCount, pixelPin);

void setup()
{
  strip.Begin();
  strip.Show();
}

void loop()
{
  Fade(Black , Red);
  Fade(Red   , Black);
  Fade(Black , Green);
  Fade(Green , Black);
  Fade(Black , Blue);
  Fade(Blue  , Black);
}

void SetAll(RgbColor colour) {
  for (int K = 0; K < pixelCount; K++) {
    strip.SetPixelColor(K, colour);
  }
}

void Fade(RgbColor rgb1, RgbColor rgb2) {
  for (int k = 0; k < 255; k++) {
    RgbColor rgb = rgb.LinearBlend(rgb1, rgb2, k);
    SetAll(rgb);
    strip.Show();
    delay(5);
  }
}