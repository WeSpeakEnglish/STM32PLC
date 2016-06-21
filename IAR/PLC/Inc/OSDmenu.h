
#ifndef __OSDMENU_H__
#define __OSDMENU_H__

//=============================================================================
// Define
//=============================================================================

#define ICON_X					0
#define ICON_COLOR				DEFAULT_COLOR
#define TOPICON_COLOR			DEFAULT_COLOR
#define NO_ICON_COLOR			NIL

#define DESC_X					2
#define DESC_X_NO_ICON			0
#define DESC_COLOR				DEFAULT_COLOR

//#define CURSOR_START			0

#define ITEMSTARTX				0
#define TITLESTARTX				0


#define BAR_NUM_RADIX			10
#define NUM_RADIX				10

#define TVTUNER				0xd		//10
#define MUTE				1	
#define MENU				2	
#define TVVOL				4	
#define CC					8	
#define INPUTINFO			0x10
#define PCINFO				0x20
#define RATINGINFO			0x40
#define TVCHN				0x80

//===================================================================
// OSD Menu Icon define.
//
//#define COLORFONT				COLORFONT_START+0x100
#ifdef BIG_FONT
#define COLORFONT				0x80
#define COLORFONT4				0x92
#define CODE2FONT				0xA0
#else
#define COLORFONT				0xC6
#define COLORFONT4				0xff
#define CODE2FONT				0xA0
#endif
//=============================================================================
// Declare
//=============================================================================
typedef struct {
	uint16_t winno;
	uint16_t sx;
	uint16_t sy;
	uint16_t w;
	uint16_t h;
	uint16_t dx;
	uint16_t dy;
	uint16_t c;
} OsdBmpCommand;

union OsdBmpCmdDefined{
	uint16_t 	arg[8];
	OsdBmpCommand Cmd;
};
struct RegisterInfo {
    int16_t Min;
    int16_t Max;
    int16_t Default;
};
struct CmdOsd {
	uint8_t Cmd;
	uint8_t Winno;
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	uint8_t color;
	uint8_t dat;  // Using Zoom infomation,.. so far
//	FAR CONST uint8_t	*Ptr;
};

// Operation Command

//--------------------------------

// Method of "DisplayedOSD" :  0000xxxx : Menu related,  xxxx0000 : Independent with Menu


enum bar_type{
	BAR_LFKEY,
	BAR_OPEN,
	BAR_EMPTY,
	BAR_CURSOR,
   	BAR_CLOSE,
	BAR_FULL,
	BAR_RTKEY
} ;

enum key_type{
	NOTHING,    // Noting happens	
	UPMENU,     // MENUKEY
	DNMENU,	    // SELKEY/LEFTKEY
	CURSORINC,  // UP
	CURSORDEC,  // DOWN
	VALUEINC,   // RIGHT
	VALUEDEC,   // LEFT
	EXITMENU,   // EXIT
	ACTITEM    // LEFT
}; 

enum KeyDef {
	Menu_Key,
	Left_Key,
	Right_Key,
	Up_Key,
	Down_Key,
	Sel_Key,
	Input_Key,
	Mute_Key
};

//---------------------------------------------------------------
struct _ConvColor {
	uint8_t addr, color;	//EnConv[7]|EnOverwrite[6]|Addr[5:0], Conversion Color
};



//---------------------------------------------------------------
typedef uint8_t (*fpActFunc)(void);
typedef uint16_t (*fpGetFunc)(void);
typedef uint16_t (*fpSetFunc)(uint16_t val);



//----------------------------------------------------------------
struct MenuType {
	uint8_t	width,	height;
	uint8_t	TitleColor;	
	uint8_t	CursorColor;
};

struct NumType {
	uint8_t	PrePostCharLen;		// high nibble(pre) / low nibble(post)
	uint8_t	PrePostChar[4];
};

struct NumberStringType {
	uint8_t	x, y;
	uint8_t    width;
	uint8_t	BackColor;
	uint8_t	Radix;
	uint8_t	NumColor;
	uint8_t    MaxLen;				// maximum length of string
	uint8_t	PrePostCharLen;		// high nibble(pre) / low nibble(post)
	uint8_t	PrePostChar[3];
};

struct TimeType {
	uint8_t	x, y;
	uint8_t    width;
	uint8_t	BackColor;
	uint8_t	Format;				//_24H_TIME
	uint8_t	TimeColor;
	uint8_t    CursorColor;
};

struct EnumType {
	uint8_t    Sz;//size
	uint8_t    ByLang;
	uint8_t	Str[15];			// doesn't matter the size !!!
};

