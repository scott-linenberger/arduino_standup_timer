#ifndef COLORTIMER_H
#define COLORTIMER_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Ticker.h"

class ColorTimer {
  /* pin for the buzzer */
  uint8_t pinBuzzer;

  /* neopixels */
  Adafruit_NeoPixel *pixels;

  /* Ticker */
  Ticker ticker = Ticker(150);

  /* state */
  boolean isStarted = false;
  boolean isOn = false;
  uint8_t positionIndicator = 0;
  
  /* time vars */
  uint16_t timeoutSpeaking;
  unsigned long timeStarted = 0;

  /* colors */
  uint32_t colorIndicator;
  uint32_t colorStandby;
  uint32_t colorRunning;
  uint32_t colorWhite;
  uint32_t colorBlack;

  public:
  ColorTimer(uint16_t _timeoutSpeaking, uint8_t _pinBuzzer);
  void begin(Adafruit_NeoPixel &_pixels);
  void start();
  void run();
  void reset();

  private:
  void degradeColor(float timeElapsed);
  void flash();

};

#endif
