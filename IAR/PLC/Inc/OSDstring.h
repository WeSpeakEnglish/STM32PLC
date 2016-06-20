#ifndef _OSD_STRING_H
#define _OSD_STRING_H

#include "variables.h"
#ifdef BIG_FONT
#define	SOUND0	0x12
#define	SOUND1	0x13
#else
#define	SOUND0	0x12
#define	SOUND1	0x13
#endif
extern const uint8_t Enter_Password_Str_E[];
extern const uint8_t Enter_Password_Str_F[];
extern const uint8_t Enter_Password_Str_D[];
extern const uint8_t Enter_Password_Str_S[];
extern const uint8_t Enter_Password_Str_K[];							   

//--------------------------------------------------------------------------------
extern const uint8_t CheckPCCableStr_E[];
extern const uint8_t CheckPCCableStr_K[];
//--------------------------------------------------------------------------------

extern const uint8_t CheckDTVCableStr_E[];
extern const uint8_t CheckDTVCableStr_K[];

//--------------------------------------------------------------------------------
extern const uint8_t OutOfRangeStr_E[];
extern const uint8_t OutOfRangeStr_K[];

//--------------------------------------------------------------------------------

extern const uint8_t StrVolume_E[];								
extern const uint8_t StrVolume_F[];								
extern const uint8_t StrVolume_D[];								
extern const uint8_t StrVolume_S[];								
extern const uint8_t StrVolume_K[];

//--------------------------------------------------------------------------------
extern const uint8_t MuteOnStr_E[];
extern const uint8_t MuteOnStr_K[];

//--------------------------------------------------------------------------------
extern const uint8_t AutoAdjustInfo[];

extern const uint8_t Str_Input_E[];
extern const uint8_t Str_Input_F[];
extern const uint8_t Str_Input_D[];
extern const uint8_t Str_Input_S[];
extern const uint8_t Str_Input_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Picture_E[];
extern const uint8_t Str_Picture_F[];
extern const uint8_t Str_Picture_D[];
extern const uint8_t Str_Picture_S[];
extern const uint8_t Str_Picture_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Sound_E[];
extern const uint8_t Str_Sound_S[];
extern const uint8_t Str_Sound_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Utility_E[];
extern const uint8_t Str_Utility_F[];
extern const uint8_t Str_Utility_D[];
extern const uint8_t Str_Utility_S[];
extern const uint8_t Str_Utility_K[];
//--------------------------------------------------------------------------------
extern const uint8_t Str_ColorTemp_E[];
extern const uint8_t Str_ColorTemp_F[];
extern const uint8_t Str_ColorTemp_D[];
extern const uint8_t Str_ColorTemp_S[];
extern const uint8_t Str_ColorTemp_K[];


//--------------------------------------------------------------------------------
extern const uint8_t Str_Comments_E[];
extern const uint8_t Str_Comments_K[];
								 
//--------------------------------------------------------------------------------
#ifdef PAL_TV
extern const uint8_t Str_Comments1[];
extern const uint8_t Color_Comments1[];
			
#endif

/*================================================================================*/
/*                                                                                */
/* Decsription String in OSD menu                                                 */
/*                                                                                */
//==================================================================================
//MenuStr
#define		MAX_DESC			12 //14	
///* Menu String Max Length :
/*================================================================================*/
//extern const uint8_t Str_Composite_E[] = {'C','V','B','S','o','s','i','t','e',0};
extern const uint8_t Str_Composite_E[];
extern const uint8_t Str_Composite2_E[];

#ifdef SUPPORT_SVIDEO
extern const uint8_t Str_Svideo_E[];
#endif

	#ifdef SUPPORT_COMPONENT
extern const uint8_t Str_Component_E[];
	#endif

	#ifdef SUPPORT_656
extern const uint8_t Str_Dtv_E[];
	#endif

	#ifdef SUPPORT_PC
extern const uint8_t Str_Pc_E[];
	#endif

	#ifdef SUPPORT_DIGITALVGA
extern const uint8_t Str_DigitalVGA_E[];
	#endif

