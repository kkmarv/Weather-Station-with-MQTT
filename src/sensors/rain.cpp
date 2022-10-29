#include <Arduino.h>

#include "sensors.hpp"

// int threshold_dry = 1000;
// int threshold_moist = 800;
// int threshold_wet = 500;

/**
 * @param pin The rain sensor's analog read pin.
 * @param controlPin The rain sensor's digital write pin.
 * If set to HIGH, The rain sensor's readings will be written to the analog pin. (This will be handled internally.)
 * This is used because the Wemos D1 only has one analog pin available.
 */
RainSensor::RainSensor(uint8_t pin, uint8_t controlPin) {
  pin_ = pin;
  controlPin_ = controlPin;
  pinMode(pin, INPUT);
  pinMode(controlPin, OUTPUT);
}

/*
 * Read and return the current rain sensor's wetness.
 * @return Wetness from 1024 (low) to 0 (high).
 */
int RainSensor::read() {
  digitalWrite(controlPin_, HIGH);
  int wetness = analogRead(pin_);
  digitalWrite(controlPin_, LOW);
  isnan(wetness) ? LOG_LN(F("Error reading rain sensor.")) : LOG_LN(F("Rain: ") + String(wetness));
  return wetness;
}
