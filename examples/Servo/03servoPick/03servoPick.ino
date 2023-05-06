#include "3in1easy.h"

void setup() {
  Easy3in1_Setup();
}

void loop() {
gripperSetup();
delay(2000);
pickUp();
delay(2000);
pickDown();
delay(2000);
}