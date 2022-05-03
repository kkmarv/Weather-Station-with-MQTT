#include <Arduino.h>

#include "blink.h"
#include "humtemp.h"
#include "ultraSound.h"

void setup() {
  // setupBlink(LED_BUILTIN);
  setupDHT();
  // setupUltraSound(D6, D7);
}

void loop() {
  // blinkHz():
  readDHT();
  // readDistance();
}