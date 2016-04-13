#include "timer13.h"
#include "tim.h"
#include "variables.h"
#include "userinterface.h"
#include "core.h"
#include "gui.h"

// 
void Timer13_Init(void){

TIM13->PSC = 400;
TIM13->ARR = 1759; //one second
TIM13->DIER |= TIM_DIER_UIE; //разрешаем прерывание от таймера
TIM13->CR1 |= TIM_CR1_CEN; // Начать отсчёт!
NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn); //Разрешение TIM6_DAC_IRQn прерывания

  return;
}

void TIM13_IRQHandler(void){
static u32 Counter = 0;
TIM13->SR &= ~TIM_SR_UIF; //Сбрасываем флаг UIF

switch (Counter % 8){
  case 0: break;
  case 1: break;
  case 2: break;
  case 3: break;
  case 4: break;
  case 5: break;
  case 6: break;
  case 7: M_push(Run_GUI_1); M_push(Show_GUI); break;
  
}  
/////////////
 RoutineMedium();

/////////////

//TIM13->CR1 |= TIM_CR1_CEN; // Начать отсчёт!
Counter++;
return;
}