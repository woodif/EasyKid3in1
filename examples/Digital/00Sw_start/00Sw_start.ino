#include "3in1easy.h"

void setup()
{
  Easy3in1_Setup();
}

void loop()
{
  Serial.print("SW= ");
  Serial.print(sw_start());
  Serial.println("");
  delay(200);
}