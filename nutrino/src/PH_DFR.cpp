#include "PH_DFR.h"
#include <math.h>

PH_DFR::PH_DFR (int ao_pin, float default_temp, unsigned int refresh_interval, int delay_ms) : ao_pin_(ao_pin), 
                                                                                               default_temperature_(default_temp), 
                                                                                               refresh_interval_(refresh_interval){
    setDelay(delay_ms);
    timestamp_= millis();
}

float PH_DFR::readSensor(){
// Returns PH @ default_temp_ in C
  float runningSum=0;

  if (this->buff_notFull() || this->refresh_buffer()){
  

    for (float& i : buff_) {// fix this 

    i=analogRead(ao_pin_);
    runningSum += i;
    delay(10);

    }

    ph_ = 3.5 * ((runningSum / 10) * 5.0 / 1024);
    index_=0;

    return ph_;

  }

  buff_[index_]=analogRead(ao_pin_);
  index_++;

  for (float i:buff_){
    runningSum+=i;
  }

  ph_ = 3.5 * ((runningSum / 10) * 5.0 / 1024);

  if(index_>=10){
    index_=0;
  }

  return ph_;
}

float PH_DFR::readSensor_voltage(){
// Returns voltage
  voltage_= analogRead(ao_pin_)/1024.0*5000;
  return voltage_;
}

bool PH_DFR::buff_notFull(){
  for(float i : buff_){

    if (isnan(i)){
      return true;
    }

  }

  return false;
}

bool PH_DFR::refresh_buffer(){
  
  if (millis()-timestamp_ > refresh_interval_){

    timestamp_ = millis();

    return true;

  }

  return false;
}

void PH_DFR::begin(int baud_rate){
    this->begin();
}


void PH_DFR::begin(){}