#include <Arduino.h>

// #include "blink.h"
// #include "buzz.h"
// #include "humtemp.h"
#include "infrared.h"
// #include "ultraSound.h"

void setup() {
  IRSetup();
}

void loop() {
  readIR();
}