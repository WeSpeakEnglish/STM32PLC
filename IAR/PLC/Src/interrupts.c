#include "interrupts.h"
#include "stmpe811.h"
#include "timer14.h"
#include "core.h"
#include "userinterface.h"
#include "rtc.h"





void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
 NVIC_ClearPendingIRQ (EXTI0_IRQn);

   EXTI->PR |= (1<<0);
   Timer14_Init_Deal(350, 1);
 
 return;

}

void   EXTI9_5_IRQHandler(void)        //; EXTI Line 9..5
{
// static uint8_t Counter = 0;     
        
// NVIC_ClearPendingIRQ (EXTI9_5_IRQn);
        
  if(!RESmutex_2){ 
        
      TimeIsReady = 1;   
  }
  else{
   TimeIsReady = 0; 
  }
   EXTI->PR |= EXTI_PR_PR7;
        return;
}
