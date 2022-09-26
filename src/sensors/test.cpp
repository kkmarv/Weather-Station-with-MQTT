#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "debug.hpp"
#include "sensors.hpp"

#define DHTPIN 4
#define DHTTYPE DHT11  // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)

DHT_Unified dht(DHTPIN, DHTTYPE);

void setupDHT() {
  dht.begin();

  sensor_t sensor;

  // Print temperature sensor details.
  dht.temperature().getSensor(&sensor);
  LOG_LN("------------------------------------");
  LOG_LN("Temperature sensor:");
  LOG_SENSOR_DETES(sensor, "°C");

  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  LOG_LN("------------------------------------");
  LOG_LN("Humidity sensor:");
  LOG_SENSOR_DETES(sensor, "%");
  LOG_LN("------------------------------------");
}

// Read and return temperature (°C) from DHT.
float readTemperature() {
  // Get temperature event.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    LOG_LN("Error reading temperature.");
  } else {
    LOG_LN(String(event.temperature) + "°C");
  }
  return event.temperature;
}

// Read and return relative humidity from DHT.
float readHumidity() {
  // Get humidity event.
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    LOG_LN("Error reading humidity.");
  } else {
    LOG_LN(String(event.relative_humidity) + "%");
  }
  return event.relative_humidity;
}

String toJSON() {
  return "{temperature: \"" + String(readTemperature()) + "\", humidity: \"" + String(readHumidity()) + "\"}";
}
