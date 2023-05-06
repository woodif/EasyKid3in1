#include "3in1easy.h"

void setup() {
  Easy3in1_Setup();
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  display.fillScreen(TFT_RED)
  delay(1000);
  display.fillScreen(TFT_GREEN)
  delay(1000);
  display.fillScreen(TFT_BLUE)
  delay(1000);
}