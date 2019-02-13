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
  Serial.begin(9600);
  clock.begin();
  clock.fillByYMD(2013, 1, 19); //Jan 19,2013
  clock.fillByHMS(12, 00, 55); //15:28 30"
  clock.fillDayOfWeek(SAT);//Saturday
  clock.setTime();
  pixels.begin();
  count();
}

void loop() {
  clock.getTime();
  printTime();
  if (clock.second == 59) {
    count();
    Serial.print("Minute Done");
  }
  if (clock.minute == 59) {

    redcount = (red[clock.hour][1] - red[clock.hour][0]) / STEPS;
    greencount = (green[clock.hour][1] - green[clock.hour][0]) / STEPS;
    bluecount = (blue[clock.hour][1] - blue[clock.hour][0]) / STEPS;

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
  Serial.print("  ");
  Serial.print(clock.month, DEC);
  Serial.print("/");
  Serial.print(clock.dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(clock.year+2000, DEC);
  Serial.print(" ");
  Serial.print(clock.dayOfMonth);
  Serial.print("*");
  switch (clock.dayOfWeek)// Friendly printout the weekday
  {
    case MON:
      Serial.print("MON");
      break;
    case TUE:
      Serial.print("TUE");
      break;
    case WED:
      Serial.print("WED");
      break;
    case THU:
      Serial.print("THU");
      break;
    case FRI:
      Serial.print("FRI");
      break;
    case SAT:
      Serial.print("SAT");
      break;
    case SUN:
      Serial.print("SUN");
      break;
  }
  Serial.println(" ");
}
