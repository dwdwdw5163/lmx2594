#ifndef _LMX2594_H_
#define _LMX2594_H_

#include "spi.h"
#include "stm32f405xx.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>

static uint32_t CHDIV_MAP[] = {
  2,4,6,8,12,16,24,32,48,64,72,96,128,192,256,384,512,768
};

void LMX2594_Init();
void LMX2595_WriteReg(uint8_t addr, uint16_t data);
uint32_t LMX2594_ReadReg(uint8_t addr);

void DrawUI();

#endif
