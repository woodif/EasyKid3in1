#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_PWMServoDriver.h>
#include "SPI.h"
#include <TFT_eSPI.h>
#include <Ps3Controller.h>
// #include <TridentTD_LineNotify.h>
// ------- NeoPixels ------
#define LED_PIN 25
#define LED_COUNT 6
#define LED_PIN2 19
#define LED_COUNT2 12
// ------ Ultrasonic ------
#define trigPin 17
#define echoPin 5
// define sound speed in cm/uS
#define SOUND_SPEED 0.034
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

Adafruit_NeoPixel rgbBoard(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rgbCar(LED_COUNT2, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
TFT_eSPI display = TFT_eSPI();

/////////////////////////////////////////////////////////////////////
/*
RGB Board
#setup
•	rgbBoard.setup();
#function
•	rgbBoard(color);
•	rgbBoard.setBrightness(0-255)
•	rgbFillBoard(color() , (r,g,b))
•	rgbBoard.setPixelColor(rgb_num, color() or (r,g,b))
•	rgbBoard.setPixelColor(rgb_num, color() or (r,g,b))
•	rgbBoard.rainbow(time)
•	rgbBoard.theaterChaseRainbow(time)
•	rgbBoard.theaterChase(color() or (r,g,b), time)
•	rgbBoard.colorWipe(color() or (r,g,b), time)

RGB Car
#setup
•	rgbCar.setup();
#function
•	rgbCar(color);
•	rgbCar.setBrightness(0-255)
•	rgbFillCar(color() , (r,g,b))
•	rgbCar.setPixelColor(rgb_num, color() or (r,g,b))
•	rgbCar.setPixelColor(rgb_num, color() or (r,g,b))
•	rgbCar.rainbow(time)
•	rgbCar.theaterChaseRainbow(time)
•	rgbCar.theaterChase(color() or (r,g,b), time)
•	rgbCar.colorWipe(color() or (r,g,b), time)

//COLOR//
Black = 0, 0, 0
White = 255, 255, 255
Red = 255, 0, 0
Green = 0, 255, 0
Blue = 0, 0, 255
Yellow = 255, 255, 0
Magenta = 255, 0, 255
Cyan = 0, 255, 255
Orange = 255, 109, 0
Lemon = 109, 255, 10

*/

void rainbow(int wait)
{
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
  {
    rgbBoard.rainbow(firstPixelHue);
    rgbBoard.show(); // Update strip with new contents
    delay(wait);     // Pause for a moment
  }
}

void rainbow2(int wait)
{
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
  {
    rgbCar.rainbow(firstPixelHue);
    rgbCar.show(); // Update strip with new contents
    delay(wait);   // Pause for a moment
  }
}

void RainBow1(void *parameter)
{
  // for (;;) {
  if (digitalRead(sw) == 0)
  {
    while (true)
    {
      rainbow(2);
      // theaterChaseRainbow2(20);
    }
  }
  //  }
  vTaskDelete(NULL);
}

void RainBow2(void *parameter)
{
  // for (;;) {
  if (digitalRead(sw) == 0)
  {
    while (true)
    {
      rainbow2(2);
      // theaterChaseRainbow2(20);
    }
  }
  // }
  vTaskDelete(NULL);
}
///////////////////////////////////////////////////////////////////////////////////
void joystick_begin()
{
  joy.begin();
}
///////////////////////////////////////////////////////////////////////////////////////
// void LINE_begin()
// {
//   WiFi.begin(SSID, PASSWORD);
//   Serial.printf("WiFi connecting to %s\n", SSID);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     Serial.print(".");
//     delay(400);
//   }
//   Serial.printf("\nWiFi connected\nIP : ");
//   Serial.println(WiFi.localIP());

//   LINE.setToken(LINE_TOKEN);
// }
///////////////////////////////////////////////////////////////////////////////////
void Easy3in1_Setup()
{
  Serial.begin(115200);
  //   RemoteXY_Init ();
  //   tft.begin ();                                 // initialize a ST7789 chip
  //   tft.setSwapBytes (true);                      // swap the byte order for pushImage() - corrects endianness
  // tft.fillScreen (TFT_BLACK);
  //   tft.pushImage (0, 0, 240, 240, theReality);
  display.begin();
  display.setRotation(0);
  rgbBoard.begin();
  rgbBoard.setBrightness(100);
  rgbCar.begin();
  rgbCar.setBrightness(100);
  Serial.println("GPIO test!");
  pinMode(sw, INPUT);
  pwm.begin();
  pwm.setPWMFreq(50);
  pwm.setPWM(0, 0, 0);
  pwm.setPWM(1, 0, 0);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, 0);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, 0);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, 0);
  delay(10);
  //   gripperSetup();

  xTaskCreate(
      RainBow1,   /* Task function. */
      "RainBow1", /* String with name of task. */
      10000,      /* Stack size in words. */
      NULL,       /* Parameter passed as input of the task */
      1,          /* Priority of the task. */
      NULL);      /* Task handle. */
  xTaskCreate(
      RainBow2,   /* Task function. */
      "RainBow2", /* String with name of task. */
      10000,      /* Stack size in words. */
      NULL,       /* Parameter passed as input of the task */
      1,          /* Priority of the task. */
      NULL);      /* Task handle. */
}
///////////////////////////////////////////////////////////////////////////////////////

