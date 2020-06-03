/*
  Project Name: Bionic Arm Controller ver 1.1.1
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: June 3, 2020
  Description: Control sketch that receives EMG input via 2 analog pins coming from 2 EMG channels and outputs PWM signals to 3 servo motors. The threshold for each channel is determined
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
int amp2; 
int thresh1;
int thresh2;
int lowthresh1;
int lowthresh2;
bool opened1 = 1;
bool opened2 = 0;
Arm_Calibration Calibrate = Arm_Calibration(emgpin1);
Arm_Calibration Calibrate2 = Arm_Calibration(emgpin2); 
Arm_Servo servo = Arm_Servo();
Arm_Demo demo = Arm_Demo();
Arm_Sampler sampler = Arm_Sampler();

void setup() {
  Wire.begin();
  Serial.begin(9600);
  thresh1 = Calibrate.CalibrateAdvanced(&lowthresh1);
  thresh2 = Calibrate2.CalibrateAdvanced(&lowthresh2);
  Serial.print("Lowthresh: ");
  Serial.println(lowthresh1);
  delay(1000);
  servo.setup();
  //demo.runDemo();
}

void loop() {
  amp1 = analogRead(emgpin1);//we start by reading the signal value from the emg sensor --> assign this value to amp
  amp2 = analogRead(emgpin2);
  Serial.println(amp1);//print the amplitude to the graph
  opened1 = sampler.registerSample(thresh1, lowthresh1);
  opened2 = sampler.registerSample(thresh2, lowthresh2);
  if(opened1==1){
      servo.openFinger(thumbServo);
      servo.openFinger(pinkyServo);
      servo.openFinger(indexServo);
      servo.openFinger(middleServo);
      delay(CLOSED_DELAY);
  }
  else{
      servo.closeFinger(thumbServo);
      servo.closeFinger(pinkyServo);
      servo.closeFinger(indexServo);
      servo.closeFinger(middleServo);
      delay(OPEN_DELAY);
  }
}
