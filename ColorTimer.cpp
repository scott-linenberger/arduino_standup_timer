#include "ColorTimer.h"

ColorTimer::ColorTimer(uint16_t _timeoutSpeaking, uint8_t _pinBuzzer) {
  timeoutSpeaking = _timeoutSpeaking;
  pinBuzzer = _pinBuzzer;
}

void ColorTimer::begin(Adafruit_NeoPixel &_pixels) {
  /* assign the pixels */
  pixels = &_pixels;

  /* build colors */
  colorIndicator = pixels->Color(255, 255, 255);
  colorStandby = pixels->Color(50, 0, 255);
  colorWhite = pixels->Color(255, 255, 255);
  colorBlack = pixels->Color(0, 0, 0);

  /* reset for beginning */
  reset();
}

void ColorTimer::reset() {
  /* set started to false */
  isStarted = false;

  /* reset the pixel position */
  positionIndicator = 0;

  /* turn the buzzer off */
  digitalWrite(pinBuzzer, LOW);

  /* set the pixels green */
  for (uint8_t i = 0; i < pixels->numPixels(); i++) {
    pixels->setPixelColor(i, colorStandby);
  }
  pixels->show();
}

void ColorTimer::degradeColor(float timeElapsed) {
  /* calculate the color degrade */
  float percentage = timeElapsed / timeoutSpeaking;
  float offset = 255 * percentage;

  Serial.println(offset);

  float valueGreen = 255 - offset;
  float valueRed = 0 + offset;

  for(uint8_t i = 0; i < pixels->numPixels(); i++) {
    pixels->setPixelColor(i, pixels->Color(valueRed, valueGreen, 0));
  }

  /* set the indicator */
  pixels->setPixelColor(positionIndicator, colorIndicator);

  pixels->show();
}

void ColorTimer::flash() {
  for (uint8_t i = 0; i < pixels->numPixels(); i++) {
    if (isOn) {
      pixels->setPixelColor(i, colorWhite);
    } else {
      pixels->setPixelColor(i, colorBlack);
    }
  }

  pixels->show();

  /* toggle the buzzer */
  digitalWrite(pinBuzzer, isOn);

  /* toggle the isOn flag */
  isOn = !isOn;
}

void ColorTimer::run() {
  /* if the timer isn't started, return */
  if (!isStarted) {
    return;
  }

  /* if it's not time to tick yet, return */
  if (!ticker.isReady()){
    return;
  }

  /* update the indicator's position */
  positionIndicator++;

  /* reset the indicator if needed */
  if (positionIndicator >= pixels->numPixels()) {
    positionIndicator = 0;
  }

  /* check how much time has passed */
  float timeElapsed = millis() - timeStarted;

  /* if the timer has timed out */
  if (timeElapsed > timeoutSpeaking) {
    flash();
  } else {
    /* timer still going, degrade color */
    degradeColor(timeElapsed);
  }

  /* update the ticker */
  ticker.tick();
}

void ColorTimer::start() {
  /* set the started variable */
  isStarted = true;

  /* get the time */
  timeStarted = millis();
}
