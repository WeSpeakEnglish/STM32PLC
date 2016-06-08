#include "timer13.h"
#include "tim.h"

#include "userinterface.h"
#include "core.h"
#include "gui.h"
#include "lcd.h"
#include "keyboard.h"
#include "sound.h"



// 
void Timer13_Init(void){

TIM13->PSC = 20;
TIM13->ARR = 1759; //one second
TIM13->DIER |= TIM_DIER_UIE; //разрешаем прерывание от таймера
TIM13->CR1 |= TIM_CR1_CEN; // Начать отсчёт!
NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn); //Разрешение TIM6_DAC_IRQn прерывания

  return;
}

void TIM13_IRQHandler(void){
static uint32_t Counter = 0;
static uint32_t CounterUPD = 0;

static uint8_t FlagKBD_Repeat = 0;
 //TIM13->SR &= ~TIM_SR_UIF; //Сбрасываем флаг UIF

 switch (Counter){
  case 0:
    SetLineKbd(0); break;
  case 10:
    ReadLineKbd(0); break;
  case 20:
    SetLineKbd(1); break;
  case 30: 
    ReadLineKbd(1); break;
  case 40: 
    SetLineKbd(2); break;
  case 50: 
    ReadLineKbd(2); break;
  case 60:     
    SetLineKbd(3); break;
  case 70: 
    ReadLineKbd(3); break;
  case 80:     
    if(SolvePressedKeys()) {
      if(KB_Status.PRESSED){ 
      SOUND.CounterSound= 0; 
      SOUND.SoundPeriod = 200;
      CounterUPD = 0;
      }
      
      CounterUPD = 0;
      
      KBD_Handle(KB_Status.code);
   }
    else
      if(SOUND.CounterSound == SOUND.SoundPeriod){
         if(DISP.ReleaseTask && (Touch_Data.status == TOUCH_RELEASED) && (!DISP.ReleaseFlag)) DISP.ReleaseFlag++;//ReleaseFunction();
         
      }
    
    if((KB_Status.EVENT && KB_Status.PRESSED) &&((CounterUPD % 20) == 18))
    { 
    KBD_Handle(KB_Status.code);
    FlagKBD_Repeat =1;
    }
    if((!KB_Status.PRESSED) && (Touch_Data.status == TOUCH_RELEASED))
      CounterUPD = 0;
    if(KB_Status.EVENT && !KB_Status.PRESSED && FlagKBD_Repeat)
      {KBD_Handle(KB_Status.code); FlagKBD_Repeat =0;}
    if((CounterUPD % 20) == 18){
      if (RateChange  == 1){
        UpDownRate(1);  
        UpdateScreen = 1;
      }
      if (RateChange  == 2) {
        UpDownRate(0);
        UpdateScreen = 1;
      }
      
     CounterUPD = 0; 
    }
    CounterUPD++;
    break;
    
 //  case 90: 
//        if(UpdateScreen||TimeIsReady){
    

//   F_push(Run_GUI);//();
//   F_push(Show_GUI);//();

 //   }
    break;
 }  
 if (SOUND.CounterSound < SOUND.SoundPeriod) {
  // if(KB_Status.PRESSED)
   Bip(SOUND.CounterSound%2); 
   SOUND.CounterSound++;
 }

 Counter++;
 Counter%=100; 
 

 return;
}