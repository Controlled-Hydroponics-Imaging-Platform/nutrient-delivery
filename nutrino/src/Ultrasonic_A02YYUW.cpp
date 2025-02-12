#include "Ultrasonic_A02YYUW.h"

ultrasonic_A0266UW::ultrasonic_A0266UW (int rx, int tx, int delay_ms): rx_dpin_(rx), 
                                                         tx_dpin_(tx){
    setDelay(delay_ms);
    mySerial_(rx_dpin_,tx_dpin_);

}

void ultrasonic_A0266UW::readSensor(){

    do{
        for(int i=0;i<4;i++){
            data[i]=mySerial.read();
        }
    }while(mySerial.read()==0xff);

    mySerial.flush();

    if(data[0]==0xff){
      int sum;
      sum=(data[0]+data[1]+data[2])&0x00FF;
      if(sum==data[3])
      {
        distance=(data[1]<<8)+data[2];
        if(distance>30)
          {
           Serial.print("distance=");
           Serial.print(distance/10);
           Serial.println("cm");
          }else 
             {
               Serial.println("Below the lower limit");
             }
      }else Serial.println("ERROR");
     }

}

void ultrasonic_A0266UW::begin(int baud_rate){

    mySerial.begin(baud_rate)
    
}