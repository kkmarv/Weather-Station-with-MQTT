#include <Arduino.h>

const unsigned short cAir = 343;

unsigned int TrigPin;   // the pin number to send a trigger signal to
unsigned int EchoPin;   // the pin number to listen for a reply on
unsigned int duration;  // time from trigger-pulse to recieving an echo in µs
double distance;        // the calculated distance in cm

void setupUltraSound(unsigned short trigPin, unsigned short echoPin) {
  TrigPin = trigPin;
  EchoPin = echoPin;
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  Serial.begin(9600);
}

void readDistance() {
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH, 70300);  // min 200.660µs
  if (duration > 0) {
    distance = 34.3 * duration / 2000;
    Serial.printf("Duration: %dµs Distance: %.1fcm\n", duration, distance);
  } else {
    Serial.println("Sensor konnte nicht gelesen werden!");
  }
  digitalWrite(TrigPin, HIGH);
  delay(1000);
}
