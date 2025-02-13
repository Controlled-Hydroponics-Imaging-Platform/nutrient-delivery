#include "src/Ultrasonic_A02YYUW.h"
#include "src/Temp_DS18B20.h"
#include "lib/OneWire/OneWire.h"

#define ONE_WIRE_BUS_PIN 10
OneWire one_wire_bus(ONE_WIRE_BUS_PIN);

Sensor* DS18B20 = new Temp_DS18B20(one_wire_bus);
Sensor* ultrasonic = new Ultrasonic_A02YYUW(4, 3);
float distance, water_temp;

void setup(){
    Serial.begin(9600);
    ultrasonic->begin(9600); // uses software serial so needs baudrate
    DS18B20->begin();
}


void loop(){

    distance = ultrasonic->readSensor();
    water_temp = DS18B20->readSensor();


    Serial.println(distance);

    delay(1000);

}
