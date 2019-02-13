#include <Adafruit_NeoPixel.h>

#include <Wire.h>

#include "DS1307.h"

#define PIN            6

#define NUMPIXELS      8

#define STEPS          60

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

DS1307 clock;

const int red[12][2] = {
  {255, 255},
  {255, 255},
  {255, 128},
  {128,   0},
  {  0,   0},
  {  0,   0},
  {  0,   0},
  {  0,   0},
  {  0, 127},
  {127, 255},
  {255, 255},
  {255, 255},
};

const int green[12][2] = {
  {  0, 128},
  {128, 255},
  {255, 255},
  {255, 255},
  {255, 255},
  {255, 255},
  {255, 128},
  {128,   0},
  {  0,   0},
  {  0,   0},
  {  0,   0},
  {  0,   0},
};

const int blue[12][2] = {
  {  0,   0},
  {  0,   0},
  {  0,   0},
  {  0,   0},
  {  0, 128},
  {128, 255},
  {255, 255},
  {255, 255},
  {255, 255},
  {255, 255},
  {255, 127},
  {127,   0},
};

int redcount;
int greencount;
int bluecount;
int redstart = red[0][0];
int greenstart = green[0][0];
int bluestart = blue[0][0];
int redend;
int greenend;
int blueend;

void count() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color (redstart, greenstart, bluestart));
  }
  redstart += redcount;
  greenstart += greencount;
  bluestart += bluecount;
  Serial.print(redstart);
  Serial.print("\t");
  Serial.print(greenstart);
  Serial.print("\t");
  Serial.println(bluestart);
  pixels.show();
}

void setup() {

  pixels.begin();
  Serial.begin(9600);
  clock.begin();
  clock.fillByHMS(15,28,30);//15:28 30"
  clock.setTime();
  count();
}

void loop(){
  
}

