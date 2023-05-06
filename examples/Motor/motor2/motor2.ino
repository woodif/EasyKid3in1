#include "easy3in1.h"
#include "easy.h"
Easy3in1 easy = Easy3in1();
void setup() {
  easy.begin();
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  easy.motor(1,50);
  easy.motor(2,50);
  easy.motor(3,50);
  easy.motor(4,50);
  delay(2000);
  easy.motor(1,-50);
  easy.motor(2,-50);
  easy.motor(3,-50);
  easy.motor(4,-50);
  delay(2000);
}