#include "OSDBasic.h"
#include "OSDFont.h"
#include "tw8819.h"

//#include "FontData\udfont.h"
#include "FontData\FontAll1.h"
#include "FontData\Font2_16x26.h"
#include "FontData\CompanyLogo1.h"


#define DMA_SIZE	0x8000L

#define	FONTWIN1_ST		REG310
#define	FONTWIN2_ST		REG320
#define	FONTWIN3_ST		REG330
#define	FONTWIN4_ST		REG340

#define	FONTWIN_ENABLE	        0X00
#define	FONT_ALPHA		0x01

const uint8_t	FOSDWinBase[] = { FONTWIN1_ST, FONTWIN2_ST, FONTWIN3_ST, FONTWIN4_ST };



//=============================================================================
//		void FOSDWinEnable(uint8_t winno, uint8_t en)
//=============================================================================
/*	SPI OSD DE delay calculation 
HDE = REG(0x210[7:0])
Mixing = REG(0x400[1:1])

result = HDE - ( Mixing +41 )
*/ 
void FOSDWinEnable(uint8_t winno, uint8_t en)
{
	uint8_t index;
	uint8_t dat, page;

	page = ReadTW88( 0xff );

	index = FOSDWinBase[winno] + FONTWIN_ENABLE;

	WriteTW88( 0xff, PAGE3_FOSD );

	dat = ReadTW88(index);
	if( en ) WriteTW88(index, dat | 0x80);
	else     WriteTW88(index, dat & 0x7F);

	WriteTW88( 0xff, page );
}
	 
//=============================================================================
//		void FOSDWinAlpha(uint8_t winno, uint8_t color, uint8_t alpha)
//=============================================================================
void FOSDWinAlpha(uint8_t winno, uint8_t color, uint8_t alpha)
{
	uint8_t	index = FOSDWinBase[winno] + FONT_ALPHA;
	uint8_t	page;

	page = ReadTW88( 0xff );

	WriteTW88( 0xff, PAGE3_FOSD );

	//WriteTW88( index, ( color <<4 ) + alpha );	 		// first select color
    WriteTW88( index, ( color <<4 ) + (0x0f&ReadTW88( index )) );   // first select color
	WriteTW88( index, ( color <<4 ) + alpha );			// second write alpha value

	WriteTW88( 0xff, page );
}

//=============================================================================
//		uint16_t FOSDGetWindowX(uint8_t winno)	  : winno 1~4
//=============================================================================
#ifdef SUPPORT_OSDPOSITIONMOVE
uint16_t FOSDGetWindowX(uint8_t winno)
{
	uint8_t 	index;
	uint8_t	page;
	uint16_t	Pos;

	page = ReadTW88(0xff);

	WriteTW88( 0xff, PAGE3_FOSD );

	index = FOSDWinBase[winno-1];

	Pos = ReadTW88(index+2)&0x70;
	Pos <<= 4;
	Pos += ReadTW88(index+3);

	WriteTW88( 0xff, page );

	return (Pos);
}
#endif

//=============================================================================
//		void FOSDSetWindowX(uint8_t winno, uint16_t x)	  : winno 1~4
//=============================================================================
void FOSDSetWindowX(uint8_t winno, uint16_t x)
{
	uint8_t 	index;
	uint8_t	page;

	page = ReadTW88(0xff);

	WriteTW88( 0xff, PAGE3_FOSD );

	#ifdef DEBUG_OSD
	dPrintf("\nFOSDSetWindowX( %bd, %d )", winno, x );
	#endif
	index = FOSDWinBase[winno-1];

	WriteTW88(index+2, (ReadTW88(index+2)&0x8F) | ((x>>4)&0x70));
	WriteTW88(index+3, x);

	WriteTW88( 0xff, page );
}


