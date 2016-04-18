#include "core.h"
#include "fmc.h"
#include "stm32f7xx_hal.h"


volatile s8 Semaphore = 0; // that semaphore for queues and routines control if you need :)
volatile u32 TicksGlobalUS = 0; //US ticking timer // in the timer interrupt handle needs just ++ operation
volatile u8 mutexF = 0;
volatile u8 mutexM = 0;
volatile u8 mutexS = 0;


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
  static u8 branch=0; // way of switch
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
  static u8 branch=0; // way of switch
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
  static u8 branch=0; // way of switch
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
s8 S_last =0; // number of the last element of slow-speed queue
s8 M_last =0; // number of the last element of medium-speed queue
s8 F_last =0; // number of the last element of fast-speed queue

s8 S_first =0; // number of the first element of slow-speed queue
s8 M_first =0; // number of the first element of medium-speed queue
s8 F_first =0; // number of the first element of fast-speed queue



//for the debugging only
void emptyS(){;} // dummy function for safe initialization of queue Slow
void emptyM(){;} // dummy function for safe initialization of queue Medium
void emptyF(){;} // dummy function for safe initialization of queue Fast
void emptyD(){;} // dummy function for safe initialization of delay on ANY function 

/// INI ELEMENTs IN THE QUEUES
void pSlowQueueIni(void){
 static u8 i =0;
  for(i = 0; i < Q_SIZE_SLOW; i++){
	pSlowQueue[i] = emptyS;
	}
}
void pMediumQueueIni(void){
 static u8 i =0;
  for(i = 0; i < Q_SIZE_MEDIUM; i++){
	pMediumQueue[i] = emptyM;
	}
}
void pFastQueueIni(void){
 static u8 i =0;
  for(i = 0; i < Q_SIZE_FAST; i++){
	pFastQueue[i] = emptyF;
	}
}
/// ADD ELEMENTs TO THE QUEUES
s8 S_push(void (*pointerQ)(void) ){
 if ((S_last+1)%Q_SIZE_SLOW == S_first)	return 1;
   if(mutexS == 0){
    mutexS = 1;  // enter to critical section
    pSlowQueue[S_last++] = pointerQ;
    S_last%=Q_SIZE_SLOW;
    mutexS = 0; 
   }
   else return 1;
 return 0;
}

s8 M_push(void (*pointerQ)(void) ){

 if ((M_last+1)%Q_SIZE_MEDIUM == M_first) return 1;
 
 if(mutexM == 0){
    mutexM = 1;  // enter to critical section
    pMediumQueue[M_last++] = pointerQ;
    M_last%=Q_SIZE_MEDIUM;
    mutexM = 0; 
   }
   else return 1;
 return 0;
}

s8 F_push(void (*pointerQ)(void) ){
  if ((F_last+1)%Q_SIZE_FAST == F_first)return 1;
  if(mutexF == 0){
    mutexF = 1;  // enter to critical section
    pFastQueue[F_last++] = pointerQ;
    F_last%=Q_SIZE_FAST;
    mutexF = 0; 
   }
  else return 1;
 return 0;
}
/// GET ELEMENTs FROM THE QUEUES
void (*S_pull(void))(void){
 void (*pullVarS)(void);

 if (S_last == S_first)return emptyS;
  if(mutexS == 0){
    mutexS = 1;  // enter to critical section
    pullVarS = pSlowQueue[S_first++];
    S_first%=Q_SIZE_SLOW;
    mutexS = 0;  // enter to critical section 
  }
    else return emptyS;
return pullVarS;
}

void (*M_pull(void))(void){
 void (*pullVar)(void);
 if (M_last == M_first)return emptyM;
   if(mutexM == 0){
    mutexM = 1;  // enter to critical section
    pullVar = pMediumQueue[M_first++];
    M_first%=Q_SIZE_MEDIUM;
    mutexM = 0;  // enter to critical section 
  }
    else return emptyM;
return pullVar;
}

