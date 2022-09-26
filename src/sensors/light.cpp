#include <Wire.h>

#include "sensors.hpp"

// LightSensor (BH1750FVI)
#define BH_SDA_PIN D14
#define BH_SCL_PIN D15

LightSensor::LightSensor() {
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin(BH_SDA_PIN, BH_SCL_PIN);
  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);
}

float LightSensor::read() {
  // Wait a short amount of time for the sensor be able to read again.
  while (!lightMeter.measurementReady(true)) {
    yield();
  }
  float lux = lightMeter.readLightLevel();
  LOG_LN("Light: " + String(lux) + " lx");
  lightMeter.configure(BH1750::ONE_TIME_HIGH_RES_MODE);
  return lux;
}