//=============================================================================
//		uint16_t FOSDGetWindowY(uint8_t winno)	  : winno 1~4
//=============================================================================
uint16_t FOSDGetWindowY(uint8_t winno)
{
	uint8_t 	index;
	uint8_t	page;
	uint16_t	Pos;

	page = ReadTW88(0xff);

	WriteTW88( 0xff, PAGE3_FOSD );

	index = FOSDWinBase[winno-1];

	Pos = ReadTW88(index+2)&0x03;
	Pos <<= 8;
	Pos += ReadTW88(index+4);

	WriteTW88( 0xff, page );

	return (Pos);
}

//=============================================================================
//		void FOSDSetWindowY(uint8_t winno, uint16_t y)	  : winno 1~4
//=============================================================================
void FOSDSetWindowY(uint8_t winno, uint16_t y)
{
	uint8_t 	index;
	uint8_t	page;

	page = ReadTW88(0xff);

	WriteTW88( 0xff, PAGE3_FOSD );

	index = FOSDWinBase[winno-1];

	#ifdef DEBUG_OSD
	dPrintf("\nFOSDSetWindowY( %bd, %d )", winno, y );
	#endif

	WriteTW88(index+2, (ReadTW88(index+2)&0xFC)|(y>>8));
	WriteTW88(index+4, y);

	WriteTW88( 0xff, page );
}

//=============================================================================
//		void FOSDSetWindowW(uint8_t winno, uint16_t w)	  : winno 1~4
//=============================================================================
void FOSDSetWindowW(uint8_t winno, uint16_t w)
{
	uint8_t 	index;
	uint8_t	page;

	page = ReadTW88(0xff);

	WriteTW88( 0xff, PAGE3_FOSD );

	index = FOSDWinBase[winno-1];

	#ifdef DEBUG_OSD
	dPrintf("\nFOSDSetWindowW( %bd, %d )", winno, w );
	#endif

	WriteTW88(index+6, w);

	WriteTW88( 0xff, page );
}


//=============================================================================
//		void FOSDWinScreen(uint8_t winno, uint16_t x, uint16_t y, uint8_t w, uint8_t h, uint8_t zoomH, uint8_t zoomV)
//=============================================================================
void FOSDWinScreen(uint8_t winno, uint16_t x, uint16_t y, uint8_t w, uint8_t h, uint8_t zoomH, uint8_t zoomV)
{
	uint8_t 	index, temp;
	uint8_t	page;

	page = ReadTW88(0xff);

	WriteTW88( 0xff, PAGE3_FOSD );

	index = FOSDWinBase[winno];
	WriteTW88( 0xff, PAGE3_FOSD );
	temp = zoomH*4 + zoomV;
	temp += (ReadTW88( index ) & 0xf0);
	WriteTW88( index, temp );				// write Zoom value
	temp = x >> 8;
	temp <<= 4;
	temp += ( y >> 8 );
	WriteTW88( index+2,  temp );			// upper bit for position x, y
	WriteTW88( index+3, x );				// position x
	WriteTW88( index+4, y );				// position y
	WriteTW88( index+5, h );
	WriteTW88( index+6, w );

	WriteTW88( 0xff, page );
}

//=============================================================================
//		void FOSDShowWindowAll(uint8_t on)
//=============================================================================
void FOSDShowWindowAll(uint8_t on)
{
	uint8_t	page, val;

	page = ReadTW88(0xff);

	WriteTW88( 0xff, PAGE3_FOSD );


	if( on ) {
		val = ReadTW88(REG30C) & 0xBF;
	}
	else  {
		val = ReadTW88(REG30C)|0x40;
	}
	WaitVBlank	(1);				// Wait Vblank()
	WriteTW88(REG30C, val);	// bit6 is OSD On/Off
	WriteTW88( 0xff, page );
}


