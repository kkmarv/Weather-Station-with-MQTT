#pragma once

#include <Arduino.h>
#include <BH1750.h>
#include <DHT.h>

#include "debug.hpp"

class HumidityTemperatureSensor {
 private:
  DHT _dht;

 public:
  HumidityTemperatureSensor();

  // Read and return temperature (°C) from DHT.
  float readTemperature();
  // Read and return relative humidity (%) from DHT.
  float readHumidity();
  // virtual String toJSON() override;
};

class LightSensor {
 private:
  BH1750 lightMeter;

 public:
  LightSensor();

  // Read an return ambient light intensity (lx) from BH1750.
  float read();
  // virtual String toJSON() override;
};

/* Deprecated declarations */

// Pressure & Altitude
void readPressureAltitude();
void setupPressureAltitude();

// Rain
void setupRain();
void loopRain();
String readRain();

// Air Quality
void setupAir();
void readAir();
