#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H
#include "gui.h"
#include "stmpe811.h"
#include "rtc.h"
#include "lcd.h"

typedef struct{
  uint8_t       Screen; //0 =base 1= lateral blade 2 = frontal blade 3 = topping 4 = brush 
  uint8_t       Event;
  uint8_t       KbdCode;
  int8_t        TS_ZoneNumber;
  int8_t        SelectedField;
  int8_t        ReleaseTask; // task for release button or touch screen
 // int8_t        ReleaseFlag; // task for release button or touch screen
}Disp;

// define zones for Touh Screen pressing detection
typedef struct { 
  Point LeftTop;
  Point RightBottom;
} Zone;

extern volatile uint8_t UpdateScreen;
extern volatile uint8_t TimeIsReady;
extern volatile Disp DISP;
extern date_time_t dt;
void Load_GUI_0(void);
void Load_GUI_2(void);
void ChangeCircle1(uint8_t Consistance);
void Run_GUI(void);
void KBD_Handle(uint8_t code);
void TouchScreen_Handle(uint16_t x, uint16_t y);
void PreLoadImages(uint32_t BaseAddr);
void ViewScreen(void);
void ReleaseFunction(void);
uint8_t solveTriangleZones(const Zone * pZone, uint8_t Type, const uint16_t X,  const uint16_t Y);





#endif