//HW 16 default color table
const uint16_t FOsdPaletteColor[16] = {
//*0:Black*/			0x0000,
/*3:DarkCyan*/		0x0410,
/*1:DarkBlue*/		0x0010,
/*2:Green*/			0x0400,
/*3:DarkCyan*/		0x0410,
/*4:DarkRed*/		0x8000,
/*5:DarkMagenta*/	0x8010,
/*6:DarkYellow*/	0x8400,
/*7:Gray*/			0x8410,
/*8:Silver*/		0xC618,
/*9:Blue*/			0x001F,
/*A:Lime*/			0x07E0,
/*B:Cyan*/			0x07FF,
/*V:Red*/			0xF800,
/*D:Magenta*/		0xF81F,
/*E:Yellow*/		0xFFE0,
/*F:White*/			0xFFFF 
};

//=============================================================================
//				   void FontLUT( void )
//=============================================================================
void FOSDDefaultLUT( void )
{
uint8_t	i, page;

	page = ReadTW88(0xff);
	WaitVBlank(1);	

	WriteTW88( 0xff, PAGE3_FOSD );

	for ( i=0; i<16; i++ ) {
		WriteTW88(REG30C, (ReadTW88(REG30C)&0xC0) | i);			// select address
		WriteTW88( REG30D, FOsdPaletteColor[i]>>8 );
		WriteTW88( REG30E, FOsdPaletteColor[i] );
	}

	WriteTW88( 0xff, page );
}



//=============================================================================
//				   void FOSDLUT( uint16_t *PalettePtr, uint8_t StartAddr, uint8_t Count )
//=============================================================================
void FOSDLUT( uint16_t *PalettePtr, uint8_t StartAddr, uint8_t Count )
{
uint8_t	i, page, j;

	#ifdef DEBUG_OSD
	dPuts("\nLUT update !!!!");
	#endif
	page = ReadTW88(0xff);
	WaitVBlank(1);	

	WriteTW88( 0xff, PAGE3_FOSD );

	j = ReadTW88(REG30C)&0xC0;
	for ( i=StartAddr; i<(StartAddr+Count); i++ ) {
		WriteTW88(REG30C, j | i);			// select address
		WriteTW88( REG30D, *PalettePtr>>8 );
		WriteTW88( REG30E, *PalettePtr );
		PalettePtr++;
	}

	WriteTW88( 0xff, page );
}

//=======================================
// Palette Functions
//=======================================

//old code use index 2 for normal foreground	   Now 6bit.(64).
#if 0
void FOSDSetPaletteColor(uint8_t start, uint16_t color, uint8_t size)
{
	uint8_t i;
	uint8_t r30c;
	uint8_t page;

	page = ReadTW88(0xff);
	WaitVBlank(1);	

	WriteTW88Page( PAGE3_FOSD );
	r30c = ReadTW88(REG30C) & 0xC0;
	for(i=start; i < (start+size); i++) {
		WriteTW88(REG30C, r30c | i );
		WriteTW88(REG30D, (uint8_t)(color>>8));
		WriteTW88(REG30E, (uint8_t)color);
	}
	
	WriteTW88Page(page);
}
//110124
void FOSDSetPaletteColorArray(uint8_t index, uint16_t *array, uint8_t size)
{
	uint8_t i, page;
	uint8_t r30c;

	page = ReadTW88( 0xff );
	WaitVBlank(1);	

	WriteTW88Page( PAGE3_FOSD );
	r30c = ReadTW88(REG30C) & 0xC0;
	dPrintf("\nFontOsdSetPaletteColorArray index:%bd",index);
	for(i=0; i < size; i++) {
		WriteTW88(REG30C, (index+i) | r30c); //index 2 is for normal foreground	   Now 6bit.(64).
		WriteTW88(REG30D, (uint8_t)(array[i] >> 8));
		WriteTW88(REG30E, (uint8_t)array[i]);
		dPrintf(" 0x%02bx%02bx(%04x)",(uint8_t)(array[i] >> 8),(uint8_t)array[i],array[i]);
	}

	WriteTW88( 0xff, page );
}
#endif

