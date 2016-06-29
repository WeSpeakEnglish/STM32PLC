#include "video.h"
#include "gui.h"
#include "stm32f7xx_hal.h"
#include "variables.h"
#include "core.h"
#include "ltdc.h"
#include "ff.h"
#include "rtc.h"
#include "variables.h"
#include "fonts.h"
#include "tw8819.h"
#include "OSDFont.h"
#include "OSDBasic.h"
#include "OSDinitTable.h"
#include "DispInfo.h"


volatile DMA2D_Status PLC_DMA2D_Status = {1};
volatile uint8_t LayerOfView = 0;
const uint32_t ProjectionLayerAddress[2]={SDRAM_BANK_ADDR + LAYER_1_OFFSET, SDRAM_BANK_ADDR + LAYER_2_OFFSET}; // Were we fill out our objects?


uint8_t _HW_DrawLine( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t c)
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
                        ProjectionLayerAddress[LayerOfView] + 4 * ((uint32_t)y1 * DisplayWIDTH + (uint32_t)x1),  /* DMA2D output buffer */
                        x2-x1+1, /* width of buffer in pixels */
                        1) /* height of buffer in lines */ 
     == HAL_OK)
    {
    while(PLC_DMA2D_Status.Ready == 0){ M_pull()();}
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
  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK){ 
  if(PLC_DMA2D_Status.Ready != 0){ 
    PLC_DMA2D_Status.Ready = 0;
   if(HAL_DMA2D_Start_IT(&hdma2d, 
                        c, /* Color value in Register to Memory DMA2D mode */
                        ProjectionLayerAddress[LayerOfView] + 4 * ((uint32_t)y1 * DisplayWIDTH + (uint32_t)x1),  /* DMA2D output buffer */
                        1 , /* width of buffer in pixels */
                        y2-y1+1) /* height of buffer in lines */ 
     == HAL_OK)
   {
    while(PLC_DMA2D_Status.Ready == 0){ M_pull()();}
   } 
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

void _HW_Fill_Finite_Color(uint32_t StartAddress, uint32_t color){
 // hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_R2M;
  hdma2d.Init.ColorMode = DMA2D_ARGB8888;
   hdma2d.Init.OutputOffset       = 0;
  hdma2d.XferCpltCallback = Transfer_DMA2D_Completed;
  HAL_DMA2D_Init(&hdma2d);
  

  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK){  
   if(PLC_DMA2D_Status.Ready != 0){
   PLC_DMA2D_Status.Ready = 0;
   if(HAL_DMA2D_Start_IT(&hdma2d, 
                        color, /* Color value in Register to Memory DMA2D mode */
                        StartAddress,  /* DMA2D output buffer */
                        DisplayWIDTH, /* width of buffer in pixels */
                        DisplayHEIGHT) /* height of buffer in lines */ 
     == HAL_OK)
    {
      while(PLC_DMA2D_Status.Ready == 0){ M_pull()();}
     }  
  }
  }
}  

void _HW_Fill_Display_From_Mem(uint32_t SourceAddress, uint32_t DstAddress){
  
 hdma2d.Init.Mode               = DMA2D_M2M;
 hdma2d.Init.ColorMode          = DMA2D_ARGB8888;
 hdma2d.Init.OutputOffset       = 0;
 hdma2d.XferCpltCallback = Transfer_DMA2D_Completed;
 
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0xFF;
  hdma2d.LayerCfg[1].InputColorMode = CM_ARGB8888;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.Instance          = DMA2D;
  
  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK){  
   if(PLC_DMA2D_Status.Ready != 0){
   PLC_DMA2D_Status.Ready = 0;
   if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK)
    {
   if(HAL_DMA2D_Start_IT(&hdma2d, 
                        SourceAddress, /* Color value in Register to Memory DMA2D mode */
                        DstAddress,  /* DMA2D output buffer */
                        DisplayWIDTH, /* width of buffer in pixels */
                        DisplayHEIGHT) /* height of buffer in lines */ 
     == HAL_OK)
    {
     while(PLC_DMA2D_Status.Ready == 0){ M_pull()();}
    //  HAL_DMA2D_PollForTransfer(&hdma2d, 10); 
     }  
    }
   }
  }
}

