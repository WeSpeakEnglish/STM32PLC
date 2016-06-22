#include "DispInfo.h"
#include "OSDBasic.h"
#include "OSDFont.h"
#include "OSDmenu.h"
#include "OSDinitTable.h"
#include "tw8819.h"
#include "stm32f7xx_hal.h"
#include "InputsTW.h"
#include "OSDinitTable.h" 
#include "OSDstring.h"


uint8_t AudioVol = 50, 
	AudioBalance = 50, 
	AudioBass = 50,
	AudioTreble = 46,
	AudioEffect = 0;
uint8_t AudioMuteOn=0;

 uint16_t  OSDLastKeyInTime;		// in ms

//----------------------------------------------------------------------


uint16_t  OSDDisplayedTime;		//in ms
uint8_t  DisplayedOSD = 0;
uint8_t InputMain;


const uint8_t TW8806String[]=	{ "   TW8806   "};

const uint8_t TechwellString[]=	{ "Techwell,Inc" };

const uint8_t COMPONENT_STR[][15] = {
    "YPbPr 480i",	// 0
    "YPbPr 576i",	// 1
    "YPbPr 480p",	// 2
    "YPbPr 576p",	// 3
    "YPbPr 1080i",	// 4
    "YPbPr 720p",	// 5
	"YPbPr 1080p",	
    "YPbPr NONE",
};



//================================================================
//					Display information
//					Display Win0 :Intersil - from 0 ~ 3bit color, size 44
//					Display Win1 :Techwell - from 0x84 ~ 3bit color, size 15
//================================================================
const uint16_t INTERSIL_COLOR_8[8] = {
     0xFFFF,0x0020,0xDEDB,0xA534,0x6B6D,0xC826,0x4A49,0xDCD5
};
const uint16_t TECHWELL_COLOR_8[8] = {
     0xFFFF,0xC806,0xC98C,0xCB31,0xFE79,0xFCD9,0xCCD4,0xE71C
};
const uint16_t LOGO_COLOR_8[16] = {
     0xFFFF,0x0020,0xDEDB,0xA534,0x6B6D,0xC826,0x4A49,0xDCD5,
     0xFFFF,0xC806,0xC98C,0xCB31,0xFE79,0xFCD9,0xCCD4,0xE71C
};
void DisplayLogo(uint8_t offset)
{
	uint8_t  i;

	offset = (offset/8)*8;
	ReadTW88( 0xff );

 	InitOSDWindow((uint8_t *)Init_Osd_DisplayLogo);
	
	FOSDDownloadFont(2);

	//FOSDLUT( LOGO_COLOR_8, offset, 16 );
	FOSDLUT( (uint16_t *)LOGO_COLOR_8, offset, 8 );

	WriteTW88( 0xff, PAGE3_FOSD );

//	WriteTW88( REG30C, offset/4);				// select address
//	WriteTW88( REG30D, LOGO_COLOR_8[0]>>8 );	// makes background color as Multi-color #0
//	WriteTW88( REG30E, LOGO_COLOR_8[0] );

	WriteTW88(REG304, ReadTW88(REG304)&0xFE); // OSD RAM Auto Access Enable

	WriteTW88(REG304, (ReadTW88(REG304)&0xF3)); // Normal

	for ( i=0; i<70; i++ ) {
		WriteTW88( REG306, i );					// Font address
		WriteTW88( REG307, i*3 );				// Font Data
		WriteTW88( REG308, (offset/4)*0x11 );	   	// attribute - Select LUT position
		//WriteTW88( REG308, (offset/4)*0x11 );	   	// attribute - Select LUT position
		//WriteTW88( REG308, 0 );	   	// attribute - Select LUT position
	}

	WriteTW88( REG30B, 0 );				// 2bit multi color start = 0
	WriteTW88( REG353, 0 );				// 3bit multi color start = 0
	WriteTW88( REG354, 0xff );			// 4bit multi color start = 0

	FOSDWinEnable(TECHWELLOGO_OSDWIN-1,1);
	//FOSDWinEnable(TECHWELLOGO_OSDWIN,TRUE);
	FOSDWinEnable(TECHWELLOGO_OSDWIN,0);
	FOSDWinEnable(TECHWELLOGO_OSDWIN+1,1);
	
}