#if 0
//=============================================================================
//				   void FOSDDownloadFontCode( void )
//=============================================================================
void FOSDDownloadFontCode( void )
{
uint8_t	i, j, page;

	page = ReadTW88(0xff);

	WriteTW88( 0xff, 0 );
	WriteTW88( REG006, 0x20 );		// auto increment off
	WaitVBlank(1);	

	WriteTW88( 0xff, PAGE3_FOSD );

	WriteTW88( REG350, 0x09 );					// default FONT height: 18 = 9*2

	WriteTW88( REG300, ReadTW88(REG300) & 0xFD ); // turn OFF bypass for Font RAM
	WriteTW88( REG309, 0x00 ); //Font Addr

	i = 0;
	WriteTW88(REG304, ReadTW88(REG304) | 0x01);		// Font RAM access mode ON
	for ( i=0; i<0xA0; i++ ) {
		WriteTW88(REG309, i);

		for ( j = 0; j<27; j++ ) {
			WriteTW88( REG30A, ROMFONTDATA[i][j] );
		}
	}
	for ( i=0; i<0x22; i++ ) {
		WriteTW88(REG309, i+0xa0);

		for ( j = 0; j<27; j++ ) {
			WriteTW88( REG30A, RAMFONTDATA[i][j] );
		}
	}
	for ( i=0; i<(0x60-0x22); i++ ) {
		WriteTW88(REG309, i+0x22+0xa0);

		for ( j = 0; j<27; j++ ) {
			WriteTW88( REG30A, RAMFONTDATA[i+0x82][j] );
		}
	}
	WriteTW88(REG304, (ReadTW88(REG304) & 0xfe));		// OSD RAM access mode OFF

	WriteTW88( REG30B, 0xF0 );	  					// 2bit color font start
	WriteTW88( REG353, 0xF0 );
	WriteTW88( REG354, 0xF0 );

	WriteTW88( 0xff, page );
}

//=============================================================================
//				   void FOSDDownloadFontCode( void )
//=============================================================================
void FOSDDownloadFont2Code( void )
{
uint8_t	i, j, page;

	page = ReadTW88(0xff);
	WaitVBlank(1);	

	WriteTW88( 0xff, PAGE3_FOSD );

	WriteTW88( REG350, 0x09 );					// default FONT height: 18 = 9*2

	WriteTW88( REG300, ReadTW88(REG300) & 0xFD ); // turn OFF bypass for Font RAM
	WriteTW88( REG309, 0x00 ); //Font Addr

	i = 0;
	WriteTW88(REG304, ReadTW88(REG304) | 0x01);		// Font RAM access mode ON
	for ( i=0; i<0xA0; i++ ) {
		WriteTW88(REG309, i);

		for ( j = 0; j<27; j++ ) {
			WriteTW88( REG30A, RAMFONTDATA[i][j] );
		}
	}
	WriteTW88(REG304, (ReadTW88(REG304) & 0xfe));		// OSD RAM access mode OFF

	WriteTW88( REG30B, 0xF0 );	  					// 2bit color font start
	WriteTW88( REG353, 0xF0 );
	WriteTW88( REG354, 0xF0 );

	WriteTW88( 0xff, page );
}
#endif

