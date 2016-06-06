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
extern volatile int8_t Semaphore; // that semaphore for queues and routines control if you need :)
extern volatile uint32_t TicksGlobalUS; //US MUST be ticking in timer in the timer interrupt handle, it needs just ++ operation
extern volatile uint8_t RESmutex_1; //the Resource mutex
///////////////////////  
void RoutineFast(void);
void RoutineMedium(void);
void RoutineSlow(void);
/////SLOW QUEUE////////////
void pSlowQueueIni(void);
int8_t S_push(void (*pointerQ)(void));
void (*S_pull(void))(void);
/////MEDIUM QUEUE////////////
void pMediumQueueIni(void);
int8_t M_push(void (*pointerQ)(void));
void (*M_pull(void))(void);
////FAST QUEUE//////////////
void pFastQueueIni(void);
int8_t F_push(void (*pointerQ)(void));
int8_t F_push2(void (*pointerQ_1)(void),void (*pointerQ_2)(void));   
void (*F_pull(void))(void);
///////////////////////////
//waiting functions
void DelayOnFastQ(uint8_t WaitQFast); // push several tasks from the Fast Queue
void DelayOnMediumQ(uint8_t WaitQMedium); // push several tasks from the Medium Queue
void DelayOnSlowQ(uint8_t WaitQSlow); // push several tasks from the Slow Queue
uint8_t DelayUsOnProcessRoutine(void (*pointerF)(void),uint32_t TimeDel, uint8_t Ini); //DO OUR void function(void) while expecting TimeDel microsec or another timer periods
void MPU_Config (void);
   
#ifdef __cplusplus
}
#endif

#endif /* __CORE_H */   