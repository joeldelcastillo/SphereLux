#ifndef Sphere_H
#define Sphere_H

#include <Arduino.h>
#include <FastLED.h>
#include <stdlib.h>

#define LED_TYPE WS2812B
#define PI 3.14159265359

class Sphere
{

private:
  String name = "";
  // int NUM_PER_STRIP[19] = {300, 300, 300, 300, 300,
  //                         300, 300, 300, 300, 300,
  //                        300, 300, 300, 300, 300,
  //                       300, 300, 300, 300};

  int NUM_PER_STRIP[19] = {87, 115, 143, 170, 198,
                           218, 237, 252, 265, 276,
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
  int MAX_LED = 0;
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
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      if (NUM_PER_STRIP[i] > MAX_LED)
      {
        MAX_LED = NUM_PER_STRIP[i];
      }
    }
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

  void simpleColor(int hue, int sat, int val)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      for (int j = 0; j < NUM_PER_STRIP[i]; j++)
      {
        leds[i][j] = CHSV(hue, floor(255 * sat / 100), floor(255 * val / 100));
      }
    }
    FastLED.show();
  }

  void colorOne(int strip, int hue, int sat, int val)
  {
    for (int j = 0; j < NUM_PER_STRIP[strip]; j++)
    {
      leds[strip][j] = CHSV(hue, floor(255 * sat / 100), floor(255 * val / 100));
    }
  }

  void waveIntensity(int counter, int hue, int sat, int val, int vel)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      float k = mapF(i, 0, NUM_STRIPS, 0, 2 * PI);
      colorOne(i, hue, 255, floor(mapF(sin(k + 0.01 * vel * counter), -1, 1, 0, 100)));
    }
    FastLED.show();
  }

  // void waveVal (int counter, int color){
  //  FastLED.clear();
  //   for (int i = 0; i < NUM_STRIPS; i++)
  //     {
  //       float k = mapF (i, 0, NUM_STRIPS, 0, 2* PI  );
  //       colorOne(i, color,  floor (mapF(sin(k + counter), 0, 1, 0, 100))/100);
  //     }
  //   FastLED.show();
  // }

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

  void partitionOne(int strip, int hue, int sat, int val, int size, int parts)
  {
    int l = NUM_PER_STRIP[strip];
    int ratio = round(l / parts);
    for (int j = 0; j < l; j++)
    {
      if (j % ratio == 0)
      {
        for (int k = 0; k < size; k++)
        {
          leds[strip][j + k] = CHSV(hue, floor(255 * sat / 100), floor(255 * val / 100));
        }
      }
    }
  }

  void partitionAll(int counter, int hue, int sat, int val, int size, int parts)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int yoff = (i + counter) % NUM_STRIPS;
      if (i < NUM_STRIPS / 2)
      {
        partitionOne(yoff, hue, sat, val, size, parts);
      }
      else
      {
        partitionOne(yoff, hue, sat, val, size, parts);
      }
    }
    FastLED.show();
  }

  void halfLeds(int strip, int counter, int hue, int sat, int val)
  {
    for (int j = 0; j < NUM_PER_STRIP[strip]; j++)
    {
      if (j < NUM_PER_STRIP[strip] / 2)
      {
        int xoff = (j + counter) % NUM_PER_STRIP[strip];
        leds[strip][xoff] = CHSV(hue, floor(255 * sat / 100), floor(255 * val / 100));
      }
    }
  }

  void danceFalf(int counter, int hue, int sat, int val, int ratio)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      halfLeds(i, hue, sat, val, counter + i * ratio);
    }
    FastLED.show();
  }

  //----------------- 4/23/2022

  // Se encienden en sentido antihorario todos los LEDs de la esfera
  void fillAnticlock(int strip, int offset, int hue, int sat, int val)
  {
    for (int j = 0; j < offset; j++)
    {
      leds[strip][j] = CHSV(hue, floor(255 * sat / 100), floor(255 * val / 100));
    }
  }

  // Se encienden en sentido horario todos los LEDs de la esfera
  void fillClock(int strip, int offset, int hue, int sat, int val)
  {
    for (int j = NUM_PER_STRIP[strip] - offset; j < NUM_PER_STRIP[strip]; j++)
    {
      leds[strip][j] = CHSV(hue, floor(255 * sat / 100), floor(255 * val / 100));
    }
  }
  // Se apagan en sentido antihorario todos los LEDs de la esfera
  void clearAnticlock(int strip, int offset, int hue, int sat, int val)
  {
    for (int j = offset; j < NUM_PER_STRIP[strip]; j++)
    {
      leds[strip][j] = CHSV(hue, floor(255 * sat / 100), floor(255 * val / 100));
    }
  }

  // Se apagan en sentido horario todos los LEDs de la esfera
  void clearClock(int strip, int offset, int hue, int sat, int val)
  {
    for (int j = 0; j < NUM_PER_STRIP[strip] - offset; j++)
    {
      leds[strip][j] = CHSV(hue, floor(255 * sat / 100), floor(255 * val / 100));
    }
  }
  // Se encienden todos los LEDs en un sentido y se apagan en el contrario
  void bounce(int increment, int hue, int sat, int val)
  {
    FastLED.clear(); // actualizar frame
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int offset = (increment * NUM_PER_STRIP[i] / MAX_LED) % ((NUM_PER_STRIP[i]) * 2);
      if (offset < NUM_PER_STRIP[i])
      {
        fillClock(i, offset, hue, sat, val);
      }
      else
      {
        clearAnticlock(i, offset - NUM_PER_STRIP[i], hue, sat, val);
      }
    }
    FastLED.show(); // mostrar frame
  }

  // Se encienden todos los LEDs en un sentido y se apagan en el cmismo sentido
  void snake(int increment, int hue, int sat, int val)
  {
    FastLED.clear(); // actualizar frame

    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int offset = (increment * NUM_PER_STRIP[i] / MAX_LED) % ((NUM_PER_STRIP[i]) * 2);
      if (offset < NUM_PER_STRIP[i])
      {
        fillClock(i, offset, hue, sat, val);
      }
      else
      {
        clearClock(i, offset - NUM_PER_STRIP[i], hue, sat, val);
      }
    }
    FastLED.show(); // mostrar frame
  }
  // Se encienden y apagan todos los LEDs en un sentido y luego lo mismo en el sentido contrario
  void snakeBounce(int increment, int hue, int sat, int val)
  {
    FastLED.clear(); // actualizar frame

    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int offset = (increment * NUM_PER_STRIP[i] / MAX_LED) % ((NUM_PER_STRIP[i]) * 4);
      if (offset < NUM_PER_STRIP[i])
      {
        fillClock(i, offset, hue, sat, val);
      }
      else if (offset < 2 * NUM_PER_STRIP[i])
      {

        clearClock(i, offset - NUM_PER_STRIP[i], hue, sat, val);
      }
      else if (offset < 3 * NUM_PER_STRIP[i])
      {

        fillAnticlock(i, offset - 2 * NUM_PER_STRIP[i], hue, sat, val);
      }
      else
      {

        clearAnticlock(i, offset - 3 * NUM_PER_STRIP[i], hue, sat, val);
      }
      FastLED.show(); // mostrar frame
    }
  }
  // Se encienden todos los LEDs en un sentido, se apagan en el contrario y luego lo mismo empezando en el sentido contrario
  void doubleBounce(int increment, int hue, int sat, int val)
  {
    FastLED.clear(); // actualizar frame

    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int offset = (increment * NUM_PER_STRIP[i] / MAX_LED) % ((NUM_PER_STRIP[i]) * 4);
      if (offset < NUM_PER_STRIP[i])
      {
        fillClock(i, offset, hue, sat, val);
      }
      else if (offset < 2 * NUM_PER_STRIP[i])
      {
        clearAnticlock(i, offset - NUM_PER_STRIP[i], hue, sat, val);
      }
      else if (offset < 3 * NUM_PER_STRIP[i])
      {
        fillAnticlock(i, offset - 2 * NUM_PER_STRIP[i], hue, sat, val);
      }
      else
      {
        clearClock(i, offset - 3 * NUM_PER_STRIP[i], hue, sat, val);
      }
    }
    FastLED.show(); // mostrar frame
  }

  // Genera una paleta de "num" colores
  void fillClockCol(int strip, int offset, int hue, int sat, int val, int num)
  {
    for (int j = 0; j < NUM_PER_STRIP[strip]; j++) // all off, on to the left
    {
      if (j > NUM_PER_STRIP[strip] - offset)
      {
        leds[strip][j] = CHSV(hue, floor(255 * sat / 100), floor(255 * val / 100));
      }
      else
      {
        leds[strip][j] = CHSV(floor((256 + hue - 256 / num) % 255), floor(255 * sat / 100), floor(255 * val / 100));
      }
    }
  }

  void fillAnticlockCol(int strip, int increment, int hue, int sat, int val, int num)
  {

    int offset = increment;
    for (int j = 0; j < NUM_PER_STRIP[strip]; j++)
    {
      if (j < offset)
      {
        leds[strip][j] = CHSV(hue, floor(255 * sat / 100), floor(255 * val / 100));
      }
      else
      {
        leds[strip][j] = CHSV(floor((256 + hue - 256 / num) % 255), floor(255 * sat / 100), floor(255 * val / 100));
      }
    }
  }

  void snakeCol(int increment, int hue, int sat, int val, int num)
  {
    FastLED.clear(); // actualizar frame
    int aux = 0;
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int offset = (increment * NUM_PER_STRIP[i] / MAX_LED) % (NUM_PER_STRIP[i] * num);
      aux = floor(offset / NUM_PER_STRIP[i]);
      // fillClockCol(i, offset-aux*NUM_PER_STRIP[i],floor(color+(256*aux/num)),val,num);
      fillAnticlockCol(i, offset - aux * NUM_PER_STRIP[i], floor(hue + (256 * aux / num)), sat, val, num);
    }
    FastLED.show(); // mostrar frame
  }

  void bounceCol(int increment, int hue, int sat, int val, int num)
  {
    FastLED.clear(); // actualizar frame
    int aux = 0;
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int offset = (increment * NUM_PER_STRIP[i] / MAX_LED) % (NUM_PER_STRIP[i] * 2 * num);
      // int offset=num*NUM_PER_STRIP[i]*(1+sin(2*PI*increment/(2*MAX_LED)));
      aux = floor(offset / NUM_PER_STRIP[i]);

      if (aux % 2 == 0)
      {
        fillClockCol(i, offset - aux * NUM_PER_STRIP[i], floor(hue + (256 * aux / num)), sat, val, num);
      }
      else
      {
        fillAnticlockCol(i, offset - aux * NUM_PER_STRIP[i], floor(hue + (256 * aux / num)), sat, val, num);
      }
    }
    FastLED.show(); // mostrar frame
  }

  //--------------------------------------Extra functions
  float modulo(float x, float y, float z)
  {
    return sqrt(x * x + y * y + z * z);
  }

  float mapF(float val, float start1, float stop1, float start2, float stop2)
  {
    float outgoing = start2 + (stop2 - start2) * ((val - start1) / (stop1 - start1));
    return outgoing;
  }
};

#endif