//=============================================================================
//				   void FOSDDownloadFontDMA( uint32_t	StartAddr, uint16_t Size, uint8_t FontAddr )	 // TW8819 doesn't have DMA
//=============================================================================
void FOSDDownloadFontDirect(uint8_t dest_font_index, uint8_t const *src_loc, uint16_t size, uint8_t width, uint8_t height)
{
	uint8_t value, page, j;
	uint16_t i, FontSize;

	page = ReadTW88( 0xff );
	//save clock mode & select PCLK
	WaitVBlank(1);	

	WriteTW88Page( PAGE3_FOSD );
	value = ReadTW88(REG300);	
	if(width==16)	value |= 0x10;	   				//width 16
	else			value &= 0xEF;					//   or 12
	//value |= 0x02;									//Enable Bypass FontRam FIFO
	WriteTW88( REG300, value );  

	WriteTW88( REG304, (ReadTW88(REG304) | 0x01) ); 						//FontRAM access
	WriteTW88( REG309, dest_font_index ); 		//Font Addr
	WriteTW88( REG350, height >> 1 ); 				//Font height(2~32)
	WriteTW88( REG351, (width >> 2) * (height >> 1));	//sub-font total count.

	i = 0;
	FontSize = (uint16_t) width * height / 8;
	for ( i=0; i<size; i++ ) {
		WriteTW88( REG309, dest_font_index + i ); 		//Font Addr
		#if 1
		for ( j=0; j<FontSize; j++ ) WriteTW88( REG30A, *src_loc++ );
		#else
		WriteTW88n( REG30A, &src_loc[i*FontSize], FontSize );
		#endif
	}

	//value &= ~0x02;									//Disable Bypass FontRam FIFO
	//WriteTW88( 0x00, value );  

	WriteTW88(REG304, (ReadTW88(REG304) & 0xfe));		// OSD RAM access mode OFF

	WriteTW88( 0xff, page );
}


//=============================================================================
//				   void FOSDDownloadFont( void )
//=============================================================================
/* <LOOK-UP TABLE 8 COLORS> */
const uint16_t SPI_FONT1[40] = {
     0x0000,0x001F,0x07E0,0x07FF,0xF800,0xF81F,0xFFE0,0xFFFF,
     //0xD6BA,0x20E3,0xF79E,0x62E8,0xE104,0xA944,0x39A6,0x7BAC,0x51A6,0xC617,0x9CD1,0xB5B5,0x9BC9,0xDD85,0xF643,0xAC87,
     //0xE71c,0x0000,0xFFFF,0x62E8,0xF800,0xA944,0x39A6,0x7BAC,0x51A6,0xC617,0x9CD1,0xB5B5,0x9BC9,0xDD85,0xF643,0xAC87
     0x0410,0x20E3,0xF79E,0x62E8,0xE104,0xA944,0x39A6,0x7BAC,0x51A6,0xC617,0x9CD1,0xB5B5,0x9BC9,0xDD85,0xF643,0xAC87,
     0x07ff,0x0000,0xFFFF,0x62E8,0xF800,0xA944,0x39A6,0x7BAC,0x51A6,0xC617,0x9CD1,0xB5B5,0x9BC9,0xDD85,0xF643,0xAC87
};

void FOSDDownloadFont( uint8_t FontMode )
{
	uint8_t	page;
		page= ReadTW88(0xff);
		switch ( FontMode ) {
			case 0:
				FOSDDownloadFontDirect( 0, &FontAll[0][0], (uint16_t)0xE8, 12, 18);
				WriteTW88( 0xff, PAGE3_FOSD );
				WriteTW88( REG30B, 0xC6 );				// 2bit multi color start = 0
				WriteTW88( REG353, 0xC6 );				// 3bit multi color start = 0
				WriteTW88( REG354, 0xff );			// 4bit multi color start = 0
			break;
			case 1:
				FOSDDownloadFontDirect( 0, &Font2[0][0], (uint16_t)0x86, 16, 26);
				WriteTW88( 0xff, PAGE3_FOSD );
				WriteTW88( REG30B, 0x80 );				// 2bit multi color start = 0
				WriteTW88( REG353, 0x80 );				// 3bit multi color start = 0
				WriteTW88( REG354, 0x92 );				// 4bit multi color start = 0
				FOSDLUT( (uint16_t *)SPI_FONT1, 16, 40 );
			break;

			default:
				FOSDDownloadFontDirect( 0, (uint8_t *)SPI_FONT0_ADDRESS, (uint16_t)0x100, 12, 18);
			break;
		}
		WriteTW88(0xff, page);
}

