/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 5, 2020

*/

#ifndef Arm_Settings_h
#define Arm_Settings_h

//servo PWM settings
#define PWM_frequency 60
#define SERVOMIN 230
#define SERVOMAX 410

//emg and servo pins
#define emgpin1 A0
#define indexServo 0 //pin on servo shield
#define thumbServo 1
#define pinkyServo 2

#define SERVOSPEED 10 

//delay intervals
#define flag_duration 1000
#define del 50

//lcd screen settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 13


#endif