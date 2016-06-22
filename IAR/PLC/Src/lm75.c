#include "lm75.h"
#include "stm32f7xx_hal.h"
#include "i2c.h"
#define LM75_ADDR           0x90        // 7-bit address of LM75: left align to MSbit

#define LM75_TEMP       0x00        // Temperature Register of LM75
#define LM75_CONF       0x01        // Configuration Register of LM75
#define LM75_HYST       0x02        // 
#define LM75_TOS        0x03        // Over-temp Shutdown threshold Register of LM75
#define LM75_DevID      0x07        // Product ID Register

#define	LM75_TEMP_CORR    	(float)(0.5)		//LM75



float GetTempLM75(void){
 _TwoBytesS Result; 
 float RetRes;
 uint8_t LM75Data[2]; 
 HAL_I2C_Mem_Read(&hi2c2,(uint16_t)LM75_ADDR, (uint16_t)LM75_TEMP, I2C_MEMADD_SIZE_8BIT, LM75Data, 2, 10);
 Result.Bytes[1] = LM75Data[0];
 Result.Bytes[0] = LM75Data[1];
 Result.Word /= 128;
 
 RetRes = (float)(Result.Word)* LM75_TEMP_CORR;

return RetRes; 
}