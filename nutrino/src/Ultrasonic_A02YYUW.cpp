#include <Ultrasonic_A02YYUW.h>

ultrasonic_A0266UW::ultrasonic_A0266UW (int rx, int tx, int delay_ms): rx_dpin_(rx), 
                                                         tx_dpin_(tx){
    setDelay(delay_ms);
    mySerial_(rx_dpin_,tx_dpin_);

}

void ultrasonic_A0266UW::readSensor(){

}

void ultrasonic_A0266UW::begin(int baud_rate){

    mySerial.begin(baud_rate)
    
}