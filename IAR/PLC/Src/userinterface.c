#include "userinterface.h"
#include "video.h"
#include "lcd.h"
#include "calculations.h"
#include "core.h"
#include "keyboard.h"
#include "sound.h"
#include "fonts.h"

#define DOZE_LIMIT_H 200
#define DOZE_LIMIT_L 100
#define RANGE_LIMIT_H 6
#define RANGE_LIMIT_L 1

GUI_Object* Circles[4];
GUI_Object* Images[50]; 
GUI_Object* Text[19];
GUI_Object* Rect1;
GUI_Object* Poly2;
GUI_Object* Poly3;
uint8_t StrDate[11]="25.04.2016";
uint8_t StrTime[9]="20:00:00";
uint8_t StrDATA[16][8];


volatile uint8_t TimeIsReady = 0;
volatile uint8_t UpdateScreen = 0;
date_time_t dt;  

volatile struct{
  uint8_t       Screen; //0 =base 1= lateral blade 2 = frontal blade 3 = topping 4 = brush 
  uint8_t       Event;
  uint8_t       KbdCode;
  int8_t        TS_ZoneNumber;
  int8_t        SelectedField;
  int8_t        ReleaseTask; // task for release button or touch screen
}DISP;



struct{
ImageInfo ImgArray[100];
uint16_t Number;
}IMAGES;

struct{
uint16_t Doze;
uint16_t DiapL;
uint16_t DiapR;
uint16_t Rate;
}PatchParms;