void _HW_Fill_Region(uint32_t DstAddress, uint32_t xSize, uint32_t ySize, uint32_t OffLine, uint32_t color) 
{
  /* Register to memory mode with ARGB8888 as color Mode */ 
   hdma2d.Init.Mode         = DMA2D_R2M;
   hdma2d.Init.ColorMode    = DMA2D_ARGB8888;
   hdma2d.Init.OutputOffset = OffLine;      
   hdma2d.XferCpltCallback = Transfer_DMA2D_Completed;
   
  /* DMA2D Initialization */

   if(HAL_DMA2D_Init(&hdma2d) == HAL_OK){ 
  if(PLC_DMA2D_Status.Ready != 0){
  PLC_DMA2D_Status.Ready = 0;
      if (HAL_DMA2D_Start_IT(&hdma2d, color, DstAddress, xSize, ySize) == HAL_OK)
      {
    
    while(PLC_DMA2D_Status.Ready == 0){ M_pull()();}
       
   }
  }
 }
}

void _HW_Fill_Image(uint32_t SrcAddress, uint32_t DstAddress, uint32_t xSize, uint32_t ySize) 
{
  /* Register to memory mode with ARGB8888 as color Mode */ 
  
   hdma2d.Init.Mode         = DMA2D_M2M;
   hdma2d.Init.ColorMode    = DMA2D_ARGB8888;
   hdma2d.Init.OutputOffset = DisplayWIDTH - xSize;      
   hdma2d.XferCpltCallback = Transfer_DMA2D_Completed;
   
  /* DMA2D Initialization */

 if(HAL_DMA2D_Init(&hdma2d) == HAL_OK) 
  if(PLC_DMA2D_Status.Ready != 0){
  PLC_DMA2D_Status.Ready = 0;
      if (HAL_DMA2D_Start_IT(&hdma2d, SrcAddress, DstAddress, xSize, ySize) == HAL_OK)
      {
    while(PLC_DMA2D_Status.Ready == 0){ M_pull()();}
   }
  }
}

void _HW_Fill_ImageToRAM(uint32_t SrcAddress, uint32_t DstAddress, uint32_t xSize, uint32_t  ySize){
   hdma2d.Init.Mode             = DMA2D_M2M;
   hdma2d.Init.ColorMode        = DMA2D_ARGB8888;
   hdma2d.Init.OutputOffset     = 0;      
   hdma2d.XferCpltCallback      = Transfer_DMA2D_Completed;
   
 if(HAL_DMA2D_Init(&hdma2d) == HAL_OK) 
  if(PLC_DMA2D_Status.Ready != 0){
  PLC_DMA2D_Status.Ready = 0;
      if (HAL_DMA2D_Start_IT(&hdma2d, SrcAddress, DstAddress, xSize, ySize) == HAL_OK)
      {
   while(PLC_DMA2D_Status.Ready == 0){ M_pull()();}
   }
  }

}

