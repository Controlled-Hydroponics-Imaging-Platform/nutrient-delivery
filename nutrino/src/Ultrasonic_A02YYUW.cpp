#include "Ultrasonic_A02YYUW.h"
#include <math.h>

Ultrasonic_A02YYUW::Ultrasonic_A02YYUW (int rx, int tx, int delay_ms) : rx_dpin_(rx), 
                                                                        tx_dpin_(tx),
                                                                        mySerial_(rx,tx){
    setDelay(delay_ms);
    // mySerial_(rx_dpin_,tx_dpin_);

}

float Ultrasonic_A02YYUW::readSensor(){
// Returns distance in mm
    unsigned char incoming_byte;

    if(mySerial_.available()){

        do{
            incoming_byte = mySerial_.read();
            data_[0] = incoming_byte;
        }while(incoming_byte!=0xFF || mySerial_.available()>4);


        for(int i=1; i<4;i++){
            data_[i] = mySerial_.read();
        }

        HEADER_ = data_[0];
        DATA_H_ = data_[1];
        DATA_L_ = data_[2];
        SUM_ = data_[3];


        if(HEADER_==0xFF){
            int checksum=(HEADER_+DATA_H_+DATA_L_)&0x00FF;
        
            if(checksum==SUM_){
                distance_=(DATA_H_<<8)+DATA_L_;
                if(distance_>30){

                    return distance_;
                }else{
                    Serial.println("Error Reading value from Ultrasonic A02YYUW: Below the lower limit");
                }
            }else{
                Serial.println("Error Reading value from Ultrasonic A02YYUW: Checksum Failed");
            }
        }else{
            Serial.println("Error Reading value from Ultrasonic A02YYUW: missaligned data frame");
        }

    }else{
        Serial.println("Error Reading value from Ultrasonic A02YYUW:Connection Error");
    }

    return NAN;
}

void Ultrasonic_A02YYUW::begin(int baud_rate){
    mySerial_.begin(baud_rate);
}

void Ultrasonic_A02YYUW::begin(){
    mySerial_.begin(9600);
}