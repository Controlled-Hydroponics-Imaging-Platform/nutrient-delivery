#include "src/Lux_OPT4048.h"

Sensor* OPT4048 = new Lux_OPT4048(i2c1, OPT4048_ADDR_GND);

const uint16_t LED_PIN          = 25;
const uint16_t SDA_PIN          = 4;
const uint16_t SCL_PIN          = 5;
const uint16_t OPT4048_INT_PIN  = 6;

float ppfd;

main