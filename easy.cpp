#include "easy.h"

void Easy3in1::begin(void)
{
  Wire.begin();
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
}

void Easy3in1::motor(int num, int speedM)
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

Easy3in1 Easy;