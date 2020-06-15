#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "EMGFilters.h"
#define TIMING_DEBUG 1
#define SensorInputPin A0 // input pin number

EMGFilters myFilter;
int sampleRate = SAMPLE_FREQ_1000HZ;
int humFreq = NOTCH_FREQ_50HZ;
short num;
int reading; 
short hold = 0;

void setup() {
  myFilter.init(sampleRate, humFreq, true, true, true);
  Serial.begin(115200);
}

void loop() {
  reading = sample();
  Serial.println(reading);
  if (reading > 10000) {
    reading = 0;
    num = 2;
    hold = 10;
  }
  else if (reading < 100) num = 0;
  else {
    num = 1;
    hold = 20;
  }
  LightLED(num);
  if(hold>0) hold-=1;
  delay(10);
}

int sample(){
  int Value = analogRead(SensorInputPin);
  int DataAfterFilter = myFilter.update(Value);
  int envlope = sq(DataAfterFilter);
  return envlope;
}

void LightLED(int number) {
  if (hold == 0 || number !=0) {
    switch (number) {
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
}
