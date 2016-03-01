
//            I2C-Slave-ADR = [0x82]
//            FRQ-Max = 100kHz
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stmpe811.h"
#include "i2c.h"
#include "variables.h"
#include "core.h"

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

  // init vom I2C
 // UB_I2C3_Init();

  // check vom STMPE811
  stmpe_id=P_Touch_ReadID();
  if(stmpe_id!=STMPE811_ID) {
    return(ERROR);
  }

  // SW-Reset vom Touch
  P_Touch_Reset();

  // init
  P_Touch_FnctCmd(IOE_ADC_FCT, ENABLE);
  P_Touch_Config();

  return(SUCCESS);
}


//--------------------------------------------------------------
// auslesen vom Touch-Status und der Touch-Koordinaten
// Return_wert :
//  -> ERROR   , wenn Touch nicht gefunden wurde
//  -> SUCCESS , wenn Touch OK
//
// Touch_Data.status : [TOUCH_PRESSED, TOUCH_RELEASED]
// Touch_Data.xp     : [0...239]
// Touch_Data.yp     : [0...319] 
//--------------------------------------------------------------

u8 temp; 

ErrorStatus UB_Touch_Read(void)
{
  uint32_t xDiff, yDiff , x , y;
  static uint32_t _x = 0, _y = 0;
  int16_t i2c_wert;
  
  
  //i2c_wert=UB_I2C3_ReadByte(STMPE811_I2C_ADDR, IOE_REG_TP_CTRL);
  
  HAL_I2C_Mem_Read(&hi2c2,(uint16_t)STMPE811_I2C_ADDR,(uint16_t)IOE_REG_TP_CTRL,I2C_MEMADD_SIZE_8BIT,&temp,1,100);
  i2c_wert = (int16_t) temp;
  
  if(i2c_wert<0) return(ERROR);
  
  if((i2c_wert&0x80)==0) {
    Touch_Data.status = TOUCH_RELEASED;
  }
  else {
    Touch_Data.status = TOUCH_PRESSED;
  }

  if(Touch_Data.status==TOUCH_PRESSED) {
    x = P_Touch_Read_X();
    y = P_Touch_Read_Y();
    xDiff = x > _x? (x - _x): (_x - x);
    yDiff = y > _y? (y - _y): (_y - y);
    if (xDiff + yDiff > 5)
    {
      _x = x;
      _y = y;
    }
  }
  
  Touch_Data.xp = _x;
  Touch_Data.yp = _y;
  
  //UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_FIFO_STA, 0x01);
  temp = 0x01; 
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_FIFO_STA, I2C_MEMADD_SIZE_8BIT, &temp, 1, 200);
  //UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_FIFO_STA, 0x00);
  temp = 0x00; 
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_FIFO_STA, I2C_MEMADD_SIZE_8BIT, &temp, 1, 200);
  
  
  return(SUCCESS);
}


//--------------------------------------------------------------
// interne Funktion
//--------------------------------------------------------------
void P_Touch_Reset(void)
{
 // UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_SYS_CTRL1, 0x02);
  temp = 0x02;
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_SYS_CTRL1, I2C_MEMADD_SIZE_8BIT, &temp, 1, 200);
  //UB_I2C3_Delay(STMPE811_DELAY);
  DelayOnFastQ(2000);

 // UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_SYS_CTRL1, 0x00);
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

 // i2c_wert=UB_I2C3_ReadByte(STMPE811_I2C_ADDR, IOE_REG_SYS_CTRL2);
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
  
  //UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_SYS_CTRL2, tmp);
  HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_SYS_CTRL2, I2C_MEMADD_SIZE_8BIT, &temp, 1, 200);
  
  return(0);
}


