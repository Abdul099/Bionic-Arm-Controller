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
short hold = 0;
unsigned long timeStamp;
unsigned long timeBudget;

void setup() {
  myFilter.init(sampleRate, humFreq, true, true, true);

  // open serial
  Serial.begin(115200);
  timeBudget = 1e6 / sampleRate;
  // micros will overflow and auto return to zero every 70 minutes
}

void loop() {
  timeStamp = micros();

  int Value = analogRead(SensorInputPin);
  int DataAfterFilter = myFilter.update(Value);
  int envlope = sq(DataAfterFilter);

  if (envlope > 10000) {
    envlope = 0;
    num = 2;
    hold = 10;
  }
  else if (envlope < 100) num = 0;
  else {
    num = 1;
    hold = 20;
  }
  Serial.println(envlope);
  LightLED(num);
  if(hold!=0) hold-=1;
  delay(10);
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
