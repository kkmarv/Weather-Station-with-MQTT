#include <Arduino.h>

bool rising;
float fadePercentage = 1.0f;
const float fadeAmount = 0.05f;

void setPower(int pin, float percentage) {
  if (percentage <= 0.0f) {
    analogWrite(pin, 0);
  } else if (percentage >= 1.0f) {
    analogWrite(pin, 255);
  } else {
    analogWrite(pin, percentage * 255);
  }
}

void fade(int led) {
  if (fadePercentage <= 0) {
    rising = true;
  } else if (fadePercentage >= 1) {
    rising = false;
  }

  rising ? fadePercentage += fadeAmount : fadePercentage -= fadeAmount;

  setPower(led, fadePercentage);

  delay(100);
}