void LCD_Layers_Init(void){
 // _HW_Fill_Finite_Color(SDRAM_BANK_ADDR + LAYER_BACK_OFFSET, 0xFFFFFFFF);
 // while(!PLC_DMA2D_Status.Ready)RoutineMedium(); 
  //fill the first layer  
  _HW_Fill_Display_From_Mem(SDRAM_BANK_ADDR + LAYER_BACK_OFFSET, SDRAM_BANK_ADDR + LAYER_1_OFFSET);
  while(!PLC_DMA2D_Status.Ready)RoutineMedium(); 
  //fill the second layer
   _HW_Fill_Display_From_Mem(SDRAM_BANK_ADDR + LAYER_BACK_OFFSET, SDRAM_BANK_ADDR + LAYER_2_OFFSET);
   while(!PLC_DMA2D_Status.Ready)RoutineMedium(); 
}

  
ImgSize LoadBitmapFromSD(uint8_t *NameOfFile, uint32_t AddressOfImage)//
{
  uint32_t index = 0, byte_pixel = 0;
  uint32_t psw, scanlinebytes, padding;
  
  ImgSize Size;
 // uint32_t address;
  uint32_t input_color_mode = 0;
  uint8_t pbmp[DisplayWIDTH*4];
  uint8_t res; //variable for return values
  FATFS fs; //fat object FATFS
  FIL OurFile; // this is our file here
  UINT br; //just counter
  DWORD PositionOfFile, LineBytesSize;
  
  res = f_mount(&fs,"0:",1);
if (res == FR_OK){
  //open the file
  res = f_open(&OurFile,(char const*)NameOfFile,FA_READ);
  if (res == FR_OK)f_read(&OurFile, pbmp, 30, &br);

 }
 else{
   //не удалось смонтировать диск
   Size.height = Size.width =0;
   
   return Size;
 }


  /* Get bitmap data address offset */
  index = *(__IO uint16_t *) (pbmp + 10);
  index |= (*(__IO uint16_t *) (pbmp + 12)) << 16;
  
  /* Read bitmap width */
  Size.width  = *(uint16_t *) (pbmp + 18);
  Size.width |= (*(uint16_t *) (pbmp + 20)) << 16;
   
  /* Read bitmap height */
  Size.height = *(uint16_t *) (pbmp + 22);
  Size.height |= (*(uint16_t *) (pbmp + 24)) << 16; 
  
  /* Read bit/pixel */
  byte_pixel = (*(uint16_t *) (pbmp + 28))/8;   
  /* Set the address */
  
  /* Get the layer pixel format */    
  if (byte_pixel == 4)
  {
    input_color_mode = CM_ARGB8888;
  }
  else if (byte_pixel == 2)
  {
    input_color_mode = CM_RGB565;   
  }
  else 
  {
    input_color_mode = CM_RGB888;
  }
  /* Bypass the bitmap header */
  padding = 0;
  scanlinebytes = Size.width * byte_pixel;
  while ( ( scanlinebytes + padding ) % 4 != 0 )
		padding++;
  psw = scanlinebytes + padding;
  
  PositionOfFile = index + psw * (Size.height - 1);
  LineBytesSize = byte_pixel * Size.width;
  res = f_lseek(&OurFile, PositionOfFile); //pointer to the last line of bitmap
  res = f_read(&OurFile, &pbmp[0], LineBytesSize, &br);

  /* Convert picture to ARGB8888 pixel format */
  for(index=0; index < Size.height; index++)
  {
    /* Pixel format conversion */
    LL_ConvertLineToARGB8888(pbmp, (void *)AddressOfImage, (uint32_t) Size.width, (uint32_t) input_color_mode);
    
    /* Increment the source and destination buffers */
    AddressOfImage +=  (Size.width * 4);
    PositionOfFile -= psw;
  f_lseek(&OurFile, PositionOfFile); //pointer to the last line of bitmap
  f_read(&OurFile, pbmp, LineBytesSize + (Size.width) % 4, &br);
  } 
  f_close(&OurFile);//close the file
  f_mount(NULL, "0:", 0);//unmount the drive
  
  return Size;
}  
   
void Transfer_DMA2D_Completed(DMA2D_HandleTypeDef *hdma2d){
  
  PLC_DMA2D_Status.Ready = 1;
//  RCC->PLLSAICFGR = 0x44003FC0;
}

void TwoDigitsToChars(uint8_t * Src){
  Src[0] += 0x30; 
  Src[1] += 0x30;
  return;
}

void VideoCAMOnOff(uint8_t NumbCam, uint8_t On){
   uint8_t DispCamN[]={'K','A','M',' ',0x30};
    if(On){
          LCD_Video_GPIO_Deinit();
             while (RESmutex_1) ;
              RESmutex_1 = 1;
              HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
              HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_SET);	
              I2CDeviceInitialize(InitCVBSAll);
              FOSDDownloadFont(1);
              Switch_Camera(NumbCam);
              OSDSetDEDelay();
              DispCamN[4] = 0x30 + NumbCam;
              OSDDisplayInput((uint8_t * )DispCamN);
 //             GetTempLM75();
//             sEE_WriteBuffer((uint8_t *)RIAD_80pt.table, 0x0000, 65535);
  //            Temp16 = 128;
  //            sEE_ReadBuffer(TempReceive,62361,&Temp16);
              RESmutex_1 = 0;
  }
  else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_RESET);
            LCD_Video_GPIO_Init();
          }
}