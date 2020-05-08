
/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 7, 2020

*/

#ifndef Arm_Screen_h
#define Arm_Screen_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Arm_Settings.h>

class Arm_Screen
{
	private:

		boolean _started;

	public:
		Arm_Screen();
		void prepare();
		void setTextSize(int size);
		void printToScreen(char string[]);
		void printToScreen(int val);
		void printToScreen(char string[], int val);
		void clearScreen();
};

#endif