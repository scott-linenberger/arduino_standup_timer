#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Debouncer.h"
#include "ColorTimer.h"

/* pins */
uint8_t PIN_BUTTON = 5;
uint8_t PIN_PIXELS = 6;
uint8_t PIN_BUZZER = 7;
uint8_t NUM_PIXELS = 8;

/* debounce values */
uint16_t TIMEOUT_DEBOUNCE = 250;
uint8_t TIMEOUT_PRESS = 50;

/* speaking duration */
uint16_t TIMEOUT_SPEAKING = 35000;

/* Debouncer */
Debouncer button = Debouncer(PIN_BUTTON, TIMEOUT_DEBOUNCE, TIMEOUT_PRESS);

/* NeoPixels */
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIN_PIXELS, NEO_GRB + NEO_KHZ800);

/* ColorTimer */
ColorTimer timer = ColorTimer(TIMEOUT_SPEAKING, PIN_BUZZER);

/* timer state */
uint8_t stateTimer = 0;
uint8_t MAX_STATE_TIMER = 1;

void setup() {
  Serial.begin(9600);

  /* start the pixels */
  pixels.begin();
  pixels.setBrightness(50);
  pixels.clear();
  pixels.show();

  /* setup the button pin */
  pinMode(PIN_BUTTON, INPUT);

  /* setup the buzzer pin */
  pinMode(PIN_BUZZER, OUTPUT);
  
  /* start the timer */
  timer.begin(pixels);
}

void buttonPressed() {
    /* update the timer state */
    stateTimer++;

    switch (stateTimer) {
      case 0: // timer off
        timer.reset();
        break;

      case 1:
        timer.start(); // start timer
        break;

      default:
        /* reset state */
        stateTimer = 0;
        /* reset the timer */
        timer.reset();
        break;
    }
}

void loop() {
  /* check for button press */
  if (button.isPressed()) {
    buttonPressed();
  }

  /* exexute the timer's run method */
  timer.run();
}
