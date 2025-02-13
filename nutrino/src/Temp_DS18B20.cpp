#include "Temp_DS18B20.h"
#include <math.h>

Temp_DS18B20::Temp_DS18B20 (OneWire& ow_bus, int delay_ms) : oneWire_bus_(ow_bus), DS18B20_(&ow_bus){
    setDelay(delay_ms);
}

float Temp_DS18B20::readSensor(){
// Returns temperature in C

  DS18B20_.requestTemperatures();  // Send command to get temperature readings

  temperature_ = DS18B20_.getTempCByIndex(0);  // Read temperature in Celsius

  // Check if the sensor is connected
  if (temperature_ == DEVICE_DISCONNECTED_C) {
    Serial.println("Error Reading value from Temperature_DS18B20: DS18B20 not detected!");
  }else{
    return temperature_;
  }

  return NAN;
}

void Temp_DS18B20::begin(int baud_rate){
    this->begin();
}

void Temp_DS18B20::begin(){
    DS18B20_.begin();
}