#include "OSDBasic.h"
#include "OSDFont.h"
#include "InputsTW.h"
#include "OSDMenu.h"
#include "OSDString.h"
#include "DispInfo.h"
#include "tw8819.h"
#include "ImageControl.h"
#include "OSDinitTable.h"




extern 	uint8_t  DisplayedOSD;

uint8_t	OSDMenuX, OSDMenuY;
uint8_t	OSDLang=0;
uint8_t    OSDMenuLevel;
uint8_t     OnChangingValue = 0;
uint8_t    OSDNumberString[5];
uint8_t DisplayInputHold = 0;

uint16_t	OSDItemValue;
uint8_t   	I2CAutoIncFlagOn = 0;

uint8_t	title_item, cursor_item,   cur_osdwin,  val_osdwin=0xff, 
						val_index=0;


extern const uint8_t Init_Osd_MainMenu[];

struct MenuType   	const *MenuFormat;
struct RegisterInfo     const *BarRange;

struct DefineMenu 	const *MenuTitle;

struct DefineMenu 	const *MenuChild;
struct DefineMenu	const *MenuStack[4];

uint8_t MenuSP=0, MenuIndexStack[4];


//CODE struct RegisterInfo UserRange={0,100,50};
const struct RegisterInfo UserRange={0,100,50};

const struct RegisterInfo OSDMenuYRange= { OSDMENUY_MIN,	OSDMENUY_MAX,	OSDMENUY_50		};				
const struct RegisterInfo OSDMenuXRange= { OSDMENUX_MIN, OSDMENUX_MAX,	OSDMENUX_50		};				

const struct RegisterInfo PCUserColorTempRange = { 0, 55, 28 };			

const struct RegisterInfo PanelContrastRange={	0,255,128};
const struct RegisterInfo PanelBrightnessRange={	0,255,128};
const struct RegisterInfo PanelSharpnessRange={	0,7,3};
//CODE struct RegisterInfo PanelHueRange={	0,0x3f,0x20};
const struct RegisterInfo PanelHueRange={	-31,31,0};
const struct RegisterInfo PanelSaturationRange={	0,255,128};
const struct RegisterInfo PanelBacklightRange={	0,255,128};

const struct RegisterInfo VideoContrastRange={	0,255,128};
const struct RegisterInfo VideoBrightnessRange={	-128,127,0};
const struct RegisterInfo VideoSaturationRange={	0,255,128};
const struct RegisterInfo VideoHueRange={	-128,127,0};	//-90~90
const struct RegisterInfo VideoSharpnessRange={	0,15,7};
const struct RegisterInfo DigitalVideoSaturationRange={0, 0x7f, 0x40};


#define contrast 0
#define bright	 1
#define staturation_U 2
#define staturation_V 3
#define hue		 4
#define sharpness 5
#define backlight 7

#define PC_COLOR_DATA	0x80	// StartAddress of EEPROM for PC Color Temperature
#define PC_USERCOLOR	0x8A

extern const uint8_t	FOSDWinBase[];

extern 	     uint8_t	InputMain;


const uint8_t Contast_Reg_Addr[]={0x11, // Composite
							  0x11, // Svideo
	                          0x3b, // Component
	                          0x71, // DTV
	                          0x11, // TV
	                          0x3b  // Scart
	};
#ifdef WIDE_SCREEN
extern uint8_t WideScreenMode;
#define MAXWIDESCREEN 4
#endif
#ifdef SUPPORT_COMPONENT
extern  uint8_t  ComponentMode;
#endif

/////////////////////////////////////////////////////////////////////////////
// Mapping( int fromValue, CRegInfo fromRange,
//                                           int * toValue, CRegInfo toRange )
// Purpose: Map a value in certain range to a value in another range
// Input:   int fromValue - value to be mapped from
//          CRegInfo fromRange - range of value mapping from
//          CRegInfo toRange   - range of value mapping to
// Output:  int * toValue - mapped value
// Return:  Fail if error in parameter, else Success
// Comment: No range checking is performed here. Assume parameters are in
//          valid ranges.
//          The mapping function does not assume default is always the mid
//          point of the whole range. It only assumes default values of the
//          two ranges correspond to each other.
//          
//          The mapping formula is:
//
//            For fromRange.Min() <= fromValue <= fromRange.Default():
//
//				(fromValue -fromRange.Min())* (toRange.Default() - toRange.Min())
//				-------------------------------------------------------------------- + toRange.Min()
//					fromRange.Default() - fromRange.Min()
//
//			  For fromRange.Default() < fromValue <= fromRange.Max():
//
//				(fromValue - fromRange.Default()) * (toRange.Max() - toRange.Default())
//				--------------------------------------------------------------------- + toRange.Default()
//		             fromRange.Max() - fromRange.Default()
////
////////////////////////////////////////////////////////////////////////////
uint8_t Mapping1( int fromValue, const struct RegisterInfo *fromRange,
                                 int * toValue, const struct RegisterInfo *toRange ){

	// calculate intermediate values
	int a;
	int b;

	// perform mapping
	if ( fromValue <= fromRange->Default ) {
		a = toRange->Default - toRange->Min;
		b = fromRange->Default - fromRange->Min;
		// prevent divide by zero
		if( b==0 )		return (0);
		*toValue = (int) ( (uint32_t)fromValue- (uint32_t)fromRange->Min ) * a / b 
						+(uint32_t)toRange->Min;
	}
	else {
		a = toRange->Max - toRange->Default;
		b = fromRange->Max - fromRange->Default;
		// prevent divide by zero
		if( b==0 )		return (0);
        *toValue = (int) ( (uint32_t)fromValue - (uint32_t)fromRange->Default ) * a / b
                       + (uint32_t)toRange->Default;
	}

	#ifdef DEBUG_OSD
	dPrintf("\r\n++(Mapping1)%d(%d-%d-%d)", (uint16_t)fromValue, (uint16_t)fromRange->Min, (uint16_t)fromRange->Default, (uint16_t)fromRange->Max );
	dPrintf("->%d(%d-%d)", (uint16_t)*toValue, (uint16_t)toRange->Min, (uint16_t)toRange->Max);
	#endif
	
	return ( 1 );
   
}

//==============================================================
//
//  OSD Menu Operation Function
//
//==============================================================
#define MAX_OSDPOSITIONMODE	5
const uint8_t OSDPOSITIONMODE_TABLE[][2] = { 
	{OSDMENUX_50, OSDMENUY_50},
	{OSDMENUX_MIN,OSDMENUY_MIN},
	{OSDMENUX_MIN,OSDMENUY_MAX},
	{OSDMENUX_MAX,OSDMENUY_MAX},
	{OSDMENUX_MAX,OSDMENUY_MIN},
};

#ifdef SUPPORT_OSDPOSITIONMOVE
uint8_t GetOSDPositionMode(void)
{
	uint8_t val;
	val = GetOSDPositionModeEE();
//	Printf("OSD Position=%d\r\n",(uint8_t)val);
	
	return val;
}
#endif

#ifdef SUPPORT_OSDPOSITIONMOVE
uint8_t SetOSDPositionMode( uint8_t flag )
{
	int val, addx, addy;
	uint8_t i,inc, winno, page;
	uint8_t OSDStart[5][3];
	uint16_t tmp;

	#ifdef ADD_ANALOGPANEL
		if(IsAnalogOn()) return 0;
	#endif


	// Get OSD Position Mode
	i = GetOSDPositionMode();
	inc = ( flag==UP  ? 1  :  -1  );
	i = i + MAX_OSDPOSITIONMODE + inc;
	i %= MAX_OSDPOSITIONMODE;

	addx = OSDPOSITIONMODE_TABLE[i][0];
	addx -= OSDMenuX;
	OSDMenuX = OSDPOSITIONMODE_TABLE[i][0];

	addy = OSDPOSITIONMODE_TABLE[i][1];
	addy -= OSDMenuY;
	OSDMenuY = OSDPOSITIONMODE_TABLE[i][1];

	for( winno=OSDCURSORWINDOW; winno<=OSDMENU_TITLEWIN; winno++) {
		val = FOSDGetWindowX( winno );
		val += addx;
		tmp = (uint8_t)val<<3;
		OSDStart[winno-OSDCURSORWINDOW][1] = tmp;
		OSDStart[winno-OSDCURSORWINDOW][0] = tmp>>8;

		val = FOSDGetWindowY( winno );
		val += addy;
		tmp = (uint8_t)val<<2;
		OSDStart[winno-OSDCURSORWINDOW][2] = tmp;
		OSDStart[winno-OSDCURSORWINDOW][0] = OSDStart[winno-OSDCURSORWINDOW][0] | (tmp>>4 & 0x70);
	}

	WaitVBlank	(1);				// Wait Vblank()
	page = ReadTW88( 0xff );
	WriteTW88( 0xff, PAGE3_FOSD );
	for( winno=OSDCURSORWINDOW; winno<=OSDMENU_TITLEWIN; winno++) {
		//SetOSDWindowNum(winno);				// set winno
		//WriteI2Cn(TW88I2CAddress, 0xa0, &OSDStart[winno-OSDCURSORWINDOW], 3);  
		WriteTW88( FOSDWinBase[winno-1] + 2, OSDStart[winno-OSDCURSORWINDOW][0] );
		WriteTW88( FOSDWinBase[winno-1] + 3, OSDStart[winno-OSDCURSORWINDOW][1] );
		WriteTW88( FOSDWinBase[winno-1] + 4, OSDStart[winno-OSDCURSORWINDOW][2] );
	}
	WriteTW88( 0xff, page );
	SaveOSDPositionModeEE(i);

	WaitVBlank	(1);				// Wait Vblank()

	return i;
}
#endif

