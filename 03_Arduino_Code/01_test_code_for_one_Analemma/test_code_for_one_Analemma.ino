#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 2
#define NUMPIXELS 12

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
#define DELAYVAL 500

int counter=0;
uint32_t red = pixels.Color(255, 0, 0,0);
uint32_t green = pixels.Color(0, 255, 0,0);
uint32_t blue = pixels.Color(0, 0, 255,0);
uint32_t rgb[]={red,green,blue};
//float avgtemp2112[]={1.2, 0.8, 3.6, 15.1, 17, 20.7 , 26.8 , 13.6 , 25.2, 11.7 , 3.9 , 0.9};
float avgtemp2112[]={1.2, 0.8, 0.8, 0.8, 17, 20.7 , 26.8 , 13.6 , 25.2, 11.7 , 3.9 , 0.9};

void setup() {
  
  pixels.begin();
  
}

void loop() {
  pixels.clear();
  pixels.show();
  for(int i=0;i<12;i++){
    pixels.setPixelColor(i,255/26*(avgtemp2112[i]-0.8),0,255/26*(26.8-avgtemp2112[i]),10);
    delay(DELAYVAL);
    pixels.show();
  }
  
  delay(3*DELAYVAL);
}

