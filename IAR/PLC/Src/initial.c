#include "initial.h"



void InitPeriph(void){
SDRAM_Initialization_Sequence(&hsdram1);
  
  pMediumQueueIni();            // fill the medium queue by Zero functions
  pFastQueueIni();              // fill the fast queue by Zero functions
  pSlowQueueIni();              // fill the slow queue by Zero functions
  
  NAND_readId();
  
  Timer14_Init_Deal(1000, 0);   //just init timer
  Timer13_Init();
  
  UB_Touch_Init();
//  BD_Init_TW8819();
  
 // PCF8563_Init();
  
//   dt.weekday = 3;
//   dt.day = 22;
//   dt.month = 06;
//   dt.year = 16;
//   dt.hours = 16;
//   dt.minutes = 12;
//   dt.seconds = 0;
//   PCF8563_set_datetime(&dt);
//   config_CLKOUT(0x83); // 1 SECOND Clockuot
  
  SDRAM_free();
  
  PreLoadImages(SDRAM_BANK_ADDR);
  //LCD_Layers_Init();
 // BD_Init_TW8819(); 
 // Switch_Camera(1);
  MX_LTDC_Init();
  LCD_Init();
  LCD_SetLight(7);
  Load_GUI_0(); 
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  LED_control(1);
 

}



