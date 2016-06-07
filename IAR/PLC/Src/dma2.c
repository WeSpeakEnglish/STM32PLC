#include "dma2.h"

volatile uint8_t isDmaTransferOk = 1;
DMA_HandleTypeDef hdma;


void DMA2_Stream0_IRQHandler(DMA_HandleTypeDef *hdma){
 // HAL_NVIC_ClearPendingIRQ(DMA2_Stream0_IRQn);
  isDmaTransferOk = 1;
}

void DMA_Init(void) {

  __DMA2_CLK_ENABLE();
    hdma.Instance = DMA2_Stream0;

    // Need to deinit DMA first
   
    HAL_DMA_DeInit(&hdma);

    hdma.Init.Channel = DMA_CHANNEL_0;
    hdma.XferCpltCallback = DMA2_Stream0_IRQHandler;
    hdma.Init.Direction = DMA_MEMORY_TO_MEMORY;
    hdma.Init.PeriphInc = DMA_PINC_ENABLE;
    hdma.Init.MemInc = DMA_MINC_ENABLE;
    hdma.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma.Init.Mode = DMA_NORMAL;
    hdma.Init.Priority = DMA_PRIORITY_HIGH;
    hdma.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
//  DMA_Handle.Init.MemBurst = DMA_MBURST_SINGLE;
//   DMA_Handle.Init.PeriphBurst = DMA_PBURST_SINGLE;
    hdma.Init.MemBurst = DMA_MBURST_INC4;
    hdma.Init.PeriphBurst = DMA_PBURST_INC4;
    HAL_DMA_Init(&hdma);
    hdma.State = HAL_DMA_STATE_READY;


 // HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);   
}

