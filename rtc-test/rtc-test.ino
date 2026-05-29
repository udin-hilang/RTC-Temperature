/*
 * Project: DS1302 Real-Time Clock Reader
 * Description: Simple program to read time data from a DS1302 RTC module 
 * and print it to the Serial Monitor every minute.
 */

#include <RtcDS1302.h>
#include <ThreeWire.h>

// Define communication pins (I/O, CLK, RST)
ThreeWire myWire(25, 26, 33);

// Initialize the RTC object
RtcDS1302<ThreeWire> rtc(myWire);

// Variable to track the previous minute to avoid constant serial spam
int prevMinute = 0;

void setup() {
  Serial.begin(115200);
  
  // Start communication with the RTC module
  rtc.Begin();
  
  // Uncomment the line below to sync the RTC time with your PC's compile time
  // rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
}

void loop() {
  // Get the current time from the RTC
  RtcDateTime now = rtc.GetDateTime();
  
  // Check if the minute has changed
  if(now.Minute() != prevMinute) {
    printTime();
  }
  
  // Update the tracker so the check works for the next minute
  prevMinute = now.Minute();
}

// Function to output the time to the Serial Monitor
void printTime() {
  RtcDateTime now = rtc.GetDateTime();
  
  Serial.print(now.Hour());
  Serial.print(" : ");
  Serial.println(now.Minute());
  
  // Optional: display seconds (uncomment if needed)
  // Serial.print(" : ");
  // Serial.println(now.Second());
}
