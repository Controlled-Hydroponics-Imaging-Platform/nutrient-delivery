#ifndef ULTRASONIC_A02YYUW_H
#define ULTRASONIC_A02YYUW_H

#include "Sensor.h"
#include <SoftwareSerial.h>



class Ultrasonic_A02YYUW : public Sensor{
    public:
        Ultrasonic_A02YYUW(int rx, int tx, int delay_ms=100);
        float readSensor() override;
        void begin(int baud_rate) override;
        void begin() override;
        ~Ultrasonic_A02YYUW(){};

    private:
        int rx_dpin_;
        int tx_dpin_;
        unsigned char data_[4];
        float distance_;
        unsigned char HEADER_;
        unsigned char DATA_H_;
        unsigned char DATA_L_;
        unsigned char SUM_;
        SoftwareSerial mySerial_;

};


#endif