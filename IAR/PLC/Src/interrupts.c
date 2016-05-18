#include "interrupts.h"
#include "stmpe811.h"
#include "timer14.h"
#include "core.h"
#include "userinterface.h"





void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){


  
   Timer14_Init_Deal(100, 1);

 return;

}



void   EXTI9_5_IRQHandler(void)        //; EXTI Line 9..5
{
        
        
 NVIC_ClearPendingIRQ (EXTI9_5_IRQn);
        
 if ((GPIOD->IDR)&(1<<7) == (1<<7)){
        
         EXTI->PR |= (1<<7);
         
   //          UpdateScreen = 1;  
             //   NVIC_DisableIRQ(EXTI9_5_IRQn);
             //   GPIOA->BSRR |= 0x02;
             //   pCurrent_mode->stat.W5100_interrupt = 1;
             //   GPIOA->BSRR |= (0x02<<16);
        };
  NVIC_ClearPendingIRQ (EXTI9_5_IRQn);
        return;
}