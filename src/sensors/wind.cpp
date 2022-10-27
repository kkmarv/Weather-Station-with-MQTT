#include <Arduino.h>

#include "sensors.hpp"

/**
 * @param pin The wind sensor's digital read pin.
 */
WindSensor::WindSensor(uint8_t speedPin, uint8_t northPin, uint8_t eastPin, uint8_t southPin, uint8_t westPin) {
  speedPin_ = speedPin;
  northPin_ = northPin;
  eastPin_ = eastPin;
  southPin_ = southPin;
  westPin_ = westPin;
  pinMode(speedPin_, INPUT);
  pinMode(northPin_, INPUT);
  pinMode(eastPin_, INPUT);
  pinMode(southPin_, INPUT);
  pinMode(westPin_, INPUT);
}

/**
 * Read and return the current wind speed.
 * @returns Wind speed in m/s.
 */
float WindSensor::readSpeed() {
  return -1.0f;  // TODO
}

/**
 * Read and return the current wind direction.
 * @returns Wind direction: N: North, E: East, S: South, W: West, X: No(t enough) wind
 */
char WindSensor::readDirection() {
  char windDir;
  if (digitalRead(northPin_)) {
    windDir = 'N';
  } else if (digitalRead(eastPin_)) {
    windDir = 'E';
  } else if (digitalRead(southPin_)) {
    windDir = 'S';
  } else if (digitalRead(westPin_)) {
    windDir = 'W';
  } else {
    windDir = 'X';
  }
  return windDir;
}
