#include "stmpe811.h"
#include "i2c.h"
#include "variables.h"
#include "core.h"
#include "lcd.h"
Touch_Data_t Touch_Data;

void P_Touch_Reset(void); // reset MC
uint8_t P_Touch_FnctCmd(uint8_t Fct, FunctionalState NewState); 
void P_Touch_Config(void);
uint16_t P_Touch_ReadID(void);
uint8_t P_Touch_IOAFConfig(uint8_t IO_Pin, FunctionalState NewState);
static uint16_t P_Touch_Read_X(void);
static uint16_t P_Touch_Read_Y(void);
uint16_t P_Touch_Read_16b(uint32_t RegisterAddr);


ErrorStatus UB_Touch_Init(void)
{
  uint16_t stmpe_id=0;

  stmpe_id=P_Touch_ReadID();
  if(stmpe_id!=STMPE811_ID) {
    return(ERROR);
  }

  P_Touch_Reset();

  P_Touch_FnctCmd(IOE_ADC_FCT, ENABLE);
  P_Touch_Config();

  return(SUCCESS);
}

uint8_t temp, temp2; 

ErrorStatus UB_Touch_Read(void)
{
  uint32_t xDiff, yDiff , x , y;
  static uint32_t _x = 0, _y = 0;
  int16_t i2c_wert;
  
  HAL_I2C_Mem_Read(&hi2c2,(uint16_t)STMPE811_I2C_ADDR,(uint16_t)IOE_REG_TP_CTRL,I2C_MEMADD_SIZE_8BIT,&temp,1,100);

  i2c_wert = (int16_t) temp;
  
  if(i2c_wert<0) return(ERROR);
  
  if((i2c_wert&0x80)==0) {
    Touch_Data.status = TOUCH_RELEASED;
  }
  else {
    Touch_Data.status = TOUCH_PRESSED;
  }
  if( Touch_Data.status == TOUCH_PRESSED){
    x = P_Touch_Read_X();
    y = P_Touch_Read_Y();
    xDiff = x > _x? (x - _x): (_x - x);
    yDiff = y > _y? (y - _y): (_y - y);
    if (xDiff + yDiff > 5)
    {
      _x = x;
      _y = y;
    }
  
  Touch_Data.xp = _x;
  Touch_Data.yp = _y;
  }
  
  temp = 0x01; 
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_FIFO_STA, I2C_MEMADD_SIZE_8BIT, &temp, 1, 200);
  temp = 0x00; 
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_FIFO_STA, I2C_MEMADD_SIZE_8BIT, &temp, 1, 200);
  
  
  return(SUCCESS);
}


//--------------------------------------------------------------
// interne Funktion
//--------------------------------------------------------------
void P_Touch_Reset(void)
{
  temp = 0x02;
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_SYS_CTRL1, I2C_MEMADD_SIZE_8BIT, &temp, 1, 200);
  DelayOnFastQ(20);
  temp = 0x00;
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_SYS_CTRL1, I2C_MEMADD_SIZE_8BIT, &temp, 1, 200);
}


//--------------------------------------------------------------
// return : 0 = ok, >0 = error
//--------------------------------------------------------------
uint8_t P_Touch_FnctCmd(uint8_t Fct, FunctionalState NewState)
{
//  uint8_t tmp = 0;
  int16_t i2c_wert;

  HAL_I2C_Mem_Read(&hi2c2,(uint16_t)STMPE811_I2C_ADDR,(uint16_t)IOE_REG_SYS_CTRL2,I2C_MEMADD_SIZE_8BIT,&temp,1,100);
  i2c_wert = (int16_t)temp;
 
  if(i2c_wert<0) return(1);

  temp = (uint8_t)(i2c_wert);

  if (NewState != DISABLE) {
    temp &= ~(uint8_t)Fct;
  }
  else {
    temp |= (uint8_t)Fct;
  }
  
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_SYS_CTRL2, I2C_MEMADD_SIZE_8BIT, &temp, 1, 200);
  
  return(0);
}


//--------------------------------------------------------------
// interne Funktion
//--------------------------------------------------------------
void P_Touch_FreeIRQ(void){
  const uint8_t RegValue = 0x01; 
   HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_INT_STA, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&RegValue, 1, 200);
}

void P_Touch_Config(void)
{
 static uint8_t regArray[12]={0x50,0x01,0x9A,0x01,0x01,0x00,0x01,0x01,0x03,0xFF,1,1};
  P_Touch_FnctCmd(IOE_TP_FCT, ENABLE);
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_ADC_CTRL1, I2C_MEMADD_SIZE_8BIT, &regArray[0], 1, 200);
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_INT_CTRL, I2C_MEMADD_SIZE_8BIT, &regArray[10], 1, 200);
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_INT_EN, I2C_MEMADD_SIZE_8BIT, &regArray[11], 1, 200);
  DelayOnFastQ(20);
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_ADC_CTRL2, I2C_MEMADD_SIZE_8BIT, &regArray[1], 1, 200);
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_TP_CFG, I2C_MEMADD_SIZE_8BIT, &regArray[2], 1, 200);
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_FIFO_TH, I2C_MEMADD_SIZE_8BIT, &regArray[3], 1, 200);
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_FIFO_STA, I2C_MEMADD_SIZE_8BIT, &regArray[4], 1, 200);
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_FIFO_STA, I2C_MEMADD_SIZE_8BIT, &regArray[5], 1, 200);   
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_TP_FRACT_XYZ, I2C_MEMADD_SIZE_8BIT, &regArray[6], 1, 200);   
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_TP_I_DRIVE, I2C_MEMADD_SIZE_8BIT, &regArray[7], 1, 200);
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_TP_CTRL, I2C_MEMADD_SIZE_8BIT, &regArray[8], 1, 200);
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_INT_STA, I2C_MEMADD_SIZE_8BIT, &regArray[9], 1, 200);
  Touch_Data.status = TOUCH_RELEASED;
  Touch_Data.xp = 0;
  Touch_Data.yp = 0;
}


