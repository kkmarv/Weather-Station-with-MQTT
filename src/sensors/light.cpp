#include <Wire.h>

#include "sensors.hpp"
#include "utils.hpp"

// Light Sensor SDA Pin
#define BH_SDA_PIN D14
// Light Sensor SCL Pin
#define BH_SCL_PIN D15

/**
 * Light Sensor (BH1750FVI)
 */
LightSensor::LightSensor() {
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin(BH_SDA_PIN, BH_SCL_PIN);
  if (!_bh.begin(BH1750::ONE_TIME_HIGH_RES_MODE)) {
    LOG_LN(F("Could not initialize BH1750FVI light sensor!"));
    blinkForever(1000);
  }
}

/**
 * Read and return ambient light intensity.
 * @return Light intensity in lux (lx).
 */
float LightSensor::read() {
  // Wait a short amount of time for the sensor be able to read again.
  while (!_bh.measurementReady(true)) {
    yield();
  }
  float lux = _bh.readLightLevel();
  lux < 0 ? LOG_LN(F("Error reading ambient light.")) : LOG_LN(F("Light: ") + String(lux) + F(" lx"));
  _bh.configure(BH1750::ONE_TIME_HIGH_RES_MODE);
  return lux;
}
