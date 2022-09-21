#include <Arduino.h>

#define AIRPIN D4
int value;


void setupAir() {
  Serial.begin(9600);
  pinMode(AIRPIN, INPUT);
  Serial.println();
}

void readAir() {
    value = analogRead(AIRPIN);
    // OMEGAKEK
    Serial.print("Air Quality: ");
    Serial.print(value);
    // Serial.print(value, DEC);
    Serial.println(" PPM");
    delay(1000);
}
