#include "Ticker.h"

Ticker::Ticker(int _timeout) {
  /* set the ticker's timeout */
  timeout = _timeout;
}

boolean Ticker::isReady() {
  return (millis() - lastTicked) >= timeout;
}

void Ticker::tick() {
  lastTicked = millis();
}