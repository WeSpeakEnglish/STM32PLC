#include "timer14.h"
#include "tim.h"
#include "stmpe811.h"
#include "userinterface.h"


u8 DealNumber = 0; //the number of actual deal For pending deal
// 
void Timer14_Init_Deal(u16 ShotTime, u8 DealNumb){ //0.0001 s per one

TIM14->PSC = 8799;
TIM14->ARR = ShotTime; //one second
TIM14->DIER |= TIM_DIER_UIE; //разрешаем прерывание от таймера
TIM14->CNT = 1;



DealNumber = DealNumb;

if(!DealNumb){
  NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn); //Разрешение TIM6_DAC_IRQn прерывания
}
else
  TIM14->CR1 |= TIM_CR1_CEN; // Начать отсчёт!
  return;
}

void TIM14_IRQHandler(void){
static u32 Counter = 0;
TIM14->SR &= ~TIM_SR_UIF; //Сбрасываем флаг UIF
TIM14->DIER &= ~TIM_DIER_UIE; //разрешаем прерывание от таймера

switch (DealNumber){
  case 0: break;
  case 1: 
   P_Touch_FreeIRQ(); 
    Timer14_Init_Deal(100,2);
    
    break;
  case 2: UB_Touch_Read();
          ChangeCircle1( Touch_Data.status );
                      break;
  case 3: break;
  case 4: break;
  case 5: break;
  case 6: break;
  case 7: break;
  
}  
Counter++;
return;
}