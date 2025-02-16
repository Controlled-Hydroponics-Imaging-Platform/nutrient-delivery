#include "EC_DFR.h"
#include <math.h>

EC_DFR::EC_DFR (int ao_pin, float default_temp, int delay_ms) : ao_pin_(ao_pin), default_temperature_(default_temp){
    setDelay(delay_ms);
}

float EC_DFR::readSensor(){
// Returns EC in mS/cm @ default_temp_ in C
  voltage_= analogRead(ao_pin_)/1024.0*5000;

  ec_= DFR_EC_.readEC(voltage_, default_temperature_);

  return ec_;
}

float EC_DFR::readSensor(float temperature){
// Returns EC in mS/cm @ temperature in C

  voltage_= analogRead(ao_pin_)/1024.0*5000;

  temperature = isnan(temperature) ?  default_temperature_: temperature;

  ec_= DFR_EC_.readEC(voltage_, temperature);
  
  return ec_;
}

float EC_DFR::readSensor_voltage(){
// Returns voltage
  voltage_= analogRead(ao_pin_)/1024.0*5000;
  return voltage_;
}

void EC_DFR::calibrate(float voltage, float temperature){
  temperature = isnan(temperature) ?  default_temperature_: temperature;
  DFR_EC_.calibration(voltage, temperature);
}

void EC_DFR::begin(int baud_rate){
    this->begin();
}

void EC_DFR::begin(){
    DFR_EC_.begin();
}