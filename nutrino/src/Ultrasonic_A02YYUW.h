#ifndef ULTRASONIC_A02YYUW_H
#define ULTRASONIC_A02YYUW_H

#include "Sensor.h"
#include <SoftwareSerial.h>



class ultrasonic_A0266UW : public Sensor{
    public:
        ultrasonic_A0266UW(int rx, int tx, int delay_ms=100);
        float readSensor() override;
        void begin(int baud_rate) override;

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

}


#endif