#include <Arduino.h>
#include "utils.h"
#include "wifi.h"

#include "air_quality.h"
#include "find_i2c_address.h"
#include "humidity_temperature.h"
#include "pressure_altitude.h"
#include "rain_sensor.h"

void setup() {
  startSerialComs();
  connectToWifi();
  connectToMQTT();

  // setupDHT();
  // setupAir();
  // setupPressureAltitude();
  // setup_i2c();
  // setupRainSensor();
}

void loop() {
  Serial.println("alo");
  delay(5000);
  // readDHT();
  // readAir();
  // readPressureAltitude();
  // loop_i2c();
  // loopRainSensor();
}