//=============================================================================
//				   void FOSDDefaultLUT( uint8_t n ) // dump every Color LUTs
//=============================================================================
void FOSDRampLUT( uint8_t n )
{
uint8_t	i, page;

	page = ReadTW88(0xff);
	WaitVBlank(1);	

	WriteTW88( 0xff, PAGE3_FOSD );

	if ( n == 0 ) {		// gray pattern
		for ( i=0; i<64; i++ ) {
			WriteTW88(REG30C, (ReadTW88(REG30C)&0xC0) | i);			// select address
			WriteTW88( REG30D, (i>>3)|((i>>1)<<3) );
			WriteTW88( REG30E, (i>>1)|(i<<5) );
		}
	}
	else if ( n == 1 ) {		// Red pattern
		for ( i=0; i<64; i++ ) {
			WriteTW88(REG30C, (ReadTW88(REG30C)&0xC0) | i);			// select address
			WriteTW88( REG30D, 0x00 );
			WriteTW88( REG30E, (i>>1) );
		}
	}
	else if ( n == 2 ) {		// Green pattern
		for ( i=0; i<64; i++ ) {
			WriteTW88(REG30C, (ReadTW88(REG30C)&0xC0) | i);			// select address
			WriteTW88( REG30D, (i>>3) );
			WriteTW88( REG30E, (i<<5) );
		}
	}
	else if ( n == 3 ) {		// Blue pattern
		for ( i=0; i<64; i++ ) {
			WriteTW88(REG30C, (ReadTW88(REG30C)&0xC0) | i);			// select address
			WriteTW88( REG30D, ((i>>1)<<3) );
			WriteTW88( REG30E, 0xff );
		}
	}

	WriteTW88( 0xff, page );
}


//=============================================================================
//				   void FOSDDisplayLUT( void ) // dump every Color LUTs
//=============================================================================
void	FOSDDisplayLUT(void)
{
	uint8_t value, page, i, width, height;

	width = 16; height = 16;		// makes 16x16 FONT
	page = ReadTW88( 0xff );
	//save clock mode & select PCLK
	WaitVBlank(1);	

	WriteTW88Page( PAGE3_FOSD );
	value = ReadTW88(REG300);	
	if(width==16)	value |= 0x10;	   				//width 16
	else			value &= 0xEF;					//   or 12
	//value |= 0x02;									//Enable Bypass FontRam FIFO
	WriteTW88( REG300, value );  

	WriteTW88( REG304, (ReadTW88(REG304) | 0x01) ); 						//FontRAM access
	WriteTW88( REG350, height >> 1 ); 				//Font height(2~32)
	WriteTW88( REG351, (width >> 2) * (height >> 1));	//sub-font total count.

	WriteTW88( REG309, 0 ); 		//Font Addr	 1
	for ( i=0; i<8; i++ ) {
		WriteTW88( REG30A, 0x00 );
		WriteTW88( REG30A, 0x00 );
		WriteTW88( REG30A, 0xFF );
		WriteTW88( REG30A, 0xFF );
	}
	WriteTW88( REG309, 1 ); 		//Font Addr	 0
	for ( i=0; i<8; i++ ) {
		WriteTW88( REG30A, 0x00 );
		WriteTW88( REG30A, 0xFF );
		WriteTW88( REG30A, 0x00 );
		WriteTW88( REG30A, 0xFF );
	}

	WriteTW88(REG304, 0);		// OSD RAM access mode OFF	 and all effect off

	for ( i=0; i<64; i++ ) {
		WriteTW88( REG306, i );					// Font address
		WriteTW88( REG307, 0 );				// Font Data
		WriteTW88( REG308, (i / 4) );		   	// attribute - Select LUT position
	}

	WriteTW88( REG30B, 0 );				// 2bit multi color start = 0
	WriteTW88( REG353, 0xFF );				// 3bit multi color start = 0
	WriteTW88( REG354, 0xFF );			// 4bit multi color start = 0

	WriteTW88( 0xff, page );
}
