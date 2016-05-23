#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H
#include "gui.h"


extern volatile uint8_t UpdateScreen;
extern volatile uint8_t TimeIsReady;
void Load_GUI_0(void);
void Load_GUI_2(void);
void ChangeCircle1(uint8_t Consistance);
void Run_GUI(void);
void KBD_Handle(uint8_t code);
void TouchScreen_Handle(uint16_t x, uint16_t y);
void PreLoadImages(uint32_t BaseAddr);
//uint8_t solveTriangleZones(Zone * pZone, uint8_t Type, const * Point);
#endif