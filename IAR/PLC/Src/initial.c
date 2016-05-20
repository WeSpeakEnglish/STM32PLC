#include "initial.h"
#include "rtc.h"
#include "leds.h"
#include "userinterface.h"

void InitPeriph(void){
SDRAM_Initialization_Sequence(&hsdram1);
  
  pMediumQueueIni();            // fill the medium queue by Zero functions
  pFastQueueIni();              // fill the fast queue by Zero functions
  pSlowQueueIni();              // fill the slow queue by Zero functions
  
  NAND_readId();
  
  Timer14_Init_Deal(1000, 0);   //just init timer
  Timer13_Init();
  
  
  
  UB_Touch_Init();
  PCF8563_Init();
  
 // dt.weekday = 1;
 // dt.day = 25;
 // dt.month = 04;
 // dt.year = 16;
 // dt.hours = 10;
 // dt.minutes = 56;
 // dt.seconds = 0;
//  PCF8563_set_datetime(&dt);
//  config_CLKOUT(0x83); // 1 SECOND Clockuot
  
 // SDRAM_free();
  
  PreLoadImages(SDRAM_BANK_ADDR);
  //LCD_Layers_Init();
   
  MX_LTDC_Init();
  LCD_Init();
  LCD_SetLight(7);
  Load_GUI_1(); 
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  LED_control(1);
 

}



