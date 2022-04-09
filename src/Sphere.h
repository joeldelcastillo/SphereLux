#ifndef Sphere_H
#define Sphere_H

#include <Arduino.h>
#include <FastLED.h>
#include <stdlib.h>

#define LED_TYPE WS2812B
#define PII 3.1415926535897932384626433832795

class Sphere
{

private:
  String name;
 // int NUM_PER_STRIP[19] = {300, 300, 300, 300, 300,
  //                         300, 300, 300, 300, 300,
   //                        300, 300, 300, 300, 300,
    //                       300, 300, 300, 300};

int NUM_PER_STRIP[19] = {87, 115, 143, 170, 198,
                           218, 237,252, 265, 276,
                           275, 262, 246, 230, 205,
                           177, 149, 116, 78};


  //
  //    int NUM_PER_STRIP[19] = {15, 15, 15, 15, 15,
  //                             15, 15, 15, 15, 15,
  //                             15, 15, 15, 15, 15,
  //                             15, 15, 15, 15};

  int Total_LEDS;
  int NUM_STRIPS = 19;
  int BRIGHTNESS = 50;
  CRGBPalette16 currentPalette;
  TBlendType currentBlending;
  // extern CRGBPalette16 myRedWhiteBluePalette;
  // extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
  CRGB leds[19][300];

public:
  //    Sphere(int PINS[19], int NUM_LEDS[19], int NUM_STRIPS, int BRIGHTNESS){
  //      this->PINS = PINS;
  //      this->NUM_LEDS = NUM_LEDS;
  //      this->NUM_STRIPS = NUM_STRIPS;
  //      this->BRIGHTNESS = BRIGHTNESS;
  //    }

  Sphere(String name)
  {
    this->name = name;
    sum();
  }

  void sum()
  {
    int suma = 0;
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      suma += NUM_PER_STRIP[i];
    }
    Total_LEDS = suma;
  }

  // Power on the LED
  void setPins()
  {

    FastLED.addLeds<WS2812B, 15, GRB>(leds[0], NUM_PER_STRIP[0]);
    FastLED.addLeds<WS2812B, 2, GRB>(leds[1], NUM_PER_STRIP[1]);
    FastLED.addLeds<WS2812B, 4, GRB>(leds[2], NUM_PER_STRIP[2]);
    FastLED.addLeds<WS2812B, 16, GRB>(leds[3], NUM_PER_STRIP[3]);

    FastLED.addLeds<WS2812B, 17, GRB>(leds[4], NUM_PER_STRIP[4]);
    FastLED.addLeds<WS2812B, 5, GRB>(leds[5], NUM_PER_STRIP[5]);
    FastLED.addLeds<WS2812B, 18, GRB>(leds[6], NUM_PER_STRIP[6]);
    FastLED.addLeds<WS2812B, 19, GRB>(leds[7], NUM_PER_STRIP[7]).setCorrection(TypicalLEDStrip);

    FastLED.addLeds<WS2812B, 21, GRB>(leds[8], NUM_PER_STRIP[8]);
    FastLED.addLeds<WS2812B, 22, GRB>(leds[9], NUM_PER_STRIP[9]);
    FastLED.addLeds<WS2812B, 23, GRB>(leds[10], NUM_PER_STRIP[10]);
    FastLED.addLeds<WS2812B, 32, GRB>(leds[11], NUM_PER_STRIP[11]);

    FastLED.addLeds<WS2812B, 27, GRB>(leds[12], NUM_PER_STRIP[12]);
    FastLED.addLeds<WS2812B, 26, GRB>(leds[13], NUM_PER_STRIP[13]);
    FastLED.addLeds<WS2812B, 25, GRB>(leds[14], NUM_PER_STRIP[14]);
    FastLED.addLeds<WS2812B, 33, GRB>(leds[15], NUM_PER_STRIP[15]);

    FastLED.addLeds<WS2812B, 13, GRB>(leds[16], NUM_PER_STRIP[16]);
    FastLED.addLeds<WS2812B, 12, GRB>(leds[17], NUM_PER_STRIP[17]);
    FastLED.addLeds<WS2812B, 14, GRB>(leds[18], NUM_PER_STRIP[18]);
    //    FastLED.addLeds<WS2812B, 1, GRB>(leds[18], NUM_PER_STRIP[18]);

    FastLED.setBrightness(BRIGHTNESS);
  }

  void simpleColor(int hue)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      for (int j = 0; j < NUM_PER_STRIP[i]; j++)
      {
        leds[i][j] = CHSV(hue, 255, 255);
      }
    }
    FastLED.show();
  }

  void colorOne(int strip, int color, int intensity)
  {
    for (int j = 0; j < NUM_PER_STRIP[strip]; j++)
    {
      leds[strip][j] = CHSV(color, 255, floor(255 * intensity / 100));
    }
  }

  void waveIntensity(int counter, int color)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      float k = mapF(i, 0, NUM_STRIPS, 0, 2 * PI);
      colorOne(i, color, floor(mapF(sin(k + 0.01 * counter), -1, 1, 0, 100)));
    }
    FastLED.show();
  }

  // void waveIntensity (int counter, int color){
  //  FastLED.clear();
  //   for (int i = 0; i < NUM_STRIPS; i++)
  //     {
  //       float k = mapF (i, 0, NUM_STRIPS, 0, 2* PI  );
  //       colorOne(i, color,  floor (mapF(sin(k + counter), 0, 1, 0, 100))/100);
  //     }
  //   FastLED.show();
  // }


  void intensity(int hue, int intensity)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      for (int j = 0; j < NUM_PER_STRIP[i]; j++)
      {
        leds[i][j] = CHSV(hue, 255, 255 * (intensity / 100));
      }
    }
    FastLED.show();
  }


  void test(int increment)
  {
    FastLED.clear(); // actualizar frame
    int offset = increment % 255;
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int hue = map(i, 0, NUM_STRIPS, 0, 255);
      for (int j = 0; j < NUM_PER_STRIP[i]; j++)
      {
        if(j%3==0)
        {
        leds[i][j] = CHSV((hue + offset) % 255, 255, 255);
        }
       
      }
    }
    FastLED.show(); // mostrar frame
  }
  




