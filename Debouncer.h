#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <Arduino.h>

class Debouncer {
  uint8_t pin;
  uint16_t timeoutDebounce;
  uint16_t timeoutDepressed;
  unsigned long timeLastTriggered;

  public:
  Debouncer(uint8_t _pin, uint16_t timeoutDebounce, uint16_t timeoutDepressed);
  boolean isPressed();

};

#endif