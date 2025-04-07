/* RTC.ino: Date and time functions using a DS1307 RTC (real time clock) 
 * connected via I2C and Wire lib.
 * Author: D. Dubins
 * Date: 07-Apr-25
 * Adapted from: timestamp.h, Adafruit RTClib v2.1.4
 * 
 * This program requires the RTClib by Adafruit library, 
 * available through the Library Manager.
 * Last compiled with RTClib v2.1.4.
 * 
 * Connections:
 * RTC DS1307 - Uno:
 * ------------------
 * GND - GND
 * Vcc - 5V
 * SDA - SDA
 * SCL - SCL
 * SQW - NC (not connected)
 */

#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>

RTC_DS1307 RTC;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
  } else {
    // The following two lines sets the RTC to the date & time the sketch compiles.
    // Uncomment it & upload to set the time, date and start run the RTC.
    // This only needs to be set once for the RTC to keep track of time.
    Serial.println("Setting the RTC to the current date and time...");
    RTC.adjust(DateTime(__DATE__, __TIME__));
    // To set the time to an explicit date/time manually
    // (for the below example, April 7, 2025 at 3:00pm):
    //RTC.adjust(DateTime(2025, 4, 7, 15, 0, 0));
  }
}

void loop() {
  DateTime now = RTC.now();
  Serial.print(timeStamp(now));
  Serial.print(", "); // print comma for CSV format
  Serial.println(analogRead(A0));  // print some measured reading after timestamp
  delay(1000);
}

String timeStamp(DateTime t) {
  String stamp="";
  stamp+=String(t.year(), DEC);              // add year to string
  stamp+="/";
  stamp+=String(t.month() < 10 ? "0" : "");  // print leading zero if needed
  stamp+=String(t.month(), DEC);             // add month to string
  stamp+="/";
  stamp+=String(t.day() < 10 ? "0" : "");    // print leading zero if needed
  stamp+=String(t.day(), DEC);               // add day to string
  stamp+=" ";
  stamp+=String(t.hour() < 10 ? "0" : "");   // print leading zero if needed
  stamp+=String(t.hour(), DEC);              // add hours to string
  stamp+=":";
  stamp+=String(t.minute() < 10 ? "0" : "");  // print leading zero if needed
  stamp+=String(t.minute(), DEC);             // add minutes to string
  stamp+=":";
  stamp+=String(t.second() < 10 ? "0" : "");  // print leading zero if needed
  stamp+=String(t.second(), DEC);             // add seconds to string
  return stamp;
}
