/*
  Authors: Abdullatif Hassan, Theodore Janson
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated:June 22, 2020
*/

#include <Arm_Sampler.h>
#include <Arm_Settings.h>
#include "Arduino.h"
#include "EMGFilters.h"

//constructor
Arm_Sampler::Arm_Sampler()
{
	_open = 1;
	_count = 0;
	_pin = A0;
	base = 0;
	myBuffer.sum = 0;
	myBuffer.index = 0;
	for (int i = 0; i < buffer_arrayLength; i++) {
      myBuffer.window[i] = 0;
    }
}

Arm_Sampler::Arm_Sampler(int pin)
{
	_open = 1;
	_count = 0;
	_pin = pin;
	base = 0;
	myBuffer.sum = 0;
	myBuffer.index = 0;
	for (int i = 0; i < buffer_arrayLength; i++) {
      myBuffer.window[i] = 0;
    }
}

// byte Arm_Sampler::evaluateSample(int signal, int threshhigh, int threshlow)
// {
// 	if(signal > 300){
// 		_count = 0;
// 		return 2; 
// 	}
// 	if(_open){
// 		if(signal>=threshhigh) _count++;
// 		else _count = 0; //reset counter because the strak is broken
// 		if(_count>=THRESHOLD_TOLERENCE){ //if enough readings have been registered above threshold 
// 			_count = 0; //reset the count variable
// 			_open = 0; //close the arm
// 			return 0; //close the arm
// 		}
// 		else return 1;//remain open
// 	}

// 	else{ //if in closed state
// 		if(signal<threshlow) _count++; // if the signal falls below the threshold, start counting
// 		else _count = 0;
// 		if(_count>=THRESHOLD_TOLERENCE2){
// 			_count = 0;
// 			_open = 1;//open the hand
// 			return 1;
// 		}
// 		else return 0; //keep closed
// 	}
// }

byte Arm_Sampler::evaluateSample(int signal, int threshhigh, int threshlow)
{
	if(signal > 300){
		_count = 0;
		return 2; 
	}
		if(signal>=threshhigh) return 1;

		else return 0;//remain open
	}

	

int Arm_Sampler::simpleSample()
{
	int sample = read();
	delay(10);
	Serial.println(sample);
	return sample; 
}

int Arm_Sampler::simpleSample(byte del)
{
	int sample = read();
	delay(del);
	Serial.println(sample);
	return sample; 
}

void Arm_Sampler::checkBelow(int val, byte duration){
	short counter = duration; 
	while(counter >0){
		int reading = simpleSample();
		if (reading<=val) counter--; 
		else counter = duration; //reset the counter
	}
	delay(10);
}

void Arm_Sampler::updateBaseline(){
  long avg = 0;
  for(int i=0; i<100; i++){
    avg+= analogRead(A0);
    delay(10);
  }
  avg/=100;
  base = avg;
}

int Arm_Sampler::read()
{
  	int raw = analogRead(_pin);
  	raw = abs(raw-base);
  	updateBuffer(myBuffer, raw);
  	raw = averageBuffer(myBuffer);
  	raw = raw*4; 
  	return raw;
}

void Arm_Sampler::setBaseline(short value)
{
	base = value;
}

int Arm_Sampler::getBaseline()
{
	return base; 
}


//private methods
void Arm_Sampler::updateBuffer(_buffer& b, int value){                                              
      b.sum -= b.window[b.index];                    
      b.window[b.index] = (value); 
      b.sum += (value);                                         
      b.index = (b.index + 1) % buffer_arrayLength; 
}

/* Get mean value of cycle buffer */
int Arm_Sampler::averageBuffer(_buffer& b){
  return b.sum / buffer_arrayLength;
}
