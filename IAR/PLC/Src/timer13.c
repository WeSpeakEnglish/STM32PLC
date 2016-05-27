#include "timer13.h"
#include "tim.h"
#include "variables.h"
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
TIM13->DIER |= TIM_DIER_UIE; //��������� ���������� �� �������
TIM13->CR1 |= TIM_CR1_CEN; // ������ ������!
NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn); //���������� TIM6_DAC_IRQn ����������

  return;
}

void TIM13_IRQHandler(void){
static uint32_t Counter = 0;
static uint32_t CounterUPD = 0;

static uint8_t FlagPressed = 0;
 TIM13->SR &= ~TIM_SR_UIF; //���������� ���� UIF

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
      KBD_Handle(KB_Status.code);
      FlagPressed = 1;
       
    }
    else
      if(SOUND.CounterSound == SOUND.SoundPeriod) FlagPressed = 0;
    
    if((KB_Status.EVENT && KB_Status.PRESSED) &&((CounterUPD % 2000) == 1900))
      KBD_Handle(KB_Status.code);
    
    break;
    
    
    
 }  
 if (SOUND.CounterSound < SOUND.SoundPeriod) {
  // if(KB_Status.PRESSED)
   Bip(SOUND.CounterSound%2); 
   SOUND.CounterSound++;
 }

 Counter++;
 Counter%=100; 
 CounterUPD++;

// if(!(CounterUPD % 2048))UpdateScreen = 1;
 return;
}