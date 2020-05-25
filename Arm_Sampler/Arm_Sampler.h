/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 22, 2020

*/

#ifndef Arm_Sampler_h

#define Arm_Sampler_h

#include <Arduino.h>
#include <Arm_Settings.h>

class Arm_Sampler
{
	private: 
		bool _open;
		uint8_t _count;
	public:
		Arm_Sampler();
		bool registerSample(int threshhigh, int threshlow);
};

#endif
