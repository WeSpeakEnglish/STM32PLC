#include "tw8819.h"
#include "ltdc.h"
#include "core.h"
#include "variables.h"
//#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_ltdc.h"
#include "i2c.h"
//#include "main.h"

static uint8_t InitCVBSAll[] = {
TW8819_ADDRESS,0,

0xFF, 0x00, // Page 00
0x02, 0xCA,
0x03, 0xFF,
0x04, 0x10,
0x06, 0x26,
0x07, 0x00,
0x08, 0xC6,
0x1F, 0x00,
0x80, 0x00,
0x88, 0x00,
0x90, 0x00,
0x98, 0x08,
0xD6, 0x00,
0xDB, 0x55,
0xDC, 0x00,
0xDD, 0x80,
0xDE, 0x00,
0xDF, 0x80,
0xF6, 0x00,
0xF7, 0x16,
0xF8, 0x01,
0xF9, 0x50,
0xFA, 0x00,
0xFB, 0x40,
0xFC, 0x30,
0xFD, 0x11,

0xFF, 0x01, // Page 01
0x01, 0x68,
0x02, 0x48,		// for intput Y2
0x04, 0x00,
0x05, 0x09,
0x06, 0x00,
0x07, 0x02,
0x08, 0x12,
0x09, 0xF0,
0x0A, 0x0F,
0x0B, 0xD0,
0x0C, 0xCC,
0x0D, 0x00,
0x10, 0x00,
0x11, 0x64,		//0x5C,
0x12, 0x11,
0x13, 0x80,
0x14, 0x80,
0x15, 0x00,
0x17, 0x80,
0x18, 0x44,
0x1A, 0x10,
0x1B, 0x00,
0x1C, 0x07,
0x1D, 0x7F,
0x20, 0x50,
0x21, 0x22,
0x22, 0xF0,
0x23, 0xD8,
0x24, 0xBC,
0x25, 0xB8,
0x26, 0x44,
0x27, 0x38,
0x28, 0x00,
0x29, 0x00,
0x2A, 0x78,
0x2B, 0x44,
0x2C, 0x30,
0x2D, 0x14,
0x2E, 0xA5,
0x2F, 0xE4,
0x30, 0x00,
0x31, 0x10,
0x32, 0xFF,
0x33, 0x05,
0x34, 0x1A,
0x35, 0x00,
0x36, 0x00,
0x37, 0xBD,
0x38, 0x90,
0x39, 0x9F,
0x3A, 0xFF,
0x3B, 0x0F,
0x40, 0x00,
0x41, 0x80,
0x42, 0x00,

0xFF, 0x02, // Page 02
0x01, 0x00,
0x02, 0x20,
0x03, 0x40,
0x04, 0x1C,
0x05, 0xAF,
0x06, 0x0F,
0x07, 0xBF,
0x08, 0x8F,
0x09, 0x00,
0x0A, 0x04,
0x0B, 0x01,
0x0C, 0x20,
0x0D, 0x81,
0x0E, 0x30,
0x0F, 0x02,
0x10, 0x23,
0x11, 0x20,
0x12, 0x03,
0x13, 0x00,
0x14, 0x04,
0x15, 0x2C,
0x16, 0xE0,
0x17, 0x01,
0x18, 0x50,
0x19, 0x00,
0x1A, 0x00,
0x1B, 0x00,
0x1C, 0x42,
0x1D, 0x4F,
0x1E, 0x02,
0x1F, 0x00,
0x20, 0x00,
0x21, 0x00,
0x40, 0x11,
0x41, 0x0A,
0x42, 0x05,
0x43, 0x01,
0x44, 0x64,
0x45, 0xF4,
0x46, 0x00,
0x47, 0x0A,
0x48, 0x36,
0x49, 0x10,
0x4A, 0x00,
0x4B, 0x00,
0x4C, 0x00,
0x4D, 0x44,
0x4E, 0x04,
0x80, 0x20,
0x81, 0x80,
0x82, 0x80,
0x83, 0x80,
0x84, 0x80,
0x85, 0x80,
0x86, 0x80,
0x87, 0x80,
0x88, 0x80,
0x89, 0x80,
0x8A, 0x80,
0x8B, 0x30,
0x8C, 0x00,
0xB0, 0x30,
0xB1, 0x40,
0xB2, 0x40,
0xB6, 0x67,
0xB7, 0x94,
0xBF, 0x0D,
0xE0, 0x00,
0xE1, 0x00,
0xE2, 0x00,
0xE3, 0x03,
0xE4, 0x21,
0xF0, 0x00,
0xF1, 0x00,
0xF2, 0x00,
0xF3, 0x10,
0xF4, 0x10,
0xF5, 0x10,
0xF8, 0x00,
0xF9, 0x80,

0xff, 0x00,

0xff, 0xff
};

