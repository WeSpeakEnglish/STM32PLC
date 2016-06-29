#ifndef __VIDEO_H
#define __VIDEO_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "variables.h"
#include "dma2d.h"
#include "lcd.h"
   
typedef struct{
 uint16_t width;
 uint16_t height;
}ImgSize;

typedef struct{
 uint8_t Ready;
}DMA2D_Status;

extern volatile DMA2D_Status PLC_DMA2D_Status;
extern volatile uint8_t LayerOfView;
extern const uint32_t ProjectionLayerAddress[2]; // Were we fill out our objects?

 void Transfer_DMA2D_Completed(DMA2D_HandleTypeDef *hdma2d);  
 uint8_t _HW_DrawLine( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t c );  

 void _HW_Fill_Finite_Color(uint32_t StartAddress, uint32_t color);
 void _HW_Fill_Display_From_Mem(uint32_t SourceAddress, uint32_t DstAddress);
 void LCD_Layers_Init(void);
 void _HW_Fill_Region(uint32_t DstAddress, uint32_t xSize, uint32_t ySize, uint32_t OffLine, uint32_t color);
 void _HW_Fill_Image(uint32_t SrcAddress, uint32_t DstAddress, uint32_t xSize, uint32_t  ySize); 
 void _HW_Fill_ImageToRAM(uint32_t SrcAddress, uint32_t DstAddress, uint32_t xSize, uint32_t  ySize); 
 ImgSize LoadBitmapFromSD(uint8_t *NameOfFile, uint32_t AddressOfImage);
 void TwoDigitsToChars(uint8_t * Src);
 void VideoCAMOnOff(uint8_t NumbCam, uint8_t On);
#ifdef __cplusplus
 }
#endif

#endif /* __VIDEO_H */