#ifndef _SOUND_H
#define _SOUND_H
#include <stdint.h>

typedef struct {
uint32_t CounterSound;
uint32_t SoundPeriod;
} Sound;

extern Sound SOUND;
void Bip(uint8_t Log);













#endif
