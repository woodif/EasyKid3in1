#include "3in1easy.h"

void setup()
{
    Easy3in1_Setup();

    // put your setup code here, to run once:
}

void loop()
{
    // put your main code here, to run repeatedly:
    Serial.println(sonar());
    delay(100);
}