#include "3in1easy.h"

void setup()
{
    joystick_begin();
    Easy3in1_Setup();
    // put your setup code here, to run once:
    String address = joy.getAddress();

    Serial.print("The ESP32's Bluetooth MAC address is: ");
    Serial.println(address);
}

void loop()
{
    // put your main code here, to run repeatedly:
}