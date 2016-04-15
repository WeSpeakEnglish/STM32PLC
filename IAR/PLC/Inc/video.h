#ifndef __VIDEO_H
#define __VIDEO_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "variables.h"
#include "lcd.h"
   
typedef struct{
 u8 Ready;
}DMA2D_Status;

extern volatile DMA2D_Status PLC_DMA2D_Status;
extern volatile u8 LayerOfView;
extern const u32 ProjectionLayerAddress[2]; // Were we fill out our objects?

 void Transfer_DMA2D_Completed(DMA2D_HandleTypeDef *hdma2d);  
 u8 _HW_DrawLine( s16 x1, s16 y1, s16 x2, s16 y2, u32 c );  

 void _HW_Fill_Finite_Color(u32 StartAddress, u32 color);
 void _HW_Fill_Display_From_Mem(u32 SourceAddress, u32 DstAddress);
 void LCD_Layers_Init(void);
 void _HW_Fill_Region(u32 DstAddress, uint32_t xSize, uint32_t ySize, uint32_t OffLine, u32 color);
 void _HW_Fill_Image(u32 SrcAddress, u32 DstAddress, uint32_t xSize, uint32_t  ySize); 
 void _HW_Fill_ImageToRAM(u32 SrcAddress, u32 DstAddress, uint32_t xSize, uint32_t  ySize); 
#ifdef __cplusplus
 }
#endif

#endif /* __VIDEO_H */