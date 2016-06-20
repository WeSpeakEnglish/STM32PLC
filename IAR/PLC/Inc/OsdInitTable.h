#ifndef _OSD_INIT_H
#define _OSD_INIT_H
#include "variables.h"

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
extern const uint8_t Init_Osd_DisplayLogo[];
//
#ifdef ADD_ANALOGPANEL
extern const uint8_t Init_Osd_DisplayLogo_A[];
#endif
extern const uint8_t Init_Osd_DisplayVchipWindow[];
extern const uint8_t Init_Osd_DisplayMuteInfo[];
extern const uint8_t Init_Osd_DisplayTVChannel[];
extern const uint8_t Init_Osd_DisplayPCInfo[];
extern const uint8_t Init_Osd_DisplayInput[];

extern const uint8_t Init_Osd_DisplayInput_A[];


extern const uint8_t                    Init_Osd_MainMenu[];
extern const uint8_t                    Init_Osd_BarWindow[];

extern IdName	struct_InputSelection[];
extern IdName   struct_VInputStd[];

#endif
