#include <Arduino.h>

unsigned long previousMillis = 0;  // time since the program started running: used for calculating intervals

// Initialize serial communication and wait for its port to open.
void startSerialComs() {
  Serial.begin(9600);
  while (!Serial) {
  }
}

// Returns if the specified interval has passed since the last call to this function.
bool hasIntervalPassed(unsigned long interval, bool resetInterval) {
  const unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    if (resetInterval) {
      previousMillis = currentMillis;
    }
    return true;
  }
  return false;
}
