#include "sensors.hpp"
#include "utils.hpp"

PressureTemperatureSensor::PressureTemperatureSensor(unsigned long readRefreshInterval) {
  readRefreshInterval_ = readRefreshInterval;
}

void PressureTemperatureSensor::init() {
  if (!bmp_.begin(BMP280_ADDRESS_ALT)) {
    LOG_LN(F("Unable to initialize BMP280 pressure sensor!"));
    LOG_LN(F("Check wiring or I2C address, then restart your device."));
    blinkForever(1000);
  }

  // Settings for a single one-time high-resolution reading.
  bmp_.setSampling(Adafruit_BMP280::MODE_FORCED,      // Operating mode
                   Adafruit_BMP280::SAMPLING_X2,      // Temperature oversampling
                   Adafruit_BMP280::SAMPLING_X16,     // Pressure oversampling
                   Adafruit_BMP280::FILTER_X16,       // Filter oversampling
                   Adafruit_BMP280::STANDBY_MS_500);  // Standby time
}

float PressureTemperatureSensor::readPressure() {
  // Take a new measurement only when a new message shall be sent.
  // Otherwise, use measurements from previous reading.
  if (millis() - lastReadTimestamp_ >= readRefreshInterval_) {
    bmp_.takeForcedMeasurement();
  }

  float hPa = bmp_.readPressure() / 100;
  isnan(hPa) ? LOG_LN(F("Error reading pressure.")) : LOG_LN(F("Pressure: ") + String(hPa) + F(" hPa"));
  return hPa;
}

float PressureTemperatureSensor::readTemperature() {
  // Take a new measurement only when a new message shall be sent.
  // Otherwise, use measurements from previous reading.
  if (millis() - lastReadTimestamp_ >= readRefreshInterval_) {
    bmp_.takeForcedMeasurement();
  }

  float temperature = bmp_.readTemperature();
  isnan(temperature) ? LOG_LN(F("Error reading temperature."))
                     : LOG_LN(F("Temperature: ") + String(temperature) + F(" °C"));
  return temperature;
}
