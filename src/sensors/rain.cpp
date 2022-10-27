#include <Arduino.h>

#include "sensors.hpp"

// int threshold_dry = 1000;
// int threshold_moist = 800;
// int threshold_wet = 500;

/**
 * @param pin The rain sensor's digital read pin.
 */
RainSensor::RainSensor(uint8_t pin) {
  pin_ = pin;
  pinMode(pin, INPUT);
}

/*
 * Read and return the current rain sensor's wetness.
 * @return Wetness from 1024 (low) to 0 (high).
 */
int RainSensor::read() {
  int wetness = analogRead(pin_);
  isnan(wetness) ? LOG_LN(F("Error reading rain sensor.")) : LOG_LN(F("Rain: ") + String(wetness));
  return wetness;
}
