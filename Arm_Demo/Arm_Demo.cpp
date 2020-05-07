/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 7, 2020

*/

#include <Wire.h>
#include <Arm_Settings.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arm_Demo.h>
#include <Arm_Servo.h>

extern Arm_Servo servo;

Arm_Demo::Arm_Demo()
{
	_standardDelay = 500;
	for (int i=0; i< NUM_SERVOS; i++){ //for now, later figure out a way to store pins in a datastructure that can be accessible
		servoPins[i] = i;
	}
}

Arm_Demo::Arm_Demo(int delay)
{
	_standardDelay = delay;
}

void Arm_Demo::runDemo()
{
	openHand();
	delay(_standardDelay);
	closeHand();
	delay(_standardDelay);
	openHand();
	delay(_standardDelay);
	closeHand();
	delay(_standardDelay);
	fingerByFinger();
	delay(_standardDelay);
	closeHand();
	delay(_standardDelay);
	thumbsUp();
	delay(_standardDelay);
	closeHand();
	delay(_standardDelay);
	vSign();
	delay(_standardDelay);
}

void Arm_Demo::openHand()
{
	for(int i = 0; i<NUM_SERVOS; i++){
		servo.openFinger(servoPins[i]);
	}
}

void Arm_Demo::closeHand()
{
	for(int i = 0; i<NUM_SERVOS; i++){
		servo.closeFinger(servoPins[i]);
	}
}

void Arm_Demo::fingerByFinger()
{
	for(int i = 0; i<NUM_SERVOS; i++){
		servo.openFinger(servoPins[i]);
		delay(_standardDelay*1.5);
	}

	for(int i = 0; i<NUM_SERVOS; i++){
		servo.closeFinger(servoPins[i]);
		delay(_standardDelay*1.5);
	}
}

void Arm_Demo::thumbsUp()
{
	servo.openFinger(thumbServo);
}

void Arm_Demo::vSign()
{
	servo.openFinger(indexServo);
}