#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_PWMServoDriver.h>
#include "SPI.h"
#include <TFT_eSPI.h>

// ------- NeoPixels ------
#define LED_PIN   25
#define LED_COUNT 6
#define LED_PIN2   19
#define LED_COUNT2 12
// ------ Ultrasonic ------
#define trigPin 17
#define echoPin 5
// ------ Buzzer ------
#define buzzer 16
// ------ Switch ------
#define sw 0

//////////////////////////////////////////////////////////////////////

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT2, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
TFT_eSPI tft = TFT_eSPI();

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
*/

void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void rainbow2(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    strip2.rainbow(firstPixelHue);
    strip2.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void RainBow1(void * parameter )
{
 // for (;;) {
    if (digitalRead(sw) == 0) {
      while (true) {
        rainbow(2);
        // theaterChaseRainbow2(20);
      }
    }
//  }
  vTaskDelete( NULL );
}

void RainBow2(void * parameter) {
 // for (;;) {
    if (digitalRead(sw) == 0) {
      while (true) {
        rainbow2(2);
        // theaterChaseRainbow2(20);
      }
    }
 // }
  vTaskDelete( NULL );
}
///////////////////////////////////////////////////////////////////////////////////
void Easy3in1_Setup(){
  Serial.begin(115200);
//   RemoteXY_Init ();
//   tft.begin ();                                 // initialize a ST7789 chip
//   tft.setSwapBytes (true);                      // swap the byte order for pushImage() - corrects endianness
//   tft.fillScreen (TFT_BLACK);
//   tft.pushImage (0, 0, 240, 240, theReality);
  tft.begin();
  tft.setRotation(0);
  strip.begin();
  strip.setBrightness(100);
  strip2.begin();
  strip2.setBrightness(100);
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
    RainBow1,          /* Task function. */
    "RainBow1",        /* String with name of task. */
    10000,            /* Stack size in words. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL);            /* Task handle. */
  xTaskCreate(
    RainBow2,          /* Task function. */
    "RainBow2",        /* String with name of task. */
    10000,            /* Stack size in words. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL);            /* Task handle. */

}
///////////////////////////////////////////////////////////////////////////////////////

void motor(int num, int speedM) {
  if (speedM > 0) {
    int mapSpeed = map(speedM, 0, 100, 0, 4095);
    if (num == 1) {
      pwm.setPWM(0, mapSpeed, 0); 
      pwm.setPWM(1, 0, mapSpeed);
    }
    if (num == 2) {
      pwm.setPWM(2, mapSpeed, 0); 
      pwm.setPWM(3, 0, mapSpeed);
    }
    if (num == 3) {
      pwm.setPWM(4, mapSpeed, 0); 
      pwm.setPWM(5, 0, mapSpeed);
    }
    if (num == 4) {
      pwm.setPWM(6, mapSpeed, 0); 
      pwm.setPWM(7, 0, mapSpeed);
    }
  }
  else if (speedM < 0) {
    int mapSpeed = map(speedM, 0, -100, 0, 4095);
    if (num == 1) {
      pwm.setPWM(0, 0, mapSpeed); 
      pwm.setPWM(1, mapSpeed, 0);
    }
    if (num == 2) {
      pwm.setPWM(2, 0, mapSpeed); 
      pwm.setPWM(3, mapSpeed, 0);
    }
    if (num == 3) {
      pwm.setPWM(4, 0, mapSpeed); 
      pwm.setPWM(5, mapSpeed, 0);
    }
    if (num == 4) {
      pwm.setPWM(6, 0, mapSpeed); 
      pwm.setPWM(7, mapSpeed, 0);
    }
  }
  else if (speedM == 0) {
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

void motorStopAll() {
  pwm.setPWM(0, 0, 0);
  pwm.setPWM(1, 0, 0);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, 0);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, 0);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, 0);
}

void servo(int pin, uint16_t degree) {
  // motorStopAll();
  uint16_t mapServo = map(degree, 0, 180, 102, 512);
  //Serial.println(mapServo);
  if (pin == 1) {
    pwm.setPWM(8, 0, mapServo);

  }
  else if (pin == 2) {
    pwm.setPWM(9, 0, mapServo);
  }
  else if (pin == 3) {
    pwm.setPWM(10, 0, mapServo);
  }
  else if (pin == 4) {
    pwm.setPWM(11, 0, mapServo);
  }
  else if (pin == 5) {
    pwm.setPWM(12, 0, mapServo);
  }
  else if (pin == 6) {
    pwm.setPWM(13, 0, mapServo);
  }
}

int vr(int setValue) {
  int valueVr = analogRead(34);
  int mapValue = map(valueVr, 0, 4095, 0, setValue);
  return mapValue ;
}

void readVr() {
  Serial.print("Vr = ");
  Serial.println(vr(50));
}

void waitStart() {
  while (digitalRead(0) == 1) {}
}

void rgbBrightness(int value) {

}

void rgbFill( int r, int g, int b) {
  for (int i = 0; i <= LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

void rgb2Fill( int r, int g, int b) {
  for (int i = 0; i <= LED_COUNT2; i++) {
    strip2.setPixelColor(i, strip2.Color(r, g, b));
  }
  strip2.show();
}

void rgb(int numPin, int r, int g, int b) {
  strip.setPixelColor(numPin, strip.Color(r, g, b));
  strip.show();
}

void colorWipe(int r, int g, int b, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(r, g, b));         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for (int a = 0; a < 30; a++) { // Repeat 30 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void theaterChaseRainbow2(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for (int a = 0; a < 30; a++) { // Repeat 30 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip2.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for (int c = b; c < strip2.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip2.numPixels();
        uint32_t color = strip2.gamma32(strip2.ColorHSV(hue)); // hue -> RGB
        strip2.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip2.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void theaterChase(int r, int g, int b, int wait) {
  for (int a = 0; a < 10; a++) { // Repeat 10 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        strip.setPixelColor(c, strip.Color(r, g, b)); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

void analog(int pin) {
  analogRead(pin);
}

void digitalOut(int pin, int value) {
  digitalWrite(pin, value);
}

void digitalIn(int pin) {
  digitalRead(pin);
}

void gripperSetup() {
  servo(6, 125); // open 125, close 175 Gripper
  delay(300);
  servo(5, 59); // Up 75 Down 125
  delay(300);
  servo(4, 100); // Lock 80 In Out 120
  delay(300);
}

void pickUp() {
  servo(6, 125);
  delay(500);
  for (int i = 59; i < 125; i++) {
    servo(5, i);
    delay(15);
  }
  delay(500);
  servo(6, 175);
  delay(500);
  for (int i = 125; i > 59; i--) {
    servo(5, i);
    delay(15);
  }
  delay(500);
}

void pickDown() {
  for (int i = 59; i < 125; i++) {
    servo(5, i);
    delay(15);
  }
  delay(500);
  servo(6, 125);
  delay(500);
  for (int i = 125; i > 59; i--) {
    servo(5, i);
    delay(15);
  }
  delay(500);
}

void testServo(int numServo) {
  Serial.println(vr(180));
  int x = vr(180);
  servo(numServo, x);
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void ultrasonic() {
  long duration, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  //  Serial.print(cm);
  //  Serial.print("cm");
  //  Serial.println();
}
