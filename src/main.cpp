#include <Arduino.h>

void setup() {
  pinMode(6, HIGH);
  Serial.begin(9600);
}

void loop() {
  for (size_t i = 0; i < 5; i++) {
    pinMode(6, LOW);
    delay(6);
  }
}
