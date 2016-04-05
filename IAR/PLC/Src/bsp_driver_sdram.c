/**
 ******************************************************************************
  * @file    bsp_driver_sdram.c (based on stm32756g_eval_sdram.c)
  * @brief   This file includes a generic SDRAM driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* USER CODE BEGIN 0 */

/* Includes ------------------------------------------------------------------*/
#include "bsp_driver_sdram.h"
   
/** @defgroup STM32F7XX_Private_Functions
  * @{
  */ 
   
/**
  * @brief  Initializes the SDRAM device 
  * @param  None
  * @retval SDRAM status
  */
uint8_t BSP_SDRAM_Init(void)
{ 
  static uint8_t sdramstatus = SDRAM_ERROR;
  /* place for custom code */
  
  return sdramstatus;
}

/**
  * @brief  Reads an mount of data from the SDRAM memory in polling mode. 
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read  
  * @param  uwDataSize: Size of read data from the memory
  * @retval SDRAM status
  */
uint8_t BSP_SDRAM_ReadData(uint32_t uwStartAddress, uint32_t* pData, uint32_t uwDataSize)
{ 
  if(HAL_SDRAM_Read_32b(&_HSDRAM, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }
}

/**
  * @brief  Reads an mount of data from the SDRAM memory in DMA mode. 
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read  
  * @param  uwDataSize: Size of read data from the memory
  * @retval SDRAM status
  */
uint8_t BSP_SDRAM_ReadData_DMA(uint32_t uwStartAddress, uint32_t* pData, uint32_t uwDataSize)
{ 
  if(HAL_SDRAM_Read_DMA(&_HSDRAM, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }   
}

/**
  * @brief  Writes an mount of data to the SDRAM memory in polling mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written  
  * @param  uwDataSize: Size of written data from the memory
  * @retval SDRAM status
  */
uint8_t BSP_SDRAM_WriteData(uint32_t uwStartAddress, uint32_t* pData, uint32_t uwDataSize) 
{ 
  if(HAL_SDRAM_Write_32b(&_HSDRAM, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }
}

/**
  * @brief  Writes an mount of data to the SDRAM memory in DMA mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written  
  * @param  uwDataSize: Size of written data from the memory
  * @retval SDRAM status
  */
uint8_t BSP_SDRAM_WriteData_DMA(uint32_t uwStartAddress, uint32_t* pData, uint32_t uwDataSize) 
{ 
  if(HAL_SDRAM_Write_DMA(&_HSDRAM, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  } 
}

/**
  * @brief  Sends command to the SDRAM bank.
  * @param  SdramCmd: Pointer to SDRAM command structure 
  * @retval HAL status
  */  
uint8_t BSP_SDRAM_Sendcmd(FMC_SDRAM_CommandTypeDef *SdramCmd)
{ 
  if(HAL_SDRAM_SendCommand(&_HSDRAM, SdramCmd, SDRAM_TIMEOUT) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }
}

/**
  * @brief  Handles SDRAM DMA transfer interrupt request.
  * @param  None
  * @retval None
  */
void BSP_SDRAM_DMA_IRQHandler(void)
{
  HAL_DMA_IRQHandler(_HSDRAM.hdma); 
}

/* USER CODE END 0 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
