/*
  CHIP & PRD hydroponic system
  lux to ppfd (change from ino to a main cpp for rpi pico)
  OPT4048 breakout https://learn.adafruit.com/adafruit-opt4048-xyz-color-sensor/arduino
  https://www.waveformlighting.com/horticulture/convert-lux-to-ppfd-online-calculator
  for conversions and register maps on OPT4048 -> data sheet: 
  https://cdn-learn.adafruit.com/assets/assets/000/137/030/original/opt4048.pdf?1747857425 
  2025-08-22
  Alice Liang
*/

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>

//I2C_0 definitions
#define I2C_PORT ic20
#define SDA_PIN 4
#define SCL_PIN 5
#define OPT4048_ADDR 0x44 // could be 0x29

// Registers
#define REG_EXPONENT_CH0 0x00
#define REG_MSB_CH0 0x00
#define REG_LSB_CH0 0x01
#define REG_EXPONENT_CH1 0x02
#define REG_MSB_CH1 0x02
#define REG_LSB_CH1 0x03
#define REG_EXPONENT_CH2 0x04
#define REG_MSB_CH2 0x04
#define REG_LSB_CH2 0x05
#define REG_EXPONENT_CH3 0x06
#define REG_MSB_CH3 0x06
#define REG_LSB_CH3 0x07

const float M[4][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f},  // m0x, m1x, m2x, m3x
    {0.0f, 1.0f, 0.0f, 0.0f},  // m0y, ...
    {0.0f, 0.0f, 1.0f, 0.0f},  // m0z
    {0.0f, 0.0f, 0.0f, 1.0f}   // mlux
}

uint16_t read_u16(uint8_t reg) {
    uint8_t buf[2];
    i2c_write_blocking(I2C_PORT, OPT4048_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, OPT4048_ADDR, buf, 2, false);
    return (buf[0] << 8) | buf[1];
}

int main() {
    stdio_init_all();
    i2c_init(I2C_PORT, 100 * 1000); // 100kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    printf("Adafruit OPT4048 Tristimulus XYZ Color Sensor Test\n");

    while (true) {
        uint32_t adc[4];
        uint8_t reg_exp = REG_EXPONENT_CH0;
        for (int ch = 0; ch < 4; ch++) {
            uint8_t exponent = read_u16(reg_exp) >> 12;   // top 4 bits
            uint16_t mantissa = read_u16(reg_exp++) & 0x0FFF;
            uint32_t code = mantissa << exponent;
            adc[ch] = code;
            reg_exp++; reg_exp++; // skip LSB and move to next exponent
        }

        float x = 0, y = 0, z = 0, lux = 0;
        for (int i = 0; i < 4; i++) {
            x   += M[0][i] * adc[i];
            y   += M[1][i] * adc[i];
            z   += M[2][i] * adc[i];
            lux += M[3][i] * adc[i];
        }

        lux *= 2.15e-3f;  // convert using coefficient

        float CIE_x = x / (x + y + z);
        float CIE_y = y / (x + y + z);
        // Estimate CCT using McCamy's approximation:
        float n = (CIE_x - 0.3320f)/(0.1858f - CIE_y);
        float CCT = (449.0f * pow(n, 3)) + (3525.0f * pow(n, 2)) + (6823.3f * n) + 5520.33f;

        printf("Lux: %.2f, CCT: %.0fK, CIE_x: %.4f, CIE_y: %.4f\n", lux, CCT, CIE_x, CIE_y);

        sleep_ms(1000);
    }

    return 0;
}
//end