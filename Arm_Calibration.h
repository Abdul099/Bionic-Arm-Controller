#ifndef Arm_Calibration_h

#define Arm_Calibration_h

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

static int SCREEN_WIDTH = 128;
static int SCREEN_HEIGHT = 64;
static int OLED_RESET = 13;

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

