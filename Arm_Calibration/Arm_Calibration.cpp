/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 11, 2020
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
}

Arm_Calibration::Arm_Calibration(int pin)
{
	_emg_pin = pin;
	_averageMin = 0;
	_averageMax = 0;
}

//calibrate function
int Arm_Calibration::Calibrate(int samples)
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
  
  	while (_numberSamples < samples) {  ///take 1000 samples at 100 HZ ~ 10s
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

   	while (_numberSamples < samples) {  //rest for 10 seconds to find the max value
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
	screen.printToScreen("Min", _averageMin);
	delay(1000);
	screen.printToScreen("MAX:", _averageMax);
	delay(1000);
	screen.printToScreen("Thresh", threshold);
	delay(2000);
	//screen.printToScreen("Done Calibration");
   	return threshold;
}

int Arm_Calibration::CalibrateAdvanced(int samples)
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
  
  	while (_numberSamples < samples) {  ///take 1000 samples at 100 HZ ~ 10s
  		delay(10);
     	_amplitude = analogRead(_emg_pin);
	 	printToLaptop(_amplitude);    //print the amplitude to the graph
    	_averageMin += _amplitude;
    	_numberSamples++;
	 }

	 _averageMin /=_numberSamples;
 	screen.printToScreen("  Prepare   to     Contract");
   	delay(2000);                
	screen.printToScreen("  Contract Fully");

  	_numberSamples = 0;
  	_averageMax = 0;

   	while (_numberSamples < samples) {  //rest for 10 seconds to find the max value
  		delay(10);
    	_amplitude = analogRead(_emg_pin);
		printToLaptop(_amplitude);  //print the amplitude to the graph
     	_averageMax += _amplitude;
    	_numberSamples++;
	}

	_averageMax /=_numberSamples;

	int threshs[10];
	int threshscores[10];
	int buffers[10];
	int trainingData[samples*2];
	
	for (int i = 0; i<10; i++){
		threshs[i] = _averageMin+(i/10)*(_averageMax - _averageMin);//fill each array element with a candidate threshold value
		threshscores[i] = 0;//initialize an array of zeros
		buffers[i] = 0; //another array of zeros
	}

	screen.printToScreen("Perform 10 Contractions");
	for(int i =0; i<_numberSamples; i++){
		delay(10);
		_amplitude = analogRead(_emg_pin);
		printToLaptop(_amplitude);
		trainingData[i] = _amplitude;
	}

	for(int i=0; i<_numberSamples; i++){
		for(int j=0; j<10; j++){
			if(trainingData[i] > threshs[j] && buffers[j] >=0){
				threshscores[j]++;
				buffers[j] = BUFFER_WIDTH;
			} 
			else {
				buffers[j]--;
			}
		}
	}

	byte selectedIndex;

	for(int i=10; i>0; i--){
		if(threshscores[i]>NUM_CONTRACTIONS){
			selectedIndex = i;
			break;
		}
	}

	int threshold = threshs[selectedIndex];

	screen.printToScreen("  Computing Results");
  	delay(500);
	screen.printToScreen("Min", _averageMin);
	delay(1000);
	screen.printToScreen("MAX", _averageMax);
	delay(1000);
	screen.printToScreen("Index", selectedIndex);
	delay(1000);
	screen.printToScreen("Thresh", threshold);
	delay(2000);

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