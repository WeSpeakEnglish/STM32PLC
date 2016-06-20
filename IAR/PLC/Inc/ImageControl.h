#ifndef __IMAGECONTROL_H__
#define __IMAGECONTROL_H__
#include "variables.h"
//Decoder Display & Image control
/*
uint8_t ChangeDecoderContrast(void);
uint16_t GetDecoderContrast(void);
uint16_t SetDecoderContrast(uint16_t val);

uint8_t ChangeDecoderBright(void);
uint16_t GetDecoderBright(void);
uint16_t SetDecoderBright(uint16_t val);

uint8_t ChangeDecoderSaturation(void);
uint16_t GetDecoderSaturation(void);
uint16_t SetDecoderSaturation(uint16_t val);

uint8_t ChangeDecoderHUE(void);
uint16_t GetDecoderHUE(void);
uint16_t SetDecoderHUE(uint16_t val);

uint8_t ChangeDecoderSharp(void);
uint16_t GetDecoderSharp(void);
uint16_t SetDecoderSharp(uint16_t val);

void DecoderImageReset( void );
*/
//YCbCr Display & Image control
uint8_t ChangeYCbCrContrast(void);
uint16_t GetYCbCrContrast(void);

uint8_t ChangeYCbCrBright(void);



uint8_t ChangeYCbCrSaturation(void);
uint16_t GetYCbCrSaturation(void);


uint8_t ChangeYCbCrHUE(void);
uint16_t GetYCbCrHUE(void);


uint8_t ChangeYCbCrSharp(void);
uint16_t GetYCbCrSharp(void);
uint8_t SetYCbCrSharpReg(uint8_t regv);

void YCbCrImageReset( void );


//RGB Display & Image control
uint8_t ChangeRGBContrast(void);
uint16_t GetRGBContrast(void);
uint16_t SetRGBContrast(uint16_t val);

uint8_t ChangeRGBBright(void);
uint16_t GetRGBBright(void);
uint16_t SetRGBBright(uint16_t val);

void ResetRGBSharp( void );

void RGBImageReset( void );

void RGBAutoAdj( void );

uint8_t ChangeRGBPosH(void);
uint16_t GetRGBPosH(void);
uint16_t SetRGBPosH(uint16_t val);

uint8_t ChangeRGBPosV(void);
uint16_t GetRGBPosV(void);
uint16_t SetRGBPosV(uint16_t val);

uint8_t ChangeRGBPhase(void);
uint16_t GetRGBPhase(void);
uint16_t SetRGBPhase(uint16_t val);

uint8_t ChangeRGBClock(void);
uint16_t GetRGBClock(void);
uint16_t SetRGBClock(uint16_t val);


//CVBS2 Display & Image control
uint8_t ChangeTW9900Contrast(void);
uint16_t GetTW9900Contrast(void);
uint16_t SetTW9900Contrast(uint16_t val);

uint8_t ChangeTW9900Bright(void);
uint16_t GetTW9900Bright(void);
uint16_t SetTW9900Bright(uint16_t val);

uint8_t ChangeTW9900Saturation(void);
uint16_t GetTW9900Saturation(void);
uint16_t SetTW9900Saturation(uint16_t val);

uint8_t ChangeTW9900HUE(void);
uint16_t GetTW9900HUE(void);
uint16_t SetTW9900HUE(uint16_t val);

uint8_t ChangeTW9900Sharp(void);
uint16_t GetTW9900Sharp(void);
uint16_t SetTW9900Sharp(uint16_t val);

void TW9900ImageReset( void );



#endif