void Load_GUI_0(void){

 DISP.Screen = 0; 
 
 PatchParms.Doze = 120;
 PatchParms.Rate = 1200;
 PatchParms.DiapL = 4;
 PatchParms.DiapR = 4;
 
 DISP.SelectedField = 1; 
  GUI_Free();
 
  
   //Images[6] = GUI_SetObject(IMAGE_FAST_FILL,0xFF00FF00, 1, 5, IMAGES.ImgArray[11].address, 12, 407, IMAGES.ImgArray[11].xsize, IMAGES.ImgArray[11].ysize); 
   
   //load buttons
   Images[1] = GUI_SetObject(IMAGE_FAST_FILL,0, 1, 3, &IMAGES.ImgArray[22], 12, 48); //OFF left
   Images[2] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[3], 12, 118); //auto left
   Images[3] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[9], 12, 190); //max left
   Images[4] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[20], 12, 262); //sim left
   Images[5] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[18], 12, 337); // brush left
  
   Images[6] = GUI_SetObject(IMAGE_FAST_FILL,0, 1, 3, &IMAGES.ImgArray[11], 12, 407); // TOPPING bottom
   Images[7] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[12], 124, 407); // FRONT BLADE bottom
   Images[8] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[13], 236, 407); // SIDE BLADE bottom
   Images[9] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[14], 348, 407); // BRUSH bottom
   Images[10] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[15], 461, 407); // LIGHT bottom
   Images[11] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[16], 573, 407); // FLASH bottom
   Images[12] = GUI_SetObject(IMAGE_FAST_FILL,0, 1, 3, &IMAGES.ImgArray[2], 153, 63);   // the orange square at zero screen
   
   Images[13] = GUI_SetObject(IMAGE_FAST_FILL,0, 1, 3, &IMAGES.ImgArray[1], 151, 112); // selected square at zero screen
   Images[14] = GUI_SetObject(IMAGE_FAST_FILL,0, 1, 3, &IMAGES.ImgArray[0], 151, 250); // unselected square at zero screen
   Images[15] = GUI_SetObject(IMAGE_FAST_FILL,0, 1, 3, &IMAGES.ImgArray[42], 414, 112); // TRUCK with brush picture
   
   Images[16] = GUI_SetObject(IMAGE_WITH_TRANSP,0xFF333733, 1, 3, &IMAGES.ImgArray[7], 684, 47); // DOSE RIGHT after reflow change to 0xFF333333 
   Images[17] = GUI_SetObject(IMAGE_WITH_TRANSP,0xFF333733, 0, 3, &IMAGES.ImgArray[7], 684, 169); // RANGE RIGHT after reflow change to 0xFF333333 read transp colour
   Images[18] = GUI_SetObject(IMAGE_WITH_TRANSP,0xFF333733, 0, 3, &IMAGES.ImgArray[7], 684, 293); // RANGE RIGHT after reflow change to 0xFF333333 read transp colour
      
   //IMAGES load to STRUCT and HIDE they for the Zero screen
   Images[19] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[31], 150, 61); // SCREEN 2 LEFT PRESSED(BIG IMG)
   Images[20] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[32], 150, 61); // SCREEN 2 BOTTOM PRESSED(BIG IMG)
   Images[21] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[33], 150, 61); // SCREEN 2 RIGTH PRESSED(BIG IMG)
   Images[22] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[34], 150, 61); // SCREEN 2 TOP PRESSED(BIG IMG)
   Images[23] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[35], 150, 61); // SCREEN 2 NOT PRESSED (BIG IMG)
   Images[24] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[36], 150, 61); // SCREEN 1 NOT PRESSED (BIG IMG)
   Images[25] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[37], 150, 61); // SCREEN 1 LEFT PRESSED (BIG IMG)
   Images[26] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[38], 150, 61); // SCREEN 1 BOTTOM PRESSED (BIG IMG)
   Images[27] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[39], 150, 61); // SCREEN 1 RIGHT PRESSED (BIG IMG)
   Images[28] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[40], 150, 61); // SCREEN 1 TOP PRESSED (BIG IMG)
   Images[29] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[45], 150, 61); // SCREEN 3 NOT PRESSED (BIG IMG)
   Images[30] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[46], 150, 61); // SCREEN 3 BOTTOM BRUSH (BIG IMG)
   Images[31] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[47], 150, 61); // SCREEN 3 LEFT RATE (BIG IMG)
   Images[32] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[48], 150, 61); // SCREEN 3 TOP BRUSH (BIG IMG)
   Images[33] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[49], 150, 61); // SCREEN 3 RIGHT RATE (BIG IMG)
   
   Rect1 = GUI_SetObject(RECT_TYPE,0xFFFAC58F, 1, 4, 152, 63, 651, 99); // rect on the top of screen zero
   
  // GUI_SetObject(FILLED_RECT_TYPE, 0xFF000000, 2, 4, 20, 10, 110, 35);
 //  GUI_SetObject(FILLED_RECT_TYPE, 0xFF000000, 2, 4, 690, 10, 780, 35);
 // LCD_SetBackColor(0x0000FFFF);

  Text[2] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 40, 10, StrTime, LEFT_MODE, 1, &GOST_B_23_var,0);   // watch
  Text[3] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 700, 10, StrDate, LEFT_MODE, 1, &GOST_B_23_var,0);   // date
 
  Itoa(StrDATA[0], PatchParms.Doze);
  Itoa(StrDATA[1], PatchParms.DiapL);
  Itoa(StrDATA[2], PatchParms.Rate);
  Itoa(StrDATA[3], PatchParms.DiapR);
  Itoa(StrDATA[4], PatchParms.DiapR + PatchParms.DiapL);
  
  Text[4] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 500, 82,"1254 êã    ÏÅÑÎÊ-ÑÎËÜ", CENTER_MODE, 2, &RIAD_16pt,0); 
 
  Text[5] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 90, StrDATA[0], CENTER_MODE, 2, &RIAD_30pt,0);   // DOSE RIGHT
  Text[6] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 213, StrDATA[4], CENTER_MODE, 2, &RIAD_30pt,0);  // DIAPAZONE RIGHT 
  Text[7] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 336, StrDATA[2], CENTER_MODE, 2, &RIAD_30pt,0);  // RATE RIGHT
  
  Text[8] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 335, 350, "ì", LEFT_MODE, 1, &RIAD_16pt,0); 
  Text[9] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 330, 200, "ã/ì²", LEFT_MODE, 1, &RIAD_16pt,0);   
  Text[10] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 335, 270, StrDATA[4], RIGHT_MODE, 4, &RIAD_80pt,0);
  Text[11] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 330, 120, StrDATA[0], RIGHT_MODE, 4, &RIAD_80pt,0);

  Text[12] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 480, 300, StrDATA[1], RIGHT_MODE, 2, &RIAD_40pt,0);
  Text[13] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 588, 300, StrDATA[3], LEFT_MODE, 2, &RIAD_40pt,0);
  Text[14] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 0, 7, 527, 213, StrDATA[2], CENTER_MODE, 2, &RIAD_40pt,0); // BIG RATE on the SCREEN 3
  
  GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 120, "ã/ì²", CENTER_MODE, 1, &RIAD_16pt,0);   // with 1 pix kerning
  GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 243, "ì", CENTER_MODE, 1, &RIAD_16pt,0);
  GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 366, "îá/ìèí", CENTER_MODE, 1, &RIAD_16pt,0);
  
  
  Circles[0] = GUI_SetObject(FILLED_CIRCLE_TYPE, 0xFF00FF99, 4, 3, 800, 480, 2);
 
 UpdateScreen = 1;
}

