#include <DHT.h>

#include "sensors.hpp"
#include "utils.hpp"

/**
 * @param pin The sensor's digital read/write pin.
 * @param dhtType The type of the DHT. Possible values are: "DHT11", "DHT12", "DHT21" "DHT22"
 */
HumidityTemperatureSensor::HumidityTemperatureSensor(uint8_t pin, uint8_t dhtType) : dht_(pin, dhtType) {
  dht_.begin();
}

/**
 * Read and return temperature.
 * @return Temperature in °C.
 */
float HumidityTemperatureSensor::readTemperature() {
  float temperature = dht_.readTemperature();
  isnan(temperature) ? LOG_LN(F("Error reading temperature."))
                     : LOG_LN(F("Temperature: ") + String(temperature) + F(" °C"));
  return temperature;
}

/**
 * Read and return relative humidity.
 * @return Relative humidity in percent (1-100%).
 */
float HumidityTemperatureSensor::readHumidity() {
  float humidity = dht_.readHumidity();
  isnan(humidity) ? LOG_LN(F("Error reading humidity.")) : LOG_LN(F("Humidity: ") + String(humidity) + F(" %"));
  return humidity;
}
