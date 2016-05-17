#include "timer13.h"
#include "tim.h"
#include "variables.h"
#include "userinterface.h"
#include "core.h"
#include "gui.h"
#include "lcd.h"
#include "keyboard.h"

// 
void Timer13_Init(void){

TIM13->PSC = 200;
TIM13->ARR = 1759; //one second
TIM13->DIER |= TIM_DIER_UIE; //разрешаем прерывание от таймера
TIM13->CR1 |= TIM_CR1_CEN; // Начать отсчёт!
NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn); //Разрешение TIM6_DAC_IRQn прерывания

  return;
}

void TIM13_IRQHandler(void){
static uint32_t Counter = 0;
TIM13->SR &= ~TIM_SR_UIF; //Сбрасываем флаг UIF

switch (Counter % 16){
  case 0:
    SetLineKbd(0); break;
  case 1:
    ReadLineKbd(0); break;
  case 2:
    SetLineKbd(1); break;
  case 3: 
    ReadLineKbd(1); break;
  case 4: 
    SetLineKbd(2); break;
  case 5: 
    ReadLineKbd(2); break;
  case 6:     
    SetLineKbd(3); break;
  case 7: 
    ReadLineKbd(3); break;
  case 8:     
    SolvePressedKeys(); break;
 
}  
Counter++;
return;
}