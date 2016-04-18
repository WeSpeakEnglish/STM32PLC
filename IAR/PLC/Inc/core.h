#ifndef __CORE_H
#define __CORE_H
#include "variables.h"
#include "stm32f7xx_hal.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
   
   
//max size of queues is 127 elements (signed char) 
#define Q_SIZE_SLOW 64  // the size of slow queue
#define Q_SIZE_MEDIUM 64 // the size of medium queue
#define Q_SIZE_FAST 64   // the size of fast queue
   
   
   
//here is our variables
extern volatile s8 Semaphore; // that semaphore for queues and routines control if you need :)
extern volatile u32 TicksGlobalUS; //US MUST be ticking in timer in the timer interrupt handle, it needs just ++ operation
///////////////////////  
void RoutineFast(void);
void RoutineMedium(void);
void RoutineSlow(void);
/////SLOW QUEUE////////////
void pSlowQueueIni(void);
s8 S_push(void (*pointerQ)(void));
void (*S_pull(void))(void);
/////MEDIUM QUEUE////////////
void pMediumQueueIni(void);
s8 M_push(void (*pointerQ)(void));
void (*M_pull(void))(void);
////FAST QUEUE//////////////
void pFastQueueIni(void);
s8 F_push(void (*pointerQ)(void));
void (*F_pull(void))(void);
///////////////////////////
//waiting functions
void DelayOnFastQ(u8 WaitQFast); // push several tasks from the Fast Queue
void DelayOnMediumQ(u8 WaitQMedium); // push several tasks from the Medium Queue
void DelayOnSlowQ(u8 WaitQSlow); // push several tasks from the Slow Queue
u8 DelayUsOnProcessRoutine(void (*pointerF)(void),u32 TimeDel, u8 Ini); //DO OUR void function(void) while expecting TimeDel microsec or another timer periods
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram); // 
void MPU_Config (void);
   
#ifdef __cplusplus
}
#endif

#endif /* __CORE_H */   