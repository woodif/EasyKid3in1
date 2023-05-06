#include "3in1easy.h"

void setup() {
  Easy3in1_Setup();
}

void loop() {
Serial.println(analog(A0));
delay(20);
}