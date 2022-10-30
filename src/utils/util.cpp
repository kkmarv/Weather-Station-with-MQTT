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

void blink(unsigned long interval) {
  digitalWrite(LED_BUILTIN, LOW);
  delay(interval);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(interval);
}

void blinkForever(unsigned long interval) {
  while (1) {
    blink(interval);
  }
}
