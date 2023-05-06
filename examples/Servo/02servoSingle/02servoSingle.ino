#include "3in1easy.h"
int i;
void setup()
{
  Easy3in1_Setup();
}

void loop()
{
  for (i = 0; i <= 180; i++)
  {
    servo(1, i);
    Serial.println(i);
    delay(20);
  }
  for (i = 180; i >= 0; i--)
  {
    servo(1, i);
    Serial.println(i);
    delay(20);
  }
}
