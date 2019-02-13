#include <Adafruit_NeoPixel.h>

#include <Wire.h>

#include "DS1307.h"

#define PIN            6

#define NUMPIXELS      8

#define STEPS         60

#define COUNT          2

#define WAIT           0

#define SECOND         1

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
int redstart;
int greenstart;
int bluestart;
int state = WAIT;

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
  clock.fillByHMS(1, 00, 00);
  clock.setTime();
  clock.getTime();
  redstart = red[clock.hour - 1][0];
  greenstart = green[clock.hour - 1][0];
  bluestart = blue[clock.hour - 1][0];
  count;
  redcount = (red[clock.hour - 1][1] - red[clock.hour - 1][0]) / STEPS;
  greencount = (green[clock.hour - 1][1] - green[clock.hour - 1][0]) / STEPS;
  bluecount = (blue[clock.hour - 1][1] - blue[clock.hour - 1][0]) / STEPS;
}


void loop() {
  Serial.print("State: ");
  Serial.println(state);
  switch (state) {
    case SECOND:
      clock.getTime();
      printTime();
      redcount = (red[clock.hour - 1][1] - red[clock.hour - 1][0]) / STEPS;
      greencount = (green[clock.hour - 1][1] - green[clock.hour - 1][0]) / STEPS;
      bluecount = (blue[clock.hour - 1][1] - blue[clock.hour - 1][0]) / STEPS;
      if (clock.second == 1) {
        state = WAIT;
      }
      break;

    case WAIT:
      printTime();
      clock.getTime();
      Serial.print(redstart);
      Serial.print("\t");
      Serial.print(greenstart);
      Serial.print("\t");
      Serial.println(bluestart);
      if (clock.second == 0) {
        state = COUNT;
      }
      break;

    case COUNT:
      Serial.println("IN COUNT");
      count();
      Serial.println("Count Done");
      state = SECOND;
      break;

  }

}
void printTime()
{
  clock.getTime();
  Serial.print(clock.hour, DEC);
  Serial.print(":");
  Serial.print(clock.minute, DEC);
  Serial.print(":");
  Serial.print(clock.second, DEC);
  Serial.println(" ");
}
