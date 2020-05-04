#include <Arm_Calibration.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>


//constructors
Arm_Calibration::Arm_Calibration()
{
	_emg_pin = A0;
	_averageMin = 0;
	_averageMax = 0;
	Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
	display.setTextSize(2);   
    display.setTextColor(WHITE); 
}

Arm_Calibration::Arm_Calibration(int pin)
{
	_emg_pin = pin;
	_averageMin = 0;
	_averageMax = 0;
	Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
	display.setTextSize(2);   
    display.setTextColor(WHITE); 
}

//calibrate function
int Arm_Calibration::Calibrate()
{
	display.setCursor(0, 0);
	display.print("  Starting calibration");
	display.display();
	delay(500);
	display.print(("  Prepare to Relax"));
	display.display();
	display.clearDisplay();
 	delay(1000); //wait 1 second for patient to 
  	display.setCursor(0, 0);
  	display.println(("   Relax"));
  	display.display();
  	delay(1000); //wait for a second before we actually start sampling
  	
  	_timer = 0;
  	_startTime = millis();
  	_numberSamples = 0;
  	_averageMin = 0;
  
  	while (_timer < 10000) {  //rest for 10 seconds to find the min value
  		delay(10);
    	_amplitude = analogRead(pin);
    	Serial.print(1000);
    	Serial.print(" ");
    	Serial.print(0);
    	Serial.print(" ");
    	Serial.println(_amplitude);    //print the amplitude to the graph
    	_averageMin += _amplitude;
    	_numberSamples++;
    	_timer = millis() - _startTime;
	}

	display.clearDisplay();
	_averageMin +=_numberSamples;

	display.setCursor(0, 0);
  	display.println(("  Prepare   For Max"));
  	display.display();
  	delay(2000);                
  	display.clearDisplay();
  	display.setCursor(0, 0);
  	display.print(("   Fully    Contract"));
  	display.display();

  	_timer = 0
  	_numberSamples = 0;
  	_averageMax = 0;

  	while (_timer < 10000) {  //rest for 10 seconds to find the max value
  		delay(10);
    	_amplitude = analogRead(pin);
    	Serial.print(1000);
    	Serial.print(" ");
    	Serial.print(0);
    	Serial.print(" ");
    	Serial.println(_amplitude);    //print the amplitude to the graph
    	_averageMax += _amplitude;
    	_numberSamples++;
    	_timer = millis() - _startTime;
	}

	display.clearDisplay();
	_averageMin +=_numberSamples;
	
	display.setCursor(0, 0);
  	display.println(("  Computing Results"));
  	display.display();
  	delay(500);
  	display.setTextSize(1);
  	display.setCursor(0, 0);
  	display.print("Baseline:  ");
  	display.println(_averageMin);
  	display.print("Peak:");
  	display.println(_averageMax);
  	display.display();
  	delay(2000);
  	display.clearDisplay();
  	int threshold = _averageMin + 0.2 * _averageMax;
  	return threshold;
}

