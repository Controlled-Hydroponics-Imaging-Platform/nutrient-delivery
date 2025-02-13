#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor{
    public:
        virtual void begin()=0;
        virtual void begin(int baud_rate)=0;
        virtual float readSensor()=0;
        virtual ~Sensor(){};

        int getDelay();
        void setDelay(int delay_ms);

    private:
        int delay_;


};


#endif