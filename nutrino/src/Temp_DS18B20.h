#ifndef TEMP_DS18B20_H
#define TEMP_DS18B20_H

#include "Sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>


class Temp_DS18B20 : public Sensor{
    public:
        Temp_DS18B20(OneWire& ow_bus, int delay_ms=1000);
        float readSensor() override;
        void begin(int baud_rate) override;
        void begin() override;
        ~Temp_DS18B20(){};

    private:
        int ow_dpin_;
        unsigned char data_[4];
        float temperature_;
        OneWire& oneWire_bus_;
        DallasTemperature DS18B20_;



};


#endif