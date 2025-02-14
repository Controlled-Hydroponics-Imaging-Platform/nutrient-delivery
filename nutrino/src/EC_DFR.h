#ifndef EC_DFR_H
#define EC_DFR_H

#include "Sensor.h"
#include <DFRobot_EC.h>
#include <EEPROM.h>


class EC_DFR : public Sensor{
    public:
        EC_DFR(int ao_pin, float default_temp=25, int delay_ms=1000);
        float readSensor() override;
        float readSensor(float temperature) override;
        float readSensor_voltage();

        void begin(int baud_rate) override;
        void begin() override;
        void calibrate(float voltage, float temperature);
        ~EC_DFR(){};

    private:
        int ao_pin_;
        float volatage_;
        float ec_;
        float default_temperature_;
        DFRobot_EC DFR_EC_;

};


#endif