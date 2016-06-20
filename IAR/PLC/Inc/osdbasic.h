//osd_basic.h
//LJY11012001
#ifndef __OSD_BASIC__
#define __OSD_BASIC__

// osd_basic.h
// char code
//#include "apilib.h"
#include "variables.h"

//ljy052903
//definition for internal OSD
#define FONT_WIDTH_TW88			12
#define FONT_HEIGHT_TW88		18
#define PIXS_PER_XSTEP_TW88		8
#define LINES_PER_YSTEP_TW88	4
#define MAX_OSDWINDOW_TW88		8

// Using TW88 OSD for Menu
#define FONT_WIDTH			12
#define FONT_HEIGHT			18
#define PIXS_PER_XSTEP		8
#define LINES_PER_YSTEP		4
#define MAX_OSDWINDOW		4

#define	MAX_FONT_uint8_tS		27
#define RAMFONT		0xFE
#define ROMFONT		0xFF
#define NO_UDFONT			226 

#define FONT_ROM	1
#define FONT_RAM	2


/////////////////////////////////
// Old Registers...
/*
	#define TW88_WIN1ATTR		0x76
	#define TW88_WIN1XSTART		0x77
	#define TW88_WIN1YSTART		0x78
	#define TW88_WIN1WIDTH		0x79
	#define TW88_WIN1HEIGHT		0x7a
	#define TW88_WIN1BRDATTR	0x7b
	#define TW88_WIN1BRDWIDTH	0x7c
	#define TW88_WIN1BRDHEIGHT	0x7d
	#define TW88_WIN1XSPACE		0x7e		// between characters.
	#define TW88_WIN1YSPACE		0x7f
	#define TW88_WIN1SADDR		0x80		// starting address of OSD ram for Windows 1
*/
/////////////////////////////////

// OSD

#define TW88_ENABLERAM		0x04	// TW8804C
#define TW88_WINSADDRLO		0x0F	// starting address of OSD ram for Windows 1
/*
#define TW88_FONTRAMADDR	0x99	// TW8804C

#define TW88_FONTRAMDATA	0x9a	// TW8804C
#define TW88_OSDRAMADDRHI	0x95	// TW8804C
#define TW88_OSDRAMADDRLO	0x96	// TW8804C
#define TW88_OSDRAMDATAHI	0x97	// TW8804C
#define TW88_OSDRAMDATALO	0x98	// TW8804C
#define TW88_MULTISTART		0x9b	// TW8804C
#define TW88_OSDLOCKUPSEL	0x9c
#define TW88_WINNUM			0x9e	// TW8804C
#define TW88_WINATTR		0x9f	//
#define TW88_WINXSTART		0xa1	//
#define TW88_WINYSTART		0xa2	//
#define TW88_WINSTART_HI	0xa0	//
#define TW88_WINWIDTH		0xa3	//
#define TW88_WINHEIGHT		0xa4	//
#define TW88_WINBRDATTR		0xa5	//
#define TW88_WINBRDWIDTH	0xa6	//
#define TW88_WINBRDHEIGHT	0xa7	//
#define TW88_WINSPACE		0xa8	// between characters.
#define TW88_WINZOOM		0xa9	//

#define TW88_WINSHADOW		0xab	//
#define TW88_WINBLENDING	0xac	//
#define TW88_WINCHEFFECT	0xad	//

*/
//Attributes for OSD
#define WINZOOMx1			0x01
#define WINZOOMx2			0x02
#define WINZOOMx3			0x03
#define WINZOOMx4			0x04
#define SHOW				0x08	

#define EXTENDED_COLOR		0x80
#define BG_COLOR_BLACK 		0x00	//For background color of window, border, and char. 
#define BG_COLOR_RED		0x40	
#define BG_COLOR_GREEN		0x20
#define BG_COLOR_YELLOW		0x60
#define BG_COLOR_BLUE		0x10
#define BG_COLOR_MAGENTA	0x50
#define BG_COLOR_CYAN		0x30
#define BG_COLOR_WHITE		0x70
#define BG_COLOR_TRANS		0x80	
#define BG_COLOR_MASK		0xf0	

#define CH_COLOR_BLACK 		0x00	//For color of char.
#define CH_COLOR_RED		0x04	
#define CH_COLOR_GREEN		0x02
#define CH_COLOR_YELLOW		0x06
#define CH_COLOR_BLUE		0x01
#define CH_COLOR_MAGENTA	0x05
#define CH_COLOR_CYAN		0x03
#define CH_COLOR_WHITE		0x07
#define CH_BLINK			0x08	
#define CH_COLOR_MASK		0x0f	

