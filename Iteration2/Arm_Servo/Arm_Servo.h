/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: July 19, 2020

*/

#ifndef Arm_Servo_h
#define Arm_Servo_h

#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <Arm_Settings.h>


class Arm_Servo
{
	private: 
		int _currentIndex;
		void  moveServo(int pin, int position); //might become public

	public:
		Arm_Servo();
		void addServo(int pin);
		void closeFinger(int pin);
		void openFinger(int pin);
		void setup();
};

#endif