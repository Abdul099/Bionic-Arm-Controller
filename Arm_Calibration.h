/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 5, 2020

*/

#ifndef Arm_Calibration_h

#define Arm_Calibration_h

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Arm_Settings.h>

class Arm_Calibration
{
	private: 
		int _amplitude;
		int _emg_pin;
		long int _averageMin;
		long int _averageMax;
		long int _numberSamples;
		long int _startTime;
		long int _timer;

	public:
		Arm_Calibration();
		Arm_Calibration(int pin);
		int Calibrate();
};

#endif

