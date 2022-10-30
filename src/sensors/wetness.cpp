#include <Arduino.h>

#include "sensors.hpp"

WetnessSensor::WetnessSensor(uint8_t pin, uint8_t controlPin) {
  pin_ = pin;
  controlPin_ = controlPin;
  pinMode(pin, INPUT);
  pinMode(controlPin, OUTPUT);
}

float WetnessSensor::read() {
  digitalWrite(controlPin_, HIGH);
  int wetness = analogRead(pin_);
  digitalWrite(controlPin_, LOW);

  if (isnan(wetness)) {
    LOG_LN(F("Error reading wetness sensor."));
    return NAN;
  }

  // from raw 10 bit value to percentage
  float wetnessRatio = (float)((1.0 - (wetness) / 1024.0) * 100.0);
  LOG_LN(F("Wetness: ") + String(wetnessRatio) + F(" %"));
  return wetnessRatio;
}
