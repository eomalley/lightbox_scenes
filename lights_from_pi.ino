/* lightbox_fancy_v1  */
#include <FastLED.h>
#define NUM_LEDS 468
#define DATA_PIN 2
CRGB leds[NUM_LEDS];

int columns[13][2] = {
            {0, 35},
            {36, 71},
            {72, 107},
            {108, 143},
            {144, 179},
            {180, 215},
            {216, 251},
            {252, 287},
            {288, 323},
            {324, 359},
            {360, 395},
            {396, 431},
            {432, 467}
           };

CRGB gray = CRGB::DarkSlateGray;

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup() { 
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
Serial.begin(9600);
}
void loop() { 

  if (Serial.available() > 0) {
    
    String data = Serial.readStringUntil('\n');

    if (data == "test") {
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      FastLED.show();
      delay(1000);
      fill_solid(leds, NUM_LEDS, CRGB::Green);
      FastLED.show();
      delay(1000);
      fill_solid(leds, NUM_LEDS, CRGB::Blue);
    }

    if(data == "sunrise") {
      for (int i = 0; i <= 12; i++) {
        if (i == 0 || i % 2 == 0) {
          fill_gradient_RGB(leds, columns[i][0], CRGB::PeachPuff, columns[i][1], CRGB::LightSkyBlue);
        } else {
          fill_gradient_RGB(leds, columns[i][0], CRGB::LightSkyBlue, columns[i][1], CRGB::PeachPuff); 
        }
      }
      for (int pos = 0; pos <= 60; pos++) {
        FastLED.setBrightness(pos);
        FastLED.show();
        delay(50);
      }
    }
   
    if (data == "sunset1") {
      for (int i = 0; i <= 12; i++) {
        if (i == 0 || i % 2 == 0) {
          fill_gradient_RGB(leds, columns[i][0], CRGB::OrangeRed, columns[i][1], CRGB::DarkBlue);
        } else {
          fill_gradient_RGB(leds, columns[i][0], CRGB::DarkBlue, columns[i][1], CRGB::OrangeRed); 
        }
      }
      FastLED.setBrightness(60);
      HeatColor(2850);
    }

    if (data == "sunset2") {
      for (int i = 0; i <= 12; i++) {
        if (i == 0 || i % 2 == 0) {
          fill_gradient_RGB(leds, columns[i][0], gray, columns[i][1], CRGB::Purple);
        } else {
          fill_gradient_RGB(leds, columns[i][0], CRGB::Purple, columns[i][1], gray); 
        }
      }
      FastLED.setBrightness(60);
      HeatColor(2850);
    }

    if (data == "sunset3") {
      for (int i = 0; i <= 12; i++) {
        if (i == 0 || i % 2 == 0) {
          fill_gradient_RGB(leds, columns[i][0], CRGB::PeachPuff, columns[i][1], CRGB::LightSkyBlue);
        } else {
          fill_gradient_RGB(leds, columns[i][0], CRGB::LightSkyBlue, columns[i][1], CRGB::PeachPuff); 
        }
      }
      FastLED.setBrightness(60);
      HeatColor(2850);
    }

    if (data == "sun") {
      fill_solid(leds, NUM_LEDS, CRGB::LightGoldenrodYellow);
      FastLED.setBrightness(80);
      HeatColor(20000);
    }

    if (data == "overcast") {
      fill_solid(leds, NUM_LEDS, gray);
      HeatColor(7000);
      FastLED.setBrightness(60);
    }

    if (data == "lightning") {
      fill_solid(leds, NUM_LEDS, CRGB::Azure);
      FastLED.setBrightness(99);
      FastLED.show();
      delay(50);
      fill_solid(leds, NUM_LEDS, gray);
      HeatColor(7000);
      FastLED.setBrightness(20);
    }

    if (data == "storm") {
      fill_solid(leds, NUM_LEDS, gray);
      HeatColor(7000);
      FastLED.setBrightness(20);
    }

    if (data == "night") {
      fill_solid(leds, NUM_LEDS, gray);
      FastLED.setBrightness(10);
      HeatColor(1900);
    }

    if (data.startsWith("custom")) {
      if (data.indexOf("fill") > 0) {
        String numbas = data.substring(data.indexOf("=") + 1, data.length());
        CRGB result = CRGB(getValue(numbas,',',0).toInt(),getValue(numbas,',',1).toInt(),getValue(numbas,',',2).toInt());
        fill_solid(leds, NUM_LEDS, result);
        
        if (numbas.indexOf("+") > 0) {
          FastLED.setBrightness(numbas.substring(numbas.indexOf("+") + 1, numbas.length()).toInt());
        }
        
        FastLED.show();
      }
      if (data.indexOf("gradiant") > 0) {
        String numbasStart = data.substring(data.indexOf("=") + 1, data.length());
        CRGB starting = CRGB(getValue(numbasStart,',',0).toInt(),getValue(numbasStart,',',1).toInt(),getValue(numbasStart,',',2).toInt());
        String numbasEnd = numbasStart.substring(numbasStart.indexOf("/") + 1, numbasStart.length());
        CRGB ending = CRGB(getValue(numbasEnd,',',0).toInt(),getValue(numbasEnd,',',1).toInt(),getValue(numbasEnd,',',2).toInt());

        for (int i = 0; i <= 12; i++) {
          if (i == 0 || i % 2 == 0) {
            fill_gradient_RGB(leds, columns[i][0],ending, columns[i][1], starting);
          } else {
            fill_gradient_RGB(leds, columns[i][0], starting, columns[i][1], ending); 
          }
        }

        if (numbasEnd.indexOf("+") > 0) {
          FastLED.setBrightness(numbasEnd.substring(numbasEnd.indexOf("+") + 1, numbasEnd.length()).toInt());
        }
      }
    }

    if (data == "off") {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
    }

    FastLED.show();
  }
  
}
