#include "3in1easy.h"

void setup() {
  Easy3in1_Setup();
}

void loop() {
/////////// VR Change /////////
testServo(1);
testServo(2);
testServo(3);
testServo(4);
testServo(5);
testServo(6);
delay(10);
}