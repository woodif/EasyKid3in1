#include "3in1easy.h"

void setup() {
  Easy3in1_Setup();
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  display.setUTF8Font(CF_KN_R_09_EN, CF_KN_R_09_TH, NULL);
  display.setTextColor(0xffff, 0x0);
  display.drawUTF8String(String("Hello world!"), 0, 0, GFXFF);
  delay(1000);
}