#include "Waterflow_SEN0549.h"
#include <wiringPi.h>
#include <math.h> // #include <iostream>

#include <atomic>
#include <chrono>

using namespace std::chrono;

Waterflow_SEN0549::Waterflow_SEN0549(int pin, float ppl) : pin_(pin),
    pulsesPerLiter(ppl), pulseCount(0), flowRate_L_per_h(0.0f), totalLiters(0.0f),
    lastUpdateTime(0), interval(1000) {} // Default interval set to 1 second

void Waterflow_SEN0549::begin() {
    wiringPiSetup();
    pinMode(pin_, INPUT);
    wiringPiISR(pin_, INT_EDGE_FALLING, +[]{

    });

    lastUpdateTime = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

void Waterflow_SEN0549::handlePulse() {
    pulseCount++;
}

void Waterflow_SEN0549::update() {
    unsigned long currentTime = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();

    if (currentTime - lastUpdateTime >= interval) {
        unsigned int count = pulseCount.exchange(0);
    
        flowRate_L_per_s = (count * 1000.0 / interval) / pulsesPerLiter;

        // Also update L/h based on L/s
        flowRate_L_per_h = flowRate_L_per_s * 3600.0; // dependent on L/s
        // flowRate_L_per_h = (count * 1000.0/interval) / pulsesPerLiter * 3600.0; //independent of L/s
        
        
        totalLiters += (count / pulsesPerLiter);

        lastUpdateTime = currentTime;

    } 
}

float Waterflow_SEN0549::getFlowRateLitersPerHour() const {
    return flowRate_L_per_h;
}

float Waterflow_SEN0549::getTotalLiters() const {
    return totalLiters;
}