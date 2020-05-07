
/*
  Project Name: Bionic Arm Controller ver 1.0.2
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 6, 2020
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

int pos1 = 175;   //servo positions
int pos2 = 0;          
int pos3 = 175;
int amp1; 
int thresh;

Arm_Calibration Calibrate = Arm_Calibration();
Arm_Servo servo = Arm_Servo();
Arm_Demo demo = Arm_Demo();

void setup() {
  Serial.begin(9600);
  thresh = Calibrate.Calibrate();
  //thresh = 200;
  servo.setup();
  demo.runDemo();
}

void loop() {
  amp1 = analogRead(A0);//we start by reading the signal value from the emg sensor --> assign this value to amp
  Serial.print(1000);
  Serial.print(" ");
  Serial.print(0);
  Serial.print(" ");
  Serial.println(amp1);//print the amplitude to the graph
  
  if (amp1 > thresh) { //close the arm
    servo.closeFinger(thumbServo);
    servo.closeFinger(pinkyServo);
    servo.closeFinger(indexServo);
    delay(flag_duration);
  }
  else { //open the arm
    servo.openFinger(thumbServo);
    servo.openFinger(pinkyServo);
    servo.openFinger(indexServo);
    delay(del);
  }
}
