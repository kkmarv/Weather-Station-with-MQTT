#include <DHT.h>

#include "sensors.hpp"
#include "utils.hpp"

HumidityTemperatureSensor::HumidityTemperatureSensor(uint8_t pin, uint8_t dhtType) : dht_(pin, dhtType) {
  dht_.begin();
}

float HumidityTemperatureSensor::readTemperature() {
  float temperature = dht_.readTemperature();
  if (isnan(temperature)) {
    LOG_LN(F("Error reading temperature."));
  } else {
    LOG_LN(F("Temperature: ") + String(temperature) + F(" °C"));
  }
  return temperature;
}

float HumidityTemperatureSensor::readHumidity() {
  float humidity = dht_.readHumidity();
  isnan(humidity) ? LOG_LN(F("Error reading humidity.")) : LOG_LN(F("Humidity: ") + String(humidity) + F(" %"));
  return humidity;
}
