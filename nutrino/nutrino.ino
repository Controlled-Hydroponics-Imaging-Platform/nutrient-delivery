#include "src/Ultrasonic_A02YYUW.h"
#include "src/Temp_DS18B20.h"
#include "src/EC_DFR.h"
#include "src/PH_DFR.h"
#include <OneWire.h>

#define ONE_WIRE_BUS_PIN 10
#define EC_PIN A3
#define PH_PIN A0

OneWire one_wire_bus(ONE_WIRE_BUS_PIN);

Sensor* DS18B20 = new Temp_DS18B20(one_wire_bus);
Sensor* ultrasonic = new Ultrasonic_A02YYUW(4, 3);
Sensor* ec_probe = new EC_DFR(EC_PIN);
Sensor* ph_probe = new PH_DFR(PH_PIN);

EC_DFR* ec_derived = static_cast<EC_DFR*>(ec_probe);

float distance, water_temp,ec,ph, ec_voltage;

void setup(){
    Serial.begin(9600);
    ultrasonic->begin(9600); // uses software serial so needs baudrate
    DS18B20->begin();
    ec_probe->begin();

    Serial.println("Sensor initialization successful");
}


void loop(){

    static unsigned long timepoint = millis();

    if(millis()-timepoint>1000U){
      timepoint=millis();
      distance = ultrasonic->readSensor();
      water_temp = DS18B20->readSensor();
      ec = ec_probe->readSensor(water_temp);
      ph = ph_probe->readSensor();
      
      Serial.print("Distance_mm:");
      Serial.print(distance);
      Serial.print(", Water_Temp_C:");
      Serial.print(water_temp);
      Serial.print(", EC_ms/cm:");
      Serial.print(ec);
      Serial.print(", PH:");
      Serial.println(ph);

      ec_voltage = ec_derived->readSensor_voltage();

      }

    // EC Specific methods (calibration)
    ec_derived->calibrate(ec_voltage,water_temp);
    
}
