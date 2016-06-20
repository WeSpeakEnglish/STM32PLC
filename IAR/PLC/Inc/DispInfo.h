#ifndef __DISPINFO__
#define __DISPINFO__

#include "variables.h"
//==================================================================
//				Display Information
//==================================================================
#if (defined WQVGA) && (defined ANALOG_7INCH)
#define		INPUTINFO_ZOOM		WINZOOMx1
#define		LOGO_ZOOM		WINZOOMx3

#else // (defined WQVGA) && (defined SHARP_LQ043T3DX02)
#define		INPUTINFO_ZOOM		WINZOOMx2
#define		LOGO_ZOOM		WINZOOMx2
#endif
//#define		VOL_ZOOM			WINZOOMx4
#define		MUTE_ZOOM		WINZOOMx3
#define		TVCHN_ZOOM		WINZOOMx4
#define		RATINGINFO_ZOOM		WINZOOMx3
#define         SCANTV_ZOOM		WINZOOMx2		//ljy012304
#define	        PCINFO_ZOOM		WINZOOMx2
#define         BAR_ZOOM		WINZOOMx2


void OSDDisplayInput(void);
uint8_t ClearInput(void);

void DisplayLogo(uint8_t offset);
void ClearLogo(void);

void DisplayPCInfo(uint8_t const *ptr);
void ClearPCInfo(void);
void DisplayAutoAdjust(void);
void ClearAutoAdjust(void);

void SetDisplayedOSD( uint8_t newd );

void ClearOSDInfo(void);

void DisplayVol(void);

void DisplayMuteInfo(void);
void ClearMuteInfo(void);
uint8_t CheckAndClearOSD(void);

//==================================================================
//						TV Info
//==================================================================

uint8_t ClearTVInfo(void);

#endif	// __DISPINFO__
