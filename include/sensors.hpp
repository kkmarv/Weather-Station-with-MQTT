#pragma once

// Temperature & Humidity
void setupDHT();
String toMQTT();

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