void ResetOSDValue(void)
{

	OSDMenuX = OSDPOSITIONMODE_TABLE[0][0];  // Default
	OSDMenuY = OSDPOSITIONMODE_TABLE[0][1];
	#ifdef SUPPORT_OSDPOSITIONMOVE
//	SaveOSDPositionModeEE(0);
	#endif

//	SaveOSDLangEE(0);	// Save default Language1
	OSDLang = 0;

	InitOSDMenu();	
}

#define HOUR			1
#define MIN				2
//#define MAX_LANG	5	// Max Language : 2
#define MAX_LANG	4	// Max Language : 2
uint8_t SetLanguage (uint8_t flag)
{
	char inc;
	inc = ( flag==UP  ? 1  :  -1  );
	OSDLang = OSDLang + MAX_LANG + inc;
	OSDLang %= MAX_LANG ; 

	//SaveOSDLangEE(OSDLang);

	return OSDLang;
}


#define INC_SLEEPTIMER		30
#define	MAX_SLEEPTIMER		150

uint8_t ChangeSleepTimer( uint8_t flag )
{
	int t;

	t = OSDItemValue / INC_SLEEPTIMER * INC_SLEEPTIMER;		//cut edge of remained sleep timer.

	if( flag==UP )	t+= INC_SLEEPTIMER;
	else			t-= INC_SLEEPTIMER;

	if( t<0 )		t = 0;
	if( t> MAX_SLEEPTIMER)	t = MAX_SLEEPTIMER;

	OSDItemValue = t;
	return OSDItemValue;
}

void OSDSetRGBContrast( uint8_t temp, uint8_t val )
{
//uint16_t index;
	uint8_t i, page;
	int newval, toValue;

	page = ReadTW88(0xff);
	WriteTW88(0xff, PAGE2_RGBLEVEL);
//	index = PC_COLOR_DATA + 1 + temp*3;
	for( i=0; i<3; i++)
	{
		 Mapping1( newval, &UserRange , &toValue, &PCUserColorTempRange);
	 	 WriteTW88(0x81+i,   toValue + val );
	}
	WriteTW88(0xff, page);
}

#define MAX_COLORTEMP	4

const uint8_t PCColorTempRGB[][3]={
	75,		50,		50,				// Mode 1: Warm
	50,		50,		50,				// Mode 2: plain -- COLOR_MODE2
	50,		50,		75,				// Mode 3: Cold
	50,		50,		50				// User mode
};

#define COLOR_MODE2		1
#define COLOR_USER		3

uint8_t SetPCColorTemp(uint8_t flag)
{
//	uint8_t val;
//	int  regv;
	char inc;

	//OSDItemValue = EE_Read( PC_COLOR_DATA );

	inc = ( flag==UP  ? 1  :  -1  );
	OSDItemValue = OSDItemValue + MAX_COLORTEMP + inc;
	OSDItemValue %= MAX_COLORTEMP ; 
//	Mapping1( val, &UserRange ,&regv, &PanelContrastRange);
//	OSDSetRGBContrast( OSDItemValue, (uint8_t)regv );

	//if( EE_Read( PC_COLOR_DATA ) != 3 )  // User
	//		DrawAttrCnt(OSDMENU_SUBADDR+MENU_WIDTH*2, BACK_COLOR, (MENU_HEIGHT-1)*MENU_WIDTH );	
//	else
//			DrawAttrCnt(OSDMENU_SUBADDR+MENU_WIDTH*2, DEFAULT_COLOR, (MENU_HEIGHT-1)*MENU_WIDTH );	

	return OSDItemValue;
}


uint8_t SetPCColor(uint8_t color, uint8_t flag) 
{
	int newval, toValue, regv;

//	GetPCColorTemp(color);
	newval = ( flag==UP  ? OSDItemValue+1  :  OSDItemValue-1  );
	if( newval< UserRange.Min || newval> UserRange.Max )
		return OSDItemValue;

	OSDItemValue = newval;
	Mapping1( newval, &UserRange , &toValue, &PCUserColorTempRange);
	//EE_Write( PC_USERCOLOR+color, newval );

//	newval = //EE_Read(0x10) ;
	Mapping1( newval, &UserRange ,&regv, &PanelContrastRange);

	WriteTW88(0x71+color,(uint8_t)(toValue + regv));

	return  OSDItemValue;
}


#define		BACKLIGHT	0x07

const uint8_t VideoModeTable[][7] ={
	{	SCONTRAST_Y,   SBRIGHT_Y,	SCONTRAST_Cb,   SCONTRAST_Cr, SHUE,  	PNLSHARPNESS,	BACKLIGHT	},// TW8804's Video Picture control Reg Address
	{	0x83,          0x80,        0x80,           0x80,         0x00,     0x60,			0xF0  },	// Mode 1: 
	{	0x88,	       0x78,	    0x90,	        0x90,         0x00,     0x60,			0xE0  },	// Mode 2: 
	{	0x78,	       0x78,	    0xa0,	        0xa0,         0x00,     0x60,			0xD0  },	// Mode 3: 
//	{	0x60,	0x00,	0x80,	0x80, 0x00, 0x80, 0x80,  0x80, 0x80, 0x80, 0x60, 0x80,  0x80, 0x80, 0x80, 0x03,  },	// User Mode 
};
#define USER_VIDEOMODE	3

void SetVideoMode(uint8_t mode)
{
	uint8_t	i, page;
	int		regv;

	page = ReadTW88(0xff);
	
	if( mode != USER_VIDEOMODE ){
		WriteTW88( 0xff, PAGE2_IMAGE );
		for (i=0; i<5 ; i++)
			WriteTW88( VideoModeTable[0][i],  VideoModeTable[mode+1][i] );

		regv = VideoModeTable[mode+1][5];	// Sharpness
		WriteTW88( PNLSHARPNESS, regv & 0x0F );	// sharpness 
		regv = VideoModeTable[mode+1][6];	// Sharpness

	}
	else // USERMODE
	{
		SetYCbCrContrast(GetVideoDatawithOffset(contrast) );
		SetYCbCrBright( GetVideoDatawithOffset(bright) );
		SetYCbCrSaturation( GetVideoDatawithOffset(staturation_U) );
		//WriteTW88(SCONTRAST_Cr, GetVideoDatawithOffset(staturation_V) );
	    SetYCbCrHUE( GetVideoDatawithOffset( hue) );
		SetYCbCrSharp( GetVideoDatawithOffset(sharpness));
		SetVideoBacklight( GetVideoDatawithOffset(backlight));
	}
	WriteTW88(0xff, page);
}

uint8_t GetVideoDatawithOffset(uint8_t offset)
{
//	OSDItemValue = GetVideoDatafromEE(offset);
	
	return OSDItemValue;
}

