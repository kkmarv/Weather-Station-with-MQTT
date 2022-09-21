#include <Arduino.h>

#include "air_quality.h"
#include "find_i2c_address.h"
#include "humidity_temperature.h"
#include "pressure_altitude.h"
#include "rain_sensor.h"

void setup() {
  // setupDHT();
  // setupAir();
  // setupPressureAltitude();
  // setup_i2c();
  setupRainSensor();
}

void loop() {
  // readDHT();
  // readAir();
  // readPressureAltitude();
  // loop_i2c();
  loopRainSensor();
}