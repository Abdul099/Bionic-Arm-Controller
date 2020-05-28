/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 26, 2020

*/

#ifndef Arm_Settings_h
#define Arm_Settings_h

//servo PWM settings
#define PWM_frequency 60
#define SERVOMIN 230
#define SERVOMAX 410

//emg channel and servo settings
#define NUM_CHANNELS 1
#define NUM_SERVOS 4 //max 4
#define emgpin1 A0
#define indexServo 0 //pin on servo shield
#define thumbServo 1
#define middleServo 2
#define pinkyServo 3

//delay intervals
#define FLAG_DURATION 100
#define del 50

//lcd screen settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 13

//Calibration Settings
#define samples 200
#define NUM_CONTRACTIONS 10 // number of contractions needed for advanced calibration mode
#define SIZE_TRAININGDATA 30 //max 40
#define TRAINING_DELAY 50 //sampling period for trainingData

//sampler settings
#define THRESHOLD_TOLERENCE 2 //number of successive highs required to initiate a 'close hand' order
#define THRESHOLD_TOLERENCE2 15 //number of successive lows required to initiate an 'open hand' order

// other settings 

#endif