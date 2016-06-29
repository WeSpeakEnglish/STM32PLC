#include "DispInfo.h"
#include "OSDBasic.h"
#include "OSDFont.h"

#include "OSDinitTable.h"
#include "tw8819.h"
#include "stm32f7xx_hal.h"
#include "InputsTW.h"
#include "OSDinitTable.h" 



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




	
#define INPUTINFO			0x10

#define RATINGINFO			0x40


void ClearOSDInfo(void)
{
	uint8_t dt;
	dt = DisplayedOSD; 
        if( dt & INPUTINFO )	        ClearInput();
}

void OSDDisplayInput(uint8_t * StringDisp)
{
	uint8_t	len1, len2;
	len1 = strlenA(StringDisp);
        len2 = strlenA("EXIT");
ClearOSDInfo();
	InitOSDWindow((uint8_t*)Init_Osd_DisplayInput);
        ClearDataCnt(INPUTINFO_ADDR, 51); // Total 42 Char.
	DrawAttrCnt(INPUTINFO_ADDR, DEFAULT_COLOR,51 );
	
        ClearDataCnt(RATINGINFO_ADDR, 51); // Total 42 Char.
	DrawAttrCnt(RATINGINFO_ADDR, DEFAULT_COLOR, 51 );
        WriteStringToAddr(INPUTINFO_ADDR, StringDisp, len1); 
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

	return 1;
//	ClearBlending();
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
