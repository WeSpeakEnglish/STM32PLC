#ifndef __OSDFONT_H__
#define __OSDFONT_H__

#define		SPI_FONT0_ADDRESS	0x40000L
#define		SPI_FONT1_ADDRESS	0x42000L
#define		SPI_LOGO_ADDRESS	0x47000L

void FOSDWinEnable(uint8_t winno, uint8_t en);
void FOSDWinAlpha(uint8_t winno, uint8_t color, uint8_t alpha);
uint16_t FOSDGetWindowX(uint8_t winno);
void FOSDSetWindowX(uint8_t winno, uint16_t x);
uint16_t FOSDGetWindowY(uint8_t winno);
void FOSDSetWindowY(uint8_t winno, uint16_t y);
void FOSDSetWindowW(uint8_t winno, uint16_t w);
void FOSDWinScreen(uint8_t winno, uint16_t x, uint16_t y, uint8_t w, uint8_t h, uint8_t zoomH, uint8_t zoomV);
void FOSDShowWindowAll(uint8_t on);
void FOSDLUT( uint16_t *PalettePtr, uint8_t StartAddr, uint8_t Count );
void FOSDDefaultLUT( void );
//void FOSDDownloadFontCode( void );
//void FOSDDownloadFont2Code( void );
void FontDMA( void );
void FOSDDownloadFontDirect(uint8_t dest_font_index, uint8_t const *src_loc, uint16_t size, uint8_t width, uint8_t height);
void FOSDDownloadFont( uint8_t FontMode );

void	FOSDDisplayLUT(void);
void 	FOSDRampLUT( uint8_t n );
extern const uint8_t	FOSDWinBase[];

#endif