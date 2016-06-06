#include "core.h"
#include "fmc.h"
#include "stm32f7xx_hal.h"


volatile int8_t Semaphore = 0; // that semaphore for queues and routines control if you need :)
volatile uint32_t TicksGlobalUS = 0; //US ticking timer // in the timer interrupt handle needs just ++ operation
volatile uint8_t mutexF = 0;
volatile uint8_t mutexM = 0;
volatile uint8_t mutexS = 0;

//////
volatile uint8_t RESmutex_1 = 0; //the Resource mutex
//////


// there are three different queues and routines for corresponding timers 
// Released Three full independent queues and service functions with their content

void emptyS(); // dummy function for safe initialization of queue Slow
void emptyM(); // dummy function for safe initialization of queue Medium
void emptyF(); // dummy function for safe initialization of queue Fast

//QUEUES of pointers to the functions (procedures), which we need to run
void (*pSlowQueue[Q_SIZE_SLOW])()={emptyS}; // queue for a Slow-speed timer for get and push a void procedures 
void (*pMediumQueue[Q_SIZE_MEDIUM])()={emptyM}; // queue for a Medium-speed timer get and push a void procedures 
void (*pFastQueue[Q_SIZE_FAST])()={emptyF}; // queue for a Fast-speed timer get and push a void procedures 

//IRQ Handlers
void RoutineSlow(void){ // timer drived 
  static uint8_t branch=0; // way of switch
  switch (branch%8){ // max from 0 to 7
   case 0:         // any deal
        break;
  default: S_pull()();        // take function from queue   
        break;
   }
 branch++;
 return;
}

void RoutineMedium(void){ // timer drived 
  static uint8_t branch=0; // way of switch
  switch (branch%8){ // max from 0 to 7
   case 0:         // any deal
     
        break;
  default: M_pull()();        // take function from queue   
        break;
  
  }
 branch++;
 return;
}

void RoutineFast(void){ // timer drived 
  static uint8_t branch=0; // way of switch
  switch (branch%8){ // max from 0 to 7
   case 0:
           F_pull()();        // take function from queue       
        break;
  default:   
        break;
  
  }
 branch++;
 return;
}

//////////////////////////////

// the service variable to maintaining right order in the queues
int8_t S_last =0; // number of the last element of slow-speed queue
int8_t M_last =0; // number of the last element of medium-speed queue
int8_t F_last =0; // number of the last element of fast-speed queue

int8_t S_first =0; // number of the first element of slow-speed queue
int8_t M_first =0; // number of the first element of medium-speed queue
int8_t F_first =0; // number of the first element of fast-speed queue



//for the debugging only
void emptyS(){;} // dummy function for safe initialization of queue Slow
void emptyM(){;} // dummy function for safe initialization of queue Medium
void emptyF(){;} // dummy function for safe initialization of queue Fast
void emptyD(){;} // dummy function for safe initialization of delay on ANY function 

/// INI ELEMENTs IN THE QUEUES
void pSlowQueueIni(void){
 static uint8_t i =0;
  for(i = 0; i < Q_SIZE_SLOW; i++){
	pSlowQueue[i] = emptyS;
	}
}
void pMediumQueueIni(void){
 static uint8_t i =0;
  for(i = 0; i < Q_SIZE_MEDIUM; i++){
	pMediumQueue[i] = emptyM;
	}
}
void pFastQueueIni(void){
 static uint8_t i =0;
  for(i = 0; i < Q_SIZE_FAST; i++){
	pFastQueue[i] = emptyF;
	}
}
/// ADD ELEMENTs TO THE QUEUES
int8_t S_push(void (*pointerQ)(void) ){
 if ((S_last+1)%Q_SIZE_SLOW == S_first)	return 1;
   while(mutexS != 0);
    mutexS = 1;  // enter to critical section
    pSlowQueue[S_last++] = pointerQ;
    S_last%=Q_SIZE_SLOW;
    mutexS = 0; 
  return 0;
}

int8_t M_push(void (*pointerQ)(void) ){

 if ((M_last+1)%Q_SIZE_MEDIUM == M_first) return 1;
 
 while(mutexM != 0);
    mutexM = 1;  // enter to critical section
    pMediumQueue[M_last++] = pointerQ;
    M_last%=Q_SIZE_MEDIUM;
    mutexM = 0; 
 return 0;
}