void ClearLogo(void)
{
	uint8_t page, i, j;

	page = ReadTW88( 0xff );
	//=============================== Fade OUT ======================================
	for ( i=0; i<9; i++ ) {
		HAL_Delay(30);
		WaitVBlank(1);	
		WriteTW88Page( PAGE3_FOSD );
		for ( j=0; j<32; j++ ) {
			WriteTW88( REG352, j );
			WriteTW88( FOSDWinBase[TECHWELLOGO_OSDWIN-1]+1, i );
			WriteTW88( FOSDWinBase[TECHWELLOGO_OSDWIN+1]+1, i );
		}
	}
	//============ Disable window and recover Trans value ============================
	WaitVBlank(1);	

	WriteTW88Page( PAGE3_FOSD );

	FOSDShowWindowAll(0);
	FOSDWinEnable(TECHWELLOGO_OSDWIN-1,0);
	FOSDWinEnable(TECHWELLOGO_OSDWIN+1,0);
	for ( j=0; j<32; j++ ) {
		WriteTW88( REG352, j );
		WriteTW88( FOSDWinBase[TECHWELLOGO_OSDWIN-1]+1, 0 );
		WriteTW88( FOSDWinBase[TECHWELLOGO_OSDWIN+1]+1, 0 );
	}

	WriteTW88( 0xff, page );
}

/*
void ClearDisplayedOSD( uint8_t newd )
{
	DisplayedOSD &= (~(newd));
}
*/

void SetDisplayedOSD( uint8_t newd )
{
	DisplayedOSD |= newd;
}
#define TVTUNER				0xd		//10
#define MUTE				1	
#define MENU				2	
#define TVVOL				4	
#define CC					8	
#define INPUTINFO			0x10
#define PCINFO				0x20
#define RATINGINFO			0x40
#define TVCHN				0x80

void ClearOSDInfo(void)
{
	uint8_t dt;

	dt = DisplayedOSD; 

	if( (dt & TVVOL) || ( dt & TVCHN) )	ClearTVInfo();

	if( dt & MUTE )			ClearMuteInfo();
	if( dt & INPUTINFO )	        ClearInput();
	if( dt & MENU )			CloseOSDMenu();
	if( dt & PCINFO )		ClearPCInfo();
	
}

void OSDDisplayInput(void)
{
	uint8_t	len1, len2;
	len1 = strlenA("KAM 1");
        len2 = strlenA("EXIT");
ClearOSDInfo();
	InitOSDWindow((uint8_t*)Init_Osd_DisplayInput);
        ClearDataCnt(INPUTINFO_ADDR, 51); // Total 42 Char.
	DrawAttrCnt(INPUTINFO_ADDR, DEFAULT_COLOR,51 );
	
        ClearDataCnt(RATINGINFO_ADDR, 51); // Total 42 Char.
	DrawAttrCnt(RATINGINFO_ADDR, DEFAULT_COLOR, 51 );
        WriteStringToAddr(INPUTINFO_ADDR, "KAM 1", len1); 
	WriteStringToAddr(RATINGINFO_ADDR, "EXIT", len2);
        
	FOSDWinEnable(OSD_Win_Num(RATINGINFO_OSDWIN),1);
	FOSDWinEnable(OSD_Win_Num(INPUTINFO_OSDWIN),1);
	FOSDShowWindowAll(1);
}

uint8_t ClearInput(void)
{
		
	//FOSDShowWindowAll(0);
	FOSDWinEnable(INPUTINFO_OSDWIN-2, 0);
	FOSDWinEnable(INPUTINFO_OSDWIN-1, 0);

	DisplayedOSD &= (~(INPUTINFO));
	#ifdef DEBUG_OSD
	dPrintf("\r\n++(ClearInput)");
	#endif

	return 1;
//	ClearBlending();
}

void DisplayVol(void)
{
	uint8_t const *Str ;
	uint8_t len;

	#ifdef DEBUG_OSD
	dPuts("\r\n++(DisplayVol)");
	#endif
	
	if(( DisplayedOSD & TVVOL ) == 0 ) 
	{

	ClearOSDInfo();
	FOSDDefaultLUT();
	HAL_Delay(100);


	InitOSDWindow((uint8_t *)Init_Osd_BarWindow);

	ClearDataCnt(OSDMENU_BARADDR, 50); // Total 25*2 Char.
	DrawAttrCnt(OSDMENU_BARADDR, BG_COLOR_CYAN | CH_COLOR_WHITE, 25 );	 
	DrawAttrCnt(OSDMENU_BARADDR+25, BG_COLOR_WHITE | CH_COLOR_CYAN, 25 );

	Str = StrVolume[OSDLang];
	len=strlenA((uint8_t *)Str);
	WriteStringToAddr(OSDMENU_BARADDR, (uint8_t *)Str, len);  

	FOSDWinEnable(OSDBARWINDOW, 1);
	FOSDShowWindowAll(1);

	}
	DisplayVolumebar(AudioVol);

	DisplayedOSD |= TVVOL;
//	OSDDisplayedTime = GetTime_ms();

}

