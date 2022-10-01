#include <Arduino.h>

// The milliseconds passed since last call to haveMillisPassed() happened.
unsigned long millisSinceLastCheck = 0;

float truncate(float value) {
  return (int)(value * 100 + 0.5) / 100.0;
}

bool haveMillisPassed(unsigned long passedMillis) {
  const unsigned long millisNow = millis();

  if (millisNow - millisSinceLastCheck >= passedMillis) {
    millisSinceLastCheck = millisNow;
    return true;
  }
  return false;
}

void blinkForever(unsigned long intervall) {
  while (1) {
    blink(intervall);
  }
}

void blink(unsigned long intervall) {
  digitalWrite(LED_BUILTIN, LOW);
  delay(intervall);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(intervall);
}
