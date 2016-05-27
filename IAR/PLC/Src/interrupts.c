#include "interrupts.h"
#include "stmpe811.h"
#include "timer14.h"
#include "core.h"
#include "userinterface.h"
#include "rtc.h"





void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){


  
   Timer14_Init_Deal(100, 1);
 
 return;

}



void   EXTI9_5_IRQHandler(void)        //; EXTI Line 9..5
{
 static uint8_t Counter = 0;     
        
 NVIC_ClearPendingIRQ (EXTI9_5_IRQn);
        
 if ((GPIOD->IDR)&(1<<7) == (1<<7)){
        
         EXTI->PR |= (1<<7);
         
    
    
  if(!(Counter%32)) TimeIsReady = 1;

        };
  
        return;
}