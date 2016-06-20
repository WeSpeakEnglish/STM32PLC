#include "OSDstring.h"
#include "OSDBasic.h"

const uint8_t Enter_Password_Str_E[] = {' ',' ',' ',' ','E','n','t','e','r',' ','P','I','N',' ',':',' ','-','-','-','-',0};
const uint8_t Enter_Password_Str_F[] = {' ',' ',' ','E','n','t','r','e','r',' ','P','I','N',' ',':',' ','-','-','-','-',0};
const uint8_t Enter_Password_Str_D[] = {' ',' ','E','i','n','g','a','b','e',' ','P','I','N',' ',':',' ','-','-','-','-',0};
const uint8_t Enter_Password_Str_S[] = {' ',' ',' ','E','n','t','r','e','r',' ','P','I','N',' ',':',' ','-','-','-','-',0};
const uint8_t Enter_Password_Str_K[] = {' ',' ',RAMFONT,0x41,0x3d,0x3e,0x6e,0x38,0x71,0x4e,0x36,0x71,0x6b,0x49,0x52,ROMFONT,':',' ','-','-','-','-',0};							   

//--------------------------------------------------------------------------------
const uint8_t CheckPCCableStr_E[] = {'C','h','e','c','k',' ','P','C',' ','C','a','b','l','e',0};
const uint8_t CheckPCCableStr_K[] = {RAMFONT,0x4e,0x36,0x43,0x6e,0x38,0x71,0x6c,0x50,0x6b,0x49,0x52,ROMFONT,0};
//--------------------------------------------------------------------------------

