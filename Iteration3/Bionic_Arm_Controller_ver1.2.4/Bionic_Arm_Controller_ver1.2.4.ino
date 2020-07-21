/*
  Project Name: Bionic Arm Controller ver 1.2.4
  Authors: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
           Theodore Janson
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: July 20, 2020
  Description: Arm Controller sketch that receives emg input via analog pin and outputs PWM signals for up to 5 servo motors. An all-or-none basis is used to drive the control,
               where a signal below a certain threshold causes the arm to remain in the same state (open/close) and  signal above the threshold causes the arm to change state. The threshold is determined
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
#include <Arm_Screen.h>

int amp1;
int thresh;
int counter = 0;
byte opened = 0;
short baseline;
Arm_Calibration Calibrate = Arm_Calibration();
Arm_Servo servo = Arm_Servo();
Arm_Demo demo = Arm_Demo();
Arm_Sampler sampler = Arm_Sampler();
Arm_Screen screen = Arm_Screen();

void setup() {
  Wire.begin();
  Serial.begin(9600);
  thresh = Calibrate.CalibrateDry(&baseline);
  servo.setup();
  screen.prepare();
  sampler.setBaseline(baseline);
}

void loop() {
  counter++;
  amp1 = sampler.simpleSample();//we start by reading the signal value from the emg sensor --> assign this value to amp
  opened = sampler.evaluateSampleFindPeak(amp1, thresh);
  if (LED_DEBUG_MODE) {
    switch (opened) {
      case 0:
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        break;
      case 1:
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        break;
      case 2:
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        delay(1000);
        break;
    }
  }
  else {
    if (opened ==2){//error in electrode
      screen.printToScreen("Misplaced  Electrode");
      delay(1000);
    }
    if (opened == 1) {
      screen.printToScreen("");
      servo.openFinger(thumbServo);
      servo.openFinger(pinkyServo);
      servo.openFinger(indexServo);
      servo.openFinger(middleServo);
      servo.openFinger(ringServo);
      delay(CLOSED_DELAY);
    }
    else {
      screen.printToScreen("");
      servo.closeFinger(thumbServo);
      servo.closeFinger(pinkyServo);
      servo.closeFinger(indexServo);
      servo.closeFinger(ringServo);
      servo.closeFinger(middleServo);
      delay(OPEN_DELAY);
    }
  }

//  if(counter>=50000 && opened){
//    sampler.updateBaseline();
//    counter = 0; //reset counter
//  }
}
