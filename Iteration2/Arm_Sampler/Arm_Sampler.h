/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: June 16, 2020

*/

#ifndef Arm_Sampler_h

#define Arm_Sampler_h

#include <Arduino.h>
#include <Arm_Settings.h>
#include "EMGFilters.h"

class Arm_Sampler
{
	private: 
		bool _open;
		uint8_t _count;
		int _pin;
		EMGFilters myFilter;
		int sampleRate;
		int humFreq;
		int read();
	public:
		Arm_Sampler();
		Arm_Sampler(int pin);
		bool registerSample(int threshhigh, int threshlow);
		int rawSample();
		void checkBelow(int val, byte duration);
};

#endif