#define CL_BLACK 			0x00	//For color of char.
#define CL_BLUE				0x01
#define CL_GREEN			0x02
#define CL_CYAN				0x03
#define CL_RED				0x04	
#define CL_MAGENTA			0x05
#define CL_YELLOW			0x06
#define CL_WHITE			0x07
#define CL_BLINK			0x08	

// 0x76*(WindowNo*0x0b)
#define WINDOW_DISABLE		0x00
#define WINDOW_ENABLE		0x01
#define WINDOW_3D_ENABLE    0x04
#define WINDOW_3D_BOTTOM    0x08
#define WINDOW_3D_TOP	    0x00
#define WINDOW_TRANS_ENABLE 0x80

#define WINBDCOLOR_ENABLE	0x80
#define WINBDCOLOR_EXTENT	0x80


#define WINBLENDING_DISABLE 0x00
#define WINBLENDING_BACK    0x10
#define WINBLENDING_FORE    0x20
#define WINBLENDING_ALL     0x30

#define WINSHADOW_ENABLE	0x80
// 0xc8*WindowNo
#define WIN_MULTICOLOR_ENABLE 0x20
#define WIN_CH_EFFECT_ENABLE  0x10
#define WIN_CH_EFFECT_SHADOW  0x08



///////// TW8804C /////////////
// Window Number
#define WINNUM1				1
#define WINNUM2				2
#define WINNUM3				3
#define WINNUM4				4

// Index 0x00 Defination
#define OSD_Win_CONTROL_00(a)		a
#define WIN_EN				0x80
#define WIN_EN0				0x00
#define WIN_MULTI_EN		0x40
#define WIN_MULTI_EN0		0x00
#define WIN_V_EXT_EN		0x20
#define WIN_V_EXT_EN0		0x00
#define WIN_HZOOM(a)		((a-1)<<2)
#define WIN_VZOOM(a)		(a-1)

// index 0x01
#define OSD_Win_Blending_01(a)		a

// index 0x02 ~ 0x04
#define OSD_Win_Start_02_4(h,v)		(uint8_t)(((uint16_t)v>>8) | (((uint16_t)h>>8)<<4)),(uint8_t)h, (uint8_t)v

// index 0x05
#define OSD_Win_Height_05(a)		a

// index 0x06
#define OSD_Win_Width_06(a)			a

// index 0x07
#define OSD_Win_BorderColor_07(a)	a

// index 0x08 - Border_Color_Enable
#define OSD_Win_Border_08(a)		a
#define WIN_BD_EN			0x80
#define WIN_BD_EN0			0x00
#define WIN_BD_WIDTH(a)		a

// index 0x09
#define OSD_Win_HBorder_09(a)		a
#define WIN_H_BD_W(a)		a

// index 0x0a
#define OSD_Win_VBorder_0A(a)		a
#define WIN_V_BD_W(a)		a

// index 0x0b
#define	OSD_Win_3D_0B(a)			a
#define WIN_3D_EN				0x80
#define WIN_3D_EN0				0x00
#define WIN_3D_TYPE				0x40
#define WIN_3D_TYPE0			0x00
#define WIN_3D_LEVEL			0x20
#define WIN_3D_LEVEL0			0x00
#define WIN_CH_BDSH_SEL(a)		a
#define SEL_BORDER				0
#define SEL_SHADOW				0x10

// index 0x0c
//#define OSD_Win_Shadow_0C(a)		a
#define WIN_SHADOW_EN		0x80
#define WIN_SHADOW_EN0		0x00
#define WIN_SHADOW_W(a)		a

// index 0x0d
//#define OSD_Win_CH_Space_0D(a)		a			
#define WIN_CH_VSPACE(a)	a
#define WIN_CH_HSPACE(a)	a

#define OSD_Win_0C_0D(a,h,v)		a | ((h & 0x10)<<2) | ((v&0x10)<<1), (h<<4) | (v&0x0F)

// index 0x0e
#define OSD_Win_Attr_0E(a)			a			

// index 0x0f
#define OSD_Win_SAddr_0F(a)			a			
#define WIN_SADDR(a)		a


#define WIN_BG_COLOR_EX		0x80
#define WIN_BG_COLOR_EX0	0x00

#define WIN_BD_COLOR_EX		0x80
#define WIN_BD_COLOR_EX0	0x00

#define WIN_SHADOW_COLOR_EX		0x80
#define WIN_SHADOW_COLOR_EX0	0x00

#define WIN_CH_BDSH_COLOR_EX	0x08
#define WIN_CH_BDSH_COLOR_EX0	0x00


#define OSD_Win_Num(a)				(a-1)


#define	SetOSDWindowNum(winno)		WriteTW88(TW88_WINNUM, winno-1)