//--------------------------------------------------------------------------------
#ifdef SUPPORT_PC
extern const uint8_t Str_VPosition_E[];
extern const uint8_t Str_VPosition_F[];
extern const uint8_t Str_VPosition_D[];
extern const uint8_t Str_VPosition_S[];
extern const uint8_t Str_VPosition_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_HPosition_E[];
extern const uint8_t Str_HPosition_F[];
extern const uint8_t Str_HPosition_D[];
extern const uint8_t Str_HPosition_S[];
extern const uint8_t Str_HPosition_K[];

#endif
//--------------------------------------------------------------------------------
#ifdef SUPPORT_OSDPOSITIONMOVE
extern const uint8_t Str_OSDPosition_E[];
extern const uint8_t Str_OSDPosition_S[];
extern const uint8_t Str_OSDPosition_K[];

#endif

//--------------------------------------------------------------------------------
extern const uint8_t Str_OSDLang_E[];
extern const uint8_t Str_OSDLang_F[];
extern const uint8_t Str_OSDLang_D[];
extern const uint8_t Str_OSDLang_S[];
extern const uint8_t Str_OSDLang_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_SleepTimerE[];
extern const uint8_t Str_SleepTimerK[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_VInputStd_E[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Information_E[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Volume_E[];
extern const uint8_t Str_Volume_D[];
extern const uint8_t Str_Volume_S[];
extern const uint8_t Str_Volume_K[];
//--------------------------------------------------------------------------------

extern const uint8_t Str_Treble_E[];
extern const uint8_t Str_Treble_F[];
extern const uint8_t Str_Treble_D[];
extern const uint8_t Str_Treble_S[];
extern const uint8_t Str_Treble_K[];
//--------------------------------------------------------------------------------

extern const uint8_t Str_Bass_E[];
extern const uint8_t Str_Bass_F[];
extern const uint8_t Str_Bass_D[];
extern const uint8_t Str_Bass_S[];
extern const uint8_t Str_Bass_K[];
//--------------------------------------------------------------------------------
extern const uint8_t Str_Balance_E[];
extern const uint8_t Str_Balance_F[];
extern const uint8_t Str_Balance_D[];
extern const uint8_t Str_Balance_S[];
extern const uint8_t Str_Balance_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Red_E[];
extern const uint8_t Str_Red_F[];
extern const uint8_t Str_Red_D[];
extern const uint8_t Str_Red_S[];
extern const uint8_t Str_Red_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Green_E[];
extern const uint8_t Str_Green_F[];
extern const uint8_t Str_Green_D[];
extern const uint8_t Str_Green_S[];
extern const uint8_t Str_Green_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Blue_E[];
extern const uint8_t Str_Blue_F[];
extern const uint8_t Str_Blue_D[];
extern const uint8_t Str_Blue_S[];
extern const uint8_t Str_Blue_K[];

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
extern const uint8_t Str_Hue_E[];
extern const uint8_t Str_Hue_F[];
extern const uint8_t Str_Hue_D[];
extern const uint8_t Str_Hue_S[];
extern const uint8_t Str_Hue_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Sharpness_E[];
extern const uint8_t Str_Sharpness_F[];
extern const uint8_t Str_Sharpness_D[];
extern const uint8_t Str_Sharpness_S[];
extern const uint8_t Str_Sharpness_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Contrast_E[];
extern const uint8_t Str_Contrast_F[];
extern const uint8_t Str_Contrast_D[];
extern const uint8_t Str_Contrast_S[];
extern const uint8_t Str_Contrast_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Brightness_E[];
extern const uint8_t Str_Brightness_F[];
extern const uint8_t Str_Brightness_D[];
extern const uint8_t Str_Brightness_S[];
extern const uint8_t Str_Brightness_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Backlight_E[];
extern const uint8_t Str_Backlight_F[];
extern const uint8_t Str_Backlight_D[];
extern const uint8_t Str_Backlight_S[];
extern const uint8_t Str_Backlight_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Saturation_E[];
extern const uint8_t Str_Saturation_D[];
extern const uint8_t Str_Saturation_S[];
extern const uint8_t Str_Saturation_K[];

//--------------------------------------------------------------------------------
extern const uint8_t Str_Reset_E[];
extern const uint8_t Str_Reset_F[];
extern const uint8_t Str_Reset_D[];
extern const uint8_t Str_Reset_S[];
extern const uint8_t Str_Reset_K[];

//--------------------------------------------------------------------------------

#ifdef SUPPORT_PC
//--------------------------------------------------------------------------------
extern const uint8_t Str_Phase_E[];
extern const uint8_t Str_Phase_S[];
//--------------------------------------------------------------------------------
extern const uint8_t Str_Clock_E[];
extern const uint8_t Str_Clock_F[];
extern const uint8_t Str_Clock_D[];
extern const uint8_t Str_Clock_S[];

//--------------------------------------------------------------------------------

extern const uint8_t Str_AutoColor_E[];
extern const uint8_t Str_AutoColor_K[];

extern const uint8_t Str_AutoAdjust_E[];
extern const uint8_t Str_AutoAdjust_K[];
#endif

//--------------------------------------------------------------------------------
#ifdef WIDE_SCREEN
extern const uint8_t Str_WideScreen_E[];
extern const uint8_t Str_WideScreen_K[];
#endif

extern const uint8_t OSDLangString[];
extern const uint8_t ModeChoice[];
extern const uint8_t VInputStdChoice[];
#ifdef WIDE_SCREEN
extern const uint8_t WideScreenChoice[];
#endif

#ifdef SUPPORT_OSDPOSITIONMOVE
extern const uint8_t OsdPositionModeChoice[];
#endif


extern const uint8_t CaptionChoice[];

//--------------------------------------------------------------------------------

extern const uint8_t 	*Enter_Password_Str[];					   
extern const uint8_t 	*CheckPCCableStr[];
extern const uint8_t 	*CheckDTVCableStr[];
extern const uint8_t 	*OutOfRangeStr[];
extern const uint8_t 	*StrVolume[];
extern const uint8_t 	*MuteOnStr[];
//--------------------------------------------------------------------------------
extern const uint8_t 	*Str_Input[];
extern const uint8_t 	*Str_Picture[];
extern const uint8_t 	*Str_Sound[];
extern const uint8_t 	*Str_Utility[];
extern const uint8_t 	*Str_ColorTemp[];

extern const uint8_t 	*Str_Comments[];
//============================================================================================
//  OSD Menu String Table
extern const uint8_t 	*Str_Composite[];

#ifdef SUPPORT_CVBS2
extern const uint8_t 	*Str_Composite2[];
#endif
#ifdef SUPPORT_SVIDEO
extern const uint8_t 	*Str_Svideo[];
#endif
#ifdef SUPPORT_COMPONENT
extern const uint8_t 	*Str_Component[];
#endif
#ifdef SUPPORT_656
extern const uint8_t 	*Str_656[];
#endif
#ifdef SUPPORT_PC
extern const uint8_t 	*Str_Pc[];
#endif
#ifdef SUPPORT_DIGITALVGA
extern const uint8_t 	*Str_DigitalVGA[];
#endif

#ifdef SUPPORT_PC
extern const uint8_t 	*Str_VPosition[];
extern const uint8_t 	*Str_HPosition[];
#endif

#ifdef SUPPORT_OSDPOSITIONMOVE
extern const uint8_t 	*Str_OSDPosition[];
#endif
extern const uint8_t 	*Str_OSDLang[];
extern const uint8_t 	*Str_SleepTimer[];
extern const uint8_t 	*Str_VInputStd[];
extern const uint8_t 	*Str_Information[];
extern const uint8_t 	*Str_Volume[];
extern const uint8_t 	*Str_Treble[];
extern const uint8_t 	*Str_Bass[];
extern const uint8_t 	*Str_Balance[];
extern const uint8_t 	*Str_Red[];
extern const uint8_t 	*Str_Blue[];
extern const uint8_t 	*Str_Green[];
extern const uint8_t 	*Str_Hue[];
extern const uint8_t 	*Str_Backlight[];
extern const uint8_t 	*Str_Sharpness[];
extern const uint8_t 	*Str_Contrast[];
extern const uint8_t 	*Str_Brightness[];
extern const uint8_t 	*Str_Saturation[];
extern const uint8_t 	*Str_Reset[];

#ifdef SUPPORT_PC
extern const uint8_t 	*Str_Phase[];
extern const uint8_t 	*Str_Clock[];
extern const uint8_t 	*Str_AutoColor[];
extern const uint8_t 	*Str_AutoAdjust[];
#endif

#ifdef WIDE_SCREEN
extern const uint8_t 	*Str_WideScreen[];
#endif

#endif
