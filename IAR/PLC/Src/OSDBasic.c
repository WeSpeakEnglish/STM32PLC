#include "OSDBasic.h"
#include "tw8819.h"
#include "stm32f7xx_hal.h"

#ifdef BIG_FONT
#define COLORFONT				0x80
#define COLORFONT4				0x92
#define CODE2FONT				0xA0
#else
#define COLORFONT				0xC6
#define COLORFONT4				0xff
#define CODE2FONT				0xA0
#endif

extern const struct RegisterInfo UserRange;

//CODE uint8_t ZoomAttr[]={	0,	0,	0x40,	0x80,	0xc0	};

//IDATA struct BarInfo BarInfo;
struct OSDStrInfo OSDStrInfo;
extern	uint8_t   I2CAutoIncFlagOn ;
extern const	uint8_t	FOSDWinBase[];

uint8_t	const *ptrFont;



//=============================================================================
//			Download RAM Font Data
//=============================================================================
/*
struct MultiGridInfo
{
	unsigned char	NFonts;
	unsigned char	NChars;
	unsigned char	*LUT;
	unsigned char	NofWindows;
	unsigned int	*WPos0;
	unsigned char	*WColors0;
	unsigned int	*WPos1;
	unsigned char	*WColors1;
	unsigned int	*WPos2;
	unsigned char	*WColors2;
	unsigned int	*WPos3;
	unsigned char	*WColors3;
	unsigned char	*CharPos;
	unsigned char	*FontData;
	unsigned char	*DisplayData;
};
*/



//*****************************************************************************
//	OSD Window internal subfunction for TW88xx
//*****************************************************************************

//===============================================================================
//  void WriteStringToAddr(uint8_t addr, uint8_t *str, uint8_t cnt)
//===============================================================================
void WriteStringToAddr(uint8_t addr, uint8_t *str, uint8_t cnt)
{
uint8_t	page, i;

	page = ReadTW88( 0xff );

	WriteTW88( 0xff, PAGE3_FOSD );

	WriteTW88(REG304, ReadTW88(REG304)&0xFE); // OSD RAM Auto Access Enable

	//WriteTW88(0x04, (ReadTW88(0x04)&0xF3)|0x04); // Auto Data increment with 
	WriteTW88(REG304, (ReadTW88(REG304)&0xF3)); // Normal 

	//WriteTW88(0x06, addr);

	for ( i=0; i<cnt; i++ ) {
		WriteTW88(REG306, addr++);
		if ( *str >= COLORFONT4 ) {
			WriteTW88( REG308, 6 );			// starting LUT = 32
		}
		else if ( *str >= COLORFONT ) {
			//WriteTW88( 0x08, 4 );			// starting LUT = 16
			WriteTW88( REG308, 0 );			// starting LUT = 0
		}
		WriteTW88( REG307, *str++ );
	}

	WriteTW88( 0xff, page );
}


//===============================================================================
//  void DrawAttrCnt(uint8_t addr, uint8_t color, uint8_t cnt)
//===============================================================================
void DrawAttrCnt(uint8_t addr, uint8_t color, uint8_t cnt)
{
uint8_t	page, i, j;

	//if ( addr < 8 ) return;			// skip color font
	page = ReadTW88( 0xff );

	WriteTW88( 0xff, PAGE3_FOSD );

	WriteTW88(REG304, ReadTW88(REG304)&0xFE); // OSD RAM Auto Access Enable

	WriteTW88(REG304, (ReadTW88(REG304)&0xF3)|0x04); // Auto addr increment with D or A
	WriteTW88(REG306, addr);
	#ifdef BIG_FONT
	if ( addr == 6 ) {				// 4bit color
		for ( i=0; i<(cnt/8); i++) {
			for ( j=0; j<8; j++ )
				WriteTW88(REG308, 10);	// offset for 40
			Delay1ms(1);
		}
		for ( j=0; j<(cnt%8); j++ )
			WriteTW88(REG308, 10);
	}
	else {
		for ( i=0; i<(cnt/8); i++) {
			for ( j=0; j<8; j++ )
				WriteTW88(REG308, color);
			Delay1ms(1);
		}
		for ( j=0; j<(cnt%8); j++ )
			WriteTW88(REG308, color);
	}
	#else
	for ( i=0; i<(cnt/8); i++) {
		for ( j=0; j<8; j++ )
			WriteTW88(REG308, color);
		HAL_Delay(1);
	}
	for ( j=0; j<(cnt%8); j++ )
		WriteTW88(REG308, color);
	#endif

	WriteTW88( 0xff, page );
}

//===============================================================================
//  void ClearDataCnt(uint8_t addr, uint8_t cnt)
//===============================================================================
void ClearDataCnt(uint8_t addr, uint8_t cnt)
{
uint8_t	page, i;

	
	page = ReadTW88( 0xff );

	WriteTW88( 0xff, PAGE3_FOSD );

	WriteTW88(REG304, ReadTW88(REG304)&0xFE); // OSD RAM Auto Access Enable

	WriteTW88(REG304, (ReadTW88(REG304)&0xF3)|0x04); // Auto Data increment with 

	WriteTW88(REG306, addr);

	WriteTW88( REG304, ReadTW88(REG304)&0xDF);			// clear it
	for ( i=0; i<cnt; i++ ) {
		WriteTW88( REG307, ' ' );
	}

	WriteTW88( 0xff, page );
}
//*****************************************************************************
//
//	Conversion Functions.
//
//*****************************************************************************
uint8_t utoa(uint16_t value, uint8_t *str, uint8_t radix)
{
	uint8_t cnt;//, *str1;
	uint16_t i, div;

//	str1 = str;
	cnt=0;
	if( radix==10) {
		for(div = 10000; div>=10; div/=10) {
			i = value/div;
			if( i ) {
				*str++ = i+'0';
				cnt++;
			}
			else if( cnt )		// 100, 200, 20,,,,
				*str++ = '0';

			value%=div;
		}
		*str++ = value+'0';
		*str = 0;
	}
	else if( radix==16) {
		for(div = 0x1000; div>=0x10; div/=0x10) {
			i = value/div;
			if( i ) {
				if( i>=0xa ) 
					*str++ = i-0xa+'A';
				else
					*str++ = i+'0';
				value%=div;
			}
		}
		if( value>=0xa ) 
			*str++ = value-0xa+'A';
		else
			*str++ = value+'0';
		*str = 0;
	}
	return 1;
}
uint8_t strlenA( uint8_t *str )
{
	uint8_t i=0;

	while( *str++ ) i++;
	return i;
}
//=============================================================================
//			Init Menu Window Data initialize 
//=============================================================================
void InitOSDWindow(uint8_t *ptr)
{
	uint8_t i, j, page;
		
	page = ReadTW88(0xff);
	WriteTW88( 0xff, PAGE3_FOSD );


    i = 0;
	j = *ptr;
    while( j ) {
		ptr++;
		i = FOSDWinBase[*ptr];				// start register address
		ptr++;
		do {

			WriteTW88( i, *ptr );
			i++; ptr++;
			j--;
		} while(j);
		j = *ptr;
    };

	WriteTW88( 0xff, page );
}



