#include "easy3in1.h"

void setup() {
  Easy3in1_Setup();
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  motor(1,100);
  motor(2,100);
  motor(3,100);
  motor(4,100);
  delay(2000);
  motor(1,-100);
  motor(2,-100);
  motor(3,-100);
  motor(4,-100);
  delay(2000);
  motorStopAll();
  delay(1000);
}