void chaosOne(int group, int increment, int color, int intensity,int strip)
{
  int offset = (increment/5)%NUM_PER_STRIP[strip]; 
 for (int j = 0; j < NUM_PER_STRIP[strip]; j++)
      {
        if (j<group)
        {
        leds[strip][offset+j] = CHSV(color, 255, floor(255 * intensity / 100));
        }
        
       
      }
}


void chaosAll(int group, int increment, int color, int intensity)
  {
     FastLED.clear(); 
 
    for (int i = 0; i < NUM_STRIPS; i++)
    {
       chaosOne(group,increment,color,intensity,i);
    }
    FastLED.show();
  }


void busOne(int group, int increment, int color, int intensity,int strip)
{
  int offset = ((increment*NUM_PER_STRIP[strip]*2/(276))%NUM_PER_STRIP[strip]); 
 for (int j = 0; j < NUM_PER_STRIP[strip]; j++)
      {
        if (j<group)
        {
        leds[strip][offset+j] = CHSV(color, 255, floor(255 * intensity / 100));
        }
        
       
      }
}

void busAll(int group, int increment, int color, int intensity)
  {
     FastLED.clear(); 
  
    for (int i = 0; i < NUM_STRIPS; i++)
    {
       busOne(group,increment,color,intensity,i);
    }
    FastLED.show();
  }






  void rainbow(int increment)
  {
    FastLED.clear();
    int offset = increment % 255;
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int hue = map(i, 0, NUM_STRIPS, 0, 255);
      for (int j = 0; j < NUM_PER_STRIP[i]; j++)
      {
        leds[i][j] = CHSV((hue + offset) % 255, 255, 255);
      }
    }
    FastLED.show();
  }

  void partitionOne(int strip, int parts, int intensity, int color)
  {
    int l = NUM_PER_STRIP[strip];
    int ratio = round(l / parts);
    for (int j = 0; j < l; j++)
    {
      if (j % ratio == 0)
      {
        for (int k = 0; k < 1; k++)
        {
          leds[strip][j + k] = CHSV(color, 255, 255 * intensity);
        }
      }
    }
  }

  void partitionAll(int count, int parts, int color)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int yoff = (i + count) % NUM_STRIPS;
      if (i < NUM_STRIPS / 2)
      {
        partitionOne(yoff, 5, 1, 100);
      }
      else
      {
        partitionOne(yoff, 5, 0.4, 100);
      }
    }

    FastLED.show();
  }

  void fadeOne(int strip, int center, int color)
  {
    int len = NUM_PER_STRIP[strip];
    float newCenter = (center % len);
    for (int j = 0; j < len; j++)
    {
      float distance;

      if ((newCenter - j) > len * 0.5)
      {
        distance = abs(newCenter - (j + len));
      }
      else if ((newCenter - j) < -(len * 0.5))
      {
        distance = abs(newCenter - j + len);
      }
      else
      {
        distance = abs(newCenter - j);
      }

      float grad = 1 - (distance / len) * 4;
      int atenuacion = mapF(grad, 0, 1, 0, 255);
      // console.log(col);
      leds[strip][j] = CHSV(color, 255, atenuacion);
    }
  }

  void fadeAll(float center, int color)
  {
    FastLED.clear();
    // int offset = increment % 255;
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      fadeOne(i, center, color);
    }
    FastLED.show();
  }

  void danceFalf(int counter, int ratio, int color)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      halfLeds(i, counter + i * ratio, 200);
    }
    FastLED.show();
  }

  void halfLeds(int strip, int counter, int color)
  {
    for (int j = 0; j < NUM_PER_STRIP[strip]; j++)
    {
      if (j < NUM_PER_STRIP[strip] / 2)
      {
        int xoff = (j + counter) % NUM_PER_STRIP[strip];
        leds[strip][xoff] = CHSV(color, 255, 255);
      }
    }
  }

  void percentageOne(int strip, float percentage, int color)
  {
    //    float percentage = p % 100;
    for (int j = 0; j < NUM_PER_STRIP[strip]; j++)
    {
      if (j < (percentage / 100) * NUM_PER_STRIP[strip])
      {
        leds[strip][j] = CHSV(color, 255, 255);
      }
    }
  }

  int porcentaje(float percentage, int color)
  {
    //    percentage = percentage%100;
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      for (int j = 0; j < 10; j++)
      {
        if (j < (percentage / 100) * 10)
        {
          leds[i][j] = CHSV(color, 255, 255);
        }
      }
    }
    FastLED.show();
  }

  void progressivePercentage(int counter, int color)
  {
    FastLED.clear();

    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int progress = floor(counter / (NUM_STRIPS * NUM_PER_STRIP[i]));
      if (i < progress)
      {
        percentageOne(i, counter, color);
      }
    }
    FastLED.show();
  }

  void percentageAll(int counter, int color)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      percentageOne(i, counter, color);
    }
    FastLED.show();
  }

  float modulo(float x, float y, float z)
  {
    return sqrt(x * x + y * y + z * z);
  }

  float mapF(float value, float start1, float stop1, float start2, float stop2)
  {
    float outgoing = start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    return outgoing;
  }
};

#endif