//#define  OSD_Window_Attr(Trans_en,Color,3D_Type,3D_en,W_en)       (((( Trans_en | Color ) | 3D_Type) | 3D_en) | W_en)
#define  OSD_Window_Attr(a,b,c,d,e)									(((( a | b ) | c) | d) | e)
#define  OSD_WShadow_Attr(W_Shadow_en,Color,Width)					W_Shadow_en | Color | Width
//#define  OSD_Blending(en,level)										en | (level & 0x0f)
//#define  OSD_Ch_Effect(Multi, Effect_En, ShadowBorder, Color)		Multi | Effect_En | ShadowBorder | Color  


struct OSDStrInfo 
{
	uint8_t	cnt;
	uint16_t	addr;
	uint8_t	attr;
	uint32_t	str;
};
/*
struct BarInfo {
	struct RegisterInfo BarCnt;
	uint8_t	winno;
	uint8_t	xoff;
	uint8_t	yoff;
	uint8_t	color;
	int		bar_cnt;
};
*/
struct FontData {
	uint8_t	font[27];
} ;

//====================================================================
//  Internal OSD Function
void CopyCharToOSDRAM_TW88(uint8_t Addr, uint8_t attr, uint8_t ch);
void CopyUDCharToOSDRAM_TW88(uint8_t Addr, uint8_t attr, uint8_t ch);
//uint8_t GetOSDWindowWidth_TW88(uint8_t winno);
uint16_t GetOSDWindowSA_TW88(uint8_t winno);
void SetOSDWindowX(uint8_t winno, uint8_t x);
void SetOSDWindowY(uint8_t winno, uint8_t y);

void SetOSDItalicsAndUnderline(uint8_t italics, uint8_t underline);

void SetOSDHBorderWidth_TW88(uint8_t winno, uint8_t w);
//uint8_t GetOSDWindowColor_TW88(uint8_t winno);
void SetOSDWindowColor_TW88(uint8_t CCWin, uint8_t color);
void EnableOSDRAMAndChangeFont(uint8_t type);
void WriteCharToOSDRAM(uint16_t addr, uint8_t ch, uint8_t attr);
void InitOSDWindow(uint8_t * ptr);

void ShowOSDWindowAll(uint8_t on);
void ShowOSDWindow(uint8_t winno, uint8_t onoff);
void ClearOSD_TW88(void);
//void CreateOSDWindow_TW88(uint8_t winno, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t sa, uint8_t attr);
/*not yet!!
//ljy012304...CC_ADJUST_POS
void SetOSDWindowXS_TW88(uint8_t winno, uint8_t xs);
void SetOSDWindowYS_TW88(uint8_t winno, uint8_t ys);
*/

//====================================================================
//	OSDMenu Functions

//--------------------------------------------------------------------
//	Functions used in only Menu
#define		CONVERT_CODE			0x80

void InitOSDWindow(uint8_t *ptr);

uint16_t GetOSDWindowX(uint8_t winno);
uint16_t GetOSDWindowY(uint8_t winno);
uint8_t CreateOSDWindowOutline(uint8_t winno, uint8_t w, uint8_t color);
void CreateOSDMenuWindow(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
void ClearOSDLine(uint8_t winno, uint8_t sx, uint8_t sy, uint8_t cnt, uint8_t attr);
void WriteStringToAddr(uint8_t addr, uint8_t *str, uint8_t cnt);
void DrawAttrString(uint8_t addr, uint8_t *str, uint8_t cnt);
void DrawAttrCnt(uint8_t addr, uint8_t color, uint8_t cnt);
void ClearDataCnt(uint8_t, uint8_t);


//--------------------------------------------------------------------
//	Functions used in Menu and others
#define     ClearOSD()									ClearOSD_TW88()

//================================================================
//	Font
void DownloadUDFont(void);
void DisplayROMFont(uint8_t);
void DisplayRAMFont(uint8_t);
void DownloadFont(uint8_t cod, const uint8_t * fontdata);
void DisplayGrid( void );
void DisplayCone( void );
void DisplayJapanese( void );
void TestRAMFont( void );
#ifdef BANKING
void DisplayMGrid( uint8_t );
void DisplayMessage( void );
void DisplayChinese( void );
void DisplayJapanese( void );
void DisplayKorean( void );
void DisplayGridBank0( uint8_t n );
void DisplayGridBank1( uint8_t n );
#endif

//================================================================
//	OSD COLOR
void Reset_OSDColorLookup(void);

//====================================================================
//				Conversion
//====================================================================
uint8_t utoa(uint16_t value, uint8_t *str, uint8_t radix);
uint8_t ltoa_K(long value, uint8_t *str, uint8_t);
uint8_t strlenA( uint8_t *str );




#endif	// __OSD_BASIC__