int8_t F_push(void (*pointerQ)(void) ){
  if ((F_last+1)%Q_SIZE_FAST == F_first)return 1;
while(mutexF != 0);

    mutexF = 1;  // enter to critical section
    pFastQueue[F_last++] = pointerQ;
    F_last%=Q_SIZE_FAST;
    mutexF = 0; 
 return 0;
}

int8_t F_push2(void (*pointerQ_1)(void),void (*pointerQ_2)(void)){
  if ((F_last + 2)%Q_SIZE_FAST == F_first)return 1;
while(mutexF != 0);

    mutexF = 1;  // enter to critical section
    pFastQueue[F_last++] = pointerQ_1;
    pFastQueue[F_last++] = pointerQ_2;
    F_last%=Q_SIZE_FAST;
    mutexF = 0; 
 return 0;
}
/// GET ELEMENTs FROM THE QUEUES
void (*S_pull(void))(void){
 void (*pullVarS)(void);

 if (S_last == S_first)return emptyS;
while(mutexS != 0);
    mutexS = 1;  // enter to critical section
    pullVarS = pSlowQueue[S_first++];
    S_first%=Q_SIZE_SLOW;
    mutexS = 0;  // enter to critical section 
return pullVarS;
}

void (*M_pull(void))(void){
 void (*pullVar)(void);
 if (M_last == M_first)return emptyM;
   while(mutexM != 0);
    mutexM = 1;  // enter to critical section
    pullVar = pMediumQueue[M_first++];
    M_first%=Q_SIZE_MEDIUM;
    mutexM = 0;  // enter to critical section 
return pullVar;
}

void (*F_pull(void))(void){
 void (*pullVar)(void);
 if (F_last == F_first)return emptyF;
   while(mutexF != 0);
    mutexF = 1;  // enter to critical section
    pullVar = pFastQueue[F_first++];
    F_first%=Q_SIZE_FAST;
    mutexF = 0;  // enter to critical section 
return pullVar;
}

// wait some condition but no more that, for exapmle: while (var1!=0 && WaitOnFastQ())
void DelayOnFastQ(uint8_t WaitQFast){// set this variable and stay waiting on the fast queue
  while(WaitQFast){
         F_pull()(); 
         WaitQFast--; 
   }
};
// push several tasks from the Medium Queue
void DelayOnMediumQ(uint8_t WaitQMedium){
    while(WaitQMedium){
         M_pull()(); 
         WaitQMedium--; 
   }
}
// push several tasks from the Slow Queue

void DelayOnSlowQ(uint8_t WaitQSlow){
    while(WaitQSlow){
         S_pull()(); 
         WaitQSlow--; 
   }
} 
// We can use it like this:
//	DelayUsOnMainRoutine((main,10,1);// Initialization
//      while(!DelayUsOnMainRoutine(0,0,0)){/*do something by waiting*/}
//
//this funnction DOES NOT contain loops (linear)
uint8_t DelayUsOnProcessRoutine(void (*pointerF)(void),uint32_t TimeDel, uint8_t Ini){ //check the us changing by the Timer not just stay, but DO ANY FUNCTION
 static uint32_t OldTicksGlobalUS 	=0x00000000;
 static uint32_t Difference 		=0x00000000;
 static void (*pointerFunction)(void)  = emptyD;
 static uint32_t TimeDelay = 10; 

 if(!Ini){ // ONLY FAST RUN
 	if(OldTicksGlobalUS > TicksGlobalUS ){
 		Difference = 0xFFFFFFFF - OldTicksGlobalUS + TicksGlobalUS + 1;
 		}
 	else Difference = TicksGlobalUS - OldTicksGlobalUS;

 if (Difference > TimeDelay) return 1;	
// not stupid stay
 pointerFunction(); // DO ANY attached function
	}	
 else{  // INITIALIZATION
	OldTicksGlobalUS = TicksGlobalUS; 
        pointerFunction = pointerF;
        TimeDelay = TimeDel;
     }
	
 return 0;
}
 
 void MPU_Config (void) {
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes for SDRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x60000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4MB; //MPU_REGION_SIZE_4MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}



