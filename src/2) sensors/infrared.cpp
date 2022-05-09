#include <Arduino.h>

#define IRPIN D8

void IRSetup() {
  int seconds = 90;
  Serial.begin(9600);
  pinMode(IRPIN, INPUT);
  for (size_t i = 0; i < 18; i++) {
    Serial.printf("\n");
    Serial.printf("Calibrating... (%d)", seconds);
    seconds -= 5;
    delay(5000);
  }
  Serial.println("\nCalibration done. Searching...");
}

void readIR() {
  if (digitalRead(IRPIN) == HIGH) {
    Serial.println("Motion spotted!");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    Serial.println("No Motion.");
  }
  delay(1000);
}
