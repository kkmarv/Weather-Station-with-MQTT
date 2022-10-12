#include <Arduino.h>

#include "sensors.hpp"

#define RAINSENS_PIN A0

// int threshold_dry = 1000;
// int threshold_moist = 800;
// int threshold_wet = 500;

RainSensor::RainSensor() {
    pinMode(RAINSENS_PIN, INPUT);
}

/*
 * Read and return the current rain intensity.
 * @return rain intensity from 1024 (low) to 0 (high).
 */
int RainSensor::read() {
    int intensity = analogRead(RAINSENS_PIN);
    isnan(intensity) ? LOG_LN(F("Error reading rain intensity.")) : LOG_LN(F("Rain: ") + String(intensity));
    return intensity;
}
