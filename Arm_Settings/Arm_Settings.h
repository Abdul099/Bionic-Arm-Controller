/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 18, 2020

*/

#ifndef Arm_Settings_h
#define Arm_Settings_h

//servo PWM settings
#define PWM_frequency 60
#define SERVOMIN 230
#define SERVOMAX 410

//emg channel and servo settings
#define NUM_CHANNELS 1
#define NUM_SERVOS 3
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

//Calibration Settings
#define NUM_CONTRACTIONS 10 // number of contractions needed for advanced calibration mode
#define SIZE_TRAININGDATA 80
// other settings 

#endif