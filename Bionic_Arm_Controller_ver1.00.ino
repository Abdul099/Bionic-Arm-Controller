/*
  Project Name: Bionic Arm Controller ver 1.00
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 5, 2020
  Description: Simplified program that receives emg input via analog pin and outputs PWM signals to 3 servo motors. An all-or-none basis is used to drive the control,
               where a signal below a certain threshold causes the arm to open and a signal above the threshold causes the arm to close. The threshold is determined
               through calibration, which is done through the Arm_Calibration library.
*/

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arm_Calibration.h>
#include <Adafruit_GFX.h>
#include <Arm_Settings.h>

int pos1 = 175;   //servo positions
int pos2 = 0;
int pos3 = 175;
int amp1; 
int thresh;

Arm_Calibration Calibrate = Arm_Calibration(A0);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();//default i2c address: 0x40

void setup() {
  thresh = Calibrate.Calibrate();
  pwm.begin();
  pwm.setPWMFreq(PWM_frequency);
}

void loop() {
  amp1 = analogRead(emgpin1);//we start by reading the signal value from the emg sensor --> assign this value to amp
  Serial.print(1000);
  Serial.print(" ");
  Serial.print(0);
  Serial.print(" ");
  Serial.println(amp1);//print the amplitude to the graph
  
  if (amp1 > thresh) { //close the arm
    pwm.setPWM(indexServo, 0, 0 + SERVOMIN);
    pwm.setPWM(thumbServo, 0, 175 + SERVOMIN);
    pwm.setPWM(pinkyServo, 0, 0 + SERVOMIN);
    delay(flag_duration);
  }
  else { //open the arm
    pwm.setPWM(indexServo, 0, 150 + SERVOMIN);
    pwm.setPWM(thumbServo, 0, 0 + SERVOMIN);
    pwm.setPWM(pinkyServo, 0, 150 + SERVOMIN);
    delay(del);
  }
}
