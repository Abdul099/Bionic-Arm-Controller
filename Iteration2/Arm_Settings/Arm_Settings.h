/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: July 20, 2020
*/

#ifndef Arm_Settings_h
#define Arm_Settings_h

#define BRUNEL_ARM
//#define MBEC_ARM

#define SKIP_CALIBRATION 1
#define LED_DEBUG_MODE 0

//emg channel and servo settings
#define NUM_CHANNELS 2 //1 or 2
#define NUM_SERVOS 5//max 5
#define emgpin1 A0
#define emgpin2 A3
#define indexServo 0 //pin on servo relay module
#define thumbServo 1
#define middleServo 2
#define ringServo 3
#define pinkyServo 4

//servo PWM settings
#define PWM_frequency 60

#ifdef BRUNEL_ARM
#define HAND_TYPE 0
#define SERVOMIN 230 
#define SERVOMAX 410 
#define THUMB_MOD 20 //20
#define INDEX_MOD 10  //20
#define MIDDLE_MOD 25 //25
#define RING_MOD 30 //30
#define PINKY_MOD 0 //not used in this case but must be defined nevertheless
#endif

#ifdef MBEC_ARM
#define HAND_TYPE 1
#define SERVOMIN 250 
#define SERVOMAX 450 
#define THUMB_MOD 0 
#define INDEX_MOD 0
#define MIDDLE_MOD 0
#define RING_MOD 0
#define PINKY_MOD 0
#endif

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
#define SIZE_TRAININGDATA 30 //max 40
#define TRAINING_DELAY 20 //sampling period for trainingData

//sampler settings
#define THRESHOLD_TOLERENCE 2 //number of successive highs required to initiate a 'close hand' order
#define THRESHOLD_TOLERENCE2 2 //number of successive lows required to initiate an 'open hand' order
#define HOLD 2
#define buffer_arrayLength 8
#define PEAKWINDOW 40
#define PEAK_HOLD 0

#endif