//--------------------------------------------------------------
// interne Funktion
//--------------------------------------------------------------
void P_Touch_Config(void)
{
 static u8 regArray[10]={0x49,0x01,0x9A,0x01,0x01,0x00,0x01,0x01,0x03,0xFF};	
  P_Touch_FnctCmd(IOE_TP_FCT, ENABLE);
  
 // UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_ADC_CTRL1, 0x49);
    HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_ADC_CTRL1, I2C_MEMADD_SIZE_8BIT, &regArray[0], 1, 200);
	
  //UB_I2C3_Delay(STMPE811_DELAY);
    DelayOnFastQ(2000);
	
	
  //UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_ADC_CTRL2, 0x01);
    HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_ADC_CTRL2, I2C_MEMADD_SIZE_8BIT, &regArray[1], 1, 200);
	
    P_Touch_IOAFConfig((uint8_t)TOUCH_IO_ALL, DISABLE);
  
  //  UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_TP_CFG, 0x9A);
    HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_TP_CFG, I2C_MEMADD_SIZE_8BIT, &regArray[2], 1, 200);
  //  UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_FIFO_TH, 0x01);
    HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_FIFO_TH, I2C_MEMADD_SIZE_8BIT, &regArray[3], 1, 200);
  // UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_FIFO_STA, 0x01);
    HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_FIFO_STA, I2C_MEMADD_SIZE_8BIT, &regArray[4], 1, 200);
  // UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_FIFO_STA, 0x00);
    HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_FIFO_STA, I2C_MEMADD_SIZE_8BIT, &regArray[5], 1, 200);   
  // UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_TP_FRACT_XYZ, 0x01);
    HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_TP_FRACT_XYZ, I2C_MEMADD_SIZE_8BIT, &regArray[6], 1, 200);   
  // UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_TP_I_DRIVE, 0x01);
    HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_TP_I_DRIVE, I2C_MEMADD_SIZE_8BIT, &regArray[7], 1, 200);
  // UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_TP_CTRL, 0x03);
    HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_TP_CTRL, I2C_MEMADD_SIZE_8BIT, &regArray[8], 1, 200);
  // UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_INT_STA, 0xFF);
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

  //i2c_wert1=UB_I2C3_ReadByte(STMPE811_I2C_ADDR, 0);
  HAL_I2C_Mem_Read(&hi2c2,(uint16_t)STMPE811_I2C_ADDR,0x00,I2C_MEMADD_SIZE_8BIT,&temp,1,100);
  i2c_wert1 = (int16_t)temp;
  HAL_I2C_Mem_Read(&hi2c2,(uint16_t)STMPE811_I2C_ADDR,0x01,I2C_MEMADD_SIZE_8BIT,&temp,1,100);
  //i2c_wert2=UB_I2C3_ReadByte(STMPE811_I2C_ADDR, 1);
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
  //uint8_t tmp = 0;
  int16_t i2c_wert;

 // i2c_wert=UB_I2C3_ReadByte(STMPE811_I2C_ADDR, IOE_REG_GPIO_AF);
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

 // UB_I2C3_WriteByte(STMPE811_I2C_ADDR, IOE_REG_GPIO_AF, tmp);
   HAL_I2C_Mem_Write(&hi2c2, (uint16_t)STMPE811_I2C_ADDR, (uint16_t)IOE_REG_GPIO_AF, I2C_MEMADD_SIZE_8BIT, &temp, 1, 200);
  
  return(0);
}


//--------------------------------------------------------------
// interne Funktion
//--------------------------------------------------------------
static uint16_t P_Touch_Read_X(void)
{
  int32_t x, xr;

  x = P_Touch_Read_16b(IOE_REG_TP_DATA_X);

  if(x <= 3000) {
    x = 3870 - x;
  }
  else {
    x = 3800 - x;
  }

  xr = x / 15;

  if(xr <= 0) {
    xr = 0;
  }
  else if (xr >= 240) {
    xr = 239;
  }

  return (uint16_t)(xr);
}


//--------------------------------------------------------------
// interne Funktion
//--------------------------------------------------------------
static uint16_t P_Touch_Read_Y(void)
{
  int32_t y, yr;

  y = P_Touch_Read_16b(IOE_REG_TP_DATA_Y);
  y -= 360;
  yr = y / 11;

  if(yr <= 0) {
    yr = 0;
  }
  else if (yr >= 320) {
    yr = 319;
  }

  return (uint16_t)(yr);
}


//--------------------------------------------------------------
// interne Funktion
//--------------------------------------------------------------
uint16_t P_Touch_Read_16b(uint32_t RegisterAddr)
{
  uint16_t ret_wert=0;
  int16_t i2c_wert1, i2c_wert2;

//  i2c_wert1=UB_I2C3_ReadByte(STMPE811_I2C_ADDR, RegisterAddr);
  HAL_I2C_Mem_Read(&hi2c2,(uint16_t)STMPE811_I2C_ADDR,(uint16_t)RegisterAddr,I2C_MEMADD_SIZE_8BIT,&temp,1,100);
  i2c_wert1 = (int16_t) temp;
//  i2c_wert2=UB_I2C3_ReadByte(STMPE811_I2C_ADDR, RegisterAddr+1);
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


