#include "userinterface.h"
#include "video.h"
#include "lcd.h"
#include "stmpe811.h"
#include "rtc.h"
#include "calculations.h"
#include "core.h"
#include "keyboard.h"
#include "sound.h"
#include "fonts.h"

GUI_Object* Circles[4];
GUI_Object* Images[10]; 
GUI_Object* Text1;
GUI_Object* Text2; 
GUI_Object* Text3;
GUI_Object* Text4;
GUI_Object* Poly1;
GUI_Object* Poly2;
GUI_Object* Poly3;
uint8_t StrDate[11]="25.04.2016";
uint8_t StrTime[9]="20:00:00";

volatile uint8_t TimeIsReady = 0;
volatile uint8_t UpdateScreen = 0;


struct{
  uint8_t       Screen; //0 =base 1= lateral blade 2 = frontal blade 3 = topping 4 = brush 
  uint8_t       Event;
  uint8_t       KbdCode;
  int8_t        TS_ZoneNumber;
}DISP;

struct ImageInfo{
  uint16_t index;
  uint16_t xsize;
  uint16_t ysize;
  uint32_t address;
};

struct{
struct ImageInfo ImgArray[100];
uint16_t Number;
}IMAGES;




void Load_GUI_0(void){

DISP.Screen = 0; 

  GUI_Free();
 
  
   Images[0] = GUI_SetObject(IMAGE_FAST_FILL,0xFF00FF00, 1, 5, IMAGES.ImgArray[11].address, 12, 407, IMAGES.ImgArray[11].xsize, IMAGES.ImgArray[11].ysize); 
   
   //load buttons
   Images[1] = GUI_SetObject(IMAGE_FAST_FILL,0xFF00FF00, 1, 5, IMAGES.ImgArray[22].address, 12, 48, IMAGES.ImgArray[22].xsize, IMAGES.ImgArray[22].ysize); //OFF left
   Images[2] = GUI_SetObject(IMAGE_FAST_FILL,0xFF00FF00, 0, 5, IMAGES.ImgArray[3].address, 12, 118, IMAGES.ImgArray[3].xsize, IMAGES.ImgArray[3].ysize); //auto left
   Images[3] = GUI_SetObject(IMAGE_FAST_FILL,0xFF00FF00, 0, 5, IMAGES.ImgArray[9].address, 12, 190, IMAGES.ImgArray[9].xsize, IMAGES.ImgArray[9].ysize); //max left
   Images[4] = GUI_SetObject(IMAGE_FAST_FILL,0xFF00FF00, 0, 5, IMAGES.ImgArray[20].address, 12, 262, IMAGES.ImgArray[20].xsize, IMAGES.ImgArray[20].ysize); //sim left
   Images[5] = GUI_SetObject(IMAGE_FAST_FILL,0xFF00FF00, 0, 5, IMAGES.ImgArray[18].address, 12, 337, IMAGES.ImgArray[18].xsize, IMAGES.ImgArray[18].ysize); //sim brush
   
   GUI_SetObject(FILLED_RECT_TYPE, 0xFF000000, 2, 4, 20, 10, 110, 35);
  GUI_SetObject(FILLED_RECT_TYPE, 0xFF000000, 2, 4, 690, 10, 780, 35);
 // LCD_SetBackColor(0x0000FFFF);

 // Text2 = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 40, 10, StrTime, LEFT_MODE, 1, &GOST_B_23_var, 0x0000FFFF);   // with 1 pix kerning and center
 // Text3 = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 700, 10, StrDate, LEFT_MODE, 1, &GOST_B_23_var, 0x0000FFFF);   // with 1 pix kerning


  Text4 = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 200, 200, "Привет", LEFT_MODE, 1, &RIAD_80pt, 0x0000FFFF);   // with 1 pix kerning
 
  Circles[0] = GUI_SetObject(FILLED_CIRCLE_TYPE, 0xFF00FF99, 4, 3, 800, 480, 2);
 
 UpdateScreen = 1;
}

void Run_GUI(void){

  date_time_t dt;
  
  if(TimeIsReady){
  TimeIsReady = 0;
    PCF8563_read_datetime(&dt);
    GetDateToStr(StrDate, &dt);
    GetTimeToStr(StrTime, &dt);
  }
  if(DISP.Event){  
  switch(DISP.Screen){
  case 0:
        switch(DISP.TS_ZoneNumber){
        case 0:  //toggle index of button
          if(!Images[1]->z_index){
          Images[1]->z_index = 1;
          Images[2]->z_index = 0;
          Images[3]->z_index = 0;
          Images[4]->z_index = 0;
          } 
          break;
        case 1:  //toggle index of button
          if(!Images[2]->z_index){
          Images[2]->z_index = 1;
          Images[1]->z_index = 0;
          Images[3]->z_index = 0;
          Images[4]->z_index = 0;
          } 
          break;  
        case 2:  //toggle index of button
          if(!Images[3]->z_index){
          Images[3]->z_index = 1;
          Images[1]->z_index = 0;
          Images[2]->z_index = 0;
          Images[4]->z_index = 0;
          } 
          break;  
        case 3:  //toggle index of button
          if(!Images[4]->z_index){
          Images[4]->z_index = 1;
          Images[1]->z_index = 0;
          Images[2]->z_index = 0;
          Images[3]->z_index = 0;
          } 
          break; 
        case 4:
          if(!Images[5]->z_index){
          Images[5]->z_index = 1;
           }   
          else Images[5]->z_index = 0;
          break;
      } 
     DISP.TS_ZoneNumber = -1; 
     DISP.Screen = 0;
    
   break;
  }
  
  DISP.Event = 0;
  } 
}

