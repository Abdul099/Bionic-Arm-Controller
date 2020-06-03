/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 27, 2020

*/

#ifndef Arm_Settings_h
#define Arm_Settings_h

//servo PWM settings
#define PWM_frequency 60
#define SERVOMIN 230
#define SERVOMAX 410

//emg channel and servo settings
#define NUM_CHANNELS 2
#define NUM_SERVOS 5//max 5
#define emgpin1 A0
#define emgpin2 A1
#define indexServo 0 //pin on servo relay module
#define thumbServo 1
#define middleServo 2
#define pinkyServo 3
#define ringServo 4

//delay intervals
#define OPEN_DELAY 20
#define CLOSED_DELAY 20

//lcd screen settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 13

//Calibration Settings
#define samples 200
#define NUM_CONTRACTIONS 10 // number of contractions needed for advanced calibration mode
#define SIZE_TRAININGDATA 80 //max 100
#define TRAINING_DELAY 20 //sampling period for trainingData

//sampler settings
#define THRESHOLD_TOLERENCE 5 //number of successive highs required to initiate a 'close hand' order
#define THRESHOLD_TOLERENCE2 10 //number of successive lows required to initiate an 'open hand' order

// other settings 

#endif