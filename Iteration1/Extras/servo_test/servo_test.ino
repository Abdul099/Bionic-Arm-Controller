#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();//default i2c address: 0x40

#define PWM_frequency 60
#define SERVOMIN  230    
#define SERVOMAX  410  
#define SERVOSPEED 5
int pos1 = 0;
int pos2 = 0;
int pos3 = 0;

int move_servo (int servo, int pos, int final_position, int cycles){ //min 2 cycles
  int real_end_pos = final_position+SERVOMIN;
  int i = 0;
  if (pos+SERVOMIN<real_end_pos){
  while(pos+SERVOMIN<real_end_pos){
    pwm.setPWM(0,0, pos+SERVOMIN);
    pwm.setPWM(1,0, pos+SERVOMIN);   
    pwm.setPWM(2,0, pos+SERVOMIN);
    delay(45);
    i++;
    pos+=SERVOSPEED;
    if (i>=cycles) break;    
  }
  } 
    if (pos+SERVOMIN>real_end_pos){
    while(pos+SERVOMIN>=real_end_pos){
      pwm.setPWM(0,0, pos+SERVOMIN);
      pwm.setPWM(1,0, pos+SERVOMIN);   
      pwm.setPWM(2,0, pos+SERVOMIN);
      delay(45);
      i++;
      pos-=SERVOSPEED;
      if (i>=cycles) break; 

      }    
   }
   return pos1;
 }
void sweep(){
  
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen+=SERVOSPEED) {
    pwm.setPWM(0, 0, pulselen);
    pwm.setPWM(1, 0, pulselen);
    pwm.setPWM(2, 0, pulselen);
    delay(45);
  }
  delay(100);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen-=SERVOSPEED) {
    pwm.setPWM(0, 0, pulselen);
    pwm.setPWM(1, 0, pulselen);
    pwm.setPWM(2, 0, pulselen);
    delay(45);
  }
   delay(100);
}
void setup() {
  pwm.begin();  
  pwm.setPWMFreq(PWM_frequency);  
  sweep();
  
}

void loop(){
pos1 = move_servo(0, pos1, 100, 1000);
pos2 = move_servo(1, pos2, 100, 1000);
pos3 = move_servo(2, pos2, 100, 1000);
delay(50);
pos1 = move_servo(0, pos1, 120, 1000);
pos2 = move_servo(1, pos2, 120, 1000);
pos3 = move_servo(2, pos2, 120, 1000);
delay(50);
pos1 = move_servo(0, pos1, 20, 1000);
pos2 = move_servo(1, pos2, 20, 1000);
pos2 = move_servo(2, pos2, 20, 1000);
delay(50);
pos1 = move_servo(0, pos1, 180, 1000);
pos2 = move_servo(1, pos2, 180, 1000);
pos2 = move_servo(2, pos2, 180, 1000);
}

  
  
