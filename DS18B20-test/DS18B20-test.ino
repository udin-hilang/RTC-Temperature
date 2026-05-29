/*
 * Project: DS18B20 Temperature Sensor Reader
 * Description: Reads temperature data from a DS18B20 sensor 
 * using the OneWire protocol and prints it to the Serial Monitor.
 */

#include <OneWire.h>
#include <DallasTemperature.h>

// Pin where the DS18B20 data wire is connected
OneWire oneWire(5);

// Pass the OneWire reference to Dallas Temperature library
DallasTemperature sensor(&oneWire);

void setup() {
  Serial.begin(115200);
  
  // Set the pin as input with pull-up (required for OneWire)
  pinMode(5, INPUT_PULLUP);
  
  // Initialize the sensor
  sensor.begin();
}

void loop() {
  // Command the sensor to perform a temperature conversion
  sensor.requestTemperatures();
  
  // Fetch the temperature in Celsius from the first sensor on the bus
  float temp = sensor.getTempCByIndex(0);
  
  // Print the temperature to Serial with 1 decimal precision
  Serial.printf("%.1f°C\n", temp);
  
  // Wait 1 second before the next reading
  delay(1000);
}
