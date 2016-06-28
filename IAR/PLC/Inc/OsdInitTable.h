#ifndef _OSD_INIT_H
#define _OSD_INIT_H
#include "variables.h"

#define RATINGINFO_OSDWIN      1
#define RATINGINFO_ADDR         0
#define INPUTINFO_OSDWIN        2  
#define RATINGINFO_OSDWIN	1	
#define INPUTINFO_ADDR		160	// 9x1:9
#define DEFAULT_COLOR			BG_COLOR_TRANS|CH_COLOR_RED

#define	FONT_W	16
#define	FONT_H	26

typedef struct {
uint8_t Id;
uint8_t Name[10];
}IdName;

//*****************************************************************************
//
//           OSD Window Initialization Table
//
//*****************************************************************************
//=============================================================================
//			Initialize Window for DisplayLogo "Techwell"
//=============================================================================



extern const uint8_t Init_Osd_DisplayInput[];


extern const uint8_t                    Init_Osd_MainMenu[];
extern const uint8_t                    Init_Osd_BarWindow[];

extern IdName	struct_InputSelection[];
extern IdName   struct_VInputStd[];

#endif
