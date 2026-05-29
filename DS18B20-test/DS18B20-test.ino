#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(5);

DallasTemperature sensor(&oneWire);

void setup() {
  Serial.begin(115200);
  pinMode(5, INPUT_PULLUP);
  sensor.begin();
}

void loop() {
  sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  Serial.printf("%.1f C\n", temp);
  delay(1000);
}
