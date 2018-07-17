#ifndef TICKER_H
#define TICKER_H
#include <Arduino.h>

class Ticker {

  int timeout;
  unsigned long lastTicked = 0;

  public:
  Ticker(int _timeout);
  boolean isReady();
  void tick();
};

#endif