#include "core.h"
// there are three different queues and routines for corresponding timers 
// We try to release Three full independent queues and service functions with their content



void emptyS(); // dummy function for safe initialization of queue Slow
void emptyM(); // dummy function for safe initialization of queue Medium
void emptyF(); // dummy function for safe initialization of queue Fast

//QUEUES of pointers to the functions (procedures), which we need to run
void (*pSlowQueue[Q_SIZE_SLOW])()={emptyS}; // queue for a Slow-speed timer for get and push a void procedures 
void (*pMediumQueue[Q_SIZE_MEDIUM])()={emptyM}; // queue for a Medium-speed timer get and push a void procedures 
void (*pFastQueue[Q_SIZE_FAST])()={emptyF}; // queue for a Fast-speed timer get and push a void procedures 

//The pointers and counters
//void (*pointerS)(); // pointer to actutal slow-speed function
//void (*pointerM)(); // pointer to actual medium-speed function
//void (*pointerF)(); // pointer to actual fast-speed function

// the service variable to maintaining right order in the queues
s8 S_last =0; // number of the last element of slow-speed queue
s8 M_last =0; // number of the last element of medium-speed queue
s8 F_last =0; // number of the last element of fast-speed queue

s8 S_first =0; // number of the first element of slow-speed queue
s8 M_first =0; // number of the first element of medium-speed queue
s8 F_first =0; // number of the first element of fast-speed queue

s8 Semaphore =0; // that semaphore for queues and routines control

//for the debugging only
void emptyS(){;} // dummy function for safe initialization of queue Slow
void emptyM(){;} // dummy function for safe initialization of queue Medium
void emptyF(){;} // dummy function for safe initialization of queue Fast

/// INI ELEMENTs IN THE QUEUES
void pSlowQueueIni(void){
 static s8 i =0;
  for(i = 0; i < Q_SIZE_SLOW; i++){
	pSlowQueue[i] = emptyS;
	}
}
void pMediumQueueIni(void){
 static s8 i =0;
  for(i = 0; i < Q_SIZE_MEDIUM; i++){
	pMediumQueue[i] = emptyM;
	}
}
void pFastQueueIni(void){
 static s8 i =0;
  for(i = 0; i < Q_SIZE_FAST; i++){
	pFastQueue[i] = emptyF;
	}
}
/// ADD ELEMENTs TO THE QUEUES
s8 S_push(void (*pointerQ)(void) ){
 if ((S_last+1)%Q_SIZE_SLOW == S_first)	return 1;
 pSlowQueue[S_last++] = pointerQ;
 S_last%=Q_SIZE_SLOW;
 return 0;
}

s8 M_push(void (*pointerQ)(void) ){
 if ((M_last+1)%Q_SIZE_MEDIUM == M_first)return 1;
 pMediumQueue[M_last++] = pointerQ;
 M_last%=Q_SIZE_MEDIUM;
 return 0;
}

s8 F_push(void (*pointerQ)(void) ){
 if ((F_last+1)%Q_SIZE_FAST == F_first)return 1;
 pFastQueue[F_last++] = pointerQ;
 F_last%=Q_SIZE_FAST;
 return 0;
}
/// GET ELEMENTs FROM THE QUEUES
void (*S_pull(void))(void){
 void (*pullVar)(void);
 if (S_last == S_first)return emptyS;
 pullVar = pSlowQueue[S_first++];
 S_first%=Q_SIZE_SLOW;
return pullVar;
}

void (*M_pull(void))(void){
 void (*pullVar)(void);
 if (M_last == M_first)return emptyM;
 pullVar = pMediumQueue[M_first++];
 M_first%=Q_SIZE_MEDIUM;
return pullVar;
}

void (*F_pull(void))(void){
 void (*pullVar)(void);
 if (F_last == F_first)return emptyF;
 pullVar = pFastQueue[F_first++];
 F_first%=Q_SIZE_FAST;
return pullVar;
}


