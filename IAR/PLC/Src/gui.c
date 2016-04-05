#include "gui.h"
#include "lcd.h"
#include <stdarg.h>

static GUI_Object GUI_Objects[MAX_OBJECTS_Q];


void GUI_Free(void){
int i, j;
 for(i = 0; i < MAX_OBJECTS_Q;  i++) {
   GUI_Objects[i].existance = 0;
   GUI_Objects[i].type = 0;
   GUI_Objects[i].color = 0;
   GUI_Objects[i].z_index = 0;
   for (j = 0; j < MAX_PARAMS_Q; j++)
   GUI_Objects[i].params[j] = 0;
  }
return;
}

 
GUI_Object*  GUI_SetObject(u32 typeObj, u32 colorObj, u32 z_Index, u32 NumbOfParms,...){
 va_list arg_ptr;
 static int i, j;      //indexes
 u8 takedFlag = 0;     // Take
 static GUI_Object NullObj;
 
 va_start(arg_ptr, NumbOfParms);
 
 

   
 NullObj.existance =0;
 
 for(i = 0; i < MAX_OBJECTS_Q; i++)       // find the nearest vacansion
   if (GUI_Objects[i].existance == 0x00){ 
     takedFlag = 1; 
     break;
   }
 if (takedFlag){ 
   GUI_Objects[i].existance = 1; // set the status of existance
   GUI_Objects[i].type = typeObj;
   GUI_Objects[i].color = colorObj;
   GUI_Objects[i].z_index = z_Index;

   for(j = 0; j < NumbOfParms; j++){
      GUI_Objects[i].params[j] = va_arg(arg_ptr, u32);
   }
    va_end(arg_ptr);
   return &GUI_Objects[i]; 
  }
 
return &NullObj;
}



void GUI_Release(){  // create GUI 
  static int i, j;       //indexes

 j = 0;
 for(j = 0; j < MAX_Z_INDEX; j++ ){
  
    for(i = 0; i < MAX_OBJECTS_Q; i++){
     if(GUI_Objects[i].z_index == j){
       if(GUI_Objects[i].existance){
      LCD_SetColorPixel(GUI_Objects[i].color); // set the font, color of font and the color of line
        switch(GUI_Objects[i].type){
          case LINE_TYPE:
             LCD_DrawLine(GUI_Objects[i].params[0], GUI_Objects[i].params[1], GUI_Objects[i].params[2], GUI_Objects[i].params[3]);
                   break;
          case VERTICAL_LINE_TYPE:
                   break;    
          case HORIZONTAL_LINE_TYPE:
                   break;  
          case POLYGON_TYPE:
                   break;
          case TEXT_TYPE:
                   break; 
          case CIRCLE_TYPE:
            LCD_DrawCircle(GUI_Objects[i].params[0], GUI_Objects[i].params[1], GUI_Objects[i].params[2]);
                   break;
       }
      } 
    }
   }
  }  
 }

u8 GUI_Del_Obj(GUI_Object* deleteObj){
 deleteObj->existance = 0;  // delete existance
return 0;
}

u8 GUI_Hide_Obj(GUI_Object* hideObj){
 hideObj->color = (hideObj->color)&0x00FFFFFF;  // hide object
return 0;
}

u8 GUI_SetVisibility_Obj(GUI_Object* Obj, u32 Value){  // the alpha level of Object
 Obj->color = Value;  // hide object
return 0;
}