const uint8_t CheckDTVCableStr_E[] = {'C','h','e','c','k',' ','D','T','V',' ','C','a','b','l','e',0};
const uint8_t CheckDTVCableStr_K[] = {RAMFONT,0x4e,0x36,0x43,0x6e,0x38,0x71,0x6c,0x50,0x6b,0x49,0x52,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t OutOfRangeStr_E[] = {'O','u','t',' ','O','f',' ','R','a','n','g','e',0};
const uint8_t OutOfRangeStr_K[] = {RAMFONT,0x62,0x59,0x6b,0x62,0x71,0x4c,0x2f,0x71,0x3a,0x34,ROMFONT,0};

//--------------------------------------------------------------------------------

const uint8_t StrVolume_E[] = {0x12,0x13,'V','o','l','u','m','e',0};								
const uint8_t StrVolume_F[] = {0x12,0x13,'V','o','l','u','m','e',0};								
const uint8_t StrVolume_D[] = {0x12,0x13,'L', 'a', 'u', 't', 's', 't', 'a', 'r', 'k', 'e',0};								
const uint8_t StrVolume_S[] = {0x12,0x13,'V','o','l','u','m','e','n',0};								
const uint8_t StrVolume_K[] = {0x12,0x13,RAMFONT,0x53,0x37,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t MuteOnStr_E[] = {'M','u','t','e',0};
const uint8_t MuteOnStr_K[] = {RAMFONT,0x71,0x5f,0x51,0x69,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t AutoAdjustInfo[]=	{"   Auto Adjusting ....   "};

const uint8_t Str_Input_E[] = {'I','n','p','u','t',0};
const uint8_t Str_Input_F[] = {'S','o','u','r','c','e',' ','d',0x27, 'e', 'n', 't', 'r', 0x62, 'e',0};
const uint8_t Str_Input_D[] = {'E', 'i', 'n', 'g', 'a', 'n', 'g', 's', 'q', 'u', 'e', 'l', 'l', 'e',0};
const uint8_t Str_Input_S[] = {'F', 'u', 'e', 'n', 't', 'e', ' ', 'E', 'n', 't', 'r', 'a', 'd', 'e', 0};
const uint8_t Str_Input_K[] = {RAMFONT,0x4e,0x36,0x71,0x46,0x67,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_Picture_E[] = {'P', 'i', 'c', 't', 'u', 'r', 'e', 0};
const uint8_t Str_Picture_F[] = {'E', 'c', 'r', 'a', 'n',  0};
const uint8_t Str_Picture_D[] = {'B', 'i', 'l', 'd',  0};
const uint8_t Str_Picture_S[] = {'P', 'a', 'n', 't', 'a', 'l', 'l', 'a',0};
const uint8_t Str_Picture_K[] = {RAMFONT,0x6d,0x3b,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_Sound_E[] = {'A','u','d','i','o',0};
const uint8_t Str_Sound_S[] = {'S','o','n','i','d','o',0};
const uint8_t Str_Sound_K[] = {RAMFONT,0x53,0x70,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_Utility_E[] = {'U','t','i','l','i','t','y',0};
const uint8_t Str_Utility_F[] = {'U', 't', 'i', 'l', 'i', 't', 'a', 'i', 'r', 'e',0};
const uint8_t Str_Utility_D[] = {'F', 'u', 'n', 'k', 't', 'i', 'o', 'n',0};
const uint8_t Str_Utility_S[] = {'U', 't', 'i', 'l', 'i', 'd', 'a', 'd',0};
const uint8_t Str_Utility_K[] = {RAMFONT,0x24,0x2e,0x71,0x46,0x67,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_ColorTemp_E[] = {'C','o','l','o','r',' ','T','e','m','p',0};
const uint8_t Str_ColorTemp_F[] = {'T', 'e', 'm', 'p', '.', ' ', 'C', 'o', 'u', 'l', 'e', 'u', 'r',0};
const uint8_t Str_ColorTemp_D[] = {'F', 'a', 'r', 'b', 't', 'e', 'm', 'p', 'e', 'r', 'a', 't', 'u', 'r',0};
const uint8_t Str_ColorTemp_S[] = {'T', 'e', 'm', 'p', '.', ' ',  'd', 'e', ' ', 'C', 'o', 'l', 'o', 'r',0};
const uint8_t Str_ColorTemp_K[] = {RAMFONT,0x4a,0x55,0x33,0x71,0x5f,0x60,ROMFONT,0};


//--------------------------------------------------------------------------------
const uint8_t Str_Comments_E[] = {'E','x','i','t',':','M','E','N','U',' ',' ','M','o','v','e',':',0x1d,0x1e,' ',' ','S','e','l',':',0x1c,0};
const uint8_t Str_Comments_K[] = {RAMFONT,0x2a,0x26,ROMFONT,':','M','E','N','U',' ',' ',' ',' ',RAMFONT,0x4d,0x35,ROMFONT,':',0x1d,0x1e,
											' ',' ',' ',' ',' ',RAMFONT,0x46,0x67,ROMFONT,':',0x1c,0};
								 
//--------------------------------------------------------------------------------
#ifdef PAL_TV
const uint8_t Str_Comments1[] = {'M','o','v','e',':',0x7f,0x7f,' ','S','k','i','p','/','A','d','d',':',0x7f,' ','E','d','i','t',':',0x7f,0};
const uint8_t Color_Comments1[] = {CH_COLOR_RED|TITLE_BACK_COLOR,CH_COLOR_GREEN|TITLE_BACK_COLOR,
 							   COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,
							   COMMENT_COLOR,COMMENT_COLOR,
							   CH_COLOR_YELLOW|TITLE_BACK_COLOR,
							   COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,
							   CH_COLOR_CYAN|TITLE_BACK_COLOR
								};
			
#endif

/*================================================================================*/
/*                                                                                */
/* Decsription String in OSD menu                                                 */
/*                                                                                */
//==================================================================================
//MenuStr

///* Menu String Max Length :
/*================================================================================*/
//const uint8_t Str_Composite_E[] = {'C','V','B','S','o','s','i','t','e',0};
const uint8_t Str_Composite_E[] = {'C','V','B','S',0};
const uint8_t Str_Composite2_E[] = {'C','V','B','S','2','-','D','i','f','f',0};

#ifdef SUPPORT_SVIDEO
const uint8_t Str_Svideo_E[] = {'S','-','V','i','d','e','o',0};
#endif

	#ifdef SUPPORT_COMPONENT
const uint8_t Str_Component_E[] = {'C','o','m','p','o','n','e','n','t',0};
	#endif

	#ifdef SUPPORT_656
const uint8_t Str_Dtv_E[] = {'6','5','6',0};
	#endif

	#ifdef SUPPORT_PC
const uint8_t Str_Pc_E[] = {'P','C',0};
	#endif

	#ifdef SUPPORT_DIGITALVGA
const uint8_t Str_DigitalVGA_E[] = {'D','i','g','i','t','a','l',' ','V','G','A',0};
	#endif

//--------------------------------------------------------------------------------
#ifdef SUPPORT_PC
const uint8_t Str_VPosition_E[] = {'V',' ','P','o','s','i','t','i','o','n',0};
const uint8_t Str_VPosition_F[] = {'P','o','s','i','t','i','o','n',' ','V','.',0};
const uint8_t Str_VPosition_D[] = {'V',' ','P','o','s','i','t','i','o','n',0};
const uint8_t Str_VPosition_S[] = {'P','o','s','i','c','i',0x5f,'n',' ','V','.',0};
const uint8_t Str_VPosition_K[] = {RAMFONT,0x6d,0x3b,0x71,0x45,0x63,0x71,0x54,0x65,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_HPosition_E[] = {'H',' ','P','o','s','i','t','i','o','n',0};
const uint8_t Str_HPosition_F[] = {'P','o','s','i','t','i','o','n',' ','H','.',0};
const uint8_t Str_HPosition_D[] = {'H',' ','P','o','s','i','t','i','o','n',0};
const uint8_t Str_HPosition_S[] = {'P','o','s','i','c','i',0x5f,'n',' ','H','.',0};
const uint8_t Str_HPosition_K[] = {RAMFONT,0x6d,0x3b,0x71,0x45,0x68,0x71,0x54,0x65,0x71,0x5f,0x60,ROMFONT,0};

#endif
//--------------------------------------------------------------------------------
#ifdef SUPPORT_OSDPOSITIONMOVE
const uint8_t Str_OSDPosition_E[] =	{'O','S','D',' ','P','o','s','i','t','i','o','n',0};
const uint8_t Str_OSDPosition_S[] =	{'O','S','D',' ','P','o','s','i','c','i',0x5f,'n',0};
const uint8_t Str_OSDPosition_K[] =	{'O','S','D',' ',RAMFONT,0x54,0x65,0x71,0x46,0x67,ROMFONT,0};

#endif

//--------------------------------------------------------------------------------
const uint8_t Str_OSDLang_E[] = {'L','a','n','g','u','a','g','e',0};
const uint8_t Str_OSDLang_F[] = {'L', 'a', 'n', 'g', 'u', 'e',0};
const uint8_t Str_OSDLang_D[] = {'S', 'p', 'r', 'a', 'c', 'h', 'e',0};
const uint8_t Str_OSDLang_S[] =	{'I', 'd', 'i', 'o', 'm', 'a',0};
const uint8_t Str_OSDLang_K[] = {RAMFONT,0x57,0x56,0x71,0x46,0x67,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_SleepTimerE[] = {'S','l','e','e','p',' ','T','i','m','e','r',0};
const uint8_t Str_SleepTimerK[] = {RAMFONT,0x30,0x27,0x71,0x42,0x22,0x71,0x44,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_VInputStd_E[] = {'I','n','p','u','t',' ','S','t','d','.',0};

//--------------------------------------------------------------------------------
const uint8_t Str_Information_E[] =	{'I','n','f','o','r','m','a','t','i','o','n',0};

//--------------------------------------------------------------------------------
const uint8_t Str_Volume_E[] = {'V','o','l','u','m','e',0};
const uint8_t Str_Volume_D[] = {'V','o','l','u','m','e','n',0};
const uint8_t Str_Volume_S[] = {'L', 'a', 'u', 't', 's', 't', 'a', 'r', 'k', 'e',0};
const uint8_t Str_Volume_K[] = {RAMFONT,0x53,0x37,0x71,0x5f,0x60,ROMFONT,0};
//--------------------------------------------------------------------------------

const uint8_t Str_Treble_E[] = {'T','r','e','b','l','e',0};
const uint8_t Str_Treble_F[] = {'A','i','g','u','e','s',0};
const uint8_t Str_Treble_D[] = {'H','o','h','e','n',0};
const uint8_t Str_Treble_S[] = {'A','g','u','d','o','s',0};
const uint8_t Str_Treble_K[] = {RAMFONT,0x29,0x53,0x71,0x5f,0x60,ROMFONT,0};
//--------------------------------------------------------------------------------

const uint8_t Str_Bass_E[] = {'B','a','s','s',0};
const uint8_t Str_Bass_F[] = {'B','a','s','s','e','s',0};
const uint8_t Str_Bass_D[] = {'T','i','e','f','e','n',0};
const uint8_t Str_Bass_S[] = {'G','r','a','v','e','s',0};
const uint8_t Str_Bass_K[] = {RAMFONT,0x5e,0x53,0x71,0x5f,0x60,ROMFONT,0};
//--------------------------------------------------------------------------------
const uint8_t Str_Balance_E[] = {'B','a','l','a','n','c','e',0};
const uint8_t Str_Balance_F[] = {'B','a','l','a','n','c','e',0};
const uint8_t Str_Balance_D[] =	{'B','a','l','a','n','c','e',0};
const uint8_t Str_Balance_S[] =	{'B','a','l','a','n','c','e',0};
const uint8_t Str_Balance_K[] = {RAMFONT,0x53,0x25,0x6f,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_Red_E[] = {'R','e','d',0};
const uint8_t Str_Red_F[] =	{'R','o','u','g','e',0};
const uint8_t Str_Red_D[] = {'R','o','t',0};
const uint8_t Str_Red_S[] = {'R','o','j','o',0};
const uint8_t Str_Red_K[] = {RAMFONT,0x5c,0x4a,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_Green_E[] = {'G','r','e','e','n',0};
const uint8_t Str_Green_F[] = {'V','e','r','t',0};
const uint8_t Str_Green_D[] = {'G','r',0xae,'n',0};
const uint8_t Str_Green_S[] = {'V', 'e', 'r', 'd', 'e',0};
const uint8_t Str_Green_K[] = {RAMFONT,0x2b,0x4a,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_Blue_E[] = {'B','l','u','e',0};
const uint8_t Str_Blue_F[] = {'B','l','e','u',0};
const uint8_t Str_Blue_D[] = {'B','l','a','u',0};
const uint8_t Str_Blue_S[] = {'A','z','u','l',0};
const uint8_t Str_Blue_K[] = {RAMFONT,0x64,0x4a,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
const uint8_t Str_Hue_E[] = {'H','u','e',0};
const uint8_t Str_Hue_F[] = {'T', 'o', 'n', 'a', 'l', 'i', 't', 0x5c,0};
const uint8_t Str_Hue_D[] = {'F', 'a', 'r', 'b', 'e',0};
const uint8_t Str_Hue_S[] = {'T', 'o', 'n', 'a', 'l', 'i', 'd', 'a', 'd',0};
const uint8_t Str_Hue_K[] =	{RAMFONT,0x4a,0x54,0x48,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_Sharpness_E[] = {'S','h','a','r','p','n','e','s','s',0};
const uint8_t Str_Sharpness_F[] = {'A', 'c', 'u', 'i', 't', 0x5c,0};
const uint8_t Str_Sharpness_D[] = {'S', 'c', 'h', 0xaa, 'r','f', 'e',0};
const uint8_t Str_Sharpness_S[] = {'A', 'g', 'u', 'd', 'e', 'z', 'a',0};
const uint8_t Str_Sharpness_K[] = {RAMFONT,0x46,0x39,0x33,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_Contrast_E[] = {'C','o','n','t','r','a','s','t',0};
const uint8_t Str_Contrast_F[] = {'C','o','n','t','r','a','s','t','e',0};
const uint8_t Str_Contrast_D[] = {'K','o','n','t','r','a','s','t',0};
const uint8_t Str_Contrast_S[] = {'C','o','n','t','r','a','s','t','e',0};
const uint8_t Str_Contrast_K[] = {RAMFONT,0x39,0x4f,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_Brightness_E[] = {'B','r','i','g','h','t','n','e','s','s',0};
const uint8_t Str_Brightness_F[] = {'L', 'u', 'm', 'i', 'n', 'o', 's', 'i', 't', 0x5f,0};
const uint8_t Str_Brightness_D[] = {'H', 'e', 'l', 'l', 'i', 'g', 'k', 'e', 'i', 't',0};
const uint8_t Str_Brightness_S[] = {'B', 'r', 'i', 'l', 'l', 'o',0};
const uint8_t Str_Brightness_K[] = {RAMFONT,0x40,0x24,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_Backlight_E[] = {'B','a','c','k','l','i','g','h','t',0};
const uint8_t Str_Backlight_F[] = {'B','a','c','k','l','i','g','h','t',0};
const uint8_t Str_Backlight_D[] = {'B','a','c','k','l','i','g','h','t',0};
const uint8_t Str_Backlight_S[] = {'B','a','c','k','l','i','g','h','t',0};
const uint8_t Str_Backlight_K[] = {'B','a','c','k','l','i','g','h','t',0};

//--------------------------------------------------------------------------------
const uint8_t Str_Saturation_E[] = {'S','a','t','u','r','a','t','i','o','n',0};
const uint8_t Str_Saturation_D[] = {'S', 0xaa, 't', 't', 'i', 'g', 'u', 'n', 'g',0};
const uint8_t Str_Saturation_S[] = {'S', 'a', 't', 'u', 'r', 'a', 'c', 'i', 0x5f, 'n',0};
const uint8_t Str_Saturation_K[] = {RAMFONT,0x4a,0x2c,0x33,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
const uint8_t Str_Reset_E[] = {'R','e','s','e','t',0};
const uint8_t Str_Reset_F[] = {'D', 0x5c, 'f', 'a', 'u', 't',0};
const uint8_t Str_Reset_D[] = {'G', 'r', 'u', 'n', 'd', 'e', 'i', 'n', 's', 't', 'e', 'l', 'u', 'g',0};
const uint8_t Str_Reset_S[] = {'P', 'r', 'e', 'd', 'e', 't', 'e', 'r', 'm', 'i', 'n', 'a', 'c', 'i',0x5f, 'n',0};
const uint8_t Str_Reset_K[] = {RAMFONT,0x66,0x24,0x6d,ROMFONT,0};

//--------------------------------------------------------------------------------

#ifdef SUPPORT_PC
//--------------------------------------------------------------------------------
const uint8_t Str_Phase_E[] = {'P','h','a','s','e',0};
const uint8_t Str_Phase_S[] = {'F','a','s','e',0};

//--------------------------------------------------------------------------------
const uint8_t Str_Clock_E[] = {'C','l','o','c','k',0};
const uint8_t Str_Clock_F[] = {'H', 'o', 'r', 'l', 'o', 'g', 'e',0};
const uint8_t Str_Clock_D[] = {'T', 'a', 'k', 't',0};
const uint8_t Str_Clock_S[] = {'R', 'e', 'l', 'o', 'j',0};

//--------------------------------------------------------------------------------

const uint8_t Str_AutoColor_E[] = {'A','u','t','o',' ','C','o','l','o','r',0};
const uint8_t Str_AutoColor_K[] = {RAMFONT,0x5b,0x35,0x71,0x4a,0x48,0x71,0x5f,0x60,ROMFONT,0};

const uint8_t Str_AutoAdjust_E[] = {'A','u','t','o',' ','A','d','j','u','s','t',0};
const uint8_t Str_AutoAdjust_K[] = {RAMFONT,0x5b,0x35,0x71,0x6d,0x3b,0x71,0x5f,0x60,ROMFONT,0};
#endif

//--------------------------------------------------------------------------------
#ifdef WIDE_SCREEN
const uint8_t Str_WideScreen_E[] = {'W','i','d','e',' ','S','c','r','e','e','n',0};
const uint8_t Str_WideScreen_K[] = {'W','I','D','E',' ',RAMFONT,0x6d,0x3b,0x71,0x46,0x67,ROMFONT,0};
#endif

//==================================================================================
//
//   Choice Menu String define in osd menu.
//
//==================================================================================
// Form
// 
//struct EnumType {
//	BYTE    Sz;
//	BYTE    ByLang;
//	BYTE	Str[15];			// doesn't matter size of the string !!!
//};


const uint8_t OSDLangString[] = 
{
		0x02, // Size 
		0, // Independence by language:0, Dependenced by language:1 
//					 Language I			Language II			Language III....
		'E','n','g','l','i','s','h',0,	
        'F', 'r', 'a', 'n', 0x7b, 'a', 'i', 's',0,
        'D', 'e', 'u', 't', 's', 'c', 'h',0,
        'E', 's', 'p', 'a', 0x7e, 'o', 'l',0,
		RAMFONT,0x6a,0x23,0x56,ROMFONT,' ',0
};

const uint8_t ModeChoice[] =		{
		0x04, // Size 
		1,
		'M','o','d','e','1',0,	'M','o','d','e','2',0, 'M','o','d','e','3',0,	'U','s','e','r',0,
		'M','o','d','e','1',0,	'M','o','d','e','2',0, 'M','o','d','e','3',0,	'U','s','a','g','e','r',0,
		'M','o','d','u','s','1',0, 'M','o','d','u','s','2',0, 'M','o','d','u','s','3',0, 'B','e','n','u','t','z','e','r',0,
		'M','o','d','o','1',0,	'M','o','d','o','2',0,	'M','o','d','o','3',0,	'U','s','u','a','r','i','o',0,
		RAMFONT,0x3a,0x34,ROMFONT,'1',0, RAMFONT,0x3a,0x34,ROMFONT,'2',0,	RAMFONT,0x3a,0x34,ROMFONT,'3',0, RAMFONT,0x47,0x51,0x5b,0x71,ROMFONT,' ',0  // Caution!: Do not end to osd control command "ROMFONT" or "RAMFONT". 
};


const uint8_t VInputStdChoice[] = {
			0x08,//size of supported system.(Attention!!)
			0,// None by language.
			'A','u','t','o',0,
			'N','T','S','C',0,
#ifdef SUPPORT_PAL
			'P','A','L',0,
#endif
#ifdef SUPPORT_SECAM
			'S','E','C','A','M',0,	
#endif
#ifdef SUPPORT_NTSC4
			'N','T','S','C','4','.','4','3',0,	
#endif
#ifdef SUPPORT_PALM
			'P','A','L','M',0,	
#endif
#ifdef SUPPORT_PALN
			'P','A','L','N',0,	
#endif
#ifdef SUPPORT_PAL60
			'P','A','L','6','0',0,	
#endif
};

#ifdef WIDE_SCREEN
const uint8_t WideScreenChoice[] = {
			5,//size 
			0,// by language.
			'N','o','r','m','a','l',0, 			'W','i','d','e',0, 			'P','a','n','o','r','a','m','a',0,	'F','u','l','l',0,//			'Z','o','o','m',0,
};
#endif

#ifdef SUPPORT_OSDPOSITIONMOVE
const uint8_t OsdPositionModeChoice[] = {
			5,//size
			0,// by language.
			CODE2FONT+0x1a,CODE2FONT+0x1b,' ',0,				CODE2FONT+0x1c,CODE2FONT+0x1d,' ',0,
			CODE2FONT+0x1e,CODE2FONT+0x1d,' ',0,				CODE2FONT+0x1f,CODE2FONT+0x20,' ',0,
			CODE2FONT+0x1f,CODE2FONT+0x21,' ',0,
};
#endif


const uint8_t CaptionChoice[] = {
			0x09,//size
			0,// None by lang.
			'O','f','f',0,	'C','C','1',0,	'C','C','2',0,	'C','C','3',0,	'C','C','4',0,
			'T','1',0,		'T','2',0,		'T','3',0,		'T','4',0,

};


//--------------------------------------------------------------------------------

const uint8_t 	*Enter_Password_Str[]={Enter_Password_Str_E,Enter_Password_Str_F,Enter_Password_Str_D,Enter_Password_Str_S,Enter_Password_Str_K};					   
const uint8_t 	*CheckPCCableStr[] =	{CheckPCCableStr_E,CheckPCCableStr_E,CheckPCCableStr_E,CheckPCCableStr_E,CheckPCCableStr_K};
const uint8_t 	*CheckDTVCableStr[] = {CheckDTVCableStr_E,CheckDTVCableStr_E,CheckDTVCableStr_E,CheckDTVCableStr_E,CheckDTVCableStr_K};
const uint8_t 	*OutOfRangeStr[] =	{OutOfRangeStr_E,OutOfRangeStr_E,OutOfRangeStr_E,OutOfRangeStr_E,OutOfRangeStr_K};
const uint8_t 	*StrVolume[]=			{StrVolume_E,StrVolume_F,StrVolume_D,StrVolume_S,StrVolume_K};
const uint8_t 	*MuteOnStr[]=			{MuteOnStr_E,MuteOnStr_E,MuteOnStr_E,MuteOnStr_E,MuteOnStr_K};
//--------------------------------------------------------------------------------
const uint8_t 	*Str_Input[]=			{Str_Input_E,	Str_Input_F,	Str_Input_D,	Str_Input_S,	Str_Input_K};
const uint8_t 	*Str_Picture[]=		{Str_Picture_E,	Str_Picture_F,	Str_Picture_D,	Str_Picture_S,	Str_Picture_K};
const uint8_t 	*Str_Sound[]=			{Str_Sound_E,Str_Sound_E,Str_Sound_E,Str_Sound_S,Str_Sound_K};
const uint8_t 	*Str_Utility[]=		{Str_Utility_E,Str_Utility_F,Str_Utility_D,Str_Utility_S,Str_Utility_K};
const uint8_t 	*Str_ColorTemp[]=		{Str_ColorTemp_E,Str_ColorTemp_F,Str_ColorTemp_D,Str_ColorTemp_S,Str_ColorTemp_K};

const uint8_t 	*Str_Comments[]=		{Str_Comments_E,Str_Comments_E,Str_Comments_E,Str_Comments_E,Str_Comments_K};
//============================================================================================
//  OSD Menu String Table
const uint8_t 	*Str_Composite[] =	{Str_Composite_E,Str_Composite_E,Str_Composite_E,Str_Composite_E,Str_Composite_E};

#ifdef SUPPORT_CVBS2
const uint8_t 	*Str_Composite2[] =		{Str_Composite2_E,Str_Composite2_E,Str_Composite2_E,Str_Composite2_E,Str_Composite2_E};
#endif
#ifdef SUPPORT_SVIDEO
const uint8_t 	*Str_Svideo[] =		{Str_Svideo_E,Str_Svideo_E,Str_Svideo_E,Str_Svideo_E,Str_Svideo_E};
#endif
#ifdef SUPPORT_COMPONENT
const uint8_t 	*Str_Component[] =	{Str_Component_E,Str_Component_E,Str_Component_E,Str_Component_E,Str_Component_E};
#endif
#ifdef SUPPORT_656
const uint8_t 	*Str_656[] =			{Str_Dtv_E,Str_Dtv_E,Str_Dtv_E,Str_Dtv_E,Str_Dtv_E};
#endif
#ifdef SUPPORT_PC
const uint8_t 	*Str_Pc[] = 			{Str_Pc_E,Str_Pc_E,Str_Pc_E,Str_Pc_E,Str_Pc_E};
#endif
#ifdef SUPPORT_DIGITALVGA
const uint8_t 	*Str_DigitalVGA[] =   {Str_DigitalVGA_E,Str_DigitalVGA_E,Str_DigitalVGA_E,Str_DigitalVGA_E,Str_DigitalVGA_E};
#endif

#ifdef SUPPORT_PC
const uint8_t 	*Str_VPosition[]=		{Str_VPosition_E,Str_VPosition_F,Str_VPosition_D,Str_VPosition_S,Str_VPosition_K};
const uint8_t 	*Str_HPosition[]=		{Str_HPosition_E,Str_HPosition_F,Str_HPosition_D,Str_HPosition_S,Str_HPosition_K};
#endif

#ifdef SUPPORT_OSDPOSITIONMOVE
const uint8_t 	*Str_OSDPosition[]=	{Str_OSDPosition_E,Str_OSDPosition_E,Str_OSDPosition_E,Str_OSDPosition_S,Str_OSDPosition_K};
#endif
const uint8_t 	*Str_OSDLang[]=		{Str_OSDLang_E,Str_OSDLang_F,Str_OSDLang_D,Str_OSDLang_S,Str_OSDLang_K};
const uint8_t 	*Str_SleepTimer[]=	{Str_SleepTimerE,Str_SleepTimerE,Str_SleepTimerE,Str_SleepTimerE,Str_SleepTimerK};
const uint8_t 	*Str_VInputStd[]=		{Str_VInputStd_E,Str_VInputStd_E,Str_VInputStd_E,Str_VInputStd_E,Str_VInputStd_E};
const uint8_t 	*Str_Information[]=	{Str_Information_E,Str_Information_E,Str_Information_E,Str_Information_E,Str_Information_E};
const uint8_t 	*Str_Volume[]=		{Str_Volume_E,Str_Volume_E,Str_Volume_D,Str_Volume_S,Str_Volume_K};
const uint8_t 	*Str_Treble[]=		{Str_Treble_E,Str_Treble_F,Str_Treble_D,Str_Treble_S,Str_Treble_K};
const uint8_t 	*Str_Bass[]=			{Str_Bass_E,Str_Bass_F,Str_Bass_D,Str_Bass_S,Str_Bass_K};
const uint8_t 	*Str_Balance[]=		{Str_Balance_E,Str_Balance_F,Str_Balance_D,Str_Balance_S,Str_Balance_K};
const uint8_t 	*Str_Red[]=			{Str_Red_E,Str_Red_F,Str_Red_D,Str_Red_S,Str_Red_K};
const uint8_t 	*Str_Blue[]=			{Str_Blue_E,Str_Blue_F,Str_Blue_D,Str_Blue_S,Str_Blue_K};
const uint8_t 	*Str_Green[]=			{Str_Green_E,Str_Green_F,Str_Green_D,Str_Green_S,Str_Green_K};
const uint8_t 	*Str_Hue[]=			{Str_Hue_E,Str_Hue_F,Str_Hue_D,Str_Hue_S,Str_Hue_K};
const uint8_t 	*Str_Backlight[]=		{Str_Backlight_E,Str_Backlight_F,Str_Backlight_D,Str_Backlight_S,Str_Backlight_K};
const uint8_t 	*Str_Sharpness[]=		{Str_Sharpness_E,Str_Sharpness_F,Str_Sharpness_D,Str_Sharpness_S,Str_Sharpness_K};
const uint8_t 	*Str_Contrast[]=		{Str_Contrast_E,Str_Contrast_F,Str_Contrast_D,Str_Contrast_S,Str_Contrast_K};
const uint8_t 	*Str_Brightness[]=	{Str_Brightness_E,Str_Brightness_F,Str_Brightness_D,Str_Brightness_S,Str_Brightness_K};
const uint8_t 	*Str_Saturation[]=	{Str_Saturation_E,Str_Saturation_E,Str_Saturation_D,Str_Saturation_S,Str_Saturation_K};
const uint8_t 	*Str_Reset[]=			{Str_Reset_E,Str_Reset_F,Str_Reset_D,Str_Reset_S,Str_Reset_K};

#ifdef SUPPORT_PC
const uint8_t 	*Str_Phase[]=			{Str_Phase_E,Str_Phase_E,Str_Phase_E,Str_Phase_S,Str_Phase_E};
const uint8_t 	*Str_Clock[]=			{Str_Clock_E,Str_Clock_F,Str_Clock_D,Str_Clock_S,Str_Clock_E};
const uint8_t 	*Str_AutoColor[]=		{Str_AutoColor_E,Str_AutoColor_E,Str_AutoColor_E,Str_AutoColor_E,Str_AutoColor_K};
const uint8_t 	*Str_AutoAdjust[]=	{Str_AutoAdjust_E,Str_AutoAdjust_E,Str_AutoAdjust_E,Str_AutoAdjust_E,Str_AutoAdjust_K};
#endif

#ifdef WIDE_SCREEN
const uint8_t 	*Str_WideScreen[] =	{Str_WideScreen_E,Str_WideScreen_E,Str_WideScreen_E,Str_WideScreen_E,Str_WideScreen_K};
#endif