//--------------------------------------------------------------
// interne Funktion
// ID auslesen
//--------------------------------------------------------------
uint16_t P_Touch_ReadID(void)
{
  uint16_t tmp = 0;
  int16_t i2c_wert1, i2c_wert2;

  HAL_I2C_Mem_Read(&hi2c2,(uint16_t)STMPE811_I2C_ADDR,0x00,I2C_MEMADD_SIZE_8BIT,&temp,1,100);
  i2c_wert1 = (int16_t)temp;
  HAL_I2C_Mem_Read(&hi2c2,(uint16_t)STMPE811_I2C_ADDR,0x01,I2C_MEMADD_SIZE_8BIT,&temp,1,100);
  i2c_wert2 = (int16_t)temp;
  
  if(i2c_wert1<0) return 0;
  if(i2c_wert2<0) return 0;

  tmp = i2c_wert1;
  tmp = (uint32_t)(tmp << 8);
  tmp |= i2c_wert2;

  return (uint16_t)tmp;
}


//--------------------------------------------------------------
// return : 0=ok, >0 = error
//--------------------------------------------------------------
uint8_t P_Touch_IOAFConfig(uint8_t IO_Pin, FunctionalState NewState)
{
  int16_t i2c_wert;
  HAL_I2C_Mem_Read(&hi2c2,(uint16_t)STMPE811_I2C_ADDR,(uint16_t)IOE_REG_GPIO_AF,I2C_MEMADD_SIZE_8BIT,&temp,1,100);
  i2c_wert = (int16_t) temp;
  
  if(i2c_wert<0) return(1);

  temp = i2c_wert;

  if (NewState != DISABLE) {
    temp |= (uint8_t)IO_Pin;
  }
  else {
    temp &= ~(uint8_t)IO_Pin;
  }

   HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_GPIO_AF, I2C_MEMADD_SIZE_8BIT, &temp, 1, 200);
   return(0);
}
#define DISPLAY_8IN             1U 
//#define DISPLAY_9IN           1U 

///CALIBRATING DATA
#ifdef DISPLAY_8IN
#define X_MAGNIFIER            854
#define Y_MAGNIFIER            547
#define X_SUB                  145
#define Y_SUB                  160
#endif

#ifdef DISPLAY_9IN
#define X_MAGNIFIER            833
#define Y_MAGNIFIER            526
#define X_SUB                  77
#define Y_SUB                  150
#endif

#define ORIENTATION_DEFAULT     1U 

//--------------------------------------------------------------
// interne Funktion
//--------------------------------------------------------------
static uint16_t P_Touch_Read_X(void)
{
  int32_t x;
  

#ifdef DISPLAY_9IN 
  x = P_Touch_Read_16b(IOE_REG_TP_DATA_Y);
#endif 

#ifdef DISPLAY_8IN
  x = P_Touch_Read_16b(IOE_REG_TP_DATA_X);
#endif 
  x -=X_SUB;
  x *=  X_MAGNIFIER;
  x /= 4096;
 #ifdef DISPLAY_8IN
  if(ORIENTATION_DEFAULT) x = DisplayWIDTH - x; 
 #endif  
  if( x < 0 ) x = 0;

  return (uint16_t)(x);
}


//--------------------------------------------------------------
// interne Funktion
//--------------------------------------------------------------
static uint16_t P_Touch_Read_Y(void)
{
  int32_t y;
 if( Touch_Data.status == TOUCH_PRESSED){
  
  
#ifdef DISPLAY_8IN 
  y = P_Touch_Read_16b(IOE_REG_TP_DATA_Y); 
#endif
#ifdef DISPLAY_9IN 
  y = P_Touch_Read_16b(IOE_REG_TP_DATA_X); 
#endif   
  y -= Y_SUB;
  y *=  Y_MAGNIFIER;
  y /= 4096;
  
 if(ORIENTATION_DEFAULT) y = DisplayHEIGHT - y;
 if( y < 0 ) y = 0;
 
}
  return (uint16_t)(y);
}


//--------------------------------------------------------------
// interne Funktion
//--------------------------------------------------------------
uint16_t P_Touch_Read_16b(uint32_t RegisterAddr)
{
  uint16_t ret_wert=0;
  int16_t i2c_wert1, i2c_wert2;

  HAL_I2C_Mem_Read(&hi2c2,(uint16_t)STMPE811_I2C_ADDR,(uint16_t)RegisterAddr,I2C_MEMADD_SIZE_8BIT,&temp,1,100);
  i2c_wert1 = (int16_t) temp;
  HAL_I2C_Mem_Read(&hi2c2,(uint16_t)STMPE811_I2C_ADDR,(uint16_t)(RegisterAddr+1),I2C_MEMADD_SIZE_8BIT,&temp,1,100);
  i2c_wert2 = (int16_t) temp;

  if(i2c_wert1<0) return 0;
  if(i2c_wert2<0) return 0;

  ret_wert=(i2c_wert1<<8)|i2c_wert2;

  return(ret_wert);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */


