#include "3in1easy.h"

void setup()
{
    joystick_begin();
    Easy3in1_Setup();
    // put your setup code here, to run once:
    joy.begin("01:02:03:04:05:06");
    Serial.println("Ready.");
}

void loop()
{
    // put your main code here, to run repeatedly:
        if(joy.isConnected()){

        if( joy.data.button.cross ){
            Serial.println("Pressing the cross button");
        }

        if( joy.data.button.square ){
            Serial.println("Pressing the square button");
        }

        if( joy.data.button.triangle ){
            Serial.println("Pressing the triangle button");
        }

        if( joy.data.button.circle ){
            Serial.println("Pressing the circle button");
        }

    }
}