#define ICON_CH_SZ		2
//#define BAR_NUM_SZ		4
#define ICON_BUF_SZ		2
struct DefineMenu {
	//uint16_t						Icon[ICON_BUF_SZ];	
	uint8_t				                const	*Icon;
	uint8_t						**Desc;				
	uint8_t						PreFnId, 
								PostFnId;
//	void		(*CalltoFunction)(void);				    // Un/Dn/Sel Function
	uint8_t						IconColor;			//NIL: not to display icon
	uint8_t						DescColor;			//NIL: not to display desc. (IconColor==NIL && DescColor==NIL)->Last Item
	struct DefineMenu	                        const	*Child;
	uint8_t						Type;				// MENU, CHOICEMENU, BAR, NUMBER, TIME, ACTION, ENUM_STRING
	uint8_t						ActiveWithCursor;
	uint8_t						Id;
	uint8_t				                const	*TypeData;	//MenuType, BarType, NumType,,,
} ;

struct PictureInfo {

	uint8_t Register_Addr;
	uint8_t EEPROM_Addr;
	struct RegisterInfo 	const	*Control_Range;
};



//----------------------------------------------------------------

void	InitLogo( void );
void 	EnterMenu( void );
void 	ExitMenu( void );
void 	MoveCursorNext( void );
void 	MoveCursorPrev( void );
void 	MoveCursor( uint8_t key );
uint8_t 	SystemDemo( void );
uint8_t	InputChangeCVBS( void );
uint8_t	InputChangeSVIDEO( void );
uint8_t	InputChangeYUV( void );
uint8_t	InputChangeRGB( void );
uint8_t	InputChange656( void );
uint8_t	InputChangeCVBS2( void );


//=======================================================================
// 
//uint8_t GetOSDDuration(void);

void ResetVideoValue(void);
//#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
//void ResetPCValue(void);
//#endif
uint8_t GetOSDMenuLevel( void );

void DrawMenulist(uint8_t);
void Display_EnterPin(void);
void OSDHighMenu_sub(void);
void ResetOSDValue(void);
//uint8_t OnChangingValue(void);
//Not used yet *******************uint8_t OnChangingTime(void);

//uint16_t GetOSDclock(void);

void InitOSDMenu(void);
uint8_t CloseOSDMenu(void);
void OpenOSDMenu(void);
void OSDHighMenu(void);
void OSDSelect(void);
void OSDCursorMove(uint8_t flag );
void OSDLeftRight(uint8_t flag );
void OSDValueUpDn(uint8_t flag);
uint16_t SetItemValue( uint8_t id, uint8_t flag );
uint8_t DoAction(uint8_t id);

uint8_t SaveValue1(void);
void ClearValueWin(void);

void OSDNumber( uint8_t num );

void Set4WideScreen(uint8_t id);

uint8_t SetPCColorTemp(uint8_t flag);
void ResetPanelAttributeValue(void);
uint16_t GetItemValue( uint8_t);
void DisplayViewBar( uint16_t,uint8_t);
void DrawNum(uint16_t, const struct NumType *, uint16_t);
void DrawStringByLang( uint16_t, const struct EnumType *, uint16_t);

void DisplayVolumebar(uint8_t val);
void InitOSDMenuXY(void);

void Display_TVGuide_Window(void);
void Display_TVGuide_Status(void);

void ChangeVchip_LevelCursor(uint8_t);
void ChangeVchip_ContentCursor(uint8_t);
void Select_VchipLevel(void);
void SetVideoMode(uint8_t mode);
uint8_t GetVideoDatawithOffset(uint8_t offset);
void SetVideoContrast(uint8_t newv);
void SetVideoBrightness(uint8_t newv);
void SetVideoHue(uint8_t newv) ;
void SetVideoSaturation(uint8_t svtype, uint8_t newv) ;
uint8_t SetVideoSharpness(uint8_t flag) ;
void SetVideoBacklight(uint8_t newv) ;

void DisplayLineOSD(void);	// OSD Line display Demo

extern uint8_t DisplayInputHold;
extern uint8_t	OSDLang;
//-------------------------------------------------------------------
// OSD Window Information
//-------------------------------------------------------------------
// Window Number
#define OSDCURSORWINDOW			1
#define OSDMENUWINDOW			OSDCURSORWINDOW+1
#define OSDMENU_TOPWIN			OSDCURSORWINDOW+2
#define OSDMENU_TITLEWIN		OSDCURSORWINDOW+3
#define OSDBARWINDOW			OSDCURSORWINDOW

