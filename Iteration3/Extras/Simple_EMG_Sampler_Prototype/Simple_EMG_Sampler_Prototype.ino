/*
 * Simple EMG Sampler Prototype
 * Authors: Theodore Janson and Abdullatif Hassan
 * Last Modified: June 23, 2020
 * Description: This sketch provides signal processing to the raw EMG input signal collected from the gravity dry-electrode emg sensor
 */

int emgPin = A0;
int dataMultiplier = 2;
int buffer_arrayLength = 8;
int baseline;

// Cycle buffer 
 struct _buffer {
  int index;   
  int window[8]; // Buffer window to rectify AC value: larger values yield less precise waveforms. 
  int sum;     //Sum over the buffer window
};
int updateBaseline(){
  long avg = 0;
  for(int i=0; i<100; i++){
    avg+= analogRead(A0);
    delay(10);
  }
  avg/=100;
 return avg;
}
/*
 * Update the cycle buffer for new average: LIFO
 * Subtract the last data value from the sum, add the next data value to the array and to the sum, reset the index. 
 */
void update_buffer(_buffer& b, int value){                                              
      b.sum -= b.window[b.index];                    
      b.window[b.index] = (value); 
      b.sum += (value);                                         
      b.index = (b.index + 1) % buffer_arrayLength; 
}

/* Get mean value of cycle buffer */
int average_buffer(_buffer& b){
  return b.sum / buffer_arrayLength;
}

struct _buffer myBuffer;

void setup() {
    //Initializing buffer struct 
    myBuffer.sum = 0;
    myBuffer.index = 0;
    for (int i = 0; i < buffer_arrayLength; i++) {
      myBuffer.window[i] = 0;
    }
     baseline = updateBaseline();
     Serial.begin(9600);
}

void loop() {
    int data = analogRead(emgPin);
    int filteredData = data-baseline;
    update_buffer(myBuffer, abs(filteredData));
    int envelope = average_buffer(myBuffer)*dataMultiplier;
    Serial.print(300);
    Serial.print(" ");
    Serial.print(0);
    Serial.print(" ");
    Serial.println(envelope);
    delay(5);
}
