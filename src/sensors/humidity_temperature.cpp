#include <DHT.h>

#include "sensors.hpp"

// DHT configuration
#define DHT_PIN D4
#define DHT_TYPE DHT11  // if using DHT 11
//#define DHTTYPE DHT22 // is using DHT 22

HumidityTemperatureSensor::HumidityTemperatureSensor() : _dht(DHT_PIN, DHT_TYPE) {
  _dht.begin();
}

float HumidityTemperatureSensor::readTemperature() {
  float temperature = _dht.readTemperature();
  isnan(temperature) ? LOG_LN("Error reading temperature.") : LOG_LN(String(temperature) + "°C");
  return temperature;
}

float HumidityTemperatureSensor::readHumidity() {
  float humidity = _dht.readHumidity();
  isnan(humidity) ? LOG_LN("Error reading humidity.") : LOG_LN(String(humidity) + "%");
  return humidity;
}
