#include "LuxSensor.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <math.h>

static constexpr float Low_CRI_3500K = 16036.96f/1.0e7f;
static constexpr float Low_CRI_6000K = 13406.81f/1.0e7f;

LuxSensor::LuxSensor(i2c_inst_t* i2c, uint sda_pin, uint scl_pin, uint8_t address)
    : i2c(i2c), sda_pin(sda_pin), scl_pin(scl_pin), address(address) {}

LuxSensor::~LuxSensor() {}

bool LuxSensor::begin() {
    i2c_init(i2c, 100 * 1000); // 100 kHz
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);

    uint8_t config_reg = REG_CONFIG; //unsure
    uint8_t config_value[2] = {0x10, 0x00};

    int result = i2c_write_blocking(i2c, address, config_value, 2, false);
    if (result < 0) {
        printf("OPT4048 config failed\n");
        return false;
    }

    printf("OPT4048 lux sensor ready to go\n");

    return true;
}

bool LuxSensor::readLux() {
//need config
}

float LuxSensor::calculateCCT(float x, float y) {
    float n = (x - 0.3320) / (0.1858 - y);
    float cct = (437.0 * pow(n, 3)) + (3601.0 * pow(n, 2)) + (6861.0 * n) + 5517.0;
    return cct;
}

float LuxSensor::calculatePPFD(float lux, float cct) {
    float ppfd = 0.0f;

    if (cct >= 3000 && cct <= 3200) {
        ppfd = lux * Low_CRI_3500K;
    } else if (cct >= 6000 && cct <= 6500) {
        ppfd = lux * Low_CRI_6000K;
    } else {
        printf("Warning: Color temperature out of range for PPFD conversion.\n");
        ppfd = 0.0f;
    }
    return ppfd;
}