//static uint8_t isInit=1;
/////////////////////////////////////////////////////////////////////////////////////
uint8_t WriteTW88Page(uint8_t* buf){
  static uint8_t buffer[2]={0xff,0x00};
  buffer[1] = *buf;
HAL_I2C_Master_Transmit(&hi2c2, TW8819_ADDRESS, buffer, 2, 1000);
return 0;
}

uint8_t WriteTW88(uint8_t addr, uint8_t* buf){
  static uint8_t buffer[2];
  buffer[0] = addr;
  buffer[1] = *buf;
HAL_I2C_Master_Transmit(&hi2c2, TW8819_ADDRESS, buffer, 2, 1000);
return 0;
}
//
//HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
// I2C_RequestMemoryRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint32_t Timeout)
uint8_t ReadTW88(uint8_t addr, uint8_t* buf){
HAL_I2C_Mem_Read(&hi2c2,(uint16_t)TW8819_ADDRESS, (uint16_t)addr, I2C_MEMADD_SIZE_8BIT, buf, 1, 1000);
return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
//***Video chip initialization control pin

void LCD_Video_GPIO_Deinit(void){
  HAL_LTDC_MspDeInit(&hltdc);
}
void LCD_Video_GPIO_Init(void){
  HAL_LTDC_MspInit(&hltdc);
}
void Switch_Camera(uint8_t type)
{
	uint8_t mode, val;
	
//	cur_cam = type;
	
	if(type > 0)
	{
//		BD_TW8819_Config();
		BD_Init_TW8819();
		ChangeCVBS();	
//		BD_I2C_Init();		//Re-initialize once, when there is no cause to prevent TW8819 I2C obstruction
	}
	
	if(type==0)
	{
		
                
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);		//Switch to STM	
                //WaitOnFastQ(); // one task from queue instead of waiting	
                DelayOnFastQ(10);
                LCD_Video_GPIO_Init();		
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC, ENABLE);
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, ENABLE);
	}
	else if(type==1)
	{	
		mode = PAGE1_DECODER;
		WriteTW88Page(&mode);
		val = 0x40;	
		WriteTW88( REG102, &val );
//		ChangeCVBS();
		LCD_Video_GPIO_Deinit();
                DelayOnFastQ(10); //one task from queue instead of waiting
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC, DISABLE);
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, DISABLE);		
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);		//Switch to TW8819		
	}
	else if(type==2)
	{
		mode = PAGE1_DECODER;
		WriteTW88Page(&mode);
		val = 0x44;	
		WriteTW88( REG102, &val );		
//		ChangeCVBS();
		LCD_Video_GPIO_Deinit();
                DelayOnFastQ(10);// one task from queue instead of waiting
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC, DISABLE);
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, DISABLE);		
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);		//Switch to TW8819	
	}
	else if(type==3)
	{
	        mode = PAGE1_DECODER;
		WriteTW88Page(&mode);
		val = 0x48;	
		WriteTW88( REG102, &val );	
//		ChangeCVBS();		
		LCD_Video_GPIO_Deinit();
                DelayOnFastQ(10);
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC, DISABLE);	
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, DISABLE);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);		//Switch to TW8819		
	}
	else if(type==4)
	{
		mode = PAGE1_DECODER;
		WriteTW88Page(&mode);
		val = 0x4C;	
		WriteTW88( REG102, &val );	
//		ChangeCVBS();		
		LCD_Video_GPIO_Deinit();
                DelayOnFastQ(10);
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC, DISABLE);
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, DISABLE);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);		//Switch to TW8819		
	}	
}

void BD_Init_TW8819(void)
{
	uint8_t 	 addr, index, val;//, mode;
	uint8_t 	*RegSet;
        static uint8_t buffer[2]={0xff,0x00};
        
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

	val = 0;
//	WriteTW88Page(&val);
//	ReadTW88(0,&mode);
	
	RegSet = InitCVBSAll;
	addr = *RegSet;
	//cnt = *(RegSet+1);
	RegSet+=2;

	while (( RegSet[0] != 0xFF ) || ( RegSet[1]!= 0xFF )) // 0xff, 0xff is end of data
	{			
		index = *RegSet;
		val = *(RegSet+1);
	//	WriteTW88(index,&val);
  buffer[0] = index;                
  buffer[1] = val;
HAL_I2C_Master_Transmit(&hi2c2, addr, buffer, 2, 1000);
	//	ReadTW88(index,&mode);
		RegSet+=2;
//		WriteTW88( 0xff, PAGE1_DECODER );
//		ReadTW88( REG102, &val);
//		val *=1;
	}
}

