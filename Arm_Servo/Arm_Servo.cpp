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

void Arm_Servo::addServo(int pin)
{
	_servos[_currentIndex].servoPin = pin;
	_servos[_currentIndex].position = 0;
	_currentIndex++;
}

void Arm_Servo::moveServo(int pin, int pos) //might become a public method later on
{
	if(pin == thumbServo) pwm.setPWM(pin, 0, SERVOMAX-pos);
	else pwm.setPWM(pin, 0, pos + SERVOMIN);

}

void Arm_Servo::closeFinger(int pin)
{
	moveServo(pin, 0);
}

void Arm_Servo::openFinger(int pin)
{
	moveServo(pin, 175);
}
//add a close hand function

_Servo Arm_Servo::findServo(int pin)
{
	for (int i =0; i< NUM_SERVOS; i++){
		if(pin == _servos[i].servoPin) return _servos[i]; //look into the else case
	}
}