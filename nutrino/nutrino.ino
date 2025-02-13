#include "src/Ultrasonic_A02YYUW.h"

Sensor* ultrasonic = new Ultrasonic_A02YYUW(4, 3);
float distance;

void setup(){
    Serial.begin(9600);
    ultrasonic->begin(9600);
}


void loop(){

    distance = ultrasonic->readSensor();

    Serial.println(distance);

    delay(1000);

}
