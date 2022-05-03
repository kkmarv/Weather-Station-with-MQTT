#include <Arduino.h>

#include "blink.h"
#include "humtemp.h"
#include "ultraSound.h"

void setup() {
  setupUltraSound(D6, D7);
}

void loop() {
  readDistance();
}