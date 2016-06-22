#include "variables.h"
#include "OSDMenu.h"
#include "OSDBasic.h"

#include "InputsTW.h"
#include "Dispinfo.h"

#include "OSDinitTable.h"
#include "tw8819.h"
extern	const	uint8_t	FOSDWinBase[];


//*****************************************************************************
//
//           OSD Window Initialization Table
//
//*****************************************************************************
//=============================================================================
//			Initialize Window for DisplayLogo "Techwell"
//=============================================================================
const uint8_t Init_Osd_DisplayLogo[] = {

	16,
	OSD_Win_Num				( TECHWELLOGO_OSDWIN ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(3) | WIN_HZOOM(3) ),
	OSD_Win_Blending_01		( 0 ),
	OSD_Win_Start_02_4		( 30, 0x80 ),	// 3 bytes
	OSD_Win_Height_05		( 2 ),
	OSD_Win_Width_06		( 21 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN0 | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(0) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(0) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
 	OSD_Win_Attr_0E			( WIN_BG_COLOR_EX0 | BG_COLOR_BLACK | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(0) ),

	16,
	OSD_Win_Num				( TECHWELLOGO_OSDWIN+1 ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(3) | WIN_HZOOM(3) ),
	OSD_Win_Blending_01		( 0 ),
	OSD_Win_Start_02_4		( 264, 280 ),	// 3 bytes
	OSD_Win_Height_05		( 1 ),
	OSD_Win_Width_06		( 14 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN0 | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(0) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(0) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( WIN_BG_COLOR_EX0 | BG_COLOR_BLACK | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(42) ),

	16,
	OSD_Win_Num				( TECHWELLOGO_OSDWIN+2 ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN0 | WIN_V_EXT_EN0 | WIN_VZOOM(4) | WIN_HZOOM(4) ),
	OSD_Win_Blending_01		( 0 ),
	OSD_Win_Start_02_4		( 0, 0 ),	// 3 bytes
	OSD_Win_Height_05		( 3 ),
	OSD_Win_Width_06		( 14 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN0 | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(0) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(0) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(31) | WIN_CH_VSPACE(31) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(28), WIN_CH_VSPACE(15) ),	 // 2bytes
	OSD_Win_Attr_0E			( WIN_BG_COLOR_EX0 | BG_COLOR_BLACK | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(0) ),

	0 // End of Data
};
//
#ifdef ADD_ANALOGPANEL
const uint8_t Init_Osd_DisplayLogo_A[] = {

	16,
	OSD_Win_Num				( TECHWELLOGO_OSDWIN ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(WINZOOMx2) | WIN_HZOOM(WINZOOMx3) ),
	OSD_Win_Blending_01		( 0x0f ),
	OSD_Win_Start_02_4		( ((480*2-12*FONT_W*WINZOOMx3)/2), ((234-FONT_H*2*WINZOOMx2)/2)),	// 3 bytes
	OSD_Win_Height_05		( 2 ),
	OSD_Win_Width_06		( 12 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN0 | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(0) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( WIN_BG_COLOR_EX0 | BG_COLOR_BLACK | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(LOGO_ADDR) ),

	0 // End of Data
};
#endif
//=============================================================================
//			Initialize Window for Vchip Rathing
//=============================================================================
const uint8_t Init_Osd_DisplayVchipWindow[] = {

	16,
	OSD_Win_Num				( RATINGINFO_OSDWIN ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(LOGO_ZOOM) | WIN_HZOOM(LOGO_ZOOM) ),
	OSD_Win_Blending_01		( 0x0f ),
	OSD_Win_Start_02_4		( ((PHR_-FONT_W*18*LOGO_ZOOM-18)/2), ((PVR_-FONT_H*2*LOGO_ZOOM-8)/2)),	// 3 bytes
	OSD_Win_Height_05		( 2 ),
	OSD_Win_Width_06		( 18 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(0x10) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0x08) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( BACK_COLOR | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(RATINGINFO_ADDR) ),

	0 // End of Data
};
//=============================================================================
//			Initialize Window for DisplayMuteInfo
//=============================================================================
const uint8_t Init_Osd_DisplayMuteInfo[] = {

	16,
	OSD_Win_Num				( TVINFO_OSDWIN ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(MUTE_ZOOM) | WIN_HZOOM(MUTE_ZOOM) ),
	OSD_Win_Blending_01		( 0x0f ),
	OSD_Win_Start_02_4		( PHR_-FONT_W*4*MUTE_ZOOM, 0 ),	// 3 bytes
	OSD_Win_Height_05		( 1 ),
	OSD_Win_Width_06		( 4 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN0 | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(0x00) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0x00) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( WIN_BG_COLOR_EX0 | BG_COLOR_BLACK | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(MUTEINFO_ADDR) ),

	0 // End of Data
};
//=============================================================================
//			Initialize Window for DisplayTvchannel
//=============================================================================
const uint8_t Init_Osd_DisplayTVChannel[] = {

	16,
	OSD_Win_Num				( TVINFO_OSDWIN ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(TVCHN_ZOOM) | WIN_HZOOM(TVCHN_ZOOM) ),
	OSD_Win_Blending_01		( 0x0f ),
	OSD_Win_Start_02_4		( PHR_-FONT_W*3*TVCHN_ZOOM, 0 ),	// 3 bytes
	OSD_Win_Height_05		( 1 ),
	OSD_Win_Width_06		( 3 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN0 | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(0x00) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0x00) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( WIN_BG_COLOR_EX0 | BG_COLOR_BLACK | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(TVCHINFO_ADDR) ),

	0 // End of Data
};

//=============================================================================
//			Initialize Window for DisplayPCInfo
//=============================================================================
const uint8_t Init_Osd_DisplayPCInfo[] = {

	16,
	OSD_Win_Num				( PCINFO_OSDWIN ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(PCINFO_ZOOM) | WIN_HZOOM(PCINFO_ZOOM) ),
	OSD_Win_Blending_01		( 4 ),
	OSD_Win_Start_02_4		( 12, 13 ),	// 3 bytes
	OSD_Win_Height_05		( 1 ),
	OSD_Win_Width_06		( 10 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(4) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(4) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( BACK_COLOR | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(PCMEASUREINFO_ADDR) ),

	0 // End of Data
};
//=============================================================================
//			Initialize Window for DisplayInput
//=============================================================================
const uint8_t Init_Osd_DisplayInput[] = {

	//----- Input Selection : Zoom 2
	16,
	OSD_Win_Num				( RATINGINFO_OSDWIN ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(WINZOOMx1) | WIN_HZOOM(WINZOOMx1) ),
	OSD_Win_Blending_01		( 0x04 ),
	OSD_Win_Start_02_4		( 730, 450 ),	// 3 bytes
	OSD_Win_Height_05		( 1 ),
	OSD_Win_Width_06		( 4 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(8) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( BG_COLOR_TRANS | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR( RATINGINFO_ADDR) ),

	//----- Input Discription : Zoom 1
	16,
	OSD_Win_Num				( INPUTINFO_OSDWIN ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(WINZOOMx1) | WIN_HZOOM(WINZOOMx1) ),
	OSD_Win_Blending_01		( 0x04 ),
	OSD_Win_Start_02_4		( 11, 12 ),	// 3 bytes
	OSD_Win_Height_05		(1),
	OSD_Win_Width_06		(5),
	OSD_Win_BorderColor_07	( BG_COLOR_TRANS ),
	OSD_Win_Border_08		( WIN_BD_EN | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(8) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( BG_COLOR_TRANS | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(INPUTINFO_ADDR) ),

	0 // End of Data
};          


const uint8_t Init_Osd_DisplayInput_A[] = {
	//----- Input Selection : Zoom 1
	16,
	OSD_Win_Num				( INPUTINFO_OSDWIN-1 ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(INPUTINFO_ZOOM) | WIN_HZOOM(WINZOOMx2) ),
	OSD_Win_Blending_01		( 4 ),
	OSD_Win_Start_02_4		( 12, 13 ),	// 3 bytes
	OSD_Win_Height_05		( 1 ),
	OSD_Win_Width_06		( 9 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN0 | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(1) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( BACK_COLOR | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(INPUTINFO_ADDR) ),

	16,
	OSD_Win_Num				( INPUTINFO_OSDWIN ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(INPUTINFO_ZOOM) | WIN_HZOOM(WINZOOMx2) ),
	OSD_Win_Blending_01		( 4 ),
	OSD_Win_Start_02_4		( 11, 12 ),	// 3 bytes
	OSD_Win_Height_05		( 2 ),
	OSD_Win_Width_06		( 11 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN0 | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(1) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( BACK_COLOR | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(INPUTINFO_ADDR) ),

	0
};

//=============================================================================
//			Initialize Window for MainMenu
//=============================================================================
#if (defined ADD_ANALOGPANEL)
 #define OSDHSTART_MAX_A (480-(FONT_W+1)*25 - 56*2 -4)  //PHR - (pixelsize +Hspace)*MenuWidth - Hborder*2 - outlinewidth*2
 #define OSDVSTART_MAX_A (234-(FONT_H+11)*9 - 5*2 ) //  PVR - (Linesize+Vspace)*MENU_HEIGHT - Vborder*2  - outlinewidth*2
const uint8_t Init_Osd_MainMenu_A[] = {
						#include "data\MenuWindow_A.txt" 
};
#endif

#if ((defined WQVGA) && ((defined ANALOG_7INCH)||(defined TMD_ANALOG)))// || (defined QVGA) 
 #define OSDHSTART_MAX_A (480-(FONT_W+2)*25 - 56*2 -8) //OSDHSTART_MAX  //PHR - (pixelsize +Hspace)*MenuWidth - Hborder*2 - outlinewidth*2
 #define OSDVSTART_MAX_A OSDVSTART_MAX  //  PVR - (Linesize+Vspace)*MENU_HEIGHT - Vborder*2  - outlinewidth*2

const uint8_t Init_Osd_MainMenu[] = {
						#include "data\MenuWindow_A.txt" 
};
#elif (defined QVGA) && (defined SHARP_LQ050Q5DR01)
 #define OSDHSTART_MAX_A (480-(FONT_W+2)*25 - 56*2 -8-10) //OSDHSTART_MAX  //PHR - (pixelsize +Hspace)*MenuWidth - Hborder*2 - outlinewidth*2
 #define OSDVSTART_MAX_A OSDVSTART_MAX  //  PVR - (Linesize+Vspace)*MENU_HEIGHT - Vborder*2  - outlinewidth*2

const uint8_t Init_Osd_MainMenu[] = {
						#include "data\MenuWindow_A.txt" 
};
#else

const uint8_t Init_Osd_MainMenu[] = {
//						#include "data\MenuWindow.txt" 
/*===========================================================================*/
// Normal Panel Menu Window tabel
/*===========================================================================*/
	//----- Top(Left) Window
	16,
	OSD_Win_Num				( OSDMENU_TOPWIN ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_EN | WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_HZOOM(WINZOOMx2) | WIN_VZOOM(WINZOOMx2) ),
	OSD_Win_Blending_01		( 3 ),
	OSD_Win_Start_02_4		( (OSDHSTART_MAX/2+14), ((OSDVSTART_MAX/2)+FONT_H+10) ),	// 3 bytes
	OSD_Win_Height_05		( 5 ),
	OSD_Win_Width_06		( 2 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(4) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(3) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(4) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(2) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(4), WIN_CH_HSPACE(0), WIN_CH_VSPACE(2) ),	 // 2bytes
	OSD_Win_Attr_0E			( BACK_COLOR | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(OSDMENU_MAINADDR) ),

	//----- Title Window
	16,
	OSD_Win_Num				( OSDMENU_TITLEWIN ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(WINZOOMx1) | WIN_HZOOM(WINZOOMx1) ),
	OSD_Win_Blending_01		( 3 ),
	OSD_Win_Start_02_4		( (OSDHSTART_MAX/2), (OSDVSTART_MAX/2) ),	// 3 bytes
	OSD_Win_Height_05		( 0x09 ),
	OSD_Win_Width_06		( TITLE_MAX_DESC ),
	OSD_Win_BorderColor_07	( WIN_BD_COLOR_EX | CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN | WIN_BD_WIDTH(2) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(FONT_W*4+8) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0x05) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
//	OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(8) ),
//	OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(1) | WIN_CH_VSPACE(0x0b) ),
#ifdef BIG_FONT
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(8), WIN_CH_HSPACE(1), WIN_CH_VSPACE(0x0e) ),	 // 2bytes
#else
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(8), WIN_CH_HSPACE(1), WIN_CH_VSPACE(0x0b) ),	 // 2bytes
#endif
	OSD_Win_Attr_0E			( BG_COLOR_BLUE | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(OSDMENU_SUBADDR) ),

	//----- Sub(Right) Window
	16,
	OSD_Win_Num				( OSDMENUWINDOW ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(WINZOOMx1) | WIN_HZOOM(WINZOOMx1) ),
	OSD_Win_Blending_01		( 3 ),
	OSD_Win_Start_02_4		( ((OSDHSTART_MAX/2)+FONT_W*4+18+14), (OSDVSTART_MAX/2+FONT_H+10) ),	// 3 bytes
	OSD_Win_Height_05		( MENU_HEIGHT ),
	OSD_Win_Width_06		( MENU_WIDTH ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(FONT_W*2-4) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0x16+1) ),
	OSD_Win_3D_0B			( WIN_3D_EN0 | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0x06) ),
#ifdef BIG_FONT
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0x0a) ),	 // 2bytes
#else
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0x06) ),	 // 2bytes
#endif
	OSD_Win_Attr_0E			( BACK_COLOR | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(OSDMENU_SUBADDR+MENU_WIDTH) ),

	//----- 3D Cursor Window
	16,
	OSD_Win_Num				( OSDCURSORWINDOW ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(WINZOOMx2) | WIN_HZOOM(WINZOOMx2) ),
	OSD_Win_Blending_01		( 3 ),
	OSD_Win_Start_02_4		( ((OSDHSTART_MAX/2)+7+14+1), ((OSDVSTART_MAX/2)+4+FONT_H+10+1) ),	// 3 bytes
	OSD_Win_Height_05		( 1 ),
	OSD_Win_Width_06		( 2 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN | WIN_BD_WIDTH(2) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(0) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(0) ),
	OSD_Win_3D_0B			( WIN_3D_EN | WIN_3D_TYPE0 | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLACK ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( BACK_COLOR | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(OSDMENU_MAINADDR) ),

	0 // End of Data
/*===========================================================================*/
};

#endif

const uint8_t Init_Osd_BarWindow[] = {

	//----- Bar/Message Window
	16,
	OSD_Win_Num				( OSDBARWINDOW ),	// 1 byte Offset for windows
	OSD_Win_CONTROL_00		( WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_VZOOM(BAR_ZOOM) | WIN_HZOOM(BAR_ZOOM) ),
	OSD_Win_Blending_01		( 5 ),
	OSD_Win_Start_02_4		( ((PHR_-FONT_W*25*BAR_ZOOM)/2), (PVR_-FONT_H*2*BAR_ZOOM-76) ),	// 3 bytes
	OSD_Win_Height_05		( 2 ),
	OSD_Win_Width_06		( 25 ),
	OSD_Win_BorderColor_07	( CH_COLOR_WHITE ),
	OSD_Win_Border_08		( WIN_BD_EN | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder_09		( WIN_H_BD_W(2) ),
	OSD_Win_VBorder_0A		( WIN_V_BD_W(4) ),
	OSD_Win_3D_0B			( WIN_3D_EN | WIN_3D_TYPE | WIN_3D_LEVEL0 | WIN_CH_BDSH_SEL(SEL_BORDER) | CH_COLOR_BLUE ),
	//OSD_Win_Shadow_0C		( WIN_SHADOW_EN0 | WIN_SHADOW_W(0) ),
	//OSD_Win_CH_Space_0D		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
 	OSD_Win_0C_0D			( WIN_SHADOW_EN0 | WIN_SHADOW_W(0), WIN_CH_HSPACE(0), WIN_CH_VSPACE(0) ),	 // 2bytes
	OSD_Win_Attr_0E			( BACK_COLOR | CH_COLOR_WHITE ),
	OSD_Win_SAddr_0F		( WIN_SADDR(OSDMENU_MAINADDR) ),

	0 // End of Data
};


IdName	struct_InputSelection[]={
	{ UNKNOWN			,	"" },				//don't remove or change this.
	{ INPUT_CVBS			,	"CVBS" },			//don't remove or change this.

												// you can change the order of the followings
	{ INPUT_SVIDEO			,	"S-Video" },

	{ INPUT_CVBS2			,	"CVBS2" },			//don't remove or change this.
	{0					,	""},				//don't remove or change this.
};


IdName struct_VInputStd[]={
	{ UNKNOWN			,	"" },				//don't remove or change this.
	{ NTSC,					"NTSC"},			//don't remove or change this.

	#ifdef SUPPORT_PAL
	{ PAL,					"PAL"},
	#endif

	#ifdef SUPPORT_SECAM
	{ SECAM,				"SECAM"},
	#endif

	#ifdef SUPPORT_PALM
	{ PALM,					"PALM"},
	#endif

	#ifdef SUPPORT_PALN
	{ PALN,					"PALN"},
	#endif

	#ifdef SUPPORT_PAL60
	{ PAL60,				"PAL60"},
	#endif

	#ifdef SUPPORT_NTSC4
	{ NTSC4,				"NTSC4.43"},
	#endif

	{0					,	""},				//don't remove or change this.
};

