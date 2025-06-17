#ifndef WATERFLOW_SEN0549_H
#define WATERFLOW_SEN0549_H

#include "Sensor.h"
#include <atomic> // included in standard C++ library

class Waterflow_SEN0549 : public Sensor {
    public:
         Waterflow_SEN0549(int pin, float pulsesPerLiter = 540.0f);
        void begin() override;
        void update();
        float getFlowRateLitersPerHour() const override;
        float getTotalLiters() const override;
        void handlePulse() override;
        ~Waterflow_SEN0549(){};
    
    private:
        int pin_;
        float pulsesPerLiter;
        std::atomic<unsigned int> pulseCount;
        float flowRate_L_per_h;
        float totalLiters;
        unsigned long lastUpdateTime;
        unsigned long interval;
}

#endif