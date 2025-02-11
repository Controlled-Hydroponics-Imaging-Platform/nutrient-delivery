#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>

float temperature;

#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature water_probe(&oneWire);


void setup()
{
  Serial.begin(115200);  
  water_probe.begin();

}

void loop()
{
    static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U)  //time interval: 1s
    {
      timepoint = millis();
      temperature = readTemperature();          // read your temperature sensor to execute temperature compensation
      Serial.print("water_temperature:");
      Serial.println(temperature,2);
    }
}

float readTemperature()
{
  water_probe.requestTemperatures();  // Send command to get temperature readings

  float temperatureC = water_probe.getTempCByIndex(0);  // Read temperature in Celsius

  // Check if the sensor is connected
  if (temperatureC == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: DS18B20 not detected!");
    return 25;
  } else {
    return temperatureC;
  }
  
  }
