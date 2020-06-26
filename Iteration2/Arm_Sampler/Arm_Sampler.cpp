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
	hold = 1;
	previousState = 0;
	currentState = 0;
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
	hold = 1;
	previousState = 0;
	currentState = 0;
	myBuffer.sum = 0;
	myBuffer.index = 0;
	for (int i = 0; i < buffer_arrayLength; i++) {
      myBuffer.window[i] = 0;
    }
}

// byte Arm_Sampler::evaluateSample(int signal, int threshhigh, int threshlow)
// {
// 	if(_count)
// 	else{
		
// 		if(signal > 300){
// 			return 2; 
// 		}
// 		else if(signal>=threshhigh) {
// 				_open = 0;
// 				_count = 0;
// 				return 1;
// 			}

// 		else if(!_open && signal>=threshlow){
// 				_open = 0;
// 				return 1;
// 			}
// 		else {
// 				_open = 1;
// 				return 0;//remain open
// 			}
// 		}
// }
byte Arm_Sampler::evaluateSample(int signal, int threshhigh, int threshlow)
{
		byte holds[3];
		holds[0] = 1;
		holds[1] = 60;
		holds[2] = 0;

		hold = holds[previousState];
		if(signal > 300){
			currentState = 2; 
		}
		else if(signal>=threshhigh) {
				_open = 0;
				_count = 0;
				currentState =  1;
			}

		else if(!_open && signal>=threshlow){
				_open = 0;
				currentState =  1;
				hold = 2;
			}
		else {
				_open = 1;
				currentState = 0;//remain open
			}

		if (previousState == currentState){
			_count = 0;
		}
		else{//if state changes
			if(_count>=hold){
				previousState = currentState;
				_count = 0; //reset counter
			}
			else{
				_count++;
			}
		}
		return previousState;
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
	int i = 0;
	while(counter >0){
		int reading = simpleSample();
		if (reading<=val) counter--; 
		else counter = duration; //reset the counter
		i++;
		if(i%60 == 0) updateBaseline();
	}
	delay(10);
}

void Arm_Sampler::updateBaseline(){
  long avg = 0;
  if(base == 0){
  for(int i=0; i<100; i++){
    avg+= analogRead(A0);
    delay(10);
  }
  avg/=100;
  base = avg;
}
else{
  avg = 0;
  for(int i=0; i<100; i++){
    avg+= simpleSample();
  }
  avg/=100;
  base = avg;
}
}

int Arm_Sampler::read()
{
  	int raw = analogRead(_pin);
  	raw = abs(raw-base);
  	updateBuffer(myBuffer, raw);
  	raw = averageBuffer(myBuffer);
  	raw *=2; 
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
