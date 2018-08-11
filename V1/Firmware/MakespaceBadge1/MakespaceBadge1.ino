#include <Adafruit_NeoPixel.h>

/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

#define DATA_PIN 14
#define NUMPIXELS 32


int mSequence[] = {0, 1,  6, 7, 8,9,10, 11, 12, 13, 14, 
                          15, 16, 17, 18, 19, 20,  
                          19, 18, 17, 16, 15,  
                          21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 30 };
int sSequence[] = {29, 28, 27, 26, 25, 24, 23, 22, 21, 15, 16, 17 , 5, 4, 3, 2, 7, 8};

// M only (not s) pixels to switch off
int mSequenceOff[] = {0, 1, 6, 9,10, 11, 12, 13, 14, 
                          18, 19, 20,  
                          30, 31 };

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, DATA_PIN, NEO_GRB + NEO_KHZ800);

// Define the array of leds
//CRGB leds[1];

void setup() {
  pinMode(13, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  
  // Pin 14 for LEDs.
  pixels.begin(); 
  pixels.setBrightness(20);
  pixels.show(); 
}

// the loop function runs over and over again forever
void loop() {

  digitalWrite(13, HIGH);
  clearAllPixels();
  
  for (int i = 0; i< sizeof(mSequence)/sizeof(mSequence[0]); i++) {
    pixels.setPixelColor(mSequence[i], pixels.Color(255,165,0)); 
    pixels.show();
    delay(150);   
    pixels.setPixelColor(mSequence[i], pixels.Color(128,90,0)); 
  }

  for (int i = 0; i< sizeof(sSequence)/sizeof(sSequence[0]); i++) {
    pixels.setPixelColor(sSequence[i], pixels.Color(0,255,0)); 
    pixels.show();
    delay(150);   
    pixels.setPixelColor(sSequence[i], pixels.Color(0,128,0)); 
  }
  
  pixels.show();   
  digitalWrite(13, LOW);
  
  delay(1000);  

  
  for (int i = 0; i< sizeof(mSequenceOff)/sizeof(mSequenceOff[0]); i++) {
    pixels.setPixelColor(mSequenceOff[i], pixels.Color(0,0,0)); 
    pixels.show();
    delay(150);   
    pixels.setPixelColor(mSequenceOff[i], pixels.Color(0,0,0)); 
  }

  delay(2000);  

  for (int i = 0; i< sizeof(mSequence)/sizeof(mSequence[0]); i++) {
    pixels.setPixelColor(mSequence[i], pixels.Color(0,0,255)); 
    pixels.show();
    delay(150);   
    pixels.setPixelColor(mSequence[i], pixels.Color(0,0,128)); 
  }

  delay(1000);  

  clearAllPixels();

   rainbow(20);

   delay(1000);  

   rainbowCycle(20);

   delay(1000);  
}

void setAllPixels(int tile, byte red, byte green, byte blue) {
  for (int i = 0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i , pixels.Color(red, green, blue)); 
  }
  pixels.show();
}

void clearAllPixels() {
  for (int i = 0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i , pixels.Color(0,0,0)); 
  }
  pixels.show();
}



void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<NUMPIXELS; i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUMPIXELS; i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / 16) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

