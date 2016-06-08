#include "userinterface.h"
#include "video.h"
#include "calculations.h"
#include "core.h"
#include "keyboard.h"
#include "sound.h"
#include "fonts.h"
#include "timer14.h"
#include "timer13.h"
#include "ltdc.h"
#include "tw8819.h"


#define DOZE_LIMIT_H 200
#define DOZE_LIMIT_L 100
#define RANGE_LIMIT_H 6
#define RANGE_LIMIT_L 1
#define RATE_LIMIT_H 2000
#define RATE_LIMIT_L 500

GUI_Object* Images[40]; 
GUI_Object* Text[19];
GUI_Object* Rect1;
GUI_Object* Poly2;
GUI_Object* Poly3;
uint8_t StrDate[11]="25.04.2016";
uint8_t StrTime[9]="20:00:00";
uint8_t StrDATA[16][8];


volatile uint32_t TimeIsReady = 0;
volatile uint8_t UpdateScreen = 0;
volatile uint8_t CAM_flag = 0;
uint8_t RateChange = 0;

volatile date_time_t dt;  

volatile Disp DISP;

struct{
ImageInfo ImgArray[100];
uint16_t Number;
}IMAGES;

volatile PatchPARMS PatchParms;


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
   
   {{273,62},{531,142}},   //16 THE NORD BIG IMAGE
   {{152,62},{272,142}},   //17 THE NW BIG IMAGE  
   {{532,62},{654,142}},   //18 THE NE BIG IMAGE 
   
   {{273,302},{531,380}},   //19 THE SOUCH BIG IMAGE
   {{152,302},{272,380}},   //20 THE SW BIG IMAGE  
   {{532,302},{654,380}},   //21 THE SE BIG IMAGE  
   
   {{152,143},{272,301}},   //22 THE LEFT BIG IMAGE 
   {{532,143},{654,301}},   //23 THE RIGHT BIG IMAGE 
   
   {{150,66},{400,142}},    //24 THE BRUSH UP 
   {{150,298},{400,380}},   //25 THE BRUSH DOWN 
   
   {{401,66},{652,142}},    //26 THE RATE UP 
   {{401,298},{652,380}},   //27 THE RATE DOWN 
   {{690,415},{784,498}},   //28 THE RATE DOWN 
 };   

void Load_GUI_0(void){
uint16_t Temp_16;  
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
 //  Images[19] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[31], 150, 61); // SCREEN 2 LEFT PRESSED(BIG IMG)
 //  Images[20] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[32], 150, 61); // SCREEN 2 BOTTOM PRESSED(BIG IMG)
 //  Images[21] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[33], 150, 61); // SCREEN 2 RIGTH PRESSED(BIG IMG)
 //  Images[22] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[34], 150, 61); // SCREEN 2 TOP PRESSED(BIG IMG)
   Images[23] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[35], 150, 61); // SCREEN 2 NOT PRESSED (BIG IMG)
   Images[24] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[36], 150, 61); // SCREEN 1 NOT PRESSED (BIG IMG)
 // Images[25] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[37], 150, 61); // SCREEN 1 LEFT PRESSED (BIG IMG)
 // Images[26] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[38], 150, 61); // SCREEN 1 BOTTOM PRESSED (BIG IMG)
 // Images[27] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[39], 150, 61); // SCREEN 1 RIGHT PRESSED (BIG IMG)
 //  Images[28] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[40], 150, 61); // SCREEN 1 TOP PRESSED (BIG IMG)
   Images[29] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[45], 150, 61); // SCREEN 3 NOT PRESSED (BIG IMG)
 //  Images[30] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[46], 150, 61); // SCREEN 3 BOTTOM BRUSH (BIG IMG)
 //  Images[31] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[47], 150, 61); // SCREEN 3 LEFT RATE (BIG IMG)
 //  Images[32] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[48], 150, 61); // SCREEN 3 TOP BRUSH (BIG IMG)
 //  Images[33] = GUI_SetObject(IMAGE_FAST_FILL,0, 0, 3, &IMAGES.ImgArray[49], 150, 61); // SCREEN 3 RIGHT RATE (BIG IMG)
   
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
  Temp_16 = PatchParms.DiapR;
  Temp_16 += PatchParms.DiapL;
  Itoa(StrDATA[4], Temp_16);
  
  Text[4] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 500, 82,"1254 êã    ÏÅÑÎÊ-ÑÎËÜ", CENTER_MODE, 2, &RIAD_16pt,0); 
 
  Text[5] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 90, StrDATA[0], CENTER_MODE, 2, &RIAD_30pt,0);   // DOSE RIGHT
  Text[6] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 213, StrDATA[4], CENTER_MODE, 2, &RIAD_30pt,0);  // DIAPAZONE RIGHT 
  Text[7] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 336, StrDATA[2], CENTER_MODE, 2, &RIAD_30pt,0);  // RATE RIGHT
  
  Text[8] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 335, 340, "ì", LEFT_MODE, 1, &RIAD_16pt,0); 
  Text[9] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 330, 200, "ã/ì²", LEFT_MODE, 1, &RIAD_16pt,0);   
  Text[10] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 335, 260, StrDATA[4], RIGHT_MODE, 4, &RIAD_80pt,0);
  Text[11] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 330, 120, StrDATA[0], RIGHT_MODE, 4, &RIAD_80pt,0);

  Text[12] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 480, 300, StrDATA[1], RIGHT_MODE, 2, &RIAD_40pt,0);
  Text[13] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 588, 300, StrDATA[3], LEFT_MODE, 2, &RIAD_40pt,0);
  Text[14] = GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 0, 7, 527, 213, StrDATA[2], CENTER_MODE, 2, &RIAD_40pt,0); // BIG RATE on the SCREEN 3
  
  GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 120, "ã/ì²", CENTER_MODE, 1, &RIAD_16pt,0);   // with 1 pix kerning
  GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 243, "ì", CENTER_MODE, 1, &RIAD_16pt,0);
  GUI_SetObject(TEXT_STRING ,0xFFFFFFFF, 3, 7, 735, 366, "îá/ìèí", CENTER_MODE, 1, &RIAD_16pt,0);
  
  UpdateScreen = 1;
}

