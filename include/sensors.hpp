#pragma once

// Air Quality
void setupAir();
void readAir();

// Temperature & Humidity
void setupDHT();
void readDHT();

// Pressure & Altitude
void setupPressureAltitude();
void readPressureAltitude();

// Rain
void setupRainSensor();
void loopRainSensor();
