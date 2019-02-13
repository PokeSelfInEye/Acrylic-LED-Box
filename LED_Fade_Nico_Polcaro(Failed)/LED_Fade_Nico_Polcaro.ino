
#include <Adafruit_NeoPixel.h>


#define PIN            6

#define NUMPIXELS      8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 5;

void setup() {

  pixels.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  for (int x = 0; x <= 255; x++) {
    for (int i = 0; i < NUMPIXELS; i++) {

      pixels.setPixelColor(i, pixels.Color(255 - x, x, 0));

      pixels.show();

      delay(delayval);

    }
  }
  delay(delayval);
  for (int x = 0; x <= 255; x++) {
    for (int i = 0; i < NUMPIXELS; i++) {

      pixels.setPixelColor(i, pixels.Color(x, 255 - x, 0));

      pixels.show();

      delay(delayval);

    }
  }
}