void motor(int num, int speedM)
{
  if (speedM > 0)
  {
    int mapSpeed = map(speedM, 0, 100, 0, 4095);
    if (num == 1)
    {
      pwm.setPWM(0, mapSpeed, 0);
      pwm.setPWM(1, 0, mapSpeed);
    }
    if (num == 2)
    {
      pwm.setPWM(2, mapSpeed, 0);
      pwm.setPWM(3, 0, mapSpeed);
    }
    if (num == 3)
    {
      pwm.setPWM(4, mapSpeed, 0);
      pwm.setPWM(5, 0, mapSpeed);
    }
    if (num == 4)
    {
      pwm.setPWM(6, mapSpeed, 0);
      pwm.setPWM(7, 0, mapSpeed);
    }
  }
  else if (speedM < 0)
  {
    int mapSpeed = map(speedM, 0, -100, 0, 4095);
    if (num == 1)
    {
      pwm.setPWM(0, 0, mapSpeed);
      pwm.setPWM(1, mapSpeed, 0);
    }
    if (num == 2)
    {
      pwm.setPWM(2, 0, mapSpeed);
      pwm.setPWM(3, mapSpeed, 0);
    }
    if (num == 3)
    {
      pwm.setPWM(4, 0, mapSpeed);
      pwm.setPWM(5, mapSpeed, 0);
    }
    if (num == 4)
    {
      pwm.setPWM(6, 0, mapSpeed);
      pwm.setPWM(7, mapSpeed, 0);
    }
  }
  else if (speedM == 0)
  {
    pwm.setPWM(0, 0, 0);
    pwm.setPWM(1, 0, 0);
    pwm.setPWM(2, 0, 0);
    pwm.setPWM(3, 0, 0);
    pwm.setPWM(4, 0, 0);
    pwm.setPWM(5, 0, 0);
    pwm.setPWM(6, 0, 0);
    pwm.setPWM(7, 0, 0);
  }
}

void motorStopAll()
{
  pwm.setPWM(0, 0, 0);
  pwm.setPWM(1, 0, 0);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, 0);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, 0);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, 0);
}

void servo(int pin, uint16_t degree)
{
  // motorStopAll();
  uint16_t mapServo = map(degree, 0, 180, 102, 512);
  // Serial.println(mapServo);
  if (pin == 1)
  {
    pwm.setPWM(8, 0, mapServo);
  }
  else if (pin == 2)
  {
    pwm.setPWM(9, 0, mapServo);
  }
  else if (pin == 3)
  {
    pwm.setPWM(10, 0, mapServo);
  }
  else if (pin == 4)
  {
    pwm.setPWM(11, 0, mapServo);
  }
  else if (pin == 5)
  {
    pwm.setPWM(12, 0, mapServo);
  }
  else if (pin == 6)
  {
    pwm.setPWM(13, 0, mapServo);
  }
}

int vr(int setValue)
{
  int valueVr = analogRead(34);
  int mapValue = map(valueVr, 0, 4095, 0, setValue);
  return mapValue;
}

