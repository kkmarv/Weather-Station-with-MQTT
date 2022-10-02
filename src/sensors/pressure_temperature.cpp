#include "sensors.hpp"
#include "utils.hpp"

// BMP280 I2C address
#define BMP_ADDRESS 0x76

/**
 * Pressure Sensor (BMP280)
 */
PressureTemperatureSensor::PressureTemperatureSensor(unsigned long messageIntervall) {
  readRefreshIntervall = messageIntervall;

  // TODO PRINT/constructor will not do its thing when bmp is disconnect - why??

  if (!_bmp.begin(BMP_ADDRESS)) {
    LOG_LN(F("Could not initialize BMP280 pressure sensor! Check wiring or I2C address."));
    blinkForever(1000);
  }

  // Settings for a single one-time high-resolution reading.
  _bmp.setSampling(Adafruit_BMP280::MODE_FORCED,      // Operating mode
                   Adafruit_BMP280::SAMPLING_X2,      // Temperature oversampling
                   Adafruit_BMP280::SAMPLING_X16,     // Pressure oversampling
                   Adafruit_BMP280::FILTER_X16,       // Filter oversampling
                   Adafruit_BMP280::STANDBY_MS_500);  // Standby time
}

/**
 * Read and return the barometric pressure.
 * @return Barometric pressure in hPa.
 */
float PressureTemperatureSensor::readPressure() {
  // Take a new measurement only when a new message shall be sent.
  // Otherwise, use measurements from previous reading.
  if (millis() - lastReadTimestamp >= readRefreshIntervall) {
    _bmp.takeForcedMeasurement();
  }

  float hPa = _bmp.readPressure() / 100;
  isnan(hPa) ? LOG_LN(F("Error reading pressure.")) : LOG_LN(F("Pressure: ") + String(hPa) + F(" hPa"));
  return hPa;
}

/**
 * Read and return the temperature.
 * @return Temperature in °C.
 */
float PressureTemperatureSensor::readTemperature() {
  // Take a new measurement only when a new message shall be sent.
  // Otherwise, use measurements from previous reading.
  if (millis() - lastReadTimestamp >= readRefreshIntervall) {
    _bmp.takeForcedMeasurement();
  }

  float temperature = _bmp.readTemperature();
  isnan(temperature) ? LOG_LN(F("Error reading temperature."))
                     : LOG_LN(F("Temperature: ") + String(temperature) + F(" °C"));
  return temperature;
}
