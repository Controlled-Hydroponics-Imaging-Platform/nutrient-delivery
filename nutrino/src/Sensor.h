#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor{
    public:

        virtual void readSensor()=0;
        virtual ~Sensor(){}

    private:

};


#endif