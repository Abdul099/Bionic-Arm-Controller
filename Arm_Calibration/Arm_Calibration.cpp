/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 18, 2020
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
	screen.printToScreen("Thresh", threshold);
	delay(2000);
	screen.printToScreen("Done Calibration");
   	return threshold;
}

int Arm_Calibration::CalibrateAdvanced(int samples)
{
	Arm_Screen screen = Arm_Screen();
	screen.prepare();
	// screen.printToScreen(" Ready to Calibrate");
	// delay(500);
	screen.printToScreen("Prepare   to Relax");
 	delay(1000); //wait 1 second for patient to 
	screen.printToScreen("Relax");
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
 	screen.printToScreen("Prepare   to        Contract");
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

	struct candidate{
		unsigned int threshVal : 10;
		unsigned int score : 6;
	};

	candidate candidates[10];
    uint8_t* trainingData = (uint8_t*) malloc(SIZE_TRAININGDATA*sizeof(uint8_t));
    
	for (int i = 0; i<10; i++){
		candidates[i].threshVal = _averageMin+((i)*(_averageMax - _averageMin))/10;//fill each array element with a candidate threshold value
		candidates[i].score = 0;//initialize an array of zeros
	}

	for (int i = 0; i<SIZE_TRAININGDATA; i++){
  		trainingData[i] = 0;
	}

	for(int c = 0; c<NUM_CONTRACTIONS; c++){ // for each contraction
		screen.printToScreen("Contract", c+1);

		for(int i =0; i<SIZE_TRAININGDATA; i++){
			delay(50);
			_amplitude = analogRead(_emg_pin);
			printToLaptop(_amplitude);
			trainingData[i] = _amplitude/4; //compress the 10 bit ADC reading into an 8bit in order to store it
		}

		for(int i = 0; i<10; i++){//for each candidate
			bool added = 0;
			for(int j = 0; j<5; j++){
				if(!added && (trainingData[j]*4)>candidates[i].threshVal){ //decompress the value from training data and compare it
					candidates[i].score++;
					added = 1;
				}
			}
		}

		screen.printToScreen("Wait");
		delay(1000);
    }

	for (int i = 0; i<SIZE_TRAININGDATA; i++){
  		Serial.println(trainingData[i]);
	}

	free(trainingData);

	int selectedIndex;

	for (int i=0; i<10; i++){
		Serial.print(i);
		Serial.print(": ");
		Serial.println(candidates[i].score);
	}

	for(int i=9; i>0; i--){ 
		if(candidates[i].score>=8){ // aim at capturing 80 percent of contractions
			selectedIndex = i;
			break;
		}
	}

    int threshold = candidates[selectedIndex].threshVal;

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