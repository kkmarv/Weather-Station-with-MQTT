#include <Arduino.h>

bool rising;
float fadePercentage = 1.0f;
const float FADE_AMOUNT = 0.05f;

void setPower(unsigned short pin, float percentage) {
  if (percentage <= 0.0f) {
    analogWrite(pin, 0);
  } else if (percentage >= 1.0f) {
    analogWrite(pin, 255);
  } else {
    analogWrite(pin, percentage * 255);
  }
}

void fade(unsigned short led) {
  if (fadePercentage <= 0) {
    rising = true;
  } else if (fadePercentage >= 1) {
    rising = false;
  }
  rising ? fadePercentage += FADE_AMOUNT : fadePercentage -= FADE_AMOUNT;
  setPower(led, fadePercentage);
  delay(100);
}
