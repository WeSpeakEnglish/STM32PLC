#ifndef __CORE_H
#define __CORE_H
#include "variables.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

//here is our variables
extern volatile s8 Semaphore; // that semaphore for queues and routines control if you need :)

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
void WaitOnFastQ(void); // just push a task from the Fast Queue 
void DelayOnFastQ(u16 WaitQFast); // push several tasks from the Fast Queue

//max size of queues is 127 elements (signed char) 
#define Q_SIZE_SLOW 8   // the size of slow queue
#define Q_SIZE_MEDIUM 8 // the size of medium queue
#define Q_SIZE_FAST 8   // the size of fast queue

   
#ifdef __cplusplus
}
#endif

#endif /* __CORE_H */   