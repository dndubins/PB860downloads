// scale.ino:  Report measured divs, volts, and weight to Serial Monitor
// Bail-Out program for Activity 7-1
// Author: D. Dubins
// Date: 17-Nov-25
// Libraries required: None
// Wiring:
// -------
// Uno - loadCellAmp
// GND - GND
// +5V - Vcc
// Vout - A1
// SW - D4
//
// Note:
// Connect MCU AREF pin to 3.3V.

#define NUMREADS 100  // number of readings for data smoothing
int weightPin = A1;
int buttonPin = 4;

float scaleSlope = 378.07;  // call weight
float scaleInt = -210.96;   // div intercept when scale is empty

float weight = 0.0;
float tareWeight = 0.0;
\
void setup() {
  analogReference(EXTERNAL);         // use external analog reference voltage of 3.3V
  pinMode(buttonPin, INPUT_PULLUP);  // Set up pin 4 as a button. Watch the logic here.
  Serial.begin(9600);                // Opens serial port, sets data rate to 9600 bps
  Serial.println("");
  Serial.println("Weight to Serial Output");  // Print header text to Serial monitor
  Serial.println("-----------------------");
  Serial.println("Divs (0-1023), Volts (V), Weight (g)");
  Serial.println("");
}

void loop() {
  int divs = analogRead(weightPin);                         // take a reading in divs
  float voltage = divs * 3.3 / 1023.0;                      // convert to volts
  weight = scaleInt + (scaleSlope * voltage) - tareWeight;  // calculate weight
  if (digitalRead(buttonPin) == LOW) {                      // if button is pushed
    Serial.println("**ZEROING***");                         // zero the scale
    delay(2000);                                            // debounce (finger pressed skews reading)
    divs = analogRead(weightPin);                           // take a reading in divs
    voltage = divs * 3.3 / 1023.0;                          // convert to volts
    weight = scaleInt + (scaleSlope * voltage);             // convert to weight
    tareWeight = weight;                                    // store weight to tareWeight, to get subtracted
  }
  Serial.print(divs);  // print divs to Serial Monitor
  Serial.print(", ");
  Serial.print(voltage, 3);  // print volts to Serial Monitor
  Serial.print(", ");
  Serial.println(weight, 1);  // print weight to Serial Monitor
  delay(100);
}  // End loop

