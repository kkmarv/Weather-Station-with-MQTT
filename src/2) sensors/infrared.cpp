#include <Arduino.h>

#define IRPIN D8

void calibrate() {
  int seconds = 90;
  for (size_t i = 0; i < 18; i++) {
    Serial.printf("Calibrating... (%ds left)\r", seconds);
    seconds -= 5;
    delay(5000);
  }
  Serial.println("Calibration done. Searching...");
}

void IRSetup() {
  Serial.begin(9600);
  pinMode(IRPIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println();
  calibrate();
}

void readIR() {
  if (digitalRead(IRPIN) == HIGH) {
    Serial.print("Motion spotted!\r");
    digitalWrite(LED_BUILTIN, LOW);  // led on
    delay(2000);
  } else {
    Serial.print("No Motion.     \r");
  }
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);  // led off
}