uint8_t ChangeVideoData(uint8_t offset, uint8_t flag)
{
	int newv, inc;
	uint8_t	page;

	inc = ( flag==UP  ? 1  :  -1  );

	newv = OSDItemValue + inc;
	if( newv< UserRange.Min || newv> UserRange.Max ) {
		return OSDItemValue;
	}

	page = ReadTW88(0xff);
#if 0
	WriteTW88( 0xff, PAGE1_DECODER );
	switch (offset)
	{
	case contrast: WriteTW88(CONTRAST, newv);
		 break;
	case bright:  WriteTW88(BRIGHT, newv);
		 break;
	case staturation_U: WriteTW88(SAT_U, newv);
		 break;
	case staturation_V: WriteTW88(SAT_V, newv);
		 break;
	case hue:	  WriteTW88(HUE, newv);
		 break;
	case backlight:	  SetVideoBacklight(newv);
		 break;
	}
#else
	WriteTW88( 0xff, PAGE2_IMAGE );
	switch (offset)
	{
	case contrast:
		SetYCbCrContrast(newv);
		 break;
	case bright:  
		SetYCbCrBright(newv);
		 break;
	case staturation_U: 
		SetYCbCrSaturation(newv);
		 break;
	case staturation_V: 
		SetYCbCrSaturation(newv);
		 break;
	case hue:
		SetYCbCrHUE(newv);
		 break;
	case backlight:	  
		SetVideoBacklight(newv);
		 break;
	}
#endif
	//SaveVideoDatatoEE(offset, newv);

	OSDItemValue = newv;

	WriteTW88(0xff,page);

	return newv;
	
}



void SetVideoBacklight(uint8_t newv) 
{

	int 	regv;

	Mapping1( newv, &UserRange , &regv, &PanelBacklightRange);

}



uint8_t SetVideoSharpness(uint8_t flag) 
{
	uint8_t page;
	char inc;
	int newv, regv;

	page = ReadTW88( 0xff );
	WriteTW88(0xff, PAGE2_IMAGE);

	regv = ReadTW88( PNLSHARPNESS )&0x0F;
	inc = ( flag==UP  ? 1  :  -1  );
	regv += inc;
	if( regv < VideoSharpnessRange.Min ||
		regv > VideoSharpnessRange.Max )
		return OSDItemValue;

	#if 1
	newv = SetYCbCrSharpReg(regv);
	#else
	Mapping1( (uint8_t)regv, &VideoSharpnessRange, &newv, &UserRange );

	SetYCbCrSharp( regv );	// sharpness 
	#endif

	//SaveVideoDatatoEE( sharpness, newv );
	OSDItemValue = newv;
	WriteTW88(0xff, page);

	return newv;
}


#ifdef WIDE_SCREEN

#include "\data\WideModeData.txt"
void SetScale4_3Y(void) // 16:9 --> 4:3  // Normal
{
	extern  CODE struct _PCMDATA  PCMDATA[];
	extern	IDATA uint8_t PcMode;
	uint32_t outv, scale;

	// Vertical
	scale = (uint32_t)PCMDATA[PcMode].VAN	;
	outv  = (uint32_t)PVR_; 
	scale = 0x10000L * scale / outv;

	YScale2( scale );

	// Horizontal
	if (PcMode >= EE_XGA_60 && PcMode >= EE_XGA_75)
		scale = (uint32_t)PCMDATA[PcMode].HAN-4; //just 1024	for focus issue(1:1).
	else
		scale = (uint32_t)PCMDATA[PcMode].HAN;	

	scale = scale * 0x10000L * 3 / PVR_ /4;

	XScale2( scale );
}

void SetScale(void)
{
	uint32_t scale, outv;

	// Vertical
	scale = (uint32_t)PCMDATA[PcMode].VAN;
	outv  = (uint32_t)PVR_ ; 
	scale = 0x10000L * scale / outv;
	YScale2( scale );
	#ifdef DEBUG_PC
	Printf("\n PCMode[%d] %ld YScale: %ld", (uint16_t)PcMode, outv, scale);
	#endif
	// Horizontal
	scale = PCMDATA[PcMode].HAN;
	outv  = PHR_ ; 
//	scale = scale  * 0x100L / outv;
	scale = (scale*0x10000L+outv-1) / outv;
	XScale2( scale );
}

void SetScale4_3X(void)	
{
	uint32_t scale, outv;

	// Horizontal
	scale = (uint32_t)PCMDATA[PcMode].HAN;
	outv  = (uint32_t)PHR_ ; 
	scale = scale  * 0x10000L / outv;
	XScale2( scale );

	// Vertical
	scale = (uint32_t)PCMDATA[PcMode].VAN; 
	outv  = outv * 3 / 4;			// 4:3
	scale = 0x10000L * scale / outv;
	YScale2( scale);				// *********** plus 2
}
void SetLRBlank(uint8_t bl)
{
	WriteTW88(0x66, bl);
}

void Set4WideScreen( uint8_t id )
{
	if( id > WIDESCREEN_FULL ){
		Set4WideScreen(WIDESCREEN_WIDE);
		id = WIDESCREEN_WIDE;
	}

	WideScreenMode = id;

	{
		int i;
		CODE_P uint8_t *WideData;
		
		#ifdef SUPPORT_COMPONENT
		if (InputMain== COMPONENT )
		{
			switch (ComponentMode)
			{
				case YPBPR_576i:	WideData = WIDEDATA_576i[id];	break;
				#ifndef WQVGA
				case YPBPR_480p:	WideData = WIDEDATA_480p[id];	break;
				case YPBPR_576p:	WideData = WIDEDATA_576p[id];	break;
				case YPBPR_720p:	WideData = WIDEDATA_720p[id];	break;
				case YPBPR_1080i:	WideData = WIDEDATA_1080i[id];	break;
				#endif
				default:			WideData = WIDEDATA_480i[id];	break;
			}

		}
		else 
		#endif
		{
				//if( ReadVInputSTD()== NTSC || ReadVInputSTD()== NTSC4 ) 
				if( GetVInputStd() == NTSC || GetVInputStd()== NTSC4 || GetVInputStd() == 0) {
					#ifdef ADD_ANALOGPANEL
					if(IsAnalogOn()) 
					WideData = WIDEDATA_NA[id];
					else
					#endif
					WideData = WIDEDATA_N[id];
				}
				else{
					#ifdef ADD_ANALOGPANEL
					if(IsAnalogOn()) 
					WideData = WIDEDATA_PA[id];
					else
					#endif
					WideData = WIDEDATA_P[id];
				}
		}

		#ifdef DEBUG
		//Printf( "\r\nWrite Wide Mode Type: %d, Data: %d, VInputStd: %d", (uint16_t)ComponentMode, (uint16_t)id, (uint16_t)GetVInputStd());
		#endif
		WaitVBlank	(1);				// Wait Vblank()
		for(i=0; i<WIDE_DATA_MAX; i++){
					WriteTW88(WIDE_ADDRESS[i], *WideData);
					//#ifdef DEBUG
					//Printf( " %2x", (uint16_t)*WideData );
					//#endif
					WideData++;
		}
	}
	SaveWideModeEE(WideScreenMode);
}
#endif // WIDE_SCREEN




//---------------------------------------------------------------------
// Push MenuTile, title_item in stack 
//      MenuTile[title_item][]...  
//
uint8_t pushMenu(void)
{
	#ifdef DEBUG_OSD
	dPrintf("\r\n(pushMenu)-MenuSP:%d", (uint16_t)MenuSP);
	#endif
	if( MenuSP < sizeof( MenuIndexStack ) ) {
		MenuStack[MenuSP] = MenuTitle;
		MenuIndexStack[MenuSP++] = title_item;
		return 1;
	}
	return 0;
}

uint8_t popMenu(void)
{
	#ifdef DEBUG_OSD
	dPrintf("\r\n(popMenu)-MenuSP:%d", (uint16_t)MenuSP);
	#endif
	if( MenuSP ) {
		MenuTitle = MenuStack[--MenuSP];
		title_item = MenuIndexStack[MenuSP];
		return 1;
	}
	return 0;
}		

uint8_t GetLowerMenuItem( const struct DefineMenu *DMp, uint8_t itemno )
{
	if( itemno==NIL )
		return NIL;
	itemno++;
	if( (DMp[itemno].IconColor==NIL) && (DMp[itemno].DescColor==NIL) )		// end
		return NIL;
	return itemno;

}

uint8_t GetUpperMenuItem(  uint8_t itemno )
{
	//if( itemno==0 || 
	if(	itemno==NIL )
		return NIL;
	itemno--;
	return itemno;
}

uint8_t GetTargetChild( uint8_t tid)
{
	uint8_t i;


	if( MenuChild )		i = 0;
	else				i = NIL;

	
	#ifdef DEBUG_OSD
	dPrintf("\r\nTarget id:0x%x", (uint16_t)tid);
	#endif

	while( i != NIL ) {
		
		#ifdef DEBUG_OSD
		dPrintf("__ForActionId[%d]:0x%x", (uint16_t)i, (uint16_t)MenuChild[i].Id);
		#endif
		
		if ( ( MenuChild[i].Id & 0x0f ) == tid )
			return i;//break;
		i = GetLowerMenuItem(MenuChild, i );
	}

	return i;
}