#define TECHWELLOGO_OSDWIN	1	
#define TVINFO_OSDWIN		1	
#define FONTTEST_OSDWIN		1	
#define INPUTINFO_OSDWIN	2  
#define RATINGINFO_OSDWIN	1	
#define PCINFO_OSDWIN		3	

//-------------------------------------------------------------------
// Window Start address
#define OSDMENU_MAINADDR	0
#define OSDMENU_SUBADDR     OSDMENU_MAINADDR+10    //25*9:196
#define OSDMENU_BARADDR		175 //OSDMENU_SUBADDR+225    //256   //25x2:50

#define INPUTINFO_ADDR		160	// 9x1:9
#ifdef WQVGA
#define INPUTINFO1_ADDR		INPUTINFO_ADDR+17	//17x3:51
#else
#define INPUTINFO1_ADDR		INPUTINFO_ADDR+34	//17x2:51
#endif

#define MUTEINFO_ADDR	    INPUTINFO1_ADDR+51	// 4x1:4
#define TVCHINFO_ADDR		MUTEINFO_ADDR//324	// 3X1:3
#define LOGO_ADDR			0
#define RATINGINFO_ADDR		0	//addr:210(8x1:8)
#define PCMEASUREINFO_ADDR  MUTEINFO_ADDR //10x1

#ifdef BIG_FONT
#define	FONT_W	16
#define	FONT_H	26
#else
#define	FONT_W	12
#define	FONT_H	18
#endif

//--------------------------------------------------------------------
// OSD Menu Position Range
#if ((defined WQVGA) && (defined ANALOG_7INCH)) || ((defined QVGA) && (defined SHARP_LQ050Q5DR01))
	#define OSD_PHR_ PHR_/2
#else
	#define OSD_PHR_ PHR_
#endif

#define OSDHSTART_MAX (OSD_PHR_-(FONT_W+1)*25 - 56*2 -4)  //PHR - (pixelsize +Hspace)*MenuWidth - Hborder*2 - outlinewidth*2
#define OSDVSTART_MAX (PVR_-(FONT_H+11)*9 - 5*2 ) //  PVR - (Linesize+Vspace)*MENU_HEIGHT - Vborder*2  - outlinewidth*2

#define OSDMENUX_MIN 1//0
#define OSDMENUX_MAX (OSDHSTART_MAX>>3)
#define OSDMENUX_50  (OSDHSTART_MAX>>4)

#define OSDMENUY_MIN 2//0
#define OSDMENUY_MAX (OSDVSTART_MAX>>2)
#define OSDMENUY_50  (OSDVSTART_MAX>>3)

//--------------------------------------------------------------------
// OSD Menu Width, Height 

#define TOTAL_MAX_HIGHT			9

#define TOPMENU_WIDTH			2
#define TOTAL_TOP_HEIGHT		5	// Include blank line!

#define TOPMENU_HEIGHT			4	

#if (defined QVGA) && (defined SHARP_LQ050Q5DR01)
#define MENU_WIDTH				17 //23//25 
#define	TITLE_MAX_DESC			17//25	//
#define BAR_LENGTH				0
#else
#define MENU_WIDTH				23//25 
#define	TITLE_MAX_DESC			23//25	//
#define BAR_LENGTH				8
#endif

#define MENU_HEIGHT				7//6 

#define BARNUM_LENGTH 11

//#define BACK_COLOR				BG_COLOR_CYAN
#define BACK_COLOR				BG_COLOR_TRANS//BG_COLOR_CYAN	| CH_COLOR_BLUE
#define DEFAULT_COLOR			BG_COLOR_TRANS|CH_COLOR_RED//BG_COLOR_CYAN   | CH_COLOR_WHITE
//#define ACTIVE_COLOR			BG_COLOR_YELLOW | CH_COLOR_WHITE
#define TITLE_BACK_COLOR		BG_COLOR_MAGENTA
#define TITLE_COLOR				TITLE_BACK_COLOR | CH_COLOR_YELLOW
#define COMMENT_COLOR			TITLE_BACK_COLOR | CH_COLOR_WHITE
#define CURSOR_COLOR			BG_COLOR_YELLOW | CH_COLOR_BLUE
#define OSD_INFO_COLOR			DEFAULT_COLOR

#define BAR_COLOR				DEFAULT_COLOR	
#define BAR_NUM_COLOR			DEFAULT_COLOR
#define NUM_COLOR				DEFAULT_COLOR