void DisplayMuteInfo(void)
{
	uint8_t const	*Str ;
	uint8_t len;
	extern const uint8_t Init_Osd_DisplayMuteInfo[];
	extern const uint8_t *MuteOnStr[];

	ClearOSDInfo();
	InitOSDWindow((uint8_t *)Init_Osd_DisplayMuteInfo);

	Str = MuteOnStr[OSDLang];
	len = strlenA((uint8_t *)Str);
	WriteStringToAddr(MUTEINFO_ADDR, (uint8_t *) Str, len);  
	DrawAttrCnt(MUTEINFO_ADDR, BACK_COLOR|CH_COLOR_RED, len );	 

	FOSDWinEnable(TVINFO_OSDWIN, 1);
	FOSDShowWindowAll(1);
	DisplayedOSD |= MUTE;
}

void ClearMuteInfo(void)
{
	FOSDWinEnable(TVINFO_OSDWIN, 0);
	DisplayedOSD &= (~(MUTE));
}


uint8_t CheckAndClearOSD(void)
{
	
	return 0;
}

/*
void SetWindowStart(uint16_t x, uint16_t y)
{
	WriteDecoder(TW88_WINSTART_HI, (x>>8) | ((y>>8)<<4));
	WriteDecoder(TW88_WINXSTART, (uint8_t)x);
	WriteDecoder(TW88_WINYSTART, (uint8_t)y);
}
*/

/*
void SetWindowWidth(uint8_t width)
{
	WriteDecoder(TW88_WINWIDTH, width);
}
*/

void DisplayPCInfo(uint8_t const *ptr)
{
	uint16_t xstart, ystart;
	uint8_t len;

	len  = strlenA((uint8_t *)ptr);

	xstart = ( PHR_ - len*PCINFO_ZOOM*FONT_WIDTH ) / 2;
	ystart =  PVR_ / 3;
	
	InitOSDWindow((uint8_t *)Init_Osd_DisplayPCInfo);
	FOSDSetWindowX(PCINFO_OSDWIN, xstart);
	FOSDSetWindowY(PCINFO_OSDWIN, ystart);
	FOSDSetWindowW(PCINFO_OSDWIN, len);

	ClearDataCnt(PCMEASUREINFO_ADDR, len);
	DrawAttrCnt(PCMEASUREINFO_ADDR, CH_COLOR_RED, len);	 

	WriteStringToAddr(PCMEASUREINFO_ADDR, (uint8_t *)ptr, len);
	FOSDWinEnable(PCINFO_OSDWIN-1,1);
	FOSDShowWindowAll(1);
	
	DisplayedOSD |=PCINFO;

}

void ClearPCInfo(void)
{
	if( !(DisplayedOSD & PCINFO) )		return;			//ljy070803

	DisplayedOSD &= (~(PCINFO));
	FOSDWinEnable(PCINFO_OSDWIN-1,0);

//	PanelMute(0);								// HHY 1.63
}

/*
extern const uint8_t AutoAdjustInfo[]; 

void DisplayAutoAdjust(void)
{
	InitOSDWindow(Init_Osd_BarWindow);
	ClearDataCnt(OSDMENU_BARADDR, 50); // Total 25*2 Char.
	DrawAttrCnt(OSDMENU_BARADDR, BG_COLOR_CYAN | CH_COLOR_WHITE, 50 );	 
	WriteStringToAddr(OSDMENU_BARADDR, AutoAdjustInfo, 25);

	FOSDWinEnable(OSDBARWINDOW,TRUE);
	FOSDShowWindowAll(1);
}
void ClearAutoAdjust(void)
{
	FOSDWinEnable(OSDBARWINDOW,FALSE);
}
*/


//==================================================================
//						TV Info
//==================================================================

uint8_t ClearTVInfo(void)
{
	
	if( DisplayedOSD & TVVOL )
	{	FOSDWinEnable(OSDBARWINDOW, 0);
		DisplayedOSD &= (~(TVVOL));
	}
	else
	{
		FOSDWinEnable(TVINFO_OSDWIN, 0);
		DisplayedOSD &= (~(TVCHN));
	}
	return 1;
}

