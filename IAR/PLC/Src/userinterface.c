#include "userinterface.h"
#include "video.h"
#include "gui.h"
#include "lcd.h"

void Load_GUI_1(void){
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
GUI_Free();
LCD_InitParams(0, 0, 0xFF000000, &GOST_B_22x24); // set the font, color of font and the color of line

GUI_SetObject(LINE_TYPE, 1, 1, 4, 100,100,1200,1200);
GUI_SetObject(LINE_TYPE, 1, 1, 4, 100,100,500,800);
GUI_SetObject(CIRCLE_TYPE, 1, 1, 3, 300, 300, iLoad);
GUI_SetObject(CIRCLE_TYPE, 1, 1, 3, 200+iLoad, 200, iLoad);
GUI_SetObject(CIRCLE_TYPE, 1, 1, 3, 300-iLoad, 300, iLoad);
}

void Load_GUI_2(void){
GUI_Free();
LCD_InitParams(0, 0, 0xFF00FF00, &GOST_B_22x24); // set the font, color of font and the color of line
GUI_SetObject(LINE_TYPE, 1, 1, 4, 100,100,300,180);
GUI_SetObject(LINE_TYPE, 1, 1, 4, 100,100,110,110);
}