#define OSDMENU_OUTLINE_COLOR	BG_COLOR_BLUE


//DisplayedOSD
//		new	  |	MENU	TVINFO		CC		INPUTINFO		PCINFO		RATINGINFO
//	current   |
//============|=========================================================================
//	MENU	  |			TVINFO		--		INPUTINFO		PCINFO		MENU + RATINGINFO	
//			  |						 
//------------|-------------------------------------------------------------------------
//	TVINFO	  |	MENU	TVINFO		--		INPUTINFO		PCINFO		TVINFO+RATING
//------------|-------------------------------------------------------------------------
//	CC		  |	MENU->	TVINFO->			INPUTINFO->		PCINFO		RATINGINFO
//			  |	 CC		 CC					 CC				 		 
//------------|-------------------------------------------------------------------------
//	INPUTINFO |	MENU	TVINFO		--		INPUTINFO		PCINFO		--
//------------|-------------------------------------------------------------------------
//	PCINFO	  |	MENU	x			x		INPUTINFO		PCINFO		x
//------------|-------------------------------------------------------------------------
//	RATINGINFO|	MENU	TVINFO	   RATING   INPUTINFO		x			RATINGINFO
//									

//=======================================================================================
// OSD Menu Constant define.
//=======================================================================================
//Time type
#define _24H_TIME		1

//for previous, next, parent or child
#define YES				0xfe	
#define NO				0


//#define OVERWRITE		0
//#define POPUP			1

//CursorMove
#define VERT			0
#define HORI			1

//Type of MenuItem
#define OSDMENU			1
#define CHOICEMENU		2
#define ACTION			3
#define BAR				4
#define NUMBER			5
#define CHOICE			6
#define ENUM_STRING		7 //YESNO			7
#define CHOICE1			8
#define TIME			9
#define NUMBER_STRING	10

//Bar type
#define LEFT_FILLED		1
#define RIGHT_FILLED	2
#define NO_FILLED		3

//OSDmenu up and down key
#define UP					1
#define DN					2
#define RIGHT				3
#define LEFT				4

// Action Id
#define	DISP_INFO			0x16

#define	INPUTSELECTION				0x2f

#define CHANGE_TO_COMPOSITE			(0x20|INPUT_CVBS)			// Low nibble need to start from 1 
#define CHANGE_TO_COMPOSITE2		(0x20|INPUT_CVBS2)			// Low nibble need to start from 1 
#define CHANGE_TO_SVIDEO			(0x20|INPUT_SVIDEO)				// so that it match with COMPOSITE...
#define CHANGE_TO_COMPONENT			(0x20|INPUT_YUV)		
#define CHANGE_TO_656				(0x20|INPUT_656)		
//#define CHANGE_TO_TV				(0x20|TV)					
#define CHANGE_TO_PC				(0x20|INPUT_RGB)					
//#define CHANGE_TO_DIGITALVGA		(0x20|DIGITALVGA)			
//#define CHANGE_TO_SCART				(0x20|SCART)				


#define OSDPOSITIONMODE     0x10
#define OSD_VPOS			0x11
#define OSD_HPOS			0x12
#define OSD_HALFTONE		0x13
#define OSD_DURATION		0x14
#define RESET_OSDVALUE		0x15
#define OSDLANG				0x16

#define PANEL_CONTRAST		0x58
#define PANEL_BRIGHTNESS	0x59
#define PANEL_HUE			0x5a
#define PANEL_SHARPNESS		0x5b
#define PANEL_SATURATION	0x5c

#define PC_VPOS				0x43
#define PC_HPOS				0x44
#define PC_HSIZE			0x4d

#define PC_CLOCK			0x45
#define PC_PHASE			0x46

#define AUTOADJUST			0x47
#define AUTOADJUST2			0x48
//#define SAVE_AUTOADJUST		0x49
#define RESET_AUTOADJUST	0x4a

#define PCCOLORADJUST		0x4b
#define SAVE_COLORADJUST	0x4c
//#define RESET_COLORADJUST	0x4d

#define RESET_PCVALUE		0x4e

#define PC_COLOR_MODE		0x3f
#define PC_COLOR_TEMP		0x30
#define PC_COLOR_MODE1		0x31
#define PC_COLOR_MODE2		0x32
#define PC_COLOR_MODE3		0x33
#define PC_COLOR_USER		0x34
#define PC_COLOR_R			0x35
#define PC_COLOR_G			0x36
#define PC_COLOR_B			0x37

