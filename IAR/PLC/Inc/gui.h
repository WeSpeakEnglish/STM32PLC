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
////////////////////////

#include "variables.h"


typedef struct{

  u32 color;                //Visibility of Objects ALFA
  s8 z_index;                   //[MAX_OBJECTS_Q];
  u8 type;                      //[MAX_OBJECTS_Q];
  u8 existance;                // deleted or not

  u32 params[MAX_PARAMS_Q];     //
}GUI_Object;



void GUI_Free(void);
GUI_Object* GUI_SetObject(u32 typeObj, u32 colorObj, u32 z_Index, u32 NumbOfParms,...);
void GUI_Release(); // release interface
u8 GUI_Del_Obj(GUI_Object* deleteObj); // delete Object
u8 GUI_Hide_Obj(GUI_Object* hideObj); // hide Object
u8 GUI_SetVisibility_Obj(GUI_Object* Obj, u32 Value); //set Visibility
 void Show_GUI(void);
 
#endif
