#pragma once

#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <DHT.h>
#include <MQUnifiedsensor.h>
#include <map>

#include "debug.hpp"

// Represents a temperature/humidity sensor from the DHT series.
class HumidityTemperatureSensor {
 private:
  DHT dht_;

 public:
  HumidityTemperatureSensor(uint8_t pin, uint8_t dhtType);
  float readTemperature();
  float readHumidity();
};

// Represents any BH1750 light sensor.
class LightSensor {
 private:
  BH1750 bh_;

 public:
  LightSensor(uint8_t sdaPin, uint8_t sclPin);
  float read();
};

// Represents the BMP280 pressure/temperature sensor.
class PressureTemperatureSensor {
 private:
  Adafruit_BMP280 bmp_;
  unsigned long lastReadTimestamp_ = 0;
  unsigned long readRefreshInterval_;

 public:
  PressureTemperatureSensor(unsigned long messageInterval);
  float readTemperature();
  float readPressure();
};

class RainSensor {
 private:
  uint8_t pin_;

 public:
  RainSensor(uint8_t pin);
  int read();
};

// Represents the MQ-135 air quality sensor.
class GasSensor {
 private:
  MQUnifiedsensor mq_;
  std::map<String, float> readings_ = {
      {"CO", -1.0f},     // carbonMonoxide
      {"C2H6O", -1.0f},  // alcohol aka ethanol
      {"CO2", -1.0f},    // carbonDioxide
      {"C7H8", -1.0f},   // toluene
      {"NH4", -1.0f},    // ammonium
      {"C3H6O", -1.0f}   // acetone
  };

 public:
  GasSensor(uint8_t pin);
  const std::map<String, float>& read();
  float readAcetone();
  float readAmmonium();
  float readCarbonDioxide();
  float readCarbonMonoxide();
  float readEthanol();
  float readToluene();
};

// Represents a custom 3D printed anemometer.
class WindSensor {
 private:
  uint8_t speedPin_;
  uint8_t northPin_;
  uint8_t eastPin_;
  uint8_t southPin_;
  uint8_t westPin_;

 public:
  WindSensor(uint8_t speedPin, uint8_t northPin, uint8_t eastPin, uint8_t southPin, uint8_t westPin);
  float readSpeed();
  char readDirection();
};
