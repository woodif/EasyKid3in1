#include "3in1easy.h"

void setup()
{
    joystick_begin();
    Easy3in1_Setup();
    // put your setup code here, to run once:
    joy.begin("c4:4f:33:6f:41:33");
    Serial.println("Ready.");
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (joy.isConnected())
    {

        Serial.print("JoyCross=");
        Serial.print(JoyCross());
        Serial.print(" ");
        Serial.print("JoySquare=");
        Serial.print(JoySquare());
        Serial.print(" ");
        Serial.print("JoyCircle=");
        Serial.print(JoyCircle());
        Serial.print(" ");
        Serial.print("JoyTriangle=");
        Serial.print(JoyTriangle());
        Serial.print(" ");
        delay(50);
        Serial.print("JoyUp=");
        Serial.print(JoyUp());
        Serial.print(" ");
        Serial.print("JoyRight=");
        Serial.print(JoyRight());
        Serial.print(" ");
        Serial.print("JoyDown=");
        Serial.print(JoyDown());
        Serial.print(" ");
        Serial.print("JoyLeft=");
        Serial.print(Joyleft());
        Serial.print(" ");
        delay(50);
        Serial.print("L1=");
        Serial.print(JoyL1());
        Serial.print(" ");
        Serial.print("JoyL2=");
        Serial.print(JoyL2());
        Serial.print(" ");
        Serial.print("JoyR1=");
        Serial.print(JoyR1());
        Serial.print(" ");
        Serial.print("JoyR2=");
        Serial.print(JoyR2());
        Serial.print(" ");
        delay(50);

        Serial.print("L_Analog_X=");
        Serial.print(JoyLx());
        Serial.print(" ");
        Serial.print("L_Analog_Y=");
        Serial.print(JoyLy());
        Serial.print(" ");

        Serial.print("R_Analog_X=");
        Serial.print(JoyRx());
        Serial.print(" ");
        Serial.print("R_Analog_Y=");
        Serial.print(JoyRy());
        Serial.println(" ");
        delay(50);
    }
}