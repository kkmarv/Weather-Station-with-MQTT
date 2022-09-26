#include <Arduino.h>
#include <DHT.h>

#include "debug.hpp"
#include "network.hpp"
#include "sensors.hpp"

// Interval in microseconds how often a message should be sent via MQTT.
const unsigned int messageInterval = 10000;

void setup() {
  SETUP_SERIAL(9600);

  connectToWifi();
  connectToMQTT(messageInterval * 2);

  setupDHT();
  // setupRain();
}

void loop() {
  sendMessagePeriodically(messageInterval, "test", toMQTT);
}
