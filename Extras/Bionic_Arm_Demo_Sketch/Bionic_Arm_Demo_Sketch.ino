/*
  Project Name: Bionic Arm Demo Sketch
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 12, 2020
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

Arm_Servo servo = Arm_Servo();
Arm_Demo demo = Arm_Demo();

void setup() {
  Serial.begin(9600);
  servo.setup();
  demo.runDemo();
}

void loop() {
  // put your main code here, to run repeatedly:

}
