#ifndef SENSOR_H
#define SENSOR_H

#include <cstdint>
#include "pico/stdlib.h"

class Sensor{
    public:
        virtual void begin()=0;
        virtual float readSensor()=0;
        virtual float readSensor(float param);
        virtual ~Sensor(){};

        int getDelay();
        void setDelay(int delay_ms);

    private: //protected:
        int delay_;
};

#endif