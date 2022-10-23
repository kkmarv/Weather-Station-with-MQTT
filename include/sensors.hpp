#pragma once

#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <DHT.h>
#include <MQUnifiedsensor.h>
#include <map>

#include "debug.hpp"
class HumidityTemperatureSensor {
 private:
  DHT _dht;

 public:
  HumidityTemperatureSensor();

  float readTemperature();
  float readHumidity();
};

class LightSensor {
 private:
  BH1750 _bh;

 public:
  LightSensor();

  float read();
};

class PressureTemperatureSensor {
 private:
  Adafruit_BMP280 _bmp;
  unsigned long lastReadTimestamp = 0;
  unsigned long readRefreshIntervall;

 public:
  PressureTemperatureSensor(unsigned long messageInterval);

  float readTemperature();
  float readPressure();
};

class RainSensor {
 public:
  RainSensor();

  int read();
};

class GasSensor {
 private:
  MQUnifiedsensor _mq;
  std::map<String, float> _readings = {
      {"CO", -1.0f},     // carbonMonoxide
      {"C2H6O", -1.0f},  // alcohol aka ethanol
      {"CO2", -1.0f},    // carbonDioxide
      {"C7H8", -1.0f},   // toluene
      {"NH4", -1.0f},    // ammonium
      {"C3H6O", -1.0f}   // acetone
  };

 public:
  GasSensor();
  float readCarbonMonoxide();
  float readEthanol();
  float readCarbonDioxide();
  float readToluene();
  float readAmmonium();
  float readAcetone();
  const std::map<String, float>& read();
};
