#include "interrupts.h"
#include "stmpe811.h"
#include "timer14.h"





void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){


  
   Timer14_Init_Deal(100, 1);

 return;

}