//********************************************************************
//
//	Functions for BAR.
//
//********************************************************************
#define VOLBAR_LENGTH 21+3
void DisplayVolumebar(uint8_t val)
{
	const uint8_t BAR_ROM_TABLE[] = {
		0x01, // ...
		0x02,0x02, // |..
		0x05,0x05, // ||.
		0x03, // |
		0x04, // |||
	};

	uint8_t i;
	uint8_t Bar_str[VOLBAR_LENGTH]={ 0x04, 0x04, 0x04, 0x04, 0x04,
							   0x04, 0x04, 0x04, 0x04, 0x04,
							   0x04, 0x04, 0x04, 0x04, 0x04,
							   0x04, 0x04, 0x04, 0x04, 0x04, 0x03,' ',' ',' ' };
	uint16_t addr;
	
	if(val < 100)
	{
		Bar_str[val/5] = BAR_ROM_TABLE[val%5];
		for(i = val/5 + 1; i < 20; i++)
			Bar_str[i] = BAR_ROM_TABLE[0];
	}

	if( Bar_str[0] == 0x01 ) Bar_str[0] = 0x02;	// |..

	// Number
    Bar_str[23] = val % 10 + '0';    val /= 10;
    Bar_str[22] =  val % 10 + '0';    val /= 10;
    Bar_str[21] = val + '0';
	if( Bar_str[21] == '0' ) Bar_str[21] = ' ';

	addr = OSDMENU_BARADDR + 1 + VOLBAR_LENGTH;	// 

	WriteStringToAddr(addr, Bar_str, VOLBAR_LENGTH ); 

}

uint8_t Get_cursor_item(uint8_t id)
{
	uint8_t i=NIL, tid;

	#ifdef DEBUG_OSD
	dPrintf("\r\n++(Get_cursor_item) id:%d", (uint16_t)id);
	#endif

	
	switch ( id ) {
	case INPUTSELECTION:	tid = InputMain; 
							break;

	default:				return 0;// The first one
	}

	i = GetTargetChild( tid );

	if( i==NIL ) {	//couldn't find
//		dPuts("___Couldn't find cursor!!");
		i=0;
	}

	#ifdef DEBUG_OSD
	dPrintf("___Cursor:%d\r\n__(GetDefaultForChoiceMenu)", (uint16_t)i);
	#endif

	return i;
}

