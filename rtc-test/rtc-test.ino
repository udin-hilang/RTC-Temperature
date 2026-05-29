#include <RtcDS1302.h>
#include <ThreeWire.h>

//              (I/O, CLK, RST)
ThreeWire myWire(25, 26, 33);

RtcDS1302<ThreeWire> rtc(myWire);

int prevMinute = 0;

void setup() {
  Serial.begin(115200);
  rtc.Begin();
  // rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
}

void loop() {
  RtcDateTime now = rtc.GetDateTime();
  if(now.Minute() != prevMinute) {
    printTime();
  }
  prevMinute = now.Minute();
}

void printTime() {
  RtcDateTime now = rtc.GetDateTime();
  Serial.print(now.Hour());
  Serial.print(" : ");
  Serial.println(now.Minute());
  // Serial.print(" : ");
  // Serial.println(now.Second());
}
