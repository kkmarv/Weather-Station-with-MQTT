#include <Arduino.h>
#include "utils.h"
#include "wifi.h"

// #include "blink.h"
// #include "buzz.h"
// #include "humtemp.h"
// #include "infrared.h"
// #include "ultraSound.h"

void setup() {
  startSerialComs();
  connectToWifi();
  connectToMQTT();

  // setupDHT()
  // setupUltraSound(D6, D7);
  // IRSetup();
}

void loop() {
  publishMessagePeriodically("test", "Bapanada", 10000);
}