//==================================================================================================
// Func: DisplayOSDMenuOneItem
//
//
void DisplayOSDMenuOneItem(const struct DefineMenu *DMp, uint8_t x, uint8_t y, uint8_t NOTViewflag )
{
	uint8_t i,j,k;//,//IconColor;
	uint16_t addr;
	const uint8_t *Str;
	const uint8_t RightSign_str[]=	{ 0x1c,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',0 };// RIGHT mark

	if( cur_osdwin == OSDMENU_TOPWIN) addr = OSDMENU_MAINADDR;
	else addr = OSDMENU_SUBADDR;

	addr = addr + x + y*MenuFormat->width;

	#ifdef DEBUG_OSD
	//dPrintf("\nStartaddr:%d", addr);
	#endif

//	if( DMp->IconColor !=NIL ) {		// Draw Icon
		//if(OnChangingValue) IconColor = BG_COLOR_BLACK|CH_COLOR_WHITE|EXTENDED_COLOR; 
		//else
//			IconColor =  DMp->IconColor;

//		Str = DMp->Icon;
//		j=strlen((uint8_t *)Str);
//		WriteStringToAddr(addr, (uint8_t *)Str, j);
//
		x += ICON_CH_SZ;
//	}

	if( DMp->DescColor !=NIL ) {		// Draw Desc.

		Str = DMp->Desc[OSDLang];
		j=strlenA((uint8_t *)Str);

		for( i=0,k=0; i<j; i++ )
			if( *(Str+i) == ROMFONT || *(Str+i) == RAMFONT ) k++;

		#ifdef DEBUG_OSD
		dPrintf("\naddr:%d x:%d y:%d MenuFormat->width:%d", addr, (uint16_t)x, (uint16_t)y, (uint16_t)MenuFormat->width );
		#endif

		WriteStringToAddr(addr, (uint8_t *)Str, j);

		if( (j-k ) < MAX_DESC ) 
			ClearDataCnt(addr+j-k, MAX_DESC-j+k);
	
		addr+=MAX_DESC;

	}

	if( OSDMenuLevel < 3) // Main Menu Item.
	 if ( NOTViewflag==1 )	return;	// In case of not need diplay contents. ex, BAR windows, top menu display.
	
	// Menu contents view

	switch (DMp->Type ) {
	case BAR:	// Draw Bar and Number value
		DisplayViewBar( addr, GetItemValue(DMp->Id));
		break;

	case NUMBER: // Draw Number value
		{
			const uint8_t *ptr;
			ptr = DMp->TypeData;
			switch ( DMp->Id ) {
			#if defined( PAL_TV )
			case MANUAL_TUNE_CHANNEL:
				WriteStringToAddr(addr, RightSign_str, BARNUM_LENGTH); 
				break;
			#endif
			default:
				DrawNum( addr, (const struct NumType *)ptr, GetItemValue(DMp->Id) );
				break;
			}
		}
		break;
	case ENUM_STRING:		
		{
			const uint8_t *ptr;


			ptr = DMp->TypeData;
			DrawStringByLang( addr, (const struct EnumType *)ptr, GetItemValue(DMp->Id) );

		}
		break;

	case NUMBER_STRING:
	case CHOICEMENU:
	case OSDMENU:
	case ACTION:
	//		dPrintf("\ncase ACTION: DMp->Type = %bd", DMp->Type);
			WriteStringToAddr(addr, (uint8_t *)RightSign_str, BARNUM_LENGTH); 
			break;

	}
	#ifdef DEBUG_OSD
	dPrintf("\n<--(DisplayOSDMenuOneItem) ");
	#endif
  
}

void ClearCursor(void)
{
	//uint8_t cursor_x;
	uint8_t cursor_y;
	uint16_t addr;

	if( cursor_item==NIL )
		return;

	//cursor_x = MenuFormat->CursorStart;
	cursor_y = cursor_item + ( MenuFormat->TitleColor ==NIL ? 0 : 1 );
	if( cur_osdwin == 4 ) addr = 0;
	else addr = 10;
	addr += cursor_y*MenuFormat->width;
	DrawAttrCnt(addr, DEFAULT_COLOR, MenuFormat->width );	

}

void DisplayCursor(void)
{
	uint8_t cursor_y=0 ;
	uint16_t addr;

	//dPuts("\nDisplayCursor()");
	
	if( cursor_item==NIL )
		return;
	
	cursor_y = cursor_item + ( MenuFormat->TitleColor ==NIL ? 0 : 1 );

	if( OSDMenuLevel == 1 ) addr = OSDMENU_MAINADDR;
	else addr = OSDMENU_SUBADDR;

	addr += cursor_y*MenuFormat->width;

	if( OSDMenuLevel == 1)
		DrawAttrCnt(addr, MenuFormat->CursorColor, MenuFormat->width );	
	else
	{
		if(OnChangingValue)
		{
			GetItemValue(GetItemValue(MenuChild[cursor_item].Id));
			DrawAttrCnt(addr, MenuFormat->CursorColor, MenuFormat->width );	
		}
		else
		{
			DrawAttrCnt(addr, MenuFormat->CursorColor, MenuFormat->width-BARNUM_LENGTH );	
			DrawAttrCnt(addr+MAX_DESC, DEFAULT_COLOR, BARNUM_LENGTH );	
		}
	}
}


//===============================================================================
//  OSD Menu Operation funtion moved to "OSDoper.c" by RYU.
// 
//===============================================================================
extern char AudioVol, AudioBalance, AudioBass, AudioTreble, AudioEffect;

uint16_t GetItemValue( uint8_t id)
{
	uint16_t val=0;

	#ifdef DEBUG_OSD
	dPrintf("\r\n++(GetItemValue) id:0x%x __", (uint16_t)id);
	#endif

	switch( id ) {
	//case SYSTEM_CLOCK:	val = GetSystemClock_HM();			break;
	//case WAKEUP_TIME:		val = OSDItemValue = GetWakeupTime();	break;
	//case OFF_TIME:		val = OSDItemValue = GetOffTime();		break;
//	case SLEEP_TIMER:		val = OSDItemValue = GetSleepTimer();	break;

#ifdef SUPPORT_OSDPOSITIONMOVE
	case OSDPOSITIONMODE:   val = GetOSDPositionMode();				break;
	//case OSD_VPOS:			val = GetOSDMenuYValue();				break;
	//case OSD_HPOS:			val = GetOSDMenuXValue();				break;
#endif
//	case OSD_DURATION:		val = GetOSDDurationValue();			break;
	case OSDLANG:			val = OSDLang & 0x0f;					break;

	#ifdef SUPPORT_PC0
	case PANEL_CONTRAST:	val = OSDItemValue = GetPanelContrastEE();				break;
	case PANEL_BRIGHTNESS:	val = OSDItemValue = GetPanelBrightnessEE();			break;

	case PC_VPOS:			val = GetVPosition();					break;
	case PC_HPOS:			val = GetHPosition();					break;
	case PC_CLOCK:			val = GetCoarseValue();					break;
	case PC_PHASE:			val = GetPhaseCurrent();				break;

	case PC_COLOR_TEMP:		val = EE_Read( PC_COLOR_DATA );			break;
	case PC_COLOR_R:		val = GetPCColorTemp(RED);				break;	
	case PC_COLOR_G:		val = GetPCColorTemp(GREEN);			break;	
	case PC_COLOR_B:		val = GetPCColorTemp(BLUE);				break;	
	#endif


	case VIDEO_MODE:		break;//val = EE_Read( EEP_VIDEOMODE );					break;

	case VIDEO_CONTRAST:	
	case VIDEO_BRIGHTNESS:	
	case VIDEO_SATURATION:	
	case VIDEO_HUE:			
	case VIDEO_SHARPNESS:	
	case VIDEO_BACKLIGHT:	
							val = GetVideoDatawithOffset(id-VIDEO_CONTRAST);	break;

	case AUDIO_VOLUME:		val = AudioVol;					break;
	case AUDIO_BALANCE:		val = AudioBalance;				break;
	case AUDIO_BASS:		val = AudioBass;					break;
	case AUDIO_TREBLE:		val = AudioTreble;					break;
	//case AUDIO_EFFECT:		val = GetAudioEffect();					break;
	//case AUDIO_MUTE:		val = IsAudioMuteOn();					break;

	case INPUTSTD:			val = OSDItemValue = InputMain;			
							break;

	#ifdef WIDE_SCREEN		//.................................................
	case WIDESCREEN:
							val = WideScreenMode;					break;
	#endif					//.................................................

	}

	return val;
}

#define MAX_VIDEOMODE	4
#define MAXVCHIPMOVIE	7 

uint16_t SetItemValue( uint8_t id, uint8_t flag )
{
	uint16_t val=0;
//	uint8_t	i;

	//Printf("\r\nSET Item Value: id-%X", (uint16_t)id);
	switch( id ) {
	//case SYSTEM_CLOCK_H:	
	//case WAKEUP_TIME_H:		
	//case OFF_TIME_H:
	//						val = SetClock_hour(flag);				break;

	//case SYSTEM_CLOCK:
	//case WAKEUP_TIME:
	//case OFF_TIME:
	//						val = SetClock_min(flag);				break;
	case SLEEP_TIMER:		val = ChangeSleepTimer( flag );			break;

#ifdef SUPPORT_OSDPOSITIONMOVE
	case OSDPOSITIONMODE:    val = SetOSDPositionMode( flag );		break;
	//case OSD_VPOS:			val = SetOSDMenuYValue(flag);			break;
	//case OSD_HPOS:			val = SetOSDMenuXValue(flag);			break;
#endif

//	case OSD_DURATION:		val = SetOSDDurationValue(flag);		break;
	case OSDLANG:			val = SetLanguage (flag);				break;

	#if 0
	#if defined(SUPPORT_PC) || defined(SUPPORT_656)
	case PANEL_CONTRAST:	val = SetPanelContrast(flag);			break;
	case PANEL_BRIGHTNESS:	val = SetPanelBrightness(flag);			break;
	#endif

	#ifdef SUPPORT_PC
	case PC_VPOS:			val = SetVPosition(flag);				break;
	case PC_HPOS:			val = SetHPosition(flag);				break;
	case PC_CLOCK:			val = SetPCCoarseValue(flag);			break;
	case PC_PHASE:			val = SetPhaseValue(flag);				break;
	#endif
	#endif

	case PC_COLOR_TEMP:		val = SetPCColorTemp(flag);			break;

	case PC_COLOR_R:		val = SetPCColor(RED, flag);			break;	
	case PC_COLOR_G:		val = SetPCColor(GREEN, flag);			break;	
	case PC_COLOR_B:		val = SetPCColor(BLUE, flag);			break;	

	case VIDEO_MODE:		//val = EE_Read( EEP_VIDEOMODE );
							if(flag==UP) val ++;
							else val = val + MAX_VIDEOMODE -1;
							val %= MAX_VIDEOMODE ; 
							SetVideoMode(val);		
							
						//	if( EE_Read( EEP_VIDEOMODE ) != 3 )  // if not user mode, mask the control.
						//		DrawAttrCnt(OSDMENU_SUBADDR+MENU_WIDTH*2, BACK_COLOR, (MENU_HEIGHT-1)*MENU_WIDTH );	
						//	else
							//	DrawAttrCnt(OSDMENU_SUBADDR+MENU_WIDTH*2, DEFAULT_COLOR, (MENU_HEIGHT-1)*MENU_WIDTH );	
																	break;

	case VIDEO_CONTRAST:	
	case VIDEO_BRIGHTNESS:	
	case VIDEO_HUE:			
							val= ChangeVideoData(id-VIDEO_CONTRAST,flag);					break;
	case VIDEO_SATURATION:	val = ChangeVideoData(id-VIDEO_CONTRAST,flag);	
							ChangeVideoData(id+1-VIDEO_CONTRAST,flag);
																	break;
	case VIDEO_SHARPNESS:	val = SetVideoSharpness(flag);			break;
	case VIDEO_BACKLIGHT:
		val = ChangeVideoData(id-VIDEO_CONTRAST,flag);			break;



	//case AUDIO_VOLUME:		val = ChangeVol( (flag==UP ? 1 : -1) );	break;
	//case AUDIO_BALANCE:		val = ChangeBalance( (flag==UP ? 1 : -1) );	break;
	//case AUDIO_BASS:		val = ChangeBass( (flag==UP ? 1 : -1) );	break;
	//case AUDIO_TREBLE:		val = ChangeTreble( (flag==UP ? 1 : -1) );	break;


	#ifdef WIDE_SCREEN
	case WIDESCREEN:			val = WideScreenMode;
								if(flag==UP) val++;
								else val = ( val+MAXWIDESCREEN -1 );	
								val %= MAXWIDESCREEN;
								Set4WideScreen( val );
								break;
	#endif	//WIDE_SCREEN

	}

	return val;
}

#ifdef BIG_FONT

void DisplayViewBar(uint16_t addr, uint8_t val)
{
	CODE uint8_t BAR_ROM_TABLE[] = {
		0x01,0x01,0x01, // ....
		0x02,0x02,0x02,0x02, // |...
		0x05,0x05,0x05,0x05,// ||..
		0x06,0x06,0x06,// |||.
		0x03, // |
		0x04, // ||||
	};

	uint8_t i=0;
	uint8_t Bar_str[]={ 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, ' ', ' ', ' ',0 };

	// Bar
	if( BAR_LENGTH != 0 ) {
		if(val < 98)
		{
			Bar_str[val/14] = BAR_ROM_TABLE[val%14];
			for(i = val/14 + 1; i < 7; i++)
				Bar_str[i] = BAR_ROM_TABLE[0];
		}

		if( Bar_str[0] == 0x01 ) Bar_str[0] = 0x02;	// |..
	}

	i = 7;

	// Number
    Bar_str[i+2] = val % 10 + '0';    val /= 10;
    Bar_str[i+1] =  val % 10 + '0';    val /= 10;
    Bar_str[i] = val + '0';
	if( Bar_str[i] == '0' ) Bar_str[i] = ' ';

	for(;i<7;i++)
		Bar_str[i+3] = ' ';

	WriteStringToAddr(addr, Bar_str, BARNUM_LENGTH); 

}

#else
void DisplayViewBar(uint16_t addr, uint8_t val)
{
	const uint8_t BAR_ROM_TABLE[] = {
		0x01,0x01,0x01,0x01, // ...
		0x02,0x02,0x02,0x02,0x02, // |..
		0x05,0x05,0x05,0x05,0x05,// ||.
		0x03, // |
		0x04, // |||
	};

	uint8_t i = 0;
	uint8_t Bar_str[] = { 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, ' ', ' ', ' ',0 };

	// Bar
	if( BAR_LENGTH != 0 ) {
		if(val < 98)
		{
			Bar_str[val/14] = BAR_ROM_TABLE[val%14];
			for(i = val/14 + 1; i < 7; i++)
				Bar_str[i] = BAR_ROM_TABLE[0];
		}

		if( Bar_str[0] == 0x01 ) Bar_str[0] = 0x02;	// |..
	}

	i = 7;
	// Number
    Bar_str[i+2] = val % 10 + '0';    val /= 10;
    Bar_str[i+1] =  val % 10 + '0';    val /= 10;
    Bar_str[i] = val + '0';
	if( Bar_str[i] == '0' ) Bar_str[i] = ' ';

	for(;i<7;i++)
		Bar_str[i+3] = ' ';

	WriteStringToAddr(addr, Bar_str, BARNUM_LENGTH); 

}
#endif

void DrawNum(uint16_t addr, const struct NumType *nptr, uint16_t val)
{
	uint8_t i, j,k, len, mstr[5];//,color;
	uint8_t Num_str[]={ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',0 };
	const uint8_t *str;
	
	//x=  MAX_DESC;//+ICON_CH_SZ;
	i =  nptr->PrePostCharLen >> 4 ;
	j =  nptr->PrePostCharLen & 0x0f ;
	str = nptr->PrePostChar;

	// Draw char on front of number. 
	if( i ) 
		for(k=0; k<i; k++)
			Num_str[k] = *str++;
	// Draw number.
	utoa(val,mstr,BAR_NUM_RADIX);
	len = strlenA(mstr);
	str=mstr;
	for(k=0; k<len; k++)
		Num_str[k+i] = *str++;

	// Draw char on back of number
	if( j ) 
		for(k=0; k<j; k++)
			Num_str[k+i+len] = *str++;
	WriteStringToAddr(addr, Num_str, BARNUM_LENGTH); 
	
}

void DrawStringByLang( uint16_t addr, const struct EnumType *yptr, uint16_t val )
{

	uint8_t j,l,Size_val;
	uint8_t Buf[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',0 };
	const uint8_t *Str;

	Size_val = yptr->Sz;
	Str = yptr->Str;

	//dPrintf( "DrawStringByLang: yptr->ByLang= 0x%bx, val: 0x%x", yptr->ByLang, val );

	if ( yptr->ByLang)
	{
		for(j=0; j<OSDLang*Size_val; j++)			
		Str += ( strlenA((uint8_t *)Str) + 1 );
	}

	if( val ){ 
		for(j=0; j<val; j++)			
		Str += ( strlenA((uint8_t *)Str) + 1 );	
	}

	WriteStringToAddr(addr, Buf, BARNUM_LENGTH); 


	l = strlenA((uint8_t *)Str);
	WriteStringToAddr(addr, (uint8_t *)Str, l); 

}
/*
#ifdef PAL_TV
void DrawFraction( CODE_P struct NumType *nptr, uint32_t val, uint8_t fp )
{
	uint8_t mstr[6], len;

	ltoa_K( val, mstr, fp );
	len = strlen(mstr);
	CopyStrToOSDWindow(cur_osdwin, 0, 0, len, nptr->NumColor, mstr);
	ClearOSDLine(cur_osdwin, len, 0, nptr->width-len, nptr->NumColor);
}
#endif

uint8_t OnChangingValue(void)
{
	return ( (val_osdwin==0xff  ) ? 0 : 1 );	//OSDItemValue==0xffff: password error
}
// Not used yet *******************************************
uint8_t OnChangingTime(void)
{
	if ( val_osdwin==0xff )						return 0 ;
	if ( MenuChild[cursor_item].Type==TIME )	return 1;
	else										return 0;

}
*/

//========================================================
//
//========================================================
void DrawMenulist(uint8_t NOTViewflag)
{
	uint8_t  i,j,k, x=0, y=0, page;
	const struct DefineMenu *DMp;
	const uint8_t *Desc;
	uint8_t  Max_y;
	uint16_t addr;

	// Draw Title line
	if( MenuFormat->TitleColor!=NIL ) {

		#ifdef DEBUG_OSD
		dPrintf("\nTitle color:0x%2bx", MenuFormat->TitleColor);
		dPrintf("\nOSD Lang:0x%2bx", OSDLang);
		#endif
 
		DMp = &MenuTitle[title_item];
		Desc = DMp->Desc[OSDLang];
		j=strlenA((uint8_t *)Desc);

		for( i=0,k=0; i<j; i++ )
			if( *(Desc+i) == ROMFONT || *(Desc+i) == RAMFONT ) k++;

		//ClearDataCnt(OSDMENU_SUBADDR, MenuFormat->width);	// Clear the counter of OSD RAM Data from addr with space(' ').
		DrawAttrCnt(OSDMENU_SUBADDR, MenuFormat->TitleColor, MenuFormat->width );	 
		//Puts("\nDrawAttrCnt(OSDMENU_SUBADDR, MenuFormat->TitleColor, MenuFormat->width );");
		WriteStringToAddr(OSDMENU_SUBADDR, (uint8_t *)Desc, j);
		//Puts("\nWriteStringToAddr(OSDMENU_SUBADDR, Desc, j);");

		if( (j-k ) < TITLE_MAX_DESC ) 
			ClearDataCnt(OSDMENU_SUBADDR+j-k, TITLE_MAX_DESC-j+k);

		y++;
	}
	
	if( MenuChild )	i = 0;
	else			i = NIL;

	// Draw 
	 Max_y = (cur_osdwin == OSDMENU_TOPWIN ? TOTAL_TOP_HEIGHT: MENU_HEIGHT+1);
	 addr = (cur_osdwin == OSDMENU_TOPWIN ? OSDMENU_MAINADDR: OSDMENU_SUBADDR);
	 addr += y*MenuFormat->width;

	 if( NOTViewflag==0 ) {
		 I2CAutoIncFlagOn = 1;	// speedy submenu drawing 
		 page = ReadTW88( 0xff );
		 WriteTW88( 0xff, PAGE3_FOSD );
		 WriteTW88(TW88_ENABLERAM, 0x04); // OSD RAM Auto Access Enable
		 WriteTW88( 0xff, page );
	 }

	 for(  ; y < Max_y; y++)	{

		if(i != NIL) {
			DisplayOSDMenuOneItem(&MenuChild[i], x, y, NOTViewflag);
			i = GetLowerMenuItem( MenuChild, i );
		}
		else {
			ClearDataCnt(addr, MenuFormat->width);	// Clear the counter of OSD RAM Data from addr with space(' ').
		}
		addr += MenuFormat->width;

	 }

 	 if( NOTViewflag==0 ) {
		 I2CAutoIncFlagOn = 0;	// Recover  
		 page = ReadTW88( 0xff );
		 WriteTW88( 0xff, PAGE3_FOSD );
		 WriteTW88(TW88_ENABLERAM, 0x00); // OSD RAM Auto Access Disable
		 WriteTW88( 0xff, page );
	 }

}

//
// Here, Main Menu will display Only Icon at leftside.
//
#define ALLDATA  175 //25*7  MENU_WIDTH*MENU_HEIGT
void DisplayOSDMenu(void)
{
	//const uint8_t *Str;
//	uint8_t i;
//	//#ifdef DEBUG_OSD
	//dPrintf("\n++(DisplayOSDMenu)");
	//#endif

	// Clear all MENU Window Ram data ___ removed 2011. 10.17

	//DrawAttrCnt(OSDMENU_MAINADDR, DEFAULT_COLOR, 5*2 );	 // All Line Attr clear by default color.
  	//Pause("\nDrawAttrCnt(OSDMENU_MAINADDR, DEFAULT_COLOR, 5*2 );");
	
	//DrawAttrCnt(OSDMENU_SUBADDR, TITLE_COLOR, TITLE_MAX_DESC );	 // All Line Attr clear by default color.
	//{
	//	if( (MenuChild[ cursor_item ].Id == PC_COLOR_MODE && EE_Read( PC_COLOR_DATA ) != 3 )  // User
	//	||( MenuChild[ cursor_item ].Id == VIDEOPICTURE && EE_Read( EEP_VIDEOMODE ) != 3 ) ) // User
	//	{
	///		DrawAttrCnt(OSDMENU_SUBADDR+MENU_WIDTH, DEFAULT_COLOR, MENU_WIDTH );	
	//		DrawAttrCnt(OSDMENU_SUBADDR+MENU_WIDTH*2, BACK_COLOR, (MENU_HEIGHT-1)*MENU_WIDTH );	
	//	}
	///	else
	//		DrawAttrCnt(OSDMENU_SUBADDR+TITLE_MAX_DESC, DEFAULT_COLOR, MENU_HEIGHT*MENU_WIDTH );	




}

void OSDHighMenu_sub(void)
{
	uint8_t temp_cursor, page;

	#ifdef DEBUG_OSD
	dPuts("\r\n(OSDHighMenu_sub)");
	#endif
	temp_cursor = cursor_item ;
	MenuChild = MenuTitle;
	cursor_item = title_item;

	if( !popMenu() ) {
		CloseOSDMenu();

		MenuTitle = MenuChild;	//  Restore the Menu status.
		title_item = cursor_item;
		MenuChild = MenuTitle[title_item].Child;
		cursor_item = temp_cursor;
	
		//DoAction(EXITMENU);
		
		//if( DisplayInputHold ) OSDDisplayInput();
		//else if( IsAudioMuteOn() ) DisplayMuteInfo();
		return;
	}

	#ifdef DEBUG_OSD
	dPrintf("\r\n++(OSDHighMenu_sub) OSDMenuLevel:%d", (uint16_t)OSDMenuLevel );
	#endif
	
	MenuFormat = ( const struct MenuType *) MenuTitle[title_item].TypeData;

	OSDMenuLevel--; // Up Menu tree

	if(OSDMenuLevel == 1){	// Top Menu Level
		cur_osdwin = OSDMENU_TOPWIN;//Window #4
		DisplayOSDMenu();
	}
	else
	{
		DrawMenulist(0); // Redraw List and contents.
		DisplayCursor();
	}
	
	if(OSDMenuLevel == 1) {
		page = ReadTW88( 0xff );
		WriteTW88( 0xff, PAGE3_FOSD );
		//WriteDecoder(TW88_WINNUM, OSDCURSORWINDOW);
		//WriteDecoder(TW88_WINATTR, OSD_Window_Attr(WINDOW_3D_TOP,BG_COLOR_BLACK|EXTENDED_COLOR,0,WINDOW_3D_ENABLE,WINDOW_ENABLE));	
		WriteTW88( FOSDWinBase[OSDCURSORWINDOW-1]+0xB, WINDOW_3D_TOP|BG_COLOR_BLACK|EXTENDED_COLOR|WINDOW_3D_ENABLE|WINDOW_ENABLE );
		WriteTW88( 0xff, page );
	}

	return;
}


uint8_t DoAction(uint8_t id)
{
	uint8_t ret = 1;
	switch( id ) {

	case CHANGE_TO_COMPOSITE:  	ChangeCVBS(); 	break;

	case CHANGE_TO_COMPOSITE2:  	ChangeCVBS2(); 	break;

	case CHANGE_TO_SVIDEO:  	ChangeSVIDEO(); 	break;

							
	#ifdef SUPPORT_PC0
	case AUTOADJUST:			
								//AutoAdjust();

								break;

	case RESET_PCVALUE:			ClearOSDInfo();
								ResetPanelAttributeValue();
								ResetPCValue();
								ResetOSDValue();
								ResetAudioValue();
								break;

	case PCCOLORADJUST:			
								//AutoColorAdjust();
								break;
	#endif
	
	
	case RESET_VIDEOVALUE:		ClearOSDInfo();
								ResetVideoValue();
								ResetOSDValue();
								//ResetAudioValue();
								break;

//----
	case TOHIGHMENU:			OSDHighMenu_sub();						
								break;

	case EXITMENU:				CloseOSDMenu();	
								//if( DisplayInputHold ) OSDDisplayInput();
								//else if( /IsAudioMuteOn() ) DisplayMuteInfo();
								break;
	}
	return ret;
}


uint8_t GetNextCursorMenuItem(const struct DefineMenu *DMp, uint8_t itemno, uint8_t flag)
{
	uint8_t new_cursor;

	switch( flag ) {
	case UP:	new_cursor = GetUpperMenuItem(  itemno );		break;
	case DN:	new_cursor = GetLowerMenuItem( DMp, itemno );		break;
	}
	return new_cursor;
}

//============== Public functions =================================================
//CODE uint8_t TryAgainMsg[]={ "Try again."};

uint8_t SaveValue1(void)
{
//	uint8_t           addroff;

	switch( MenuChild[cursor_item].Type )	{
	
	case NUMBER:
	  //     	switch ( MenuChild[cursor_item].Id ) {

			//case SLEEP_TIMER:		SetSleepTimer( OSDItemValue );	
		//							return 1;	//break;
	//		}
			//ret = 1;
			break;
	
	default:	break;
	}

	return 0;	
}

void ClearValueWin(void)
{
	SaveValue1();
	//FOSDWinEnable(OSDBARWINDOW, FALSE);
	val_osdwin = 0xff;
	OnChangingValue = 0;
}

void OSDCursorMove(uint8_t flag )
{
	uint8_t new_cursor, old_cursor;//, page;
	uint16_t dat;

//	#ifdef DEBUG_OSD
//	dPrintf("\r\n++(OSDCursorMove)cursor_item:%d __", (uint16_t)cursor_item);
//	#endif

	//	if( MenuChild[ cursor_item ].Id == PC_COLOR_TEMP && EE_Read( PC_COLOR_DATA ) != 3 ) return; // User
	//	if( MenuChild[ cursor_item ].Id == VIDEO_MODE && EE_Read( EEP_VIDEOMODE ) != 3 ) return; // User

		new_cursor = GetNextCursorMenuItem( MenuChild, cursor_item, flag );	// Get item to move
		
		if( new_cursor ==NIL ) {		
			uint8_t i;
			if( flag == UP )
				for(i=0; i<8; ){
					new_cursor=i;
					if( (i=GetLowerMenuItem(MenuChild, i) ) == NIL) break;
					
				}
				//new_cursor = MenuFormat->height - 1;
			else
				new_cursor = 0;
		}

		if( OnChangingValue )	{
			ClearValueWin();
		}
		if( OSDMenuLevel != 1) ClearCursor();

		old_cursor = cursor_item;
		cursor_item = new_cursor;
//	Printf("\nOldItemNo: %bd, NewItemNumber: %bd", old_cursor, new_cursor );
		if(OSDMenuLevel == 1)
		{ 
			WaitVBlank	(1);				// Wait Vblank()
			dat = FOSDGetWindowY(OSDCURSORWINDOW);
			//dat += (cursor_item-old_cursor)*(0x0a);
			dat += (cursor_item-old_cursor)*((FONT_H+2)*2);
			FOSDSetWindowY(OSDCURSORWINDOW,dat);
			WriteTW88( 0xff, PAGE3_FOSD );
			WriteTW88( FOSDWinBase[OSDCURSORWINDOW-1] + TW88_WINSADDRLO,cursor_item*2 ); 
	//		WriteTW88( 0xff, page );

			DisplayOSDMenu();

		}
		else 	{
	
		if( MenuChild[ old_cursor ].Id == OSDLANG)
				DrawMenulist(0); //		Recover Attr. and menu Data list
			DisplayCursor();
		}
}

void OSDValueUpDn(uint8_t flag)
{
	const uint8_t *ptr;
	uint16_t val;
	uint16_t addr;
//	uint8_t len1;

	addr = OSDMENU_SUBADDR;
	addr = addr + MAX_DESC + (cursor_item+1)*MenuFormat->width;

	switch ( MenuChild[cursor_item].Type ) {
	
	case BAR:	
				val = SetItemValue(MenuChild[cursor_item].Id, flag );
				DisplayViewBar( addr, val);
				break;
	
	case NUMBER:
				ptr = MenuChild[cursor_item].TypeData;
				switch ( MenuChild[cursor_item].Id ) {

				#ifdef PAL_TV	//-----------------------------------------------
				case MANUAL_TUNE_CHANNEL:
						ManualTune(flag);
						break;
				#endif					//-----------------------------------------------
				default:
						val = SetItemValue(MenuChild[cursor_item].Id, flag);
						DrawNum( addr, (const struct NumType *)ptr, val );
						break;
				}
				
				break;
	/* case TIME:
				//tptr = (CODE_P struct TimeType *)MenuChild[cursor_item].TypeData;
				//val = SetItemValue( (val_index==HOUR ? MenuChild[cursor_item].Id + 1 : MenuChild[cursor_item].Id ) , flag);
				//if( val_index == HOUR )
				//	DrawTime( val, tptr->CursorColor, tptr->TimeColor);
				//else
				//	DrawTime( val, tptr->TimeColor,   tptr->CursorColor);

				
				ptr = MenuChild[cursor_item].TypeData;
				val = SetItemValue( (val_index==HOUR ? MenuChild[cursor_item].Id + 1 : MenuChild[cursor_item].Id ) , flag);
				if( val_index == HOUR )
					DrawTime( val, 
					((CODE_P struct TimeType *)ptr)->CursorColor, 
					((CODE_P struct TimeType *)ptr)->TimeColor);
				else
					DrawTime( val, 
					((CODE_P struct TimeType *)ptr)->TimeColor,   
					((CODE_P struct TimeType *)ptr)->CursorColor);
				break;
	*/
	case ENUM_STRING:
				ptr = MenuChild[cursor_item].TypeData;
				val = SetItemValue( MenuChild[cursor_item].Id , flag);
				DrawStringByLang( addr, (const struct EnumType *)ptr, val );
				break;
	
	default:	break;
	}
}

uint8_t CloseOSDMenu(void)
{
	uint8_t i;


	WaitVBlank	(1);				// Wait Vblank()
	FOSDShowWindowAll(0);  // TW8806B

	//ClearOSD();
	for (i=OSDCURSORWINDOW; i<=OSDMENU_TITLEWIN ;i++ )
	{
		//SetOSDWindowNum(i);
		//WriteTW88(TW88_WINATTR, 0x00);
		FOSDWinEnable( i-1, 0 );
	}

	//ClearDisplayedOSD (MENU);
	DisplayedOSD &= (~(MENU));

	return 1;
}
/*
#ifdef SUPPORT_OSDPOSITIONMOVE
void InitOSDMenuXY(void)
{
	int val, addx, addy;
	uint8_t winno;

	addx = OSDMenuX - OSDMenuXRange.Default;
	addy = OSDMenuY - OSDMenuYRange.Default;

	#ifdef DEBUG_OSD
	dPrintf("\r\nOSDMenuX:%d, OSDMenuY:%d", (uint16_t)OSDMenuX, (uint16_t)OSDMenuY);
	dPrintf("\r\nOSDMenuYRange.Min=%d", (uint16_t)OSDMenuXRange.Min);
	dPrintf("\r\nOSDMenuYRange.Max=%d", (uint16_t)OSDMenuXRange.Max);
	dPrintf("\r\nOSDMenuYRange.Default=%d", (uint16_t)OSDMenuXRange.Default);
	dPrintf("\r\nOSDMenuX - OSDMenuXRange.Default=%d", (uint16_t)addx);
	#endif

	for( winno=OSDCURSORWINDOW; winno<=OSDMENU_TITLEWIN; winno++) {

		val = FOSDGetWindowX( winno );
		SetOSDWindowX(winno,val+addx);

		val = FOSDGetWindowY( winno );
		SetOSDWindowY(winno,val+addy);
	}
}
#endif
*/
void OpenOSDMenu(void)
{
	uint8_t i, page, index;

	ClearOSDInfo();
	
	InitOSDMenu();		// reset OSD window and prepare menu
	
	page = ReadTW88( 0xff );
	WriteTW88( 0xff, PAGE3_FOSD );
	for(i=OSDCURSORWINDOW; i<=OSDMENU_TITLEWIN; i++) {
		index = FOSDWinBase[i-1];
		WriteTW88(index, ReadTW88(index) | 0x80);
	}
	WriteTW88( 0xff, page );

	FOSDShowWindowAll(1);
	SetDisplayedOSD( MENU );

}


//======================================================================
//		   void InitOSDMenu()
//======================================================================
void InitOSDMenu()
{
	extern const uint8_t OSDPOSITIONMODE_TABLE[][2] ;
	//uint8_t i=0;

	//OSDLang = GetOSDLangEE();

	switch( InputMain ) {

	#ifdef SUPPORT_PC0
	case PC:	MenuTitle = PCMenu;			break;
	#endif

	//#ifdef SUPPORT_DTV
	//case DTV:	MenuTitle = DTVMenu;		break;
	//#endif 

//	default:	MenuTitle = DefaultMenu;	break;
	}

	MenuSP = 0;								// Clear stack of menu.
	title_item = 0;
	MenuFormat = (const struct MenuType *) MenuTitle[title_item].TypeData;

	OSDMenuLevel = 1; // OSD menu tree level
	cur_osdwin = OSDMENU_TOPWIN;

	MenuChild = MenuTitle[title_item].Child;
	cursor_item = 0;
	
	val_osdwin = 0xff;
	val_index = 0;
	OnChangingValue = 0;

	//--- OSD Window Initialization
	#ifdef ADD_ANALOGPANEL
	if(IsAnalogOn())
		InitOSDWindow(Init_Osd_MainMenu_A);
	else	
	#endif
	InitOSDWindow((uint8_t *)Init_Osd_MainMenu);  // Define Window Top(4), Sub(3), Bar(2), Cursor(1) 

	//--- Positioning 
	#ifdef SUPPORT_OSDPOSITIONMOVE
	i = GetOSDPositionModeEE();

	OSDMenuX = OSDPOSITIONMODE_TABLE[i][0];
	OSDMenuY = OSDPOSITIONMODE_TABLE[i][1];

	InitOSDMenuXY();	 // Default + Saved OSD Position
	#endif

	//--- Display OSD Menu
	DrawAttrCnt(OSDMENU_MAINADDR, DEFAULT_COLOR, 5*2 );	 // All Line Attr clear by default color.
	DisplayOSDMenu(); 
}


void OSDHighMenu(void)
{
	if( OnChangingValue )
	{
		//OnChangingValue = 0;
		ClearValueWin();
//		DisplayCursor();
		DrawMenulist(0); //		Recover Attr. and menu Data list
		DisplayCursor();

		return;
	}

	DoAction(MenuChild[cursor_item].PostFnId); // When exiting from the previous menu, Use to need some of action.

	if( OSDMenuLevel != 1) ClearCursor();
	OSDHighMenu_sub();
	
}


void OSDSelect(void)
{

	uint8_t ret, page;
	//uint16_t addr;

	if( cursor_item==NIL )			return;

	if( MenuChild[ cursor_item ].Id == VIDEO_HUE && ReadVInputSTD()!= NTSC && ReadVInputSTD()!= NTSC4 )  		return;
	//if( MenuChild[ cursor_item ].Id == VIDEO_SHARPNESS && InputMain== SCART )  		return;

	//do  {
		ret = DoAction(MenuChild[cursor_item].PreFnId);
		if(!ret) return;

		switch ( MenuChild[ cursor_item ].Type ) {
		case ACTION:
						DoAction(MenuChild[cursor_item].Id); // Action.
						return;

		case ENUM_STRING:		
		case BAR:
						OnChangingValue = 1; // Value changable label on 				
						DisplayCursor();	//Display Setect Item cursor
						GetItemValue(MenuChild[cursor_item].Id);
						return;
						
		case NUMBER:	
						OnChangingValue = 1;

						switch ( MenuChild[cursor_item].Id ) {
						default:
								DisplayCursor();

						//		DrawNum( (CODE_P struct NumType *)ptr, GetItemValue(MenuChild[cursor_item].Id) );
								break;
						}
						return;

		case OSDMENU:
		case CHOICEMENU:
						if(OSDMenuLevel == 1) {
							//addr = OSDMENU_MAINADDR + cursor_item*MenuFormat->width + 0;
							//DrawAttrCnt(addr, CURSOR_COLOR, 2);	// TOP Menu Icon Selected by color
							// 3D Effect Cursor Bottom
							page = ReadTW88( 0xff );
							WriteTW88( 0xff, PAGE3_FOSD );
							//WriteDecoder(TW88_WINNUM, OSDCURSORWINDOW-1);
							//WriteDecoder(TW88_WINATTR, OSD_Window_Attr(WINDOW_3D_BOTTOM,BG_COLOR_BLACK|EXTENDED_COLOR,0,WINDOW_3D_ENABLE,WINDOW_ENABLE));	
							WriteTW88( FOSDWinBase[OSDCURSORWINDOW-1]+0x0B, (WINDOW_3D_BOTTOM|BG_COLOR_BLACK|EXTENDED_COLOR|WINDOW_3D_ENABLE|WINDOW_ENABLE));
							WriteTW88( 0xff, page );
						}

						OSDMenuLevel++;	// Down Menu tree.

						pushMenu();	// Push MenuTitle, title_item in stack.
						MenuTitle = MenuChild;
						title_item = cursor_item;

						MenuFormat = (const struct MenuType *) MenuTitle[title_item].TypeData;				
						MenuChild = MenuTitle[title_item].Child;
						cursor_item = Get_cursor_item( MenuTitle[title_item].Id );

						if( cur_osdwin == OSDMENU_TOPWIN ) // Window #4
							cur_osdwin = OSDMENUWINDOW; // Window #3
						else
							DisplayOSDMenu();

						DisplayCursor();
						break;
		}
	//} while( cursor_item!=NIL && MenuChild[cursor_item].ActiveWithCursor==YES );

}
