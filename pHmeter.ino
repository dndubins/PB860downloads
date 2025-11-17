// pHmeter.ino: Report measured divs, volts, and pH to Serial Monitor
// Bail-Out program for Activity 7-2
// Author: D. Dubins
// Date: 17-Nov-25
// Libraries required: None
// Wiring:
// -------
// Uno - phAmplifier
// GND - GND
// +5V - V+
// A1 - Vout
//
// Note:
// Connect MCU AREF pin to 3.3V.

byte pHPin = A1;                  // Declaring the Analog input to be Pin A2 of Arduino board.
float probeSlope = -5.333333333;  // Ideal slope, dpH/dVolts, should be negative
float probeInt = 16.14933333;     // Ideal intercept (in pH units)

void setup() {
  Serial.begin(9600);         // Start the Serial Monitor
  analogReference(EXTERNAL);  // use AREF for reference voltage. Run the 3.3V out to the Aref pin on the Arduino.
  Serial.println("");         // Results in less first-line garbage when printing to Serial monitor
  Serial.println("pH to Serial"); // Print header
  Serial.println("------------");
  Serial.println("Divs (0-1023), Volts (V), pH");
  Serial.println("");
}

void loop() {
  int div = analogRead(pHPin);               // get divs
  float volts = div * 3.3 / 1023.0;          // get divs and convert to volts
  float pH = volts * probeSlope + probeInt;  // convert volts to pH
  Serial.print(div);                         // print to serial monitor
  Serial.print(",  ");
  Serial.print(volts, 3);  // print to serial monitor
  Serial.print(",  ");
  Serial.println(pH, 1);
  delay(250);
}
