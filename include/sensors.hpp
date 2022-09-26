#pragma once

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "debug.hpp"

// Temperature & Humidity
void setupDHT();
String toJSON();

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
