#include "keyboard.h"
#include "stm32f7xx_hal.h"

union Keys_U readedKeys;
uint8_t ReadyFlagKb = 0;
KB_status KB_Status;

uint8_t getKB_event(void){
 if(KB_Status.EVENT && KB_Status.PRESSED)return (KB_Status.code);
return 0;
}

void SetLineKbd(uint8_t Number){
  switch(Number){
    case 0: 
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10,GPIO_PIN_SET);
      break;
    case 1: 
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9|GPIO_PIN_10,GPIO_PIN_SET);   
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_RESET);        
      break;  
    case 2: 
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_10,GPIO_PIN_SET);   
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,GPIO_PIN_RESET); 
      break;
    case 3: 
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9,GPIO_PIN_SET);   
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10,GPIO_PIN_RESET);
  }
return;
}

void ReadLineKbd(uint8_t Number){

  switch(Number){
    case 0: 
      readedKeys.keys.COL_0 = (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)<<1) + (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2));
      break;
    case 1: 
      readedKeys.keys.COL_1 = (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)<<1) + (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2));
      break; 
    case 2: 
      readedKeys.keys.COL_2 = (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)<<1) + (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2));
      break;    
    case 3: 
      readedKeys.keys.COL_3 = (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)<<1) + (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2));
      break;
  }
return;

}

uint8_t SolvePressedKeys(void){
  static uint8_t Lines_Kb[2]={0xFF,0xFF}; // store conditions, expect regulated 
  static uint8_t Index = 0;  // index for send data to arrays for decrease rattle
  static uint8_t OldKeysLine = 0xFF; // store old key pressed for compare with it
  static uint8_t Pressed = 0;
        
  Lines_Kb[Index] = readedKeys.bits; 
  if(Lines_Kb[0] == Lines_Kb[1]){
    if(OldKeysLine != readedKeys.bits){
    GenerateKbdMessages(OldKeysLine ^ readedKeys.bits);
    OldKeysLine  =  readedKeys.bits;
    Pressed = 1;
    }
    else{
    Pressed = 0;
    }
  }  
  
   Index++;
   Index%=2;
  return Pressed;
}


uint8_t GenerateKbdMessages(uint8_t XORedKeyBits){ // receve XOR of Old and New Keys State for resolve events
 static uint8_t Event;
 static uint8_t i;
 const uint8_t CharNames[8] = {0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31};   


for(i=0;i<8;i++){
    if(XORedKeyBits & (1<<i)){  //bit to bit lookup for events
      if(readedKeys.bits & (1<<i)) Event = 0;
      else Event = 1;
     //if(Event){   //press down is Zero
      KB_Status.PRESSED  = Event;
      KB_Status.EVENT = 1;
    //  QueueElem.QueEl.EventType = Event;              //pressed eq 0 or unpressed (eq1)
   //   QueueElem.QueEl.Keyb_Key = CharNames[i];        // what key number?
      KB_Status.code = CharNames[i];
     
   //   }
    return KB_Status.code;
    }
  }
return 0;
}

