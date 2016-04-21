#include "initial.h"


void InitPeriph(void){
uint8_t res; //variable for return values
SDRAM_Initialization_Sequence(&hsdram1);
  
  pMediumQueueIni();            // fill the medium queue by Zero functions
  pFastQueueIni();              // fill the fast queue by Zero functions
  pSlowQueueIni();              // fill the slow queue by Zero functions
  
  NAND_readId();
  
  Timer14_Init_Deal(1000, 0);   //just init timer
  Timer13_Init();
  
  UB_Touch_Init();
  
  SDRAM_free();
  // Load images
  _HW_Fill_ImageToRAM((u32)image32,SDRAM_BANK_ADDR + IMAGE_1_OFFSET, 100, 100);   
    
  LCD_Layers_Init();
  
  MX_LTDC_Init();
  LCD_Init();
  LCD_SetLight(7);
  Load_GUI_1();
  
  res = BSP_SD_Init();
  res = disk_initialize(0);

}