void (*F_pull(void))(void){
 void (*pullVar)(void);
 if (F_last == F_first)return emptyF;
    if(mutexF == 0){
    mutexF = 1;  // enter to critical section
    pullVar = pFastQueue[F_first++];
    F_first%=Q_SIZE_FAST;
    mutexF = 0;  // enter to critical section 
  }
  else return emptyF;
  
return pullVar;
}

// wait some condition but no more that, for exapmle: while (var1!=0 && WaitOnFastQ())
void DelayOnFastQ(u8 WaitQFast){// set this variable and stay waiting on the fast queue
  while(WaitQFast){
         F_pull()(); 
         WaitQFast--; 
   }
};
// push several tasks from the Medium Queue
void DelayOnMediumQ(u8 WaitQMedium){
    while(WaitQMedium){
         M_pull()(); 
         WaitQMedium--; 
   }
}
// push several tasks from the Slow Queue

void DelayOnSlowQ(u8 WaitQSlow){
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
u8 DelayUsOnProcessRoutine(void (*pointerF)(void),u32 TimeDel, u8 Ini){ //check the us changing by the Timer not just stay, but DO ANY FUNCTION
 static u32 OldTicksGlobalUS 	=0x00000000;
 static u32 Difference 		=0x00000000;
 static void (*pointerFunction)(void)  = emptyD;
 static u32 TimeDelay = 10; 

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

void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram) {    //***********************************************

//static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Cmd) {    //***********************************************
FMC_SDRAM_CommandTypeDef Cmd;
__IO uint32_t tmpmrd =0;
Cmd.CommandMode= FMC_SDRAM_CMD_CLK_ENABLE;    //Step 3:  Configure a clock configuration enable command
Cmd.CommandTarget= FMC_SDRAM_CMD_TARGET_BANK1;
Cmd.AutoRefreshNumber= 1;
Cmd.ModeRegisterDefinition= 0;


HAL_SDRAM_SendCommand(hsdram, &Cmd, 0x1000);    //Send the command
HAL_Delay(100);    

//Step 4: Insert 100 ms delay

Cmd.CommandMode= FMC_SDRAM_CMD_PALL;    //Step 5: Configure a PALL (precharge all) command
Cmd.CommandTarget= FMC_SDRAM_CMD_TARGET_BANK1;
Cmd.AutoRefreshNumber= 1;
Cmd.ModeRegisterDefinition= 0;
HAL_SDRAM_SendCommand(hsdram, &Cmd, 0x1000); 

Cmd.CommandMode= FMC_SDRAM_CMD_AUTOREFRESH_MODE;    //Step 6 : Configure a Auto-Refresh command
Cmd.CommandTarget= FMC_SDRAM_CMD_TARGET_BANK1;
Cmd.AutoRefreshNumber= 4;
Cmd.ModeRegisterDefinition= 0;
HAL_SDRAM_SendCommand(hsdram, &Cmd, 0x1000);

#define SDRAM_MODEREG_BURST_LENGTH_2 ((uint16_t) 0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_8 ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL ((uint16_t) 0x0000)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((u16)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3 ((uint16_t) 0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD ((uint16_t) 0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE ((uint16_t) 0x0200)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 

tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_8          |        //Step 7: Program the external memory mode register
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_2           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
Cmd.CommandMode= FMC_SDRAM_CMD_LOAD_MODE;
Cmd.CommandTarget= FMC_SDRAM_CMD_TARGET_BANK1;
Cmd.AutoRefreshNumber= 1;
Cmd.ModeRegisterDefinition= tmpmrd;
HAL_SDRAM_SendCommand(hsdram, &Cmd, 0x1000);
//Dummy = *((volatile uint32_t *)(SDRAM_BASE_ADDR | (0x33<<12)));


    /* Step 8: Set the refresh rate counter
64msec / 4096 fresh = 15.62 us 
refresh count= 15.62usec * 84MHz  - 20 =  1292 */
HAL_SDRAM_ProgramRefreshRate(hsdram, 1386);     //refresh count

}