void Run_GUI(void){


 // TimeIsReady = 0;
  if(TimeIsReady){
    GetDateToStr(StrDate, &dt);
    GetTimeToStr(StrTime, &dt);
    TimeIsReady = 0;
  }
  
  Itoa(StrDATA[0], PatchParms.Doze);
  Itoa(StrDATA[1], PatchParms.DiapL);
  Itoa(StrDATA[2], PatchParms.Rate);
  Itoa(StrDATA[3], PatchParms.DiapR);
  Itoa(StrDATA[4], PatchParms.DiapR + PatchParms.DiapL);
 // }
  if(DISP.Event){ 
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
        case 5:
          if(!Images[10]->z_index){
          Images[10]->z_index = 1;
           }   
          else Images[10]->z_index = 0;
          break;  
        case 6:
          if(!Images[11]->z_index){
          Images[11]->z_index = 1;
           }   
          else Images[11]->z_index = 0;
          break;   
        case 7:  //toggle index of button    
         DISP.Screen = 0;
         ViewScreen();
         if(!Images[16]->z_index){
          Images[16]->z_index = 1;
          Images[17]->z_index = 0;
          Images[18]->z_index = 0;
          } 

          break;
        case 8:  //toggle index of button  
         DISP.Screen = 0;
         ViewScreen();
         if(!Images[17]->z_index){
          Images[17]->z_index = 1;
          Images[16]->z_index = 0;
          Images[18]->z_index = 0;
          } 
          break;
          
        case 9:  //toggle index of button
         if(!Images[18]->z_index){
          Images[18]->z_index = 1;
          Images[16]->z_index = 0;
          Images[17]->z_index = 0;
          }  
         DISP.Screen = 3;
         ViewScreen();
          break;  
        case 12: //pressed topping
         DISP.Screen = 0;
         ViewScreen(); 
          break; 
        case 13: //pressed blade front
         DISP.Screen = 1;
         ViewScreen(); 
          break;   
        case 14: //pressed blade front
         DISP.Screen = 2;
         ViewScreen(); 
          break;  
        case 15: //pressed blade side
         DISP.Screen = 3;
         ViewScreen(); 
          break; 
      }
  switch(DISP.Screen){
  case 0:
    switch(DISP.TS_ZoneNumber){
        case 10:  ////toggle rectangles
            Images[13]->params[0] = (uint32_t)&IMAGES.ImgArray[1];
            Images[14]->params[0] = (uint32_t)&IMAGES.ImgArray[0];
         
         if(!Images[16]->z_index){
          Images[16]->z_index = 1;
          Images[17]->z_index = 0;
          Images[18]->z_index = 0;
          }   
      DISP.SelectedField = 1;            
          break;
        case 11:  //toggle rectangles
            Images[14]->params[0] = (uint32_t)&IMAGES.ImgArray[1];
            Images[13]->params[0] = (uint32_t)&IMAGES.ImgArray[0];
            //-select image on the left
          if(!Images[17]->z_index){
          Images[17]->z_index = 1;
          Images[16]->z_index = 0;
          Images[18]->z_index = 0;
          } 
          DISP.SelectedField = 2; 
          break;   
   }
    
    if(Images[16]->z_index){ 
     Images[13]->params[0] = (uint32_t)&IMAGES.ImgArray[1];
     Images[14]->params[0] = (uint32_t)&IMAGES.ImgArray[0];
    }
    else{
     Images[14]->params[0] = (uint32_t)&IMAGES.ImgArray[1];
     Images[13]->params[0] = (uint32_t)&IMAGES.ImgArray[0];
    }
   
   break;
  case 1:
    DISP.SelectedField = 0; 
    
   break;
  case 2:
    DISP.SelectedField = 0; 
   break;
  case 3:
    DISP.SelectedField = 0; 

    ViewScreen(3);
   break; 
  }
  DISP.TS_ZoneNumber = -1; 
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
  if(KB_Status.PRESSED){
  DISP.Event = 1;
  DISP.KbdCode = KB_Status.code;
  
  switch(DISP.SelectedField){
    case 1:
     if(KB_Status.code == 0x34) 
        if(PatchParms.Doze < DOZE_LIMIT_H)PatchParms.Doze+=10;
     if(KB_Status.code == 0x37) 
        if(PatchParms.Doze > DOZE_LIMIT_L)PatchParms.Doze-=10;   
     
       break;
       
    case 2:
      if(KB_Status.code == 0x34){ 
        if(PatchParms.DiapL < RANGE_LIMIT_H)PatchParms.DiapL++;
        if(PatchParms.DiapR < RANGE_LIMIT_H)PatchParms.DiapR++;
      }
      if(KB_Status.code == 0x37){ 
        if(PatchParms.DiapL > RANGE_LIMIT_L)PatchParms.DiapL--;
        if(PatchParms.DiapR > RANGE_LIMIT_L)PatchParms.DiapR--; 
      }
      break;
  }

  
  }
  else
  {
  
  }
  
// UpdateScreen = 1;  
 F_push(Run_GUI);
 F_push(Show_GUI);
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
   {{12,48},{116,106}},    //0 SW OFF (LEFT)
   {{12,119},{116,176}},   //1 AUTO (LEFT)
   {{12,190},{116,248}},   //2 MAX (LEFT)
   {{12,262},{116,320}},   //3 SIM (LEFT)
   {{12,338},{116,396}},   //4 BRUSH (LEFT)
   {{464,412},{558,480}},  //5 LIGHT (DOWN)
   {{572,412},{672,480}},  //6 FLASH (DOWN)
   {{690,50},{784,147}},   //7 DOZE (RIGHT)
   {{690,177},{784,267}},  //8 RANGE (RIGHT)
   {{690,300},{784,385}},  //9 RATE (RIGHT)
   {{150,118},{386,242}},  //10 SQUARE WITH DOZE
   {{150,258},{386,378}},  //11 SQUARE WITH RANGE
   {{16,415},{110,498}},   //12 TOPPING(DOWN)
   {{130,415},{220,498}},  //13 FRONT BLADE(DOWN)  
   {{240,415},{334,498}},  //14 SIDE BLADE(DOWN) 
   {{350,415},{446,498}},  //15 BRUSH(DOWN) 
 };   
 
 
 DISP.TS_ZoneNumber = -1;

