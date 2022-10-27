#include <Wire.h>

#include "sensors.hpp"
#include "utils.hpp"

/**
 * @param sdaPin The wind sensor's SDA pin.
 * @param sclPin The wind sensor's SCL pin.
 */
LightSensor::LightSensor(uint8_t sdaPin, uint8_t sclPin) {
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin(sdaPin, sclPin);
  if (!bh_.begin(BH1750::ONE_TIME_HIGH_RES_MODE)) {
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
  while (!bh_.measurementReady(true)) {
    yield();
  }
  float lux = bh_.readLightLevel();
  lux < 0 ? LOG_LN(F("Error reading ambient light.")) : LOG_LN(F("Light: ") + String(lux) + F(" lx"));
  bh_.configure(BH1750::ONE_TIME_HIGH_RES_MODE);
  return lux;
}
