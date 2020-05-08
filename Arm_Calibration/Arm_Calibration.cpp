/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 7, 2020

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
	screen.printToScreen("beyz");
	delay(1000);
	Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //lcd screen setup
    display.clearDisplay();
	display.setTextSize(2);   
    display.setTextColor(WHITE); 
	display.setCursor(0, 0);
	display.println("  Starting  Calibration");
	display.display();
	delay(500);
	display.clearDisplay();
	display.setCursor(0, 0);
	display.println(("  Prepare   to Relax"));
	display.display();
 	delay(1000); //wait 1 second for patient to 
 	display.clearDisplay();
  	display.setCursor(0, 0);
  	display.println(("   Relax "));
  	display.display();
  	delay(1000); //wait for a second before we actually start sampling

  	_numberSamples = 0;
  	_averageMin = 0;
  
  	while (_numberSamples < 1000) {  //rest for 10 seconds to find the min value
  		delay(10);
    	_amplitude = analogRead(_emg_pin);
		printToLaptop(_amplitude);    //print the amplitude to the graph
    	_averageMin += _amplitude;
    	_numberSamples++;
	}

	display.clearDisplay();
	_averageMin /=_numberSamples;

	display.setCursor(0, 0);
  	display.println(("  Prepare   For Max"));
  	display.display();
  	delay(2000);                
  	display.clearDisplay();
  	display.setCursor(0, 0);
  	display.println(("   Fully    Contract"));
  	display.display();

  	_numberSamples = 0;
  	_averageMax = 0;

  	while (_numberSamples < 1000) {  //rest for 10 seconds to find the max value
  		delay(10);
    	_amplitude = analogRead(_emg_pin);
		printToLaptop(_amplitude);  //print the amplitude to the graph
    	_averageMax += _amplitude;
    	_numberSamples++;
	}

	display.clearDisplay();
	_averageMax /=_numberSamples;
	
	int threshold = _averageMin + 0.2 * (_averageMax - _averageMin);
	
	display.setCursor(0, 0);
  	display.println(("  Computing Results"));
  	display.display();
  	delay(500);
  	display.clearDisplay();
  	display.setTextSize(1);
  	display.setCursor(0, 0);
  	display.print("Baseline:  ");
  	display.println(_averageMin);
  	display.print("Peak:");
  	display.println(_averageMax);
  	display.display();
  	display.print("Threshold:");
  	display.println(threshold);
  	display.display();
  	delay(2000);
  	display.clearDisplay();

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
