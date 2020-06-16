#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "EMGFilters.h"
#define SensorInputPin A0 // input pin number

EMGFilters myFilter;
int sampleRate = SAMPLE_FREQ_1000HZ;
int humFreq = NOTCH_FREQ_60HZ;
short num = 0;
long total = 0;
int average = 0;

int reading;
short hold = 0;
const int numReadings = 5;
int readings[numReadings];
short readIndex = 0;


void setup() {
  myFilter.init(sampleRate, humFreq, true, true, true);
  Serial.begin(115200);

  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  reading = sample();
  if (reading > 10000) {
    num = 2;
  }
  else {
    total = total - readings[readIndex];
    readings[readIndex] = reading;
    total = total + readings [readIndex];
    average = total/numReadings;
    average = reading;
    Serial.println(average);
    readIndex = (readIndex+1)%readIndex;
    if (average > 300) {
      num = 1;
      hold = 50;
    }
    else if (average > 50 && average <= 200 && num == 1) { //steady open state
      num = 1;
      hold = 50;
    }
    else {
      num = 0;
    }
  }
    switch (num) {
      case 0:
      if(hold != 0) break;
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
  
  if (hold > 0) hold --;
  delay(10);
}

int sample() {
  int Value = analogRead(SensorInputPin);
  int DataAfterFilter = myFilter.update(Value);
  int envlope = sq(DataAfterFilter);
  return envlope;
}
