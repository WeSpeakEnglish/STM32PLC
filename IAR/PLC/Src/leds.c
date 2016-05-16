#include "leds.h"
#include "stm32f7xx_hal.h"

void LED_control(uint8_t Status){
  switch(Status){
     case 0: HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3,GPIO_PIN_SET);
             break;
     case 1: HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3,GPIO_PIN_RESET);
             break;
  
  
  
  }

}
