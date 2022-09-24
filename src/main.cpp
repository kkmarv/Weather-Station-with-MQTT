#include <Arduino.h>

#include "network.h"

// #include "blink.h"
// #include "buzz.h"
// #include "humtemp.h"
// #include "infrared.h"
// #include "ultraSound.h"

void setup() {
  SETUP_SERIAL(9600);

  connectToWifi();
  connectToMQTT(1800000);

  // setupDHT()
  // setupUltraSound(D6, D7);
  // IRSetup();
}

void loop() {
  sendMessagePeriodically(10000, "test", "Bapanada");
}
