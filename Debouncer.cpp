#include "Debouncer.h"

Debouncer::Debouncer(uint8_t _pin, uint16_t _timeoutDebounce, uint16_t _timeoutDepressed) {
  /* assign the pin for debounce */
  pin = _pin;

  /* assign the timeouts */
  timeoutDebounce = _timeoutDebounce;
  timeoutDepressed = _timeoutDepressed;
}

boolean Debouncer::isPressed() {
  /* read the pin */
  if (digitalRead(pin) == LOW) {
    return false; // pin went high, return
  }

  /* track when the pin went high */
  unsigned long pinTriggered = millis();

  /* ensure pin is held high long enough */
  while(digitalRead(pin) == HIGH && (millis() - pinTriggered) < timeoutDepressed) {
    if (digitalRead(pin) == LOW) {
      return false; // if the pin goes low, press stopped, return
    }
  }

  /* debounce the pin */
  if (millis() - timeLastTriggered < timeoutDebounce) {
    return false; // debounce hasn't passed, return
  }

  /* update the triggered time */
  timeLastTriggered = millis();  

  return true;
}
