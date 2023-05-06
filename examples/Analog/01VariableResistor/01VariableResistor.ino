#include "3in1easy.h"

void setup() {
  Easy3in1_Setup();
}

void loop() {
Serial.println(vr(100)); //print value from vr 0-100
delay(10);
}