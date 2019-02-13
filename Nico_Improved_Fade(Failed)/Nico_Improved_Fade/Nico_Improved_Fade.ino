+#include <Adafruit_NeoPixel.h>

#define PIN            6

#define NUMPIXELS      8

#define STEPS          60

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

long timeThis, timeLast;

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

int seconds = 0;
int minutes = 0;
int hours = 0;
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

  count();
}

void loop() {
  timeThis = millis();
  if (timeThis - timeLast >= 1000) {
    timeThis = timeLast;

    if (seconds++ == 1) {
      count();
      Serial.println("Minute Done");
      if (minutes++ == 60) {
        Serial.println("Hour Done");
        if (hours++ == 11) {
          Serial.println("Day Done");
          seconds = 0;
          minutes = 0;
          hours = 0;
        }

        redcount = (red[hours][1] - red[hours][0]) / STEPS;
        greencount = (green[hours][1] - green[hours][0]) / STEPS;
        bluecount = (blue[hours][1] - blue[hours][0]) / STEPS;

      }
    }
  }
}
