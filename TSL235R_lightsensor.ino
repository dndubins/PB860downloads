// TSL235R Light to Frequency Converter
// Written by: David Dubins 27-Nov-18
// Last updated: 22-Dec-22
//
// Wiring:
// -------
// TSL235R -- Uno:
// Pin 1 -- GND
// Pin 2 -- +5V
// Pin 3 -- Pin 2 (this is INTO)
// Pin2 -- 0.1 uF -- Pin 1

#define TSL235R_OUT 2 // use pin 2 to detect signal

// variables changed in ISRs should be volatile:
volatile unsigned long counter=0;

void setup(){
  Serial.begin(9600);
  pinMode(TSL235R_OUT, INPUT_PULLUP); //use internal pullup pin2
}

void loop(){
  // read sensor with 1 sec integration time
  unsigned long freq=readTSL235R(100); // read 100 msec of rising pulses
  Serial.println(freq); // return freq in Hz
}

unsigned long readTSL235R(int t){ // t is integration time
  //t=100 msec: can measure up to ~140 kHz
  counter=0; // reset counter
  // for the Uno, 0 is INT0 (pin 2), 1 is INT1 (pin 3)
  // The following command attaches an interrupt triggered by rising signal to INT0.
  // When the interrupt triggers, the void function countFreq() will run.
  attachInterrupt(0, countFreq, RISING); 
  delay(t); // wait a bit to collect data
  unsigned long hertz=counter*1000/t; // calculate frequency in Hz
  detachInterrupt(0); // detatch interrupt
  return hertz;  // return the frequency
}

void countFreq(){  // ISR for measuring frequency 
  //(advance counter on rising signal)
  counter++;   // increase the counter
}
