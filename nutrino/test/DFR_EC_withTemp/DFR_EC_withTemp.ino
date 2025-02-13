/*
 * file DFRobot_EC.ino
 * @ https://github.com/DFRobot/DFRobot_EC
 *
 * This is the sample code for Gravity: Analog Electrical Conductivity Sensor / Meter Kit V2 (K=1.0), SKU: DFR0300.
 * In order to guarantee precision, a temperature sensor such as DS18B20 is needed, to execute automatic temperature compensation.
 * You can send commands in the serial monitor to execute the calibration.
 * Serial Commands:
 *   enterec -> enter the calibration mode
 *   calec -> calibrate with the standard buffer solution, two buffer solutions(1413us/cm and 12.88ms/cm) will be automaticlly recognized
 *   exitec -> save the calibrated parameters and exit from calibration mode
 *
 * Copyright   [DFRobot](http://www.dfrobot.com), 2018
 * Copyright   GNU Lesser General Public License
 *
 * version  V1.0
 * date  2018-03-21
 */

#include "../../lib/DFRobot_EC/DFRobot_EC.h"
#include <EEPROM.h>
#include "../../lib/OneWire/OneWire.h"
#include "../../lib/DallasTemperature/DallasTemperature.h"

#define EC_PIN A3
float voltage,ecValue,temperature = 25;
DFRobot_EC ec;

#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature water_probe(&oneWire);


void setup()
{
  Serial.begin(115200);  
  ec.begin();
  water_probe.begin();

}

void loop()
{
    static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U)  //time interval: 1s
    {
      timepoint = millis();
      voltage = analogRead(EC_PIN)/1024.0*5000;   // read the voltage
      temperature = readTemperature();          // read your temperature sensor to execute temperature compensation
      ecValue =  ec.readEC(voltage,temperature);  // convert voltage to EC with temperature compensation
      Serial.print("water_temperature:");
      Serial.print(temperature,2);
      Serial.print(", EC:");
      Serial.println(ecValue,2);
    }
    ec.calibration(voltage,temperature);          // calibration process by Serail CMD
}

float readTemperature()
{
  water_probe.requestTemperatures();  // Send command to get temperature readings

  float temperatureC = water_probe.getTempCByIndex(0);  // Read temperature in Celsius

  // Check if the sensor is connected
  if (temperatureC == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: DS18B20 not detected!");
    return 25;
  } else {
    return temperatureC;
  }
  
  }
