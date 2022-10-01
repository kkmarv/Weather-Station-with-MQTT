#pragma once

#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <DHT.h>

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

 public:
  PressureTemperatureSensor();

  float readTemperature();
  float readPressure();
  float calculateAltitude();
};

class RainSensor {};

class GasSensor {};

/* Deprecated declarations */

// Rain
void setupRain();
void loopRain();
String readRain();

// Air Quality
void setupAir();
void readAir();
