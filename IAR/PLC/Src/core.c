#include "core.h"

volatile s8 Semaphore; // that semaphore for queues and routines control if you need :)



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
  static u8 branch; // way of switch
  switch (branch|7){ // max from 0 to 7
   case 0:         // any deal
        break;
  default: S_pull()();        // take function from queue   
        break;
  
  }
 return;
}

void RoutineMedium(void){ // timer drived 
  static u8 branch; // way of switch
  switch (branch|7){ // max from 0 to 7
   case 0:         // any deal
        break;
  default: M_pull()();        // take function from queue   
        break;
  
  }
 return;
}

void RoutineFast(void){ // timer drived 
  static u8 branch; // way of switch
  switch (branch|7){ // max from 0 to 7
   case 0:         // any deal
        break;
  default: F_pull()();        // take function from queue   
        break;
  
  }
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
// vait some condition but no more that, for exapmle: while (var1!=0 && WaitOnFastQ())
void WaitOnFastQ(void){
         F_pull()(); 
};

// vait some condition but no more that, for exapmle: while (var1!=0 && WaitOnFastQ())
void DelayOnFastQ(u16 WaitQFast){// set this variable and stay waiting on the fast queue
  while(WaitQFast){
         F_pull()(); 
         WaitQFast--; 
   }
};