#define VIDEO_MODE			0x90
#define VIDEO_MODE1			0x91
#define VIDEO_MODE2			0x92
#define VIDEO_MODE3			0x93
#define VIDEO_USER			0x94
#define VIDEO_CONTRAST		0x95
#define VIDEO_BRIGHTNESS	0x96
#define VIDEO_SATURATION	0x97
#define VIDEO_HUE			0x99
#define VIDEO_SHARPNESS		0x9a
#define VIDEO_BACKLIGHT		0x9c		// add new value 
#define RESET_VIDEOVALUE	0x9b
#define VIDEOPICTURE		0x9f

#define INPUTSTD			0x6f
#define CHANGE_TO_AUTO		0x60
#define CHANGE_TO_NTSC		(0x60 | NTSC)
#define CHANGE_TO_PAL		(0x60 | PAL)
#define CHANGE_TO_SECAM		(0x60 | SECAM)
#define CHANGE_TO_NTSC4		(0x60 | NTSC4)
#define CHANGE_TO_PALM		(0x60 | PALM)
#define CHANGE_TO_PALN		(0x60 | PALN)
#define CHANGE_TO_PAL60		(0x60 | PAL60)




#define CLOSED_CAPTION		0x7f
#define CLOSEDCAP_OFF		0x70
#define CLOSEDCAP_CC1		0x71
#define CLOSEDCAP_CC2		0x72
#define CLOSEDCAP_CC3		0x73
#define CLOSEDCAP_CC4		0x74
#define CLOSEDCAP_T1		0x75
#define CLOSEDCAP_T2		0x76
#define CLOSEDCAP_T3		0x77
#define CLOSEDCAP_T4		0x78

#define TV_GUIDE			0x8f
#define NO_VCHIP_LOCK		0
#define VCHIP_TV_Y			1
#define VCHIP_TV_Y7			2
#define VCHIP_TV_G			3
#define VCHIP_TV_PG			4
#define VCHIP_TV_14			5
#define VCHIP_TV_MA			6
#define PASSuint16_t			0x87
#define NEW_PASSuint16_t		0x88
#define CHK_PASSuint16_t		0x89
#define RET_CHK_PASSuint16_t	0x8a

#define MPAA_RATING			0x9f
#define NO_MPAA_RATING		0
#define MPAA_G				1
#define MPAA_PG				2
#define MPAA_PG_13			3
#define MPAA_R				4
#define MPAA_NC_17			5
#define MPAA_X				6

#define TVINSTALL			0xa0
#define SCAN_CHANNEL		0xa1
#define AIR_CABLE_TV		0xa3
#define STORE_CLEAR_TVCHN	0xa4
#define MTS					0xa5
#define EDIT_CHANNEL		0xa6
	#define		MTS_STEREO			0//0x10
	#define		MTS_MONO			1//0x11

#define AUDIO_VOLUME		0xb8
#define AUDIO_BALANCE		0xb9
#define AUDIO_BASS			0xba
#define AUDIO_TREBLE		0xbb
#define AUDIO_LOUDNESS		0xbc
#define AUDIO_EFFECT		0xbd
#define AUDIO_MUTE			0xbe

#define MANUAL_TUNE_CHANNEL	0xab
#define FINE_TUNE_CHANNEL	0xac
#define STORE_PALCHANNEL	0xad

//#define CLEAR_TVCHN			0xb0
//#define STORE_TVCHN			0xb1

#define WIDESCREEN			0xc0
#define WIDESCREEN_NORMAL	0 
#define WIDESCREEN_WIDE		1 
#define WIDESCREEN_PANO		2
#define WIDESCREEN_FULL		3 
#define WIDESCREEN_ZOOM		4 

#define SYSTEM_CLOCK		0xd1
#define SYSTEM_CLOCK_H		0xd2
#define WAKEUP_TIME			0xd3
#define WAKEUP_TIME_H		0xd4
#define WAKEUP_PR			0xd5
#define OFF_TIME			0xd6
#define OFF_TIME_H			0xd7
#define SLEEP_TIMER			0xd8

#define OSDLANGI			0xe8
#define OSDLANGII			OSDLANGI+1
#define OSDLANGIII			OSDLANGI+2
#define OSDLANGIV			OSDLANGI+3


#define TOHIGHMENU			0xf1
#define MOVECURSOR2FIRST	0xf2
#define RESET_ALL			0xf3
#define EXITMENU			0xf4

#define CHOICE1_VAL			0xfc
#define CHOICE_VAL			0xfd
#define BAR_VAL				0xfe
#define NUM_VAL				0xff



#endif //__OSDMENU_H__