float Vbattery()
{
  float Vbat = analogRead(35) * 3.3 / 4095 * (110000 + 15000) / 15000;

  return Vbat;
}

float battery()
{
  float Vfull = 4.2;  // voltage of a fully charged battery
  float Vempty = 3.0; // voltage of an empty battery
  float Vbat = analogRead(35) * 3.3 / 4095 * (110000 + 15000) / 15000;
  int percentage = ((Vbat - Vempty) / (Vfull - Vempty)) * 100;
  return percentage;
}

void readVr()
{
  Serial.print("Vr = ");
  Serial.println(vr(50));
}

float analog(int pin)
{
  if (pin == 0)
    pin = A0;
  else if (pin == 1)
    pin = A1;
  else if (pin == 2)
    pin = A2;
  else if (pin == 3)
    pin = A3;
  else if (pin == 4)
    pin = A4;
  else if (pin == 5)
    pin = A5;
  else if (pin == 6)
    pin = A6;
  return analogRead(pin);
}

void digitalOut(int pin, int state)
{
  if (pin == 0)
    pin = A0;
  else if (pin == 1)
    pin = A1;
  else if (pin == 2)
    pin = A2;
  else if (pin == 3)
    pin = A3;
  else if (pin == 4)
    pin = A4;
  else if (pin == 5)
    pin = A5;
  else if (pin == 6)
    pin = A6;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, state);
}

int digitalIn(int pin)
{
  if (pin == 0)
    pin = A0;
  else if (pin == 1)
    pin = A1;
  else if (pin == 2)
    pin = A2;
  else if (pin == 3)
    pin = A3;
  else if (pin == 4)
    pin = A4;
  else if (pin == 5)
    pin = A5;
  else if (pin == 6)
    pin = A6;
  pinMode(pin, INPUT);
  return digitalRead(pin);
}

int digitalIn_Pullup(int pin)
{
  if (pin == 0)
    pin = A0;
  else if (pin == 1)
    pin = A1;
  else if (pin == 2)
    pin = A2;
  else if (pin == 3)
    pin = A3;
  else if (pin == 4)
    pin = A4;
  else if (pin == 5)
    pin = A5;
  else if (pin == 6)
    pin = A6;
  pinMode(pin, INPUT_PULLUP);
  return digitalRead(pin);
}

void waitForStart()
{
  while (digitalRead(0) == 1)
  {
  }
}

int sw_start()
{
  return digitalRead(0);
}

void rgbBrightness(int value)
{
}

///////////////////////////////////////////////////////////////////

void rgbFillBoard(int r, int g, int b)
{
  for (int i = 0; i <= LED_COUNT; i++)
  {
    rgbBoard.setPixelColor(i, rgbBoard.Color(r, g, b));
  }
  rgbBoard.show();
}

void rgbFillCar(int r, int g, int b)
{
  for (int i = 0; i <= LED_COUNT2; i++)
  {
    rgbCar.setPixelColor(i, rgbCar.Color(r, g, b));
  }
  rgbCar.show();
}

void rgb(int numPin, int r, int g, int b)
{
  rgbBoard.setPixelColor(numPin, rgbBoard.Color(r, g, b));
  rgbBoard.show();
}

void colorWipe(int r, int g, int b, int wait)
{
  for (int i = 0; i < rgbBoard.numPixels(); i++)
  {                                                     // For each pixel in strip...
    rgbBoard.setPixelColor(i, rgbBoard.Color(r, g, b)); //  Set pixel's color (in RAM)
    rgbBoard.show();                                    //  Update strip to match
    delay(wait);                                        //  Pause for a moment
  }
}

