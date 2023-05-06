#include "easy3in1.h"

void setup() {
  Easy3in1_Setup();
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  motor(1,50);
  motor(2,50);
  motor(3,50);
  motor(4,50);
  delay(2000);
  motor(1,-50);
  motor(2,-50);
  motor(3,-50);
  motor(4,-50);
  delay(2000);
  motorStopAll();
  delay(1000);
}
