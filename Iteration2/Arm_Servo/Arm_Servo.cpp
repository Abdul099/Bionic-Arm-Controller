/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: August 8, 2020

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
	//moveServo(pin, -10);
	moveServo2(pin, 0);
}

void Arm_Servo::openFinger(int pin)
{
	//moveServo(pin, 180);
	moveServo2(pin,1);
}
//add a close hand function

void Arm_Servo::moveServo(int pin, int pos) //might become a public method later on
{
	if(HAND_TYPE == 0){
		if(pin == thumbServo) pwm.setPWM(pin, 0, SERVOMAX-pos+THUMB_MOD);
		else if(pin ==ringServo) pwm.setPWM(pin, 0, pos+ SERVOMIN + RING_MOD);
		else if(pin == middleServo) pwm.setPWM(pin, 0, pos+ SERVOMIN + MIDDLE_MOD);
		else if(pin == indexServo) pwm.setPWM(pin, 0, pos+ SERVOMIN + RING_MOD);
		else pwm.setPWM(pin, 0, pos + SERVOMIN);
	}
	else{
		if(pin == thumbServo) pwm.setPWM(pin, 0, SERVOMAX-pos+THUMB_MOD);
		else if(pin ==ringServo) pwm.setPWM(pin, 0, pos+ SERVOMIN + RING_MOD);
		else if(pin == middleServo) pwm.setPWM(pin, 0, pos+ SERVOMIN + MIDDLE_MOD);
		else if(pin == indexServo) pwm.setPWM(pin, 0, pos+ SERVOMIN + RING_MOD);
		else if(pin == pinkyServo) pwm.setPWM(pin, 0, pos+ SERVOMIN + PINKY_MOD);
		else pwm.setPWM(pin, 0, pos + SERVOMIN);
	}
}

void Arm_Servo::moveServo2(int pin, bool open) //might become a public method later on
{
	if(!open){//CLOSING POSITION
		if(HAND_TYPE == 0){//brunel hand
			if(pin == thumbServo) pwm.setPWM(pin, 0, THUMB_MAX);
			else if(pin ==ringServo) pwm.setPWM(pin, 0, RING_MIN);
			else if(pin == middleServo) pwm.setPWM(pin, 0, MIDDLE_MIN);
			else if(pin == indexServo) pwm.setPWM(pin, 0, INDEX_MIN);
			else pwm.setPWM(pin, 0, SERVOMIN);
		}
		else{
			if(pin == thumbServo) pwm.setPWM(pin, 0, THUMB_MIN);
			else if(pin ==ringServo) pwm.setPWM(pin, 0, RING_MIN);
			else if(pin == middleServo) pwm.setPWM(pin, 0, MIDDLE_MIN);
			else if(pin == indexServo) pwm.setPWM(pin, 0, INDEX_MIN);
			else if(pin == pinkyServo) pwm.setPWM(pin, 0, PINKY_MIN);
			else pwm.setPWM(pin, 0, SERVOMIN);
		}
	}
	else{
		if(HAND_TYPE == 0){//brunel
			if(pin == thumbServo) pwm.setPWM(pin, 0, THUMB_MIN);
			else if(pin ==ringServo) pwm.setPWM(pin, 0, RING_MAX);
			else if(pin == middleServo) pwm.setPWM(pin, 0, MIDDLE_MAX);
			else if(pin == indexServo) pwm.setPWM(pin, 0, INDEX_MAX);
			else pwm.setPWM(pin, 0, SERVOMAX);
		}
		else{
			if(pin == thumbServo) pwm.setPWM(pin, 0, THUMB_MAX);
			else if(pin ==ringServo) pwm.setPWM(pin, 0, RING_MAX);
			else if(pin == middleServo) pwm.setPWM(pin, 0, MIDDLE_MAX);
			else if(pin == indexServo) pwm.setPWM(pin, 0, INDEX_MAX);
			else if(pin == pinkyServo) pwm.setPWM(pin, 0, PINKY_MAX);
			else pwm.setPWM(pin, 0, SERVOMAX);
		}
	}
}
void Arm_Servo::PerformSpecialMovement() 
{
	if(SPECIAL_POSITION == 0){ //V-Sign
		openFinger(indexServo);
		openFinger(middleServo);	
		closeFinger(thumbServo);
		closeFinger(pinkyServo);
		closeFinger(ringServo);
	}
	else if(SPECIAL_POSITION==1){  // Pen-Grip
		closeFinger(indexServo);
		closeFinger(middleServo);	
		closeFinger(thumbServo);
		openFinger(pinkyServo);
		openFinger(ringServo);
	}
	else if(SPECIAL_POSITION==2){  // OK sign
		closeFinger(indexServo);
		openFinger(middleServo);	
		closeFinger(thumbServo);
		openFinger(pinkyServo);
		openFinger(ringServo);
	}
	else if(SPECIAL_POSITION==3){  // Thumbs-Up
		closeFinger(indexServo);
		openFinger(middleServo);	
		closeFinger(thumbServo);
		openFinger(pinkyServo);
		openFinger(ringServo);
	}
}
