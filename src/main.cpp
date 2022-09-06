#include <Arduino.h>

// #include "blink.h"
// #include "buzz.h"
// #include "humtemp.h"
#include "infrared.h"
// #include "ultraSound.h"

void setup() {
  // setupDHT()
  // setupUltraSound(D6, D7);
  IRSetup();
}

void loop() {
  // readDHT
  // readDistance();
  readIR();
}