#include "InputsTW.h"
#include "ImageControl.h"
#include "OSDinitTable.h"
#include "OSDBasic.h"
#include "stm32f7xx_hal.h"
#include "tw8819.h"
#include "DispInfo.h"

#define	INPUT_CHANGE_DELAY	300

#define PAGE1_DECODER		0x01	//0x101::0x142
#define PAGE2_SCALER		0x02	//0x201::0x21E

//------------------------------------
//VInputStdDetectMode
#define AUTO	0

//VInputStd
#define NTSC	1			
#define PAL	2
#define SECAM	3
#define NTSC4	4
#define PALM	5
#define PALN	6
#define PAL60	7
//-----------------------------------------------

uint8_t	InputMainLoss = 0;

 uint16_t  IVF;
 uint32_t	IHF;

uint8_t	DecoderMode = 7;
uint8_t	YUVMode = 7;
uint8_t	TW9900Mode = 7;

extern	uint8_t	InputMain;






//=============================================================================
//		uint8_t IsNoInput(void)			                                               
//=============================================================================
uint8_t IsNoInput(void)
{
	uint8_t	page, ret;

	page = ReadTW88(0xff);
	WriteTW88Page(PAGE1_DECODER);
	ret = ReadTW88(CSTATUS) & 0x80; 
	WriteTW88Page(page);
	if ( ret ) return 1;
	else	return 0;
}


//=============================================================================
//		uint8_t ReadVInputSTD(void)			                                               
//=============================================================================
uint8_t ReadVInputSTD(void)
{
	uint8_t std, page, ret;

	page = ReadTW88( 0xff );
	
	if( IsNoInput() ) ret = 1; // Noinput!!
	WriteTW88Page(PAGE1_DECODER);
	std = ReadTW88(SDT) & 0xf0;
	if( std & 0x80 ) ret = 0xff; // Detection in progress..
	else 
		ret = ((( std & 0x70 ) >> 4 ) + 1 );

	WriteTW88Page(page);
	return (ret);
}

void	Mute( uint8_t on )
{
	uint8_t	page;
	page = ReadTW88(0xff);
	WriteTW88Page(PAGE2_SCALER);
	if ( on ) {
		WriteTW88( REG21E, (ReadTW88(REG21E) | 0x01) );						// force Mute
	}
	else {
		WriteTW88( REG21E, (ReadTW88(REG21E) & 0xFE) );						// force Mute off
	}
	WriteTW88Page(page);
}



