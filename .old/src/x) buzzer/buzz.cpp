#include <Arduino.h>

int buzzer = D5;
void setup_buzz() {
  pinMode(buzzer, OUTPUT);
}
void buzz(int delay_t) {
  digitalWrite(buzzer, HIGH);
  delay(delay_t);
  digitalWrite(buzzer, LOW);
  delay(delay_t);
}

void buzz_seq() {
  for (size_t i = 0; i < 50; i++) {
    for (size_t j = 0; j < 300; j++) {
      buzz(i);
    }
  }
}

void buzz_random() {
    int rnd = rand() % 100;
    buzz(rnd);
}