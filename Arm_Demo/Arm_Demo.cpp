/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 13, 2020

*/

#include <Wire.h>
#include <Arm_Settings.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arm_Demo.h>
#include <Arm_Servo.h>

extern Arm_Servo servo;

Arm_Demo::Arm_Demo()
{
	_standardDelay = 1500;
	for (int i=0; i< NUM_SERVOS; i++){ //temperory thing, later figure out a way to store pins in a datastructure that can be accessible
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
	fingerByFinger();
	delay(_standardDelay);
	thumbsUp();
	delay(_standardDelay);
	openHand();
	delay(_standardDelay);
	vSign();
	delay(_standardDelay);
	openHand();
	delay(_standardDelay);
	gangsterSign();
	delay(_standardDelay);
	openHand();
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
	servo.closeFinger(pinkyServo);
	delay(_standardDelay*0.5);
	servo.closeFinger(indexServo);
	delay(_standardDelay*0.5);
	servo.closeFinger(thumbServo);
	delay(_standardDelay*0.5);	
	servo.openFinger(pinkyServo);
	delay(_standardDelay*0.5);
	servo.openFinger(indexServo);
	delay(_standardDelay*0.5);
	servo.openFinger(thumbServo);
	delay(_standardDelay*0.5);	
}

void Arm_Demo::thumbsUp()
{
	servo.openFinger(thumbServo);
	servo.closeFinger(indexServo);
	servo.closeFinger(pinkyServo);
}

void Arm_Demo::vSign()
{
	servo.openFinger(indexServo);
	servo.closeFinger(thumbServo);
	servo.closeFinger(pinkyServo);
}

void Arm_Demo::gangsterSign()
{
	servo.openFinger(thumbServo);
	servo.closeFinger(indexServo);
	servo.openFinger(pinkyServo);
}