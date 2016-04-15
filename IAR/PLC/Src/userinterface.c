#include "userinterface.h"
#include "video.h"
#include "lcd.h"
#include "stmpe811.h"
#include "image888.h"

GUI_Object* Circle1 =0x00000000;
GUI_Object* Image1 =0x00000000;

void Load_GUI_1(void){

  GUI_Free();

  GUI_SetObject(LINE_TYPE, 0xFFFF0000, 2, 4, 100,100,1200,1200);
  GUI_SetObject(LINE_TYPE, 0x33FF0000, 2, 4, 100,100,500,800);
  GUI_SetObject(CIRCLE_TYPE, 0xFFFFFF00, 2, 3, 300, 300, 10);
//  GUI_SetObject(CIRCLE_TYPE, 0xFFFF00FF, 2, 3, 200+1, 200, 10);
  Circle1 = GUI_SetObject(FILLED_CIRCLE_TYPE, 0xFFFFFF99, 2, 3, 300-10, 300, 10-5);
 // GUI_SetObject(FILLED_CIRCLE_TYPE, 0xFF00FF00, 1, 3, 300-10, 300, 10);
//  GUI_SetObject(FILLED_RECT_TYPE, 0xFFCC0000, 1, 4, 100, 100, 200, 200);
 // GUI_SetObject(HORIZONTAL_LINE_TYPE,0xFF00FF00, 1, 3, 100, 200, 300);
  Image1 = GUI_SetObject(IMAGE_FAST_FILL,0xFF00FF00, 1, 5, SDRAM_BANK_ADDR + IMAGE_1_OFFSET, 200, 200, 100, 100);
}

void Run_GUI_1(void){
  static u32 iLoad = 0;
  static u8 condition_UpDown = 0;
  
  
  if(condition_UpDown == 0)iLoad++;
  else iLoad--;
  
  if((iLoad == 150) && (condition_UpDown == 0) ){
   condition_UpDown = 1;
   }
  if((iLoad == 10) && (condition_UpDown == 1) ){
   condition_UpDown = 0;
   }

   Image1->params[1] = 300-iLoad;
 //  Circle1->params[1] = 300;
   Circle1->params[2] = iLoad-5;

}

void Load_GUI_2(void){
GUI_Free();
//LCD_InitParams(0, 0, 0xFF00FF00, &GOST_B_22x24); // set the font, color of font and the color of line
GUI_SetObject(LINE_TYPE, 1, 1, 4, 100,100,300,180);
GUI_SetObject(LINE_TYPE, 1, 1, 4, 100,100,110,110);
}

void ChangeCircle1(u8 Consistance){

  switch(Consistance){
    case TOUCH_PRESSED:
       Circle1->color = 0xFFFFFF00;
       Circle1->z_index = 1;
       if (Touch_Data.yp > 150) Touch_Data.yp = 150;
       Circle1->params[1] = 300- Touch_Data.yp;
      break;
    case TOUCH_RELEASED: 
       Circle1->color = 0xFFFFFF99; 
       Circle1->z_index = 4;
      break;
  }

}
