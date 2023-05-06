#include "3in1easy.h"

void setup() {
  Easy3in1_Setup();
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
    rgbFillBoard(255, 0, 0);
    delay(1000);
    rgbFillBoard(0, 255, 0);
    delay(1000);
    rgbFillBoard(0, 0, 255);
    delay(1000);
}
