#ifndef __KEYB_H
#define __KEYB_H
#include <stdint.h>

typedef struct {
 // unsigned PRESSED : 1;
 // unsigned RELEASED : 1;
  unsigned PRESSED :  1;
  unsigned EVENT :    1;
  unsigned code :     6;
} KB_status;

extern KB_status KB_Status;

struct Keys{
  unsigned int COL_0 : 2;
  unsigned int COL_1 : 2;
  unsigned int COL_2 : 2;
  unsigned int COL_3 : 2;
};

union Keys_U{
  struct Keys keys;
  uint8_t bits;
};

extern uint8_t ReadyFlagKb; // is Event detected?

void SetLineKbd(uint8_t Number);
void ReadLineKbd(uint8_t Number);
uint8_t SolvePressedKeys(void);
uint8_t GenerateKbdMessages(uint8_t XORedKeyBits);
uint8_t getKB_event(void);
#endif
