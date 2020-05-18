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
	screen.printToScreen("  Prepare  to Relax");
 	delay(1000); 
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
 	screen.printToScreen(" Prepare   to      Contract");
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
	screen.printToScreen(" Computing Results");
  	delay(500);
	screen.printToScreen("Min", _averageMin);
	delay(1000);
	screen.printToScreen("MAX:", _averageMax);
	delay(1000);
	// screen.printToScreen("Thresh", threshold);
	// delay(2000);
	screen.printToScreen("Done Calibration");
   	return threshold;
}

int Arm_Calibration::CalibrateAdvanced(int samples)
{
	Arm_Screen screen = Arm_Screen();
	screen.prepare();
	// screen.printToScreen(" Ready to Calibrate");
	// delay(500);
	screen.printToScreen(" Prepare    to Relax");
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
	screen.printToScreen("Contract  Fully");

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

	int* threshs = (int*) malloc(10*sizeof(int));;//possible to use struct
	int* threshscores = (int*) malloc(10*sizeof(int));;
    int* trainingData = (int*) malloc(5*sizeof(int));
    
	for (int i = 0; i<10; i++){
		threshs[i] = _averageMin+((i)*(_averageMax - _averageMin))/10;//fill each array element with a candidate threshold value
		threshscores[i] = 0;//initialize an array of zeros
	}

	for (int i = 0; i<5; i++){
  		trainingData[i] = 0;
	}
	for (int i = 0; i<5; i++){
  		Serial.println(trainingData[i]);
	}

	for(int c = 0; c<NUM_CONTRACTIONS; c++){ // for each contraction
		screen.printToScreen("Contract", c+1);

		for(int i =0; i<5; i++){
			delay(50);
			_amplitude = analogRead(_emg_pin);
			printToLaptop(_amplitude);
			trainingData[i] = _amplitude;
		}

		for(int i = 0; i<10; i++){//for each candidate
			bool added = 0;
			for(int j = 0; j<5; j++){
				if(!added && trainingData[j]>threshs[i]){
					threshscores[i]++;
					added = 1;
				}
			}
		}

		screen.printToScreen("Wait");
		delay(1000);
    }

	free(trainingData);

	int selectedIndex;

	for (int i=0; i<10; i++){
		Serial.print(i);
		Serial.print(": ");
		Serial.println(threshscores[i]);
	}

	for(int i=9; i>0; i--){ 
		if(threshscores[i]>=9){
			selectedIndex = i;
			break;
		}
	}

    int threshold = threshs[selectedIndex];

    screen.printToScreen("Results:");
   	delay(500);
    screen.printToScreen("Min", _averageMin);
    delay(1000);
    screen.printToScreen("MAX", _averageMax);
    delay(1000);
    screen.printToScreen("Index", selectedIndex);
	delay(1000);
	screen.printToScreen("Thresh",threshold);
	delay(2000);

	screen.printToScreen("Done");
   	return 1000;
}

void Arm_Calibration::printToLaptop(int val)
{
    Serial.print(1000);
   	Serial.print(" ");
   	Serial.print(0);
   	Serial.print(" ");
   	Serial.println(val);
}