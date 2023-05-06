#ifndef EASY_h
#define EASY_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "SPI.h"
#include <TFT_eSPI.h>

// ------- NeoPixels ------
#define LED_PIN 25
#define LED_COUNT 6
#define LED_PIN2 19
#define LED_COUNT2 12
// ------ Ultrasonic ------
#define trigPin 17
#define echoPin 5
// ------ Buzzer ------
#define buzzer 16
// ------ Switch ------
#define sw 0
//////////////////////////////////////////////////////////////////////
#define A0 26
#define A1 13
#define A2 14
#define A3 15
#define A4 27
#define A5 32
#define A6 33
#define D0 26
#define D1 13
#define D2 14
#define D3 15
#define D4 27
#define D5 32
#define D6 33
//////////////////////////////////////////////////////////////////////

class Easy3in1
{
public:
    void begin(void);
    void motor(int num, int speedM);

protected:
    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
    TFT_eSPI tft = TFT_eSPI();

private:

};

extern Easy3in1 Easy;

#endif