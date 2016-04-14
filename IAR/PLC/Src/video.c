#include "video.h"
#include "dma2d.h"
#include "gui.h"
#include "stm32f7xx_hal.h"
#include "variables.h"
#include "core.h"
#include "ltdc.h"
#include "lcd.h"

volatile DMA2D_Status PLC_DMA2D_Status = {1};
volatile u8 LayerOfView = 0;
const u32 ProjectionLayerAddress[2]={SDRAM_BANK_ADDR + LAYER_1_OFFSET, SDRAM_BANK_ADDR + LAYER_2_OFFSET}; // Were we fill out our objects?


u8 _HW_DrawLine( s16 x1, s16 y1, s16 x2, s16 y2, u32 c)
{

   if ( y1 == y2 )
   {
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_R2M;
  hdma2d.Init.ColorMode = DMA2D_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.XferCpltCallback = Transfer_DMA2D_Completed;
  HAL_DMA2D_Init(&hdma2d);
 if(PLC_DMA2D_Status.Ready != 0){
  PLC_DMA2D_Status.Ready = 0;
  if(HAL_DMA2D_Start_IT(&hdma2d, 
                        c, /* Color value in Register to Memory DMA2D mode */
                        ProjectionLayerAddress[LayerOfView] + 4 * ((u32)y1 * DisplayWIDTH + (u32)x1),  /* DMA2D output buffer */
                        x2-x1+1, /* width of buffer in pixels */
                        1) /* height of buffer in lines */ 
     != HAL_OK)
    {
    M_pull()(); 
     }  
    }
   }

   else if ( x1 == x2 )
   {
 // hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_R2M;
  hdma2d.Init.ColorMode = DMA2D_ARGB8888;
  hdma2d.Init.OutputOffset = DisplayWIDTH-1;
  hdma2d.XferCpltCallback = Transfer_DMA2D_Completed;
  HAL_DMA2D_Init(&hdma2d);
  if(PLC_DMA2D_Status.Ready != 0){ 
    PLC_DMA2D_Status.Ready = 0;
   if(HAL_DMA2D_Start_IT(&hdma2d, 
                        c, /* Color value in Register to Memory DMA2D mode */
                        ProjectionLayerAddress[LayerOfView] + 4 * ((u32)y1 * DisplayWIDTH + (u32)x1),  /* DMA2D output buffer */
                        1 , /* width of buffer in pixels */
                        y2-y1+1) /* height of buffer in lines */ 
     != HAL_OK)
  {
    M_pull()(); 
  } 
 }
 
 }
 else
   {
     return 1;
   }
     return 0;
}





void Fill_Background(void){


}


void _HW_Fill_Finite_Color(u32 StartAddress, u32 color){
 // hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_R2M;
  hdma2d.Init.ColorMode = DMA2D_ARGB8888;
   hdma2d.Init.OutputOffset       = 0;
  hdma2d.XferCpltCallback = Transfer_DMA2D_Completed;
  HAL_DMA2D_Init(&hdma2d);
  
 if(PLC_DMA2D_Status.Ready != 0){
  PLC_DMA2D_Status.Ready = 0;
 if(HAL_DMA2D_Init(&hdma2d) == HAL_OK) 
  if(HAL_DMA2D_Start_IT(&hdma2d, 
                        color, /* Color value in Register to Memory DMA2D mode */
                        StartAddress,  /* DMA2D output buffer */
                        DisplayWIDTH, /* width of buffer in pixels */
                        DisplayHEIGHT) /* height of buffer in lines */ 
     != HAL_OK)
    {
    M_pull()(); 
     }  
    }
}  

void _HW_Fill_Display_From_Mem(u32 SourceAddress, u32 DstAddress){
  
 hdma2d.Init.Mode               = DMA2D_M2M;
 hdma2d.Init.ColorMode          = DMA2D_ARGB8888;
 hdma2d.Init.OutputOffset       = 0;
 hdma2d.XferCpltCallback = Transfer_DMA2D_Completed;
  if(PLC_DMA2D_Status.Ready != 0){
  PLC_DMA2D_Status.Ready = 0;
 if(HAL_DMA2D_Init(&hdma2d) == HAL_OK) 
  if(HAL_DMA2D_Start_IT(&hdma2d, 
                        SourceAddress, /* Color value in Register to Memory DMA2D mode */
                        DstAddress,  /* DMA2D output buffer */
                        DisplayWIDTH, /* width of buffer in pixels */
                        DisplayHEIGHT) /* height of buffer in lines */ 
     != HAL_OK)
    {
    M_pull()(); 
     }  
    }
 
}

void _HW_Fill_Region(u32 DstAddress, uint32_t xSize, uint32_t ySize, uint32_t OffLine, u32 color) 
{
  /* Register to memory mode with ARGB8888 as color Mode */ 
   hdma2d.Init.Mode         = DMA2D_R2M;
   hdma2d.Init.ColorMode    = DMA2D_ARGB8888;
   hdma2d.Init.OutputOffset = OffLine;      
   hdma2d.XferCpltCallback = Transfer_DMA2D_Completed;
   
  /* DMA2D Initialization */

 if(HAL_DMA2D_Init(&hdma2d) == HAL_OK) 
  if(PLC_DMA2D_Status.Ready != 0){
  PLC_DMA2D_Status.Ready = 0;
      if (HAL_DMA2D_Start_IT(&hdma2d, color, DstAddress, xSize, ySize) == HAL_OK)
      {
    
    M_pull()(); 
       
   }
  }
}


void Transfer_DMA2D_Completed(DMA2D_HandleTypeDef *hdma2d){
  
  PLC_DMA2D_Status.Ready = 1;
  RCC->PLLSAICFGR = 0x44003FC0;
}

void LCD_Layers_Init(void){
  _HW_Fill_Finite_Color(SDRAM_BANK_ADDR + LAYER_BACK_OFFSET, 0xFFFFFFFF);
  while(!PLC_DMA2D_Status.Ready)RoutineMedium(); 
  //fill the first layer  
  _HW_Fill_Display_From_Mem(SDRAM_BANK_ADDR + LAYER_BACK_OFFSET, SDRAM_BANK_ADDR + LAYER_1_OFFSET);
  while(!PLC_DMA2D_Status.Ready)RoutineMedium(); 
  //fill the second layer
   _HW_Fill_Display_From_Mem(SDRAM_BANK_ADDR + LAYER_BACK_OFFSET, SDRAM_BANK_ADDR + LAYER_2_OFFSET);
   while(!PLC_DMA2D_Status.Ready)RoutineMedium(); 
}


