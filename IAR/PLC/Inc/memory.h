#ifndef _MEMORY_H
#define _MEMORY_H
#include "variables.h"
#include "fmc.h"

#define SDRAM_BANK_ADDR         0xC0000000
#define IS42int16_t160G_SIZE    0x2000000
#define NAND_512_SIZE           0x4000000

__no_init volatile  uint8_t my_array_in_NAND[NAND_512_SIZE]@0x80000000; // FLASH NAND
__no_init volatile  uint16_t my_array_in_SDRAM[IS42int16_t160G_SIZE/2]@0xC0000000; // SDRAM

#define SDRAM_Write32(address, value)    (*(__IO uint32_t *) (SDRAM_BANK_ADDR + (address)) = (value))
#define SDRAM_Read32(address)            (*(__IO uint32_t *) (SDRAM_BANK_ADDR + (address)))
#define SDRAM_Write16(address, value)    (*(__IO uint16_t *) (SDRAM_BANK_ADDR + (address)) = (value))
#define SDRAM_Read16(address)            (*(__IO uint16_t *) (SDRAM_BANK_ADDR + (address)))
#define SDRAM_Write8(address, value)        (*(__IO uint8_t *) (SDRAM_BANK_ADDR + (address)) = (value))
#define SDRAM_Read8(address)                (*(__IO uint8_t *) (SDRAM_BANK_ADDR + (address)))
#define SDRAM_WriteFloat(address, value)    (*(__IO float *) (SDRAM_BANK_ADDR + (address)) = (value))
#define SDRAM_ReadFloat(address)            (*(__IO float *) (SDRAM_BANK_ADDR + (address)))

void SDRAM_free(void);
void NAND_free(void);
void NAND_readId(void);
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram);
#endif

