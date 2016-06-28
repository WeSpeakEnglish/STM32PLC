#ifndef __INPUTS_H__
#define __INPUTS_H__

#include "variables.h"

#define	INPUT_CVBS		0

void	Mute( uint8_t on );
void	MuteAuto( uint8_t on );
void	Freerun( uint8_t on );
void	FreerunAuto( uint8_t on );

uint8_t	CheckAndSetDecoder( void );


uint8_t 	IsNoInput(void);

#endif