uint8_t CheckDecoderVDLOSS( uint8_t n )
{
	uint8_t	mode;

	mode = PAGE1_DECODER;
	WriteTW88Page(&mode);
	ReadTW88(REG101,&mode);
	while (n--) 
	{
		ReadTW88(REG101,&mode);
		if (( mode & 0x80 ) == 0 ) 
			return ( 0 );
		//delay_nus(1000); 
                DelayOnFastQ(10);
                
	}
	return ( 1 );
}

uint8_t CheckDecoderSTD( uint8_t n )
{
	uint8_t	mode;
	
	mode = PAGE1_DECODER;
	WriteTW88Page(&mode);
	while (n--) 
	{
		ReadTW88(REG11C,&mode);
		if (( mode & 0x80 ) == 0 ) return ( mode );
		//delay_nus(10000);
               DelayOnFastQ(10); 
	}
	return ( 0x80 );
}

uint8_t CheckAndSetDecoderScaler( void )
{
	uint8_t	mode,val;
	//int	vPeriod, vDelay;
	
	if ( CheckDecoderVDLOSS(100) ) 
		return( 1 );

	mode = CheckDecoderSTD(100);
	if ( mode == 0x80 ) return( 2 );

	mode >>= 4;

	if ( mode == 0 ) 
	{				// NTSC
		mode = PAGE1_DECODER;
		WriteTW88( 0xff,  &mode);
		ReadTW88( REG102, &val);
		ReadTW88( REG11D, &val);
	}
	else if ( mode == 1 ) 
	{			 	//PAL
//		mode = PAGE1_DECODER;
//		WriteTW88( 0xff,  &mode);		
//		ReadTW88( REG107, &val);
//		val |= 0x10;
//		WriteTW88( REG107, &val );
//		val = 32;
//		WriteTW88( REG109, &val );
//		val=0x18;
//		WriteTW88( REG10A, &val );						// change H-delay
//		vPeriod = 275;									// NTSC line number
//		vDelay += 7; 									// 6 = ( 288-275 ) / 2
//		mode = PAGE2_SCALER;
//		WriteTW88( 0xff,  &mode);
//		val = 0x12;
//		WriteTW88( REG206, &val );						// set V scale
//		val=0xA2;
//		WriteTW88( REG205, &val );						// set V scale
//		val=0x30;
//		WriteTW88( REG215, &val);						// set output V delay
	}
	else 
	{
		return(1);
	}
	
	return(0);
}

#define		ContrastY		0x84
#define		BrightnessY		0x8A
#define		HueY			0x80
#define		SaturationY		0x85
#define		SharpnessY		0x8B
uint8_t Sharpness[16] = { 0, 6, 13, 20, 26, 33, 40, 47, 54, 61, 67, 74, 80, 87, 94, 100 };

 union{
         uint8_t bytes[2];
         uint16_t word;
        }valOut;

uint16_t SetYCbCrContrast(uint16_t val)
{
	uint8_t mode;

	mode = PAGE2_IMAGE;
	WriteTW88( 0xff,  &mode);
	valOut.word *= 255;
	valOut.word += 50;
	valOut.word /= 100;
	WriteTW88( ContrastY, &valOut.bytes[0]);
	ReadTW88( ContrastY,&valOut.bytes[0]);
	valOut.word *= 100;
	valOut.word += 128;
	valOut.word /= 255;
	return (valOut.word);
}

uint16_t ReadYCbCrContrast(void)
{
	uint8_t mode,val;
	mode = PAGE2_IMAGE;
	WriteTW88( 0xff,  &mode);
	ReadTW88( ContrastY,&val);
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}

uint16_t SetYCbCrBright(uint16_t val)
{
	uint8_t mode;
	mode = PAGE2_IMAGE;
	WriteTW88( 0xff,  &mode);
	valOut.word *= 255;
	valOut.word += 50;
	valOut.word /= 100;
	WriteTW88( BrightnessY, &valOut.bytes[0]);
	ReadTW88( BrightnessY ,&valOut.bytes[0]);
	valOut.word *= 100;
	valOut.word += 128;
	valOut.word /= 255;
	return (valOut.word);
}

uint16_t ReadYCbCrBright(void)
{
	uint8_t mode,val;
	mode = PAGE2_IMAGE;
	WriteTW88( 0xff,  &mode);
	ReadTW88( BrightnessY ,&val);
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}

uint16_t SetYCbCrSaturation(uint16_t val)
{
	uint8_t mode;
	mode = PAGE2_IMAGE;
	WriteTW88( 0xff,  &mode);
	valOut.word *= 255;
	valOut.word += 50;
	valOut.word /= 100;
	WriteTW88( SaturationY, &valOut.bytes[0]);
	WriteTW88( SaturationY+1, &valOut.bytes[0]);
	ReadTW88( SaturationY,&valOut.bytes[0]);
	valOut.word *= 100;
	valOut.word += 128;
	valOut.word /= 255;
	return (valOut.word);
}

