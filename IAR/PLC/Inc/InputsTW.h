#ifndef __INPUTS_H__
#define __INPUTS_H__

#include "variables.h"

#define	INPUT_CVBS		0
#define	INPUT_SVIDEO	1
#define	INPUT_CVBS2		5
#define	INPUT_YUV		2

void	BacklightOnOff( uint8_t on );

void	Mute( uint8_t on );
void	MuteAuto( uint8_t on );
void	Freerun( uint8_t on );
void	FreerunAuto( uint8_t on );

uint8_t	CheckAndSetDecoder( void );

uint8_t	ReadVInputSTD(void);
uint8_t 	GetVInputStdInx(void);

uint8_t 	IsNoInput(void);

#endif