void Load_GUI_2(void){
GUI_Free();
//LCD_InitParams(0, 0, 0xFF00FF00, &GOST_B_22x24); // set the font, color of font and the color of line
GUI_SetObject(LINE_TYPE, 1, 1, 4, 100,100,300,180);
GUI_SetObject(LINE_TYPE, 1, 1, 4, 100,100,110,110);
}


uint32_t FillStructIMG(uint32_t address, uint16_t startIndex, uint16_t stopIndex){
  uint16_t i = 0;
  static uint8_t Name[]="000.bmp";
  ImgSize SizesIMG;
  
  for(i = startIndex; i < stopIndex+1; i++){
    Name[0] = (i/100) + 0x30;
    Name[1] = (i/10 - 10*(i/100))  + 0x30;
    Name[2] = (i%10)  + 0x30;
   SizesIMG = LoadBitmapFromSD(Name, address);
  
   IMAGES.ImgArray[IMAGES.Number].index   = i;
   IMAGES.ImgArray[IMAGES.Number].xsize   = SizesIMG.width;
   IMAGES.ImgArray[IMAGES.Number].ysize   = SizesIMG.height; 
   IMAGES.ImgArray[IMAGES.Number].address = address;
   address += ((uint32_t)SizesIMG.height ) * ((uint32_t)SizesIMG.width) * 4;
   IMAGES.Number++;
  }
  return address;
}

void PreLoadImages(uint32_t BaseAddr){
  uint32_t address;

  IMAGES.Number = 0;
  // just simply load images into the memory 
  address = BaseAddr + IMAGE_1_OFFSET;
  address = FillStructIMG(address, 0,   29);
  address = FillStructIMG(address, 100, 105);
  address = FillStructIMG(address, 200, 204);
  address = FillStructIMG(address, 300, 303);
  address = FillStructIMG(address, 400, 404);
  
  
   //image 006.bmp like base  
   FillImageSoft(IMAGES.ImgArray[6].address, BaseAddr + LAYER_BACK_OFFSET, IMAGES.ImgArray[6].xsize, IMAGES.ImgArray[6].ysize); 
   FillImageSoft(IMAGES.ImgArray[6].address, BaseAddr + LAYER_1_OFFSET, IMAGES.ImgArray[6].xsize, IMAGES.ImgArray[6].ysize);
   FillImageSoft(IMAGES.ImgArray[6].address, BaseAddr + LAYER_2_OFFSET, IMAGES.ImgArray[6].xsize, IMAGES.ImgArray[6].ysize);

 return;
}

void KBD_Handle(uint8_t code){ //the handle of KBD
  
  //up flags
  DISP.Event = 1;
  DISP.KbdCode = KB_Status.code;
  UpdateScreen = 1;
 return;
}
// define zones for Touh Screen pressing detection
typedef struct { 
  Point LeftTop;
  Point RightBottom;
} Zone;

uint8_t solveTriangleZones(Zone * pZone, uint8_t Type, const pPoint Coords) //solve triangle zones [/] and [\] types 
{
  //Zone ZonesTS;
  float x1 = (float) pZone->LeftTop.X;
  float x2 = (float) pZone->RightBottom.X;
  float y1 = (float) pZone->LeftTop.Y;
  float y2 = (float) pZone->RightBottom.Y;
  float Ys, k;
  
  k = (y2 - y1)/(x2 - x1);
  if(Type)  Ys = y1 + k*(Coords->X - x1);
  else Ys = y2 - k*(Coords->X - x1);
 // float x1 = pZone->
  if((uint16_t)Ys > Coords->Y) return 1; 
  return 0;
}
void TouchScreen_Handle(uint16_t x, uint16_t y){ //the handle of Touch Screen
 uint8_t Index;
  const Zone ZonesTS_0[]={
   {{12,48},{116,106}}, // SW OFF (LEFT)
   {{12,119},{116,176}}, // AUTO (LEFT)
   {{12,190},{116,248}}, // MAX (LEFT)
   {{12,262},{116,320}},  //SIM (LEFT)
   {{12,338},{116,396}},  //BRUSH (LEFT)
 };  
 
 
 DISP.TS_ZoneNumber = -1;

 switch (DISP.Screen){ 
    case 0:
        for(Index = 0; Index < sizeof(ZonesTS_0)/8; Index++){
            if((x > ZonesTS_0[Index].LeftTop.X  && x < ZonesTS_0[Index].RightBottom.X)&&
              (y > ZonesTS_0[Index].LeftTop.Y  && y < ZonesTS_0[Index].RightBottom.Y)) DISP.TS_ZoneNumber = Index;
     } 
     break;
     case 1: 
       
      break;  
 
 
 }
  
      Circles[0]->params[0] = Touch_Data.xp;
      Circles[0]->params[1] = Touch_Data.yp;
      
 //up flags
 if(DISP.TS_ZoneNumber != -1){    
  DISP.Event = 1;
 // DISP.Screen = 1;
  UpdateScreen = 1;
      }
  
  SOUND.CounterSound= 0, SOUND.SoundPeriod = 50;
  return;
}

