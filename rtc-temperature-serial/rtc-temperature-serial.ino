/*
 * Project: Integrated RTC & Temperature Monitor
 * Description: Reads time from a DS1302 RTC module and temperature 
 * from a DS18B20 sensor, then prints both to the Serial Monitor.
 */

#include <RtcDS1302.h>
#include <ThreeWire.h>
#include <DallasTemperature.h>
#include <OneWire.h>

// --- Setup for DS18B20 (Temperature) ---
#define sensorPin 5
OneWire oneWire(sensorPin);
DallasTemperature sensor(&oneWire);

// --- Setup for DS1302 (RTC) ---
// Pins: I/O, CLK, RST
ThreeWire myWire(26, 25, 27);
RtcDS1302<ThreeWire> rtc(myWire);

void setup() {
  Serial.begin(115200);
  
  // Configure sensor pin and initialize devices
  pinMode(sensorPin, INPUT_PULLUP);
  sensor.begin();
  rtc.Begin();

  /* * Calibration Section:
   * Uncomment the lines below to set the RTC time or adjust for time drift.
   */
  // rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
  
  // RtcDateTime now = rtc.GetDateTime();
  // rtc.SetDateTime(RtcDateTime(now.Year(), now.Month(), now.Day(), now.Hour(), now.Minute(), (now.Second() + 13)));
}

void loop() {
  // Retrieve current time from RTC
  RtcDateTime now = rtc.GetDateTime();
  
  // Request and read temperature from the sensor
  sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  
  // Output formatted date, time, and temperature to Serial
  Serial.printf("%d/%d/%d %d:%d:%d == %.1f°C\n", 
                now.Day(), now.Month(), now.Year(), 
                now.Hour(), now.Minute(), now.Second(), 
                temp);
  
  // Wait 5 seconds before the next loop
  delay(5000);
}
