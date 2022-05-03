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

void blink_hz(float hz) {
  digitalWrite(led, HIGH);
  delay((int)(1000 / hz));
  digitalWrite(led, LOW);
  delay((int)(1000 / hz));
}

void blink_random(unsigned int lower, unsigned int higher) {
  const unsigned long rand_delay = rand() % higher + lower;
  digitalWrite(led, HIGH);
  delay(rand_delay);
  digitalWrite(led, LOW);
  delay(rand_delay);
}