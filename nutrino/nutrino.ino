#include "src/Ultrasonic_A02YYUW.h"
#include "src/Temp_DS18B20.h"
#include "src/EC_DFR.h"
#include "src/PH_DFR.h"
#include "src/Waterflow_SEN0549.h"
#include <OneWire.h>

#define ONE_WIRE_BUS_PIN 10
#define EC_PIN A3
#define PH_PIN A0
#define WATERFLOW_PIN 2 // ARBITRARY PIN NUMBER, depends on new pcb design

OneWire one_wire_bus(ONE_WIRE_BUS_PIN);

Sensor* DS18B20 = new Temp_DS18B20(one_wire_bus);
Sensor* ultrasonic = new Ultrasonic_A02YYUW(4, 3);
Sensor* ec_probe = new EC_DFR(EC_PIN);
Sensor* ph_probe = new PH_DFR(PH_PIN);
Sensor* waterflow = new Waterflow_SEN0549(WATERFLOW_PIN);

EC_DFR* ec_derived = static_cast<EC_DFR*>(ec_probe);

float distance, water_temp, ec, ph, ec_voltage, waterflow_rate, total_liters;

void setup(){
    Serial.begin(9600);
    ultrasonic->begin(9600); // uses software serial so needs baudrate
    DS18B20->begin();
    ec_probe->begin();
    waterflow->begin(9600);

    Serial.println("Sensor initialization successful");
}


void loop(){

    static unsigned long timepoint = millis();
    // line 46 can be modified so to ->getFlowRateLitersPerSecond()
    if(millis()-timepoint>1000U){
      timepoint=millis();
      distance = ultrasonic->readSensor();
      water_temp = DS18B20->readSensor();
      ec = ec_probe->readSensor(water_temp);
      ph = ph_probe->readSensor();
      waterflow_rate = waterflow->getFlowRateLitersPerHour(); // would it be better to seperate waterflow_sen0549 into 2 src codes? 1 for flowrate and 1 for total liters?
      total_liters = waterflow->getTotalLiters();             // so that we can actually use readSensor() function
      
      Serial.print("Distance_mm:");
      Serial.print(distance);
      Serial.print(", Water_Temp_C:");
      Serial.print(water_temp);
      Serial.print(", EC_ms/cm:");
      Serial.print(ec);
      Serial.print(", PH:");
      Serial.print(ph);
      Serial.print(", Water_Flow_Rate_L/h:");
      Serial.print(waterflow_rate);
      Serial.print(", Total_Liters:");
      Serial.println(total_liters);

      ec_voltage = ec_derived->readSensor_voltage();

      }

    // EC Specific methods (calibration)
    ec_derived->calibrate(ec_voltage,water_temp);
    
}
