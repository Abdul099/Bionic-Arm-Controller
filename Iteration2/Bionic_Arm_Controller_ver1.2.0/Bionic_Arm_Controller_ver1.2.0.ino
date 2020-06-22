/*
  Project Name: Bionic Arm Controller ver 1.0.6
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: June 22, 2020
  Description: Simplified program that receives emg input via analog pin and outputs PWM signals to 3 servo motors. An all-or-none basis is used to drive the control,
               where a signal below a certain threshold causes the arm to open and a signal above the threshold causes the arm to close. The threshold is determined
               through calibration, which is done through the Arm_Calibration library.
*/
#include <Arm_Settings.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arm_Calibration.h>
#include <Adafruit_GFX.h>
#include <Arm_Servo.h>
#include <Arm_Demo.h>
#include <Arm_Sampler.h>

int amp1;
int thresh;
short hold;
int lowThresh;
bool opened = 1;
short baseline;
Arm_Calibration Calibrate = Arm_Calibration();
Arm_Servo servo = Arm_Servo();
Arm_Demo demo = Arm_Demo();
Arm_Sampler sampler = Arm_Sampler();

void setup() {
  Wire.begin();
  Serial.begin(9600);
  thresh = Calibrate.CalibrateDry(&lowThresh, &hold, &baseline);
  Serial.print("Lowthresh: ");
  Serial.println(lowThresh);
  delay(1000);
  servo.setup();
  sampler.setBaseline(baseline); 
}

void loop() {
  amp1 = sampler.simpleSample();//we start by reading the signal value from the emg sensor --> assign this value to amp
  //opened = sampler.registerSample(thresh, lowThresh);
//  if(opened==1){
//      servo.openFinger(thumbServo);
//      servo.openFinger(pinkyServo);
//      servo.openFinger(indexServo);
//      servo.openFinger(middleServo);
//      delay(CLOSED_DELAY);
//  }
//  else{
//      servo.closeFinger(thumbServo);
//      servo.closeFinger(pinkyServo);
//      servo.closeFinger(indexServo);
//      servo.closeFinger(middleServo);
//      delay(OPEN_DELAY);
//  }
}
