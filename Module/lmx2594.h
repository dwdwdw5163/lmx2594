#ifndef _LMX2594_H_
#define _LMX2594_H_

#include "spi.h"
#include "stm32f405xx.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>


void LMX2594_Init();
void LMX2595_WriteReg(uint8_t addr, uint16_t data);
uint32_t LMX2594_ReadReg(uint8_t addr);


#endif
