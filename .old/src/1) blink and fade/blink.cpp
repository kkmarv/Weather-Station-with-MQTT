#include <Arduino.h>
#include <math.h>

unsigned int led;

void setupBlink(unsigned int pin) {
  pinMode(pin, OUTPUT);
  led = pin;
}

void blink(unsigned long intervall) {
  digitalWrite(led, LOW);
  delay(intervall);
  digitalWrite(led, HIGH);
  delay(intervall);
}

void blinkHz(float hz) {
  blink((int)(1000 / hz / 2));
}

void blinkRandom(unsigned int lower, unsigned int higher) {
  blink(rand() % higher + lower);
}