#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_PIXELS 100

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_RGB + NEO_KHZ400);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // TODO: add button to switch between patterns
  
//  colourStep(strip.Color(255, 0, 0), 25);
//  colourStep(strip.Color(0, 255, 0), 25);
//  colourStep(strip.Color(0, 0, 255), 25);

//  christmasColour();
//  lightChase();
  lightFade();
  christmasTwinkle();
  
  // Some example procedures showing how to display to the pixels:
//  colorWipe(strip.Color(255, 0, 0), 50); // Red
//  colorWipe(strip.Color(0, 255, 0), 50); // Green
//  colorWipe(strip.Color(0, 0, 255), 50); // Blue

  // Send a theater pixel chase in...
//  theaterChase(strip.Color(127, 127, 127), 50); // White
//  theaterChase(strip.Color(127, 0, 0), 50); // Red
//  theaterChase(strip.Color(0, 0, 127), 50); // Blue

//  rainbow(20);
//  rainbowCycle(20);
//  theaterChaseRainbow(50);
}

void lightChase() {
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t yellow = strip.Color(255, 255, 0);
  uint32_t green = strip.Color(0, 255, 0);
  uint32_t blue = strip.Color(0, 0, 255);

  for (int j = 0; j < 4; j++) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      switch ((i+j) % 4) {
        case 0:
          strip.setPixelColor(i, red);
          break;
        case 1:
          strip.setPixelColor(i, yellow);
          break;
        case 2:
          strip.setPixelColor(i, green);
          break;
        case 3:
          strip.setPixelColor(i, blue);
          break;
      }
    }
    strip.show();
    delay(500);
  }
}

void lightFade() {
  for (int j = 0; j < 255; j+=5) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      switch (i % 4) {
        case 0:
          strip.setPixelColor(i, strip.Color(j, 0, 0));
          break;
        case 1:
          strip.setPixelColor(i, strip.Color(j, j, 0));
          break;
        case 2:
          strip.setPixelColor(i, strip.Color(0, j, 0));
          break;
        case 3:
          strip.setPixelColor(i, strip.Color(0, 0, j));
          break;
      }
    }
    strip.show();
    delay(20);
  }
  for (int j = 255; j >= 0; j-=5) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      switch (i % 4) {
        case 0:
          strip.setPixelColor(i, strip.Color(j, 0, 0));
          break;
        case 1:
          strip.setPixelColor(i, strip.Color(j, j, 0));
          break;
        case 2:
          strip.setPixelColor(i, strip.Color(0, j, 0));
          break;
        case 3:
          strip.setPixelColor(i, strip.Color(0, 0, j));
          break;
      }
    }
    strip.show();
    delay(20);
  }
}

void colourStep(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    for(uint16_t j=0; j<strip.numPixels();j++) {
      if(i==j) {
        strip.setPixelColor(j, c);
      } else {
        strip.setPixelColor(j, strip.Color(0, 0, 0));
      }
    }
    strip.show();
    delay(wait);
  }
  allOff();
}

void christmasColour() {
  // fade in and out red/green?
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t green = strip.Color(0, 255, 0);
  int check = 0;
  for (int x = 0; x < 10; x++) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      if (i % 2 == check) {
        strip.setPixelColor(i, red);
      } else {
        strip.setPixelColor(i, green);
      }
    }
    strip.show();
    delay(500);
    check = check == 0 ? 1 : 0; // invert
  }
  allOff();
}

void christmasTwinkle() {
  // twinkle white lights randomly?
  // TODO:
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  int xPixel = 5;
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < xPixel; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+xPixel) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+xPixel) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  int xPixel = 3;
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < xPixel; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+xPixel) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+xPixel) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void allOff() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}
