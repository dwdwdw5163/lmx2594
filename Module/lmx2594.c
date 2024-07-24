#include "lmx2594.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>
#include "lmx2594_config.h"

// Define a macro to set a GPIO pin to low
#define LOW(x) HAL_GPIO_WritePin(x##_GPIO_Port, x##_Pin, GPIO_PIN_RESET)

// Define a macro to set a GPIO pin to high
#define HIGH(x) HAL_GPIO_WritePin(x##_GPIO_Port, x##_Pin, GPIO_PIN_SET)

static uint8_t spi_buffer[3];

void SPI_Delay() {
  for (int i = 0; i < 1000; i++) {
  }
}

void LMX2594_Init() {

  LMX2595_WriteReg(0x00, 0x2412);
  LMX2595_WriteReg(0x00, 0x2410);

  for (int i = 0; i < sizeof(configs); i++) {
    LMX2595_WriteReg(configs[i].addr, configs[i].data);
  }
}

void LMX2595_WriteReg(uint8_t addr, uint16_t data) {
  LOW(CSB);

  for (int i = 0; i < 8; i++) {
    LOW(SCK);
    SPI_Delay();
    if (addr & 0x80) {
      HIGH(MOSI);
    } else {
      LOW(MOSI);
    }
    SPI_Delay();
    addr <<= 1;
    HIGH(SCK);
    SPI_Delay();
  }
  for (int i = 0; i < 16; i++) {
    LOW(SCK);
    SPI_Delay();
    if (data & 0x8000) {
      HIGH(MOSI);
    } else {
      LOW(MOSI);
    }
    SPI_Delay();
    data <<= 1;
    HIGH(SCK);
    SPI_Delay();
  }

  HIGH(CSB);
}

uint32_t LMX2594_ReadReg(uint8_t addr) {
  uint32_t value = 0;
  addr |= 0x80;
  
  LOW(CSB);

  for (int i = 0; i < 8; i++) {
    LOW(SCK);
    SPI_Delay();
    if (addr & 0x80) {
      HIGH(MOSI);
    } else {
      LOW(MOSI);
    }
    SPI_Delay();
    addr <<= 1;
    HIGH(SCK);
    SPI_Delay();
  }
  for (int i = 0; i < 16; i++) {
    LOW(SCK);
    SPI_Delay();
    value<<=1;
    if (HAL_GPIO_ReadPin(MISO_GPIO_Port, MISO_Pin)) {
      value |= 0x01;
    }
    SPI_Delay();
    HIGH(SCK);
    SPI_Delay();
  }

  HIGH(CSB);

  return value;
}
