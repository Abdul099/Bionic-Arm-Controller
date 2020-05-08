/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 8, 2020

*/
#include <Arduino.h>
#include <Arm_Calibration.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Arm_Settings.h>
#include <Arm_Screen.h>

//constructors
Arm_Calibration::Arm_Calibration()
{
	_emg_pin = A0;
	_averageMin = 0;
	_averageMax = 0;
	// display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //lcd screen setup
   // display.clearDisplay();
	// display.setTextSize(2);   
 //    display.setTextColor(WHITE); 
}

Arm_Calibration::Arm_Calibration(int pin)
{
	_emg_pin = pin;
	_averageMin = 0;
	_averageMax = 0;
}

//calibrate function
int Arm_Calibration::Calibrate()
{
	Arm_Screen screen = Arm_Screen();
	screen.prepare();
	screen.printToScreen(" Ready to Calibrate");
	delay(500);
	screen.printToScreen("  Prepare   to Relax");
 	delay(1000); //wait 1 second for patient to 
	screen.printToScreen("  Relax");
   	delay(1000); //wait for a second before we actually start sampling

   	_numberSamples = 0;
   	_averageMin = 0;
  
  	while (_numberSamples < 1000) {  ///take 1000 samples at 100 HZ ~ 10s
  		delay(10);
     	_amplitude = analogRead(_emg_pin);
	 	printToLaptop(_amplitude);    //print the amplitude to the graph
    	_averageMin += _amplitude;
    	_numberSamples++;
	 }

	 _averageMin /=_numberSamples;
 	screen.printToScreen("  Prepare   to      Contract");
   	delay(2000);                
	screen.printToScreen("  Contract Fully");

  	_numberSamples = 0;
  	_averageMax = 0;

   	while (_numberSamples < 1000) {  //rest for 10 seconds to find the max value
  		delay(10);
    	_amplitude = analogRead(_emg_pin);
		printToLaptop(_amplitude);  //print the amplitude to the graph
     	_averageMax += _amplitude;
    	_numberSamples++;
	}

	_averageMax /=_numberSamples;
	int threshold = _averageMin + 0.2 * (_averageMax - _averageMin);
	screen.printToScreen("  Computing Results");
  	delay(500);
	screen.printToScreen(_averageMin);
	delay(1000);
	screen.printToScreen(_averageMax);
	delay(1000);
	screen.printToScreen(threshold);
   	return threshold;
}

void Arm_Calibration::printToLaptop(int val)
{
    Serial.print(1000);
   	Serial.print(" ");
   	Serial.print(0);
   	Serial.print(" ");
   	Serial.println(val);
}
