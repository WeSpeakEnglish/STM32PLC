#ifndef _DMA2_H
#define _DMA2_H
#include "stm32f746xx.h"
#include "stm32f7xx_hal.h"


extern volatile uint8_t isDmaTransferOk;
extern DMA_HandleTypeDef hdma;

void DMA2_Stream0_IRQHandler(DMA_HandleTypeDef *hdma);
void DMA_Init(void);
void LcdWriteDataMultiple(uint16_t *pData, int NumItems);


#endif