uint16_t ReadYCbCrSaturation(void)
{
	uint8_t mode,val;
	mode = PAGE2_IMAGE;
	WriteTW88( 0xff,  &mode);
	ReadTW88( SaturationY,&val );
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}

uint16_t SetYCbCrHUE(uint16_t val)
{
	uint8_t mode;
	mode = PAGE2_IMAGE;
	WriteTW88( 0xff,  &mode);	
	valOut.word *= 63;
	valOut.word += 50;
	valOut.word /= 100;
	valOut.word += 0x20;
	if ( valOut.word > 0x3f ) valOut.word = 0x3f;
	valOut.word &= 0x3F;
	WriteTW88( HueY, &valOut.bytes[0]);
	ReadTW88( HueY,&valOut.bytes[0]);
	valOut.word += 0x20;
	valOut.word &= 0x3F;
	valOut.word *= 100;
	valOut.word += 32;
	valOut.word /= 63;
	return (valOut.word);
}

uint16_t ReadYCbCrHUE(void)
{
	uint8_t mode,val;
	mode = PAGE2_IMAGE;
	WriteTW88( 0xff,  &mode);	
	ReadTW88( HueY,&val );
	val += 0x20;
	val &= 0x3F;
	val *= 100;
	val += 32;
	val /= 63;
	return (val);
}

uint16_t SetYCbCrSharp(uint16_t val)
{
	uint8_t	i,mode;

	mode = PAGE2_IMAGE;
	WriteTW88( 0xff,  &mode);
	for (i=0; i<16; i++) {
		if ( val == (Sharpness[i]+1) ){
			val = i+1;
			break;
		}
		if ( Sharpness[i] == (val+1) ){
			val = i-1;
			break;
		}
	}
	ReadTW88( SharpnessY ,&mode);
	mode = ( mode & 0xf0) + val;
	WriteTW88( SharpnessY,  &mode);
	val = Sharpness[i];
	return (val);
}

uint16_t ReadYCbCrSharp(void)
{
	uint8_t	mode,val;

	mode = PAGE2_IMAGE;
	WriteTW88( 0xff,  &mode);
	ReadTW88( SharpnessY ,&mode);
	val = mode & 0x0f;
	val = Sharpness[val];
	return (val);
}

uint8_t ChangeCVBS( void )
{
	uint8_t result=0,val;  //,mode;

	BD_Init_TW8819( );

	// Get Image control register value
//	SetYCbCrContrast( 50 );
//	SetYCbCrBright( 80 );
//	SetYCbCrSaturation( 50 );
//	SetYCbCrHUE( 50 );
//	SetYCbCrSharp( 20 );

//	mode=PAGE0_GENERAL;
//	WriteTW88( 0xff, &mode );
//	ReadTW88(0x00,&val);
//	mode = 0x26;
//	WriteTW88( 0x06, &mode);
//	ReadTW88(0x06,&val);
//	mode = 0x2;
//	WriteTW88( 0x07, &mode);	
//	ReadTW88(0x07,&val);
//	mode = 0xc6;
//	WriteTW88( 0x08, &mode);	
//	ReadTW88(0x08,&val);
//	mode = 0x00;
//	WriteTW88( 0x41, &mode);
//	ReadTW88(0x41,&val);	
//	
//	mode=PAGE1_DECODER;
//	WriteTW88( 0xff, &mode);
//	ReadTW88(0xFF,&val);
//	mode = 0x48;
//	WriteTW88( 0x02, &mode);	
//	ReadTW88(0x02,&val);
	
//	mode = 0x07;	
//	WriteTW88( 0x1c, &mode);	
//	ReadTW88(0x1c,&val);	
	
//	//soft start
//	mode=PAGE0_GENERAL;
//	WriteTW88( 0xff, &mode );
//	mode = 0xa6;
//	WriteTW88( 0x06, &mode);
//	//decoder rescan
//	mode=PAGE1_DECODER;
//	WriteTW88( 0xff, &mode);
//	mode = 0x8f;
//	WriteTW88( 0x1d, &mode);	

	//delay_nus(10000);	
        DelayOnFastQ(10);

	ReadTW88(0xFF,&val);
	ReadTW88(0x01,&val);
	ReadTW88(0x02,&val);
	ReadTW88(0x1c,&val);

	result = CheckAndSetDecoderScaler();
	
//	OSDSetDEDelay();
//	BlueScreenOnOff(1);
	
	return(result);
}