void Run_GUI(void){
uint16_t Temp16;

  if(TimeIsReady){
    while (RESmutex_1) ;
    RESmutex_1 = 1;
    PCF8563_read_datetime(&dt);
    RESmutex_1 = 0;
    
    GetDateToStr(StrDate, &dt);
    GetTimeToStr(StrTime, &dt);
    TimeIsReady = 0;
  }
  
  Itoa(StrDATA[0], PatchParms.Doze);
  Itoa(StrDATA[1], PatchParms.DiapL);
  Itoa(StrDATA[2], PatchParms.Rate);
  Itoa(StrDATA[3], PatchParms.DiapR);
  Temp16 = PatchParms.DiapR;
  Temp16 += PatchParms.DiapL;
  Itoa(StrDATA[4], Temp16);
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
         DISP.SelectedField = 1;
          break;
        case 8:  //toggle index of button  
         DISP.Screen = 0;
         ViewScreen();
         if(!Images[17]->z_index){
          Images[17]->z_index = 1;
          Images[16]->z_index = 0;
          Images[18]->z_index = 0;
          } 
          DISP.SelectedField = 2;
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
        case 28:
          if(!CAM_flag) {
            CAM_flag = 1;
            LCD_Video_GPIO_Deinit();
             while (RESmutex_1) ;
              RESmutex_1 = 1;
              ChangeCVBS();
              RESmutex_1 = 0;
          }
          else {
            CAM_flag = 0;
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
            LCD_Video_GPIO_Init();
          }
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
     DISP.SelectedField = 1; 
    }
    else{
     Images[14]->params[0] = (uint32_t)&IMAGES.ImgArray[1];
     Images[13]->params[0] = (uint32_t)&IMAGES.ImgArray[0];
     DISP.SelectedField = 2; 
    }
   
   break;
  case 1:
    DISP.SelectedField = 0; 
   switch(DISP.TS_ZoneNumber){
        case 16:  ////toggle rectangles
           Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[40];
                       DISP.ReleaseTask = 1;
                       break;
        case 17:  //toggle rectangles
            if(solveTriangleZones( &ZonesTS_0[17], 1, Touch_Data.xp, Touch_Data.yp))
                 Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[40]; 
            else
                 Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[37];
           DISP.ReleaseTask = 1; 
                        break; 
        case 22:  //toggle rectangles LEFT PRESSED
             Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[37];
             DISP.ReleaseTask = 1; 
             break;
        case 20:  // SW pressed
            if(solveTriangleZones( &ZonesTS_0[20], 0, Touch_Data.xp, Touch_Data.yp))
                 Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[37]; 
            else
                 Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[38];
          
           DISP.ReleaseTask = 1; 
               break;
         case 18:  // NE
            if(solveTriangleZones( &ZonesTS_0[18], 0, Touch_Data.xp, Touch_Data.yp))
                 Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[40]; 
            else
                 Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[39];
          
           DISP.ReleaseTask = 1; 
               break;
          
         case 21:  //toggle rectangles
            if(solveTriangleZones( &ZonesTS_0[21], 1, Touch_Data.xp, Touch_Data.yp))
                 Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[39]; 
            else
                 Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[38];
          
           DISP.ReleaseTask = 1; 
        break;   
        case 19:  //toggle rectangles
             Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[38];
             DISP.ReleaseTask = 1; 
          break; 
        case 23:  //toggle rectangles
             Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[39];
             DISP.ReleaseTask = 1; 
          break;   
    }
   break;
  case 2:  
    DISP.SelectedField = 0; 
   switch(DISP.TS_ZoneNumber){ 
    case 16: 
         Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[34];
         DISP.ReleaseTask = 2;
          break;  
    case 17:                   
       if(solveTriangleZones( &ZonesTS_0[17], 1, Touch_Data.xp, Touch_Data.yp))
                 Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[34]; 
            else
                 Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[31];
            DISP.ReleaseTask = 2; 
           break;  
    case 22:
           Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[31];
            DISP.ReleaseTask = 2; 
               break; 
    case 20:
           if(solveTriangleZones( &ZonesTS_0[20], 0, Touch_Data.xp, Touch_Data.yp))
                 Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[31]; 
            else
                 Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[32];
          
           DISP.ReleaseTask = 2; 
               break;  
    case 18: //NE
           if(solveTriangleZones( &ZonesTS_0[18], 0, Touch_Data.xp, Touch_Data.yp))
                 Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[34]; 
            else
                 Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[33];
           DISP.ReleaseTask = 2; 
               break;
    case 21:  //SE
            if(solveTriangleZones( &ZonesTS_0[21], 1, Touch_Data.xp, Touch_Data.yp))
                 Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[33]; 
            else
                 Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[32];
           DISP.ReleaseTask = 2; 
        break;    
   case 19:  //toggle rectangles
             Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[32];
             DISP.ReleaseTask = 2; 
          break; 
   case 23:  //RIGHT
             Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[33];
             DISP.ReleaseTask = 2; 
          break;        
        
   }
   break;
  case 3:
    DISP.SelectedField = 0; 
    
    switch(DISP.TS_ZoneNumber){ 
        case 24: //TOP BRUSH
           Images[29]->params[0] = (uint32_t) &IMAGES.ImgArray[48];
           DISP.ReleaseTask = 3; 
           break;
        case 25: //BOTTOM BRUSH
           Images[29]->params[0] = (uint32_t) &IMAGES.ImgArray[46];
           DISP.ReleaseTask = 3; 
           break;  
        case 26: //TOP RATE
           Images[29]->params[0] = (uint32_t) &IMAGES.ImgArray[49];
           DISP.ReleaseTask = 3; 
           RateChange  = 1;
           if(PatchParms.Rate < RATE_LIMIT_H)PatchParms.Rate +=10;
           //CounterUPD = 0;
           break;
        case 27: //BOTTOM RATE
           Images[29]->params[0] = (uint32_t) &IMAGES.ImgArray[47];
           DISP.ReleaseTask = 3; 
           RateChange  = 2;
           if(PatchParms.Rate > RATE_LIMIT_L)PatchParms.Rate -=10;
         //  CounterUPD = 0;
           break;      
    }
    
 
    //
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
  
  switch(DISP.Screen){
        case 1:
          switch(KB_Status.code){
               case 0x34:
                     //Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[40];
                     //  DISP.ReleaseTask = 1;
                       DISP.TS_ZoneNumber = 16; 
                       DISP.Event = 1;
                 break;
               case 0x35:  
                       Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[37];
                       DISP.ReleaseTask = 1; 
                 break; 
               case 0x36:
                       Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[39];
                       DISP.ReleaseTask = 1; 
                 break;
               case 0x37:  
                       Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[38];
                       DISP.ReleaseTask = 1; 
                 break;   
          }
          break;
        case 2:
          switch(KB_Status.code){
               case 0x34:
                      Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[34];
                      DISP.ReleaseTask = 2;
                 break;
                case 0x35:  
                       Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[31];
                       DISP.ReleaseTask = 2; 
                break; 
               case 0x36:
                       Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[33];
                       DISP.ReleaseTask = 2; 
                 break;
               case 0x37:  
                       Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[32];
                       DISP.ReleaseTask = 2; 
                 break;                   
          }
          break;
          case 3: 
                    switch(KB_Status.code){
               case 0x34:
                       DISP.TS_ZoneNumber = 24; 
                       DISP.Event = 1;
                       DISP.ReleaseTask = 3;
                 break;
               case 0x35:  
                       DISP.TS_ZoneNumber = 27; 
                       DISP.Event = 1;
                       DISP.ReleaseTask = 3;
                       DISP.SelectedField = 4; 
                       RateChange = 2;
                 break; 
               case 0x36:
                       DISP.TS_ZoneNumber = 26; 
                       DISP.Event = 1;
                       DISP.ReleaseTask = 3;
                       DISP.SelectedField = 3; 
                       RateChange  = 1;
                 break;
               case 0x37:  
                       DISP.TS_ZoneNumber = 25; 
                       DISP.Event = 1;
                       DISP.ReleaseTask = 3;
                 break;   
          }
          break;
  }

  
  }
  else
  {
  //  DISP.Event = 1;
      switch(DISP.Screen){
        case 1:
          DISP.ReleaseTask = 1;
          DISP.ReleaseFlag = 1;
          //ReleaseFunction();
          break;
        case 2:
          DISP.ReleaseTask = 2;
         // ReleaseFunction();
          DISP.ReleaseFlag = 1;
          break;
        case 3:
          DISP.ReleaseTask = 3;
         // ReleaseFunction();
          DISP.ReleaseFlag = 1;
          break;  
     }
  // DISP.SelectedField =1;
  }
  
//KB_Status.EVENT =0;
 UpdateScreen = 1;  
 return;
}

uint8_t solveTriangleZones(const Zone * pZone, uint8_t Type, const uint16_t X,  const uint16_t Y) //solve triangle zones [/] and [\] types 
{
  //Zone ZonesTS;
  float x1 = (float) pZone->LeftTop.X;
  float x2 = (float) pZone->RightBottom.X;
  float y1 = (float) pZone->LeftTop.Y;
  float y2 = (float) pZone->RightBottom.Y;
  float Ys, k;
  
  k = (y2 - y1)/(x2 - x1);
  if(Type)  Ys = y1 + k*(X - x1);
  else Ys = y2 - k*(X - x1);
 // float x1 = pZone->
  if((uint16_t)Ys > Y) return 1; 
  return 0;
}
void TouchScreen_Handle(void){ //the handle of Touch Screen
 uint8_t Index;
 uint16_t x = Touch_Data.xp;
 uint16_t y = Touch_Data.yp;
 if(Touch_Data.status == TOUCH_PRESSED){
 DISP.TS_ZoneNumber = -1;
 
  
   for(Index = 0; Index < sizeof(ZonesTS_0)/8; Index++){
      if(DISP.Screen == 0) {
         if((Index > 15 )&&(Index != 28)) continue; // throw unnecessary zones 
       }
      if(DISP.Screen == 1 || DISP.Screen == 2)
      {
        if((Index > 23)&&(Index != 28)) continue; // throw unnecessary zones 
      }
         
      
    if(DISP.Screen == 3) {
         if(Index < 24 && Index > 15) continue; // throw unnecessary zones 
       }   
            if((x > ZonesTS_0[Index].LeftTop.X  && x < ZonesTS_0[Index].RightBottom.X)&&
              (y > ZonesTS_0[Index].LeftTop.Y  && y < ZonesTS_0[Index].RightBottom.Y)) DISP.TS_ZoneNumber = Index;
     } 
  SOUND.CounterSound= 0, SOUND.SoundPeriod = 50;
 }
 else{
  Timer14_Init_Deal(200, 3);
 
 }
 if(DISP.TS_ZoneNumber != -1){    
  DISP.Event = 1;


      } 
// UpdateScreen = 1;
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
     
      Rect1->z_index = 1; //RECT
      Text[4] -> z_index = 1; // the SAND and SALT
      
      Text[8] -> z_index = 1; //pars wiew
      Text[9] -> z_index = 1;
      Text[10] -> z_index = 1;
      Text[11] -> z_index = 1;
      Text[12] -> z_index = 1;
      Text[13] -> z_index = 1;  
      
      
      DISP.SelectedField = 1;
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
UpdateScreen = 1;
}

void ReleaseFunction(void){
//  if(!KB_Status.PRESSED){
  switch(DISP.ReleaseTask){
   case 1 :
     Images[24]->params[0] = (uint32_t) &IMAGES.ImgArray[36];
         break;  
   case 2 :
     Images[23]->params[0] = (uint32_t) &IMAGES.ImgArray[35];
         break;        
   case 3 : 
     Images[29]->params[0] = (uint32_t) &IMAGES.ImgArray[45]; 
     RateChange  = 0;
         break;
  } 
//  } 

  UpdateScreen = 1;
  DISP.ReleaseTask = 0;
}
void UpDownRate(uint8_t Direction){
  if(Direction){
   if(PatchParms.Rate < RATE_LIMIT_H)PatchParms.Rate +=10;
  }
  else
   if(PatchParms.Rate > RATE_LIMIT_L)PatchParms.Rate -=10; 
}