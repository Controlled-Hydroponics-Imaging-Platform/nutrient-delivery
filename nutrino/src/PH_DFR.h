#ifndef EC_PH_H
#define EC_PH_H

#include "Sensor.h"
#include "math.h"

class PH_DFR : public Sensor{
    public:
        PH_DFR(int ao_pin, float default_temp=25, unsigned int refresh_interval=60000U, int delay_ms=1000);
        float readSensor() override;
        bool buff_notFull();
        bool refresh_buffer();
        float readSensor_voltage();

        void begin(int baud_rate) override;
        void begin() override;
        ~PH_DFR(){};

    private:
        int ao_pin_;
        float buff_[10]={NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN};
        int index_=0;
        float voltage_;
        float refresh_interval_;
        float ph_;
        float default_temperature_;
        unsigned long timestamp_;
        
};


#endif