// switch (DISP.Screen){ 
//    case 0:
        for(Index = 0; Index < sizeof(ZonesTS_0)/8; Index++){
            if((x > ZonesTS_0[Index].LeftTop.X  && x < ZonesTS_0[Index].RightBottom.X)&&
              (y > ZonesTS_0[Index].LeftTop.Y  && y < ZonesTS_0[Index].RightBottom.Y)) DISP.TS_ZoneNumber = Index;
     } 
//     break;
 //    case 1: 
       
 //     break;  
 
 
 //}
  
      Circles[0]->params[0] = Touch_Data.xp;
      Circles[0]->params[1] = Touch_Data.yp;
      
 //up flags
 if(DISP.TS_ZoneNumber != -1){    
  DISP.Event = 1;
 // DISP.Screen = 1;
 UpdateScreen = 1;
 F_push(Run_GUI);
 F_push(Show_GUI);
      }
  
  SOUND.CounterSound= 0, SOUND.SoundPeriod = 50;
  return;
}

void ViewScreen(void){
 uint16_t i;
 i = sizeof(Images);
  Rect1->z_index = 0;
  for(i = 6; i < sizeof(Images)/4; i++ )  {
  if(i > 11 || i < 10)Images[i]->z_index = 0;
  }
  for(i = 4; i < sizeof(Text)/4; i++ )  {
    if(i > 7 || i < 5) Text[i]->z_index = 0;
  }
  switch(DISP.Screen){
    case 0:
      //restore images
     Images[6]->z_index = 1; // TOPPING BOTTOM
     Images[12]->z_index = 1; // the orange square restoring
     Images[13]->z_index = 1; // 1-st big rectangle
     Images[14]->z_index = 1; // 2-nd big rectangle
     Images[15]->z_index = 1; // TRUCK show
     Images[16]-> z_index = 1; // show orange sguare
     
   //  Images[13]->params[0] = (uint32_t)&IMAGES.ImgArray[0]; // squares to the default position
   //  Images[14]->params[0] = (uint32_t)&IMAGES.ImgArray[1];
     
     
      Rect1->z_index = 1; //RECT
      Text[4] -> z_index = 1; // the SAND and SALT
      
      Text[8] -> z_index = 1; //pars wiew
      Text[9] -> z_index = 1;
      Text[10] -> z_index = 1;
      Text[11] -> z_index = 1;
      Text[12] -> z_index = 1;
      Text[13] -> z_index = 1;  
      
      
      DISP.SelectedField = 0;
            break; 
    case 1:
      Images[7]->z_index = 1;  //BLADE FRONT BOTTOM
      Images[24]->z_index = 1; //SHOW BLADE FRONT BIG PICTURE
            break;  
    case 2:
      Images[8]->z_index = 1;  //BLADE SIDE BOTTOM
      Images[23]->z_index = 1; //SHOW BLADE SIDE BIG PICTURE
            break;
    case 3:
      Images[18]->z_index = 1; //RATE RIGTH
      Images[9]->z_index = 1;  //BRUSH BOTTOM
      Images[29]->z_index = 1; //SHOW BRUSH BIG PICTURE
      Text[14]->z_index = 1;
            break;          
  }

}

void ReleaseFunction(void){
  switch(DISP.ReleaseTask){
   case 1 :
     
           break;  
  
  }

}

