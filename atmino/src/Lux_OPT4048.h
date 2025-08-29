#ifndef LUXSENSOR_H
#define LUXSENSOR_H

#include "Sensor.h"
#include "hardware/i2c.h"

class LuxSensor : public Sensor {
    public:
        LuxSensor(i2c_instance, uint sda_pin, uint scl_pin, uint8_t i2c_addr=0x44);
        virtual ~LuxSensor();

        void begin() override;
        float readSensor() override;
        float readSensor(float factor) override;

    private:
        i2c_inst_t *i2c_i2c_;
        uint sda_pin_;
        uint scl_pin_;
        uint8_t address_;

        float lux;
        float cct;

        static constexpr uint8_t REG_CONFIG   = 0x00; 
        static constexpr uint8_t REG_RESULT_X_MSB = 0x04;
        static constexpr uint8_t REG_RESULT_X_LSB = 0x05;
        static constexpr uint8_t REG_RESULT_Y_MSB = 0x06;
        static constexpr uint8_t REG_RESULT_Y_LSB = 0x07;
        static constexpr uint8_t REG_RESULT_Z_MSB = 0x08;
        static constexpr uint8_t REG_RESULT_Z_LSB = 0x09;
        static constexpr uint8_t REG_RESULT_W_MSB = 0x0A;
        static constexpr uint8_t REG_RESULT_W_LSB = 0x0B;

        void writeRegister(uint8_t reg, uint16_t value);
        uint16_t readRegister16(uint8_t reg);  // read 16-bit value (MSB + LSB)
};

#endif