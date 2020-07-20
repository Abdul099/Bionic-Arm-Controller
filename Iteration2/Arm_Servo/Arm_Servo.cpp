/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: July 19, 2020

*/

#include <Arm_Servo.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <Arm_Settings.h>
	
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();//default i2c address: 0x40

Arm_Servo::Arm_Servo()
{
	_currentIndex = 0;
}

void Arm_Servo::setup(){
	pwm.begin();
	pwm.setPWMFreq(PWM_frequency);
}

void Arm_Servo::closeFinger(int pin)
{
	moveServo(pin, -10);
}

void Arm_Servo::openFinger(int pin)
{
	moveServo(pin, 180);
}
//add a close hand function

void Arm_Servo::moveServo(int pin, int pos) //might become a public method later on
{
	if(pin == thumbServo) pwm.setPWM(pin, 0, SERVOMAX-pos-30);
	else if(pin ==pinkyServo) pwm.setPWM(pin, 0, pos+ SERVOMIN + 25);
	else if(pin == middleServo) pwm.setPWM(pin, 0, pos+ SERVOMIN + 30);
	else pwm.setPWM(pin, 0, pos + SERVOMIN);
}
