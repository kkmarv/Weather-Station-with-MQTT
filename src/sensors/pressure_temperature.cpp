#include "sensors.hpp"
#include "utils.hpp"

/**
 * Pressure Sensor (BMP280)
 */
PressureTemperatureSensor::PressureTemperatureSensor() {
  if (!_bmp.begin()) {
    LOG_LN(F("Could not initialize BMP280 pressure sensor!"));
    blinkForever(1000);
  }

  // Settings for a single one-time high-resolution reading.
  _bmp.setSampling(Adafruit_BMP280::MODE_FORCED,       // Operating mode
                   Adafruit_BMP280::SAMPLING_X2,       // Temperature oversampling
                   Adafruit_BMP280::SAMPLING_X16,      // Pressure oversampling
                   Adafruit_BMP280::FILTER_X16,        // Filter oversampling
                   Adafruit_BMP280::STANDBY_MS_4000);  // Standby time
}

/**
 * Read and return the barometric pressure.
 * @return Barometric pressure in Pa.
 */
float PressureTemperatureSensor::readPressure() {
  float pressure = _bmp.readPressure();
  isnan(pressure) ? LOG_LN(F("Error reading pressure.")) : LOG_LN(F("Pressure: ") + String(pressure) + F(" Pa"));
  return pressure;
}

/**
 * Read and return the temperature.
 * @return Temperature in °C.
 */
float PressureTemperatureSensor::readTemperature() {
  float temperature = _bmp.readTemperature();
  isnan(temperature) ? LOG_LN(F("Error reading temperature."))
                     : LOG_LN(F("Temperature: ") + String(temperature) + F(" °C"));
  return temperature;
}
