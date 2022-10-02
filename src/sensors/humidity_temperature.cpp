#include <DHT.h>

#include "sensors.hpp"
#include "utils.hpp"

// DHT configuration
#define DHT_PIN D8
#define DHT_TYPE DHT11  // if using DHT 11
//#define DHTTYPE DHT22 // is using DHT 22

HumidityTemperatureSensor::HumidityTemperatureSensor() : _dht(DHT_PIN, DHT_TYPE) {
  _dht.begin();
}

/**
 * Read and return temperature.
 * @return Temperature in °C.
 */
float HumidityTemperatureSensor::readTemperature() {
  float temperature = _dht.readTemperature();
  isnan(temperature) ? LOG_LN(F("Error reading temperature."))
                     : LOG_LN(F("Temperature: ") + String(temperature) + F(" °C"));
  return temperature;
}

/**
 * Read and return relative humidity.
 * @return Relative humidity in percent (1-100%).
 */
float HumidityTemperatureSensor::readHumidity() {
  float humidity = _dht.readHumidity();
  isnan(humidity) ? LOG_LN(F("Error reading humidity.")) : LOG_LN(F("Humidity: ") + String(humidity) + F(" %"));
  return humidity;
}
