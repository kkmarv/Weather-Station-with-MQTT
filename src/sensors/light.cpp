#include <Wire.h>

#include "sensors.hpp"
#include "utils.hpp"

LightSensor::LightSensor(uint8_t sdaPin, uint8_t sclPin) {
  sdaPin_ = sdaPin;
  sclPin_ = sclPin;
}

void LightSensor::init() {
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin(sdaPin_, sclPin_);
  if (!bh_.begin(BH1750::ONE_TIME_HIGH_RES_MODE)) {
    LOG_LN(F("Could not initialize BH1750FVI light sensor!"));
    blinkForever(1000);
  }
}

float LightSensor::read() {
  // Wait a short amount of time for the sensor be able to read again.
  while (!bh_.measurementReady(true)) {
    yield();
  }
  float lux = bh_.readLightLevel();
  lux < 0 ? LOG_LN(F("Error reading ambient light.")) : LOG_LN(F("Light: ") + String(lux) + F(" lx"));
  bh_.configure(BH1750::ONE_TIME_HIGH_RES_MODE);
  return lux;
}
