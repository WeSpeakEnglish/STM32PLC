#ifndef __GUI_H
#define __GUI_H

#define MAX_OBJECTS_Q   64
#define MAX_PARAMS_Q    8
#define MAX_Z_INDEX     8   //max index is 7 (0-7)

//////// Types of objects
#define         LINE_TYPE                    1
#define         VERTICAL_LINE_TYPE           2
#define         HORIZONTAL_LINE_TYPE         3
#define         POLYGON_TYPE                 4
#define         TEXT_TYPE                    5
#define         CIRCLE_TYPE                  6  
#define         FILLED_CIRCLE_TYPE           7
#define         FILLED_RECT_TYPE             8
#define         IMAGE_FAST_FILL              9
#define         FILLED_TRIANGLE              10
#define         TEXT_STRING                  11
#define         FILLED_POLY                  12
#define         POLY_TYPE                    13
#define         ROTATING_FILLED_POLY_TYPE    14
#define         RECT_TYPE                    15
#define         IMAGE_WITH_TRANSP            16
////////////////////////

#include "variables.h"


typedef struct{

  uint32_t color;                //Visibility of Objects ALFA
  int8_t z_index;                   //[MAX_OBJECTS_Q];
  uint8_t type;                      //[MAX_OBJECTS_Q];
  uint8_t existance;                // deleted or not

  uint32_t params[MAX_PARAMS_Q];     //
}GUI_Object;



void GUI_Free(void);
GUI_Object* GUI_SetObject(uint32_t typeObj, uint32_t colorObj, uint32_t z_Index, uint32_t NumbOfParms,...);
void GUI_Release(); // release interface
uint8_t GUI_Del_Obj(GUI_Object* deleteObj); // delete Object
uint8_t GUI_Hide_Obj(GUI_Object* hideObj); // hide Object
uint8_t GUI_SetVisibility_Obj(GUI_Object* Obj, uint32_t Value); //set Visibility
 void Show_GUI(void);
 
#endif
