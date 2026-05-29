#include <RtcDS1302.h>
#include <ThreeWire.h>
#include <DallasTemperature.h>
#include <OneWire.h>

//===(SETUP DS18B20)===>TEMPERATURE
#define sensorPin 5
OneWire oneWire(sensorPin);
DallasTemperature sensor(&oneWire);

//===(SETUP DS1302)===>RTC
ThreeWire myWire(26, 25, 27);
RtcDS1302<ThreeWire> rtc(myWire);

//float temp;

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT_PULLUP);
  sensor.begin();
  rtc.Begin();
  //============================(RUN ONCE TO SET THE TIME)============================//
  //rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
  //RtcDateTime now = rtc.GetDateTime();
  //=========(code dibawah untuk mengejar ketertinggalan dengan waktu aktual)=========//
  //rtc.SetDateTime(RtcDateTime(now.Year(), now.Month(), now.Day(), now.Hour(), now.Minute(), (now.Second() + 13)));
}

void loop() {
  RtcDateTime now = rtc.GetDateTime();
  sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  Serial.printf("%d/%d/%d %d:%d:%d == %.1f°C\n", now.Day(), now.Month(), now.Year(), now.Hour(), now.Minute(), now.Second(), temp);
  delay(5000);
}
