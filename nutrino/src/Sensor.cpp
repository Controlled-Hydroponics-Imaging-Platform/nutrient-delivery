#include "Sensor.h"
#include<math.h>

int Sensor::getDelay(){
    return delay_; 
}
void Sensor::setDelay(int delay_ms){
    delay_= delay_ms;
}

float Sensor::readSensor(float){
    return NAN;
}