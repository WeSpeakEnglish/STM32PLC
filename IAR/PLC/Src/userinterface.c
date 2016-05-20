#include "userinterface.h"
#include "video.h"
#include "lcd.h"
#include "stmpe811.h"
#include "image888.h"
#include "rtc.h"
#include "calculations.h"
#include "core.h"

GUI_Object* Circles[4];
//GUI_Object* Image1; 
GUI_Object* Text1;
GUI_Object* Text2; 
GUI_Object* Text3;
GUI_Object* Poly1;
GUI_Object* Poly2;
GUI_Object* Poly3;
uint8_t StrDate[11]="25.04.2016";
uint8_t StrTime[9]="20:00:00";

volatile uint8_t UpdateScreen = 0;


struct{
  uint8_t Screen; //0 =base 1= lateral blade 2 = frontal blade 3 = topping 4 = brush 
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




void Load_GUI_1(void){
 
static Point Poly1_points[4]={{350,150},{360,30},{370,150},{360,140}};
static Point Poly2_points[4]={{340,170},{360,50},{380,170},{360,160}};
static Point Poly3_points[4]={{340,170},{360,70},{380,170},{360,160}};
static Point CircleCenterTest = {360,190};

DISP.Screen = 0; 

  GUI_Free();

//  GUI_SetObject(LINE_TYPE, 0xFFFF0000, 3, 4, 100,100,1200,1200);
 // GUI_SetObject(LINE_TYPE, 0x33FF0000, 3, 4, 100,100,500,800);
 // GUI_SetObject(CIRCLE_TYPE, 0xFFFFFF00, 3, 3, 300, 300, 10);
//  GUI_SetObject(CIRCLE_TYPE, 0xFFFF00FF, 2, 3, 200+1, 200, 10);
//  Circle1 = GUI_SetObject(FILLED_CIRCLE_TYPE, 0xFFFFFF99, 4, 3, 300-10, 300, 10-5);
 // GUI_SetObject(FILLED_CIRCLE_TYPE, 0xFF00FF00, 1, 3, 300-10, 300, 10);
//  GUI_SetObject(FILLED_RECT_TYPE, 0xFFCC0000, 1, 4, 100, 100, 200, 200);
 // GUI_SetObject(HORIZONTAL_LINE_TYPE,0xFF00FF00, 1, 3, 100, 200, 300);
 // GUI_SetObject(FILLED_TRIANGLE, 0xFF00AA00, 1, 6, 50, 100, 650, 20, 300, 150);
//  Image1 = GUI_SetObject(IMAGE_FAST_FILL,0xFF00FF00, 1, 5, SDRAM_BANK_ADDR + IMAGE_1_OFFSET, 0, 0, 800, 480);  
//  Text1 = GUI_SetObject(TEXT_STRING ,0xFF0000FF, 2, 5, 100, 200, StrData, LEFT_MODE, 1);   // with 1 pix kerning
 
  GUI_SetObject(FILLED_RECT_TYPE, 0xFF000000, 2, 4, 20, 10, 110, 35);
  GUI_SetObject(FILLED_RECT_TYPE, 0xFF000000, 2, 4, 690, 10, 780, 35);
  LCD_SetBackColor(0x0000FFFF);
  Text2 = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 5, 40, 10, StrTime, LEFT_MODE, 1);   // with 1 pix kerning and center
//  LCD_SetBackColor(0x00FFFFFF);
  Text3 = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 5, 700, 10, StrDate, LEFT_MODE, 1);   // with 1 pix kerning
  
  Poly1 = GUI_SetObject(ROTATING_FILLED_POLY_TYPE, 0xFFFF0000, 5, 4, (uint32_t)Poly1_points, 4, (uint32_t)&CircleCenterTest, 0);
  Poly2 = GUI_SetObject(ROTATING_FILLED_POLY_TYPE, 0xFFCCCC00, 4, 4, (uint32_t)Poly2_points, 4, (uint32_t)&CircleCenterTest, 0);
  Poly3 = GUI_SetObject(ROTATING_FILLED_POLY_TYPE, 0xFF66CC00, 3, 4, (uint32_t)Poly3_points, 4, (uint32_t)&CircleCenterTest, 0);
  Circles[0] = GUI_SetObject(FILLED_CIRCLE_TYPE, 0xFF00FF99, 4, 3, CircleCenterTest.X, CircleCenterTest.Y, 2);
  Circles[1] = GUI_SetObject(CIRCLE_TYPE, 0xFF00FFFF, 4, 3, CircleCenterTest.X, CircleCenterTest.Y, 160);
//   GUI_SetObject(FILLED_CIRCLE_TYPE, 0xFF00FF00, 1, 3, CircleCenterTestMove.X, CircleCenterTestMove.Y, 2);

//  for(i = 0; i < 360; i+=20){
    //CircleCenterTestMove = RotatePoint(CircleCenterTestMove2, CircleCenterTest, (float32_t)i);
   // GUI_SetObject(FILLED_CIRCLE_TYPE, 0xFF00FF00+i, 1, 3, CircleCenterTestMove.X, CircleCenterTestMove.Y, 2);

//  }

 // Image2 = GUI_SetObject(IMAGE_FAST_FILL,0xFF00FF00, 2, 5, SDRAM_BANK_ADDR + IMAGE_2_OFFSET, 0, 0, 800, 480);
}

void Run_GUI_1(void){

  date_time_t dt;
  PCF8563_read_datetime(&dt);
//  PCF8563_read_datetime(&DataTime);
  

  
  GetDateToStr(StrDate, &dt);
  GetTimeToStr(StrTime, &dt);
 //  Image1->params[1] = 300-iLoad;
 //  Circle1->params[1] = 300;
 //  Circle1->params[2] = iLoad-5; 
//StorePoly((pPoint)(Poly1->params[0]),(uint16_t)(Poly1->params[1])); 
// RestorePoly((pPoint)(Poly1->params[0]),(uint16_t)(Poly1->params[1]));
// RotatePoly((pPoint)(Poly1->params[0]), &CircleCenterTest, (uint16_t)(Poly1->params[1]), 6.f*(float)dt.seconds);
  Poly1->params[3] = dt.seconds * 6000;
  Poly2->params[3] = dt.minutes * 6000;
  Poly3->params[3] = dt.hours*30000 + dt.minutes*200;
 // for(i = 0; i < 4; i++){
 //  Poly1_points[1] = RotatePoint(Poly1_points[1], CircleCenterTest, 0.01f);
//   Circles[i] = GUI_SetObject(FILLED_CIRCLE_TYPE, 0xFF00FF99, 4, 3, Poly1_points[i].X, Poly1_points[i].Y, 2);
 
}

void Load_GUI_2(void){
GUI_Free();
//LCD_InitParams(0, 0, 0xFF00FF00, &GOST_B_22x24); // set the font, color of font and the color of line
GUI_SetObject(LINE_TYPE, 1, 1, 4, 100,100,300,180);
GUI_SetObject(LINE_TYPE, 1, 1, 4, 100,100,110,110);
}

void ChangeCircle1(uint8_t Consistance){

  switch(Consistance){
    case TOUCH_PRESSED:
      Circles[0]->params[0] = Touch_Data.xp;
      Circles[0]->params[1] = Touch_Data.yp;
      break;
    case TOUCH_RELEASED: 

      break;
  }

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
  UpdateScreen = 1;
 return;
}
// define zones for Touh Screen pressing detection
typedef struct { 
  Point LeftTop;
  Point RightBottom;
} Zone;

uint8_t solveTriangleZones(Zone * pZone, uint8_t Type) //solve triangle zones [/] and [\] types 
{
  //Zone ZonesTS;
  float x1 = (float) pZone->LeftTop.X;
  float x2 = (float) pZone->RightBottom.X;
  float y1 = (float) pZone->LeftTop.Y;
  float y2 = (float) pZone->RightBottom.Y;
 // float x1 = pZone->
return 0;
}
void TouchScreen_Handle(uint16_t x, uint16_t y){ //the handle of Touch Screen
 const Zone ZonesTS[]={{{0,1},{2,3}},{{4,5},{6,7}}};  
  
  
  ChangeCircle1(TOUCH_PRESSED);
  
  UpdateScreen = 1;
  return;
}

