#include <Arduino.h>
#include <string>

#include "debug.hpp"
#include "network.hpp"

#include "sensors.hpp"

void setup() {
  SETUP_SERIAL(9600);

  connectToWifi();
  connectToMQTT(1800000);

  setupRain();
}

void loop() {
  String rain = readRain();
  String message = "{\"rain\":" + rain + ",\"humidity\":34.60}";
  sendMessagePeriodically(10000, "test", message);
}
