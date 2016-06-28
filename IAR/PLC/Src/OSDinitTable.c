#include "variables.h"
#include "OSDBasic.h"

#include "InputsTW.h"
#include "Dispinfo.h"

#include "OSDinitTable.h"
#include "tw8819.h"

	






extern	const	uint8_t	FOSDWinBase[];




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



