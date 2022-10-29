#include <Arduino.h>

#include "sensors.hpp"

/**
 * @param speedPin Will be used to calculate wind speed.
 * Is set to HIGH if the anemometer does a full rotation and passes a reed switch.
 * @param northPin Indicates with a HIGH that the wind direction is approximately North.
 * @param eastPin Indicates with a HIGH that the wind direction is approximately East.
 * @param southPin Indicates with a HIGH that the wind direction is approximately South.
 * @param westPin Indicates with a HIGH that the wind direction is approximately West.
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
  LOG_LN(digitalRead(speedPin_));
  return -1.0f;  // TODO
}

/**
 * Read and return the current wind direction.
 * @returns Wind direction
 */
WindSensor::WindDirection WindSensor::readDirection() {
  if (digitalRead(northPin_)) {
    if (digitalRead(eastPin_)) {
      windDir_ = WindDirection::NORTH_EAST;
    } else if (digitalRead(westPin_)) {
      windDir_ = WindDirection::NORTH_WEST;
    } else {
      windDir_ = WindDirection::NORTH;
    }

  } else if (digitalRead(southPin_)) {
    if (digitalRead(eastPin_)) {
      windDir_ = WindDirection::SOUTH_EAST;
    } else if (digitalRead(westPin_)) {
      windDir_ = WindDirection::SOUTH_WEST;
    } else {
      windDir_ = WindDirection::SOUTH;
    }

  } else if (digitalRead(eastPin_)) {
    windDir_ = WindDirection::EAST;

  } else if (digitalRead(westPin_)) {
    windDir_ = WindDirection::WEST;
  }

  return windDir_;
}