void theaterChaseRainbow(int wait)
{
  int firstPixelHue = 0; // First pixel starts at red (hue 0)
  for (int a = 0; a < 30; a++)
  { // Repeat 30 times...
    for (int b = 0; b < 3; b++)
    {                   //  'b' counts from 0 to 2...
      rgbBoard.clear(); //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for (int c = b; c < rgbBoard.numPixels(); c += 3)
      {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int hue = firstPixelHue + c * 65536L / rgbBoard.numPixels();
        uint32_t color = rgbBoard.gamma32(rgbBoard.ColorHSV(hue)); // hue -> RGB
        rgbBoard.setPixelColor(c, color);                          // Set pixel 'c' to value 'color'
      }
      rgbBoard.show();             // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void theaterChaseRainbow2(int wait)
{
  int firstPixelHue = 0; // First pixel starts at red (hue 0)
  for (int a = 0; a < 30; a++)
  { // Repeat 30 times...
    for (int b = 0; b < 3; b++)
    {                 //  'b' counts from 0 to 2...
      rgbCar.clear(); //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for (int c = b; c < rgbCar.numPixels(); c += 3)
      {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int hue = firstPixelHue + c * 65536L / rgbCar.numPixels();
        uint32_t color = rgbCar.gamma32(rgbCar.ColorHSV(hue)); // hue -> RGB
        rgbCar.setPixelColor(c, color);                        // Set pixel 'c' to value 'color'
      }
      rgbCar.show();               // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void theaterChase(int r, int g, int b, int wait)
{
  for (int a = 0; a < 10; a++)
  { // Repeat 10 times...
    for (int b = 0; b < 3; b++)
    {                   //  'b' counts from 0 to 2...
      rgbBoard.clear(); //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < rgbBoard.numPixels(); c += 3)
      {
        rgbBoard.setPixelColor(c, rgbBoard.Color(r, g, b)); // Set pixel 'c' to value 'color'
      }
      rgbBoard.show(); // Update strip with new contents
      delay(wait);     // Pause for a moment
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////

void gripperSetup()
{
  servo(6, 125); // open 125, close 175 Gripper
  delay(300);
  servo(5, 59); // Up 75 Down 125
  delay(300);
  servo(4, 100); // Lock 80 In Out 120
  delay(300);
}

void pickUp()
{
  servo(6, 125);
  delay(500);
  for (int i = 59; i < 125; i++)
  {
    servo(5, i);
    delay(15);
  }
  delay(500);
  servo(6, 175);
  delay(500);
  for (int i = 125; i > 59; i--)
  {
    servo(5, i);
    delay(15);
  }
  delay(500);
}

void pickDown()
{
  for (int i = 59; i < 125; i++)
  {
    servo(5, i);
    delay(15);
  }
  delay(500);
  servo(6, 125);
  delay(500);
  for (int i = 125; i > 59; i--)
  {
    servo(5, i);
    delay(15);
  }
  delay(500);
}

void testServo(int numServo)
{
  Serial.println(vr(180));
  int x = vr(180);
  servo(numServo, x);
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

// void ultrasonic()
// {
//   long duration, cm;
//   pinMode(trigPin, OUTPUT);
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(5);
//   digitalWrite(trigPin, LOW);
//   pinMode(echoPin, INPUT);
//   duration = pulseIn(echoPin, HIGH);
//   cm = microsecondsToCentimeters(duration);
//   //  Serial.print(cm);
//   //  Serial.print("cm");
//   //  Serial.println();
// }

float sonar()
{
  long duration;
  float distanceCm;
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distanceCm = duration * SOUND_SPEED / 2;

  return distanceCm;
}

int JoyCross()
{
  return joy.data.button.cross;
}

int JoySquare()
{
  return joy.data.button.square;
}

int JoyTriangle()
{
  return joy.data.button.triangle;
}

int JoyCircle()
{
  return joy.data.button.circle;
}

int JoyUp()
{
  return joy.data.button.up;
}

int JoyDown()
{
  return joy.data.button.down;
}

int JoyRight()
{
  return joy.data.button.right;
}

int Joyleft()
{
  return joy.data.button.left;
}

int JoyL1()
{
  return joy.data.button.l1;
}

int JoyL2()
{
  return joy.data.button.l2;
}

int JoyR1()
{
  return joy.data.button.r1;
}

int JoyR2()
{
  return joy.data.button.r2;
}

int JoySelect()
{
  return joy.data.button.select;
}

int JoyStart()
{
  return joy.data.button.start;
}

int JoyPS()
{
  return joy.data.button.ps;
}

int JoyLx()
{
  return joy.data.analog.stick.lx;
}

int JoyLy()
{
  return joy.data.analog.stick.ly;
}

int JoyRx()
{
  return joy.data.analog.stick.rx;
}

int JoyRy()
{
  return joy.data.analog.stick.ry;
}