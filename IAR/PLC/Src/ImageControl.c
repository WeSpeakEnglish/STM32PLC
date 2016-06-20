#include "ImageControl.h"

#include "tw8819.h"

#define PAGE2_IMAGE			0x02	//0x280::0x2BF

						 // 0  1   2   3   4   5   6   7   8   9   a   b   c   d   e   f 


/*
//=============================================================================
//		uint8_t ChangeDecoderContrast(void)
//=============================================================================
uint8_t ChangeDecoderContrast(void)
{
    uint16_t	val;

	val = GetDecoderContrast();

	SaveVideoDatatoEE( 0, val );
	return (val);
}

//=============================================================================
//		uint16_t GetDecoderContrast(void)
//=============================================================================
uint16_t GetDecoderContrast(void)
{
    uint16_t	val;

	WriteTW88( 0xff, PAGE1_DECODER );
	val = ReadTW88( 0x11 );
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}

//=============================================================================
//		uint16_t SetDecoderContrast(uint16_t val)
//=============================================================================
uint16_t SetDecoderContrast(uint16_t val)
{
	Printf("\nContrast: %d", val );
	WriteTW88( 0xff, PAGE1_DECODER );
	val *= 255;
	val += 50;
	val /= 100;
	Printf(" --> %02xh", val );
	WriteTW88( 0x11, val );
	val = ReadTW88( 0x11 );
	val *= 100;
	val += 128;
	val /= 255;
	Printf(" --> %d", val );
	return (val);
}

//=============================================================================
//		uint8_t ChangeDecoderBright(void)
//=============================================================================
uint8_t ChangeDecoderBright(void)
{
    uint16_t	val;

	val = GetDecoderBright();

	SaveVideoDatatoEE( 1, val );
	return (val);
}

//=============================================================================
//		uint16_t GetDecoderBright(void)
//=============================================================================
uint16_t GetDecoderBright(void)
{
    uint16_t	val;

	WriteTW88( 0xff, PAGE1_DECODER );
	val = ReadTW88( 0x10 );
	val += 0x80;
	val &= 0xff;
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}

//=============================================================================
//		uint16_t SetDecoderBright(uint16_t val)
//=============================================================================
uint16_t SetDecoderBright(uint16_t val)
{
	WriteTW88( 0xff, DECODER_PAGE );
	val *= 255;
	val += 50;
	val /= 100;
	val += 0x80;
	WriteTW88( 0x10, val );
	val = ReadTW88( 0x10 );
	val += 0x80;
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}

//=============================================================================
//		uint8_t ChangeDecoderSaturation(void)
//=============================================================================
uint8_t ChangeDecoderSaturation(void)
{
    uint16_t	val;

	val = GetDecoderSaturation();

	SaveVideoDatatoEE( 2, val );
	return (val);
}

//=============================================================================
//		uint16_t GetDecoderSaturation(void)
//=============================================================================
uint16_t GetDecoderSaturation(void)
{
    uint16_t	val;

	WriteTW88( 0xff, PAGE1_DECODER );
	val = ReadTW88( 0x13 );
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}

//=============================================================================
//		uint16_t SetDecoderSaturation(uint16_t val)
//=============================================================================
uint16_t SetDecoderSaturation(uint16_t val)
{
	WriteTW88( 0xff, PAGE1_DECODER );
	val *= 255;
	val += 50;
	val /= 100;
	WriteTW88( 0x13, val );
	WriteTW88( 0x14, val );
	val = ReadTW88( 0x13 );
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}

//=============================================================================
//		uint8_t ChangeDecoderHUE(void)
//=============================================================================
uint8_t ChangeDecoderHUE(void)
{
    uint16_t	val;

	val = GetDecoderHUE();

	SaveVideoDatatoEE( 4, val );
	return (val);
}

//=============================================================================
//		uint16_t GetDecoderHUE(void)
//=============================================================================
uint16_t GetDecoderHUE(void)
{
    uint16_t	val;

	WriteTW88( 0xff, PAGE1_DECODER );
	val = ReadTW88( 0x15 );
	val += 0x80;
	val &= 0xff;
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}

//=============================================================================
//		uint16_t SetDecoderHUE(uint16_t val)
//=============================================================================
uint16_t SetDecoderHUE(uint16_t val)
{
	WriteTW88( 0xff, PAGE1_DECODER );
	val *= 255;
	val += 50;
	val /= 100;
	val += 128;
	val &= 0xff;
	WriteTW88( 0x15, val );
	val = ReadTW88( 0x15 );
	val += 128;
	val &= 0xff;
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}

//=============================================================================
//		uint8_t ChangeDecoderSharp(void)
//=============================================================================
uint8_t ChangeDecoderSharp(void)
{
    uint16_t	val;

	val = GetDecoderSharp();

	SaveVideoDatatoEE( 5, val );
	return (val);
}

//=============================================================================
//		uint16_t GetDecoderSharp(void)
//=============================================================================
uint16_t GetDecoderSharp(void)
{
    uint16_t	val;

	WriteTW88( 0xff, PAGE1_DECODER );
	val = Sharpness[(ReadTW88( 0x12 ) & 0x0f)];
	return (val);
}

//=============================================================================
//		uint16_t SetDecoderSharp(uint16_t val)
//=============================================================================
uint16_t SetDecoderSharp(uint16_t val)
{
uint8_t	i;

	WriteTW88( 0xff, PAGE1_DECODER );
	for (i=0; i<16; i++) {
		if ( val == (Sharpness[i]+1) ){
			val = i+1;
			break;
		}
		if ( Sharpness[i] == (val+1) ){
			val = i-1;
			break;
		}
	}
	WriteTW88( 0x12, ((ReadTW88( 0x12 ) & 0xf0) | val) );
	val = Sharpness[i];
	return (val);
}

*/

//============================== YCbCr  ================================================

#define		ContrastY		0x84
#define		BrightnessY		0x8A
#define		HueY			0x80
#define		SaturationY		0x85
#define		SharpnessY		0x8B

//=============================================================================
//		uint8_t SetYCbCrSharpReg(uint8_t val)
//=============================================================================
uint8_t SetYCbCrSharpReg(uint8_t regv)
{
uint8_t	val;

	WriteTW88( 0xff, PAGE2_IMAGE );
	WriteTW88( SharpnessY, ((ReadTW88( SharpnessY ) & 0xf0) + regv) );
	val = Sharpness[regv];
	return (val);
}


#ifndef TW8820

//==============================================================================
#define		ContrastR		0x81
#define		BrightnessR		0x87
#define		Sharpness		0x8B

//=============================================================================
//		uint16_t SetRGBContrast(uint16_t val)
//=============================================================================
uint16_t SetRGBContrast(uint16_t val)
{
	WriteTW88( 0xff, PAGE2_IMAGE );
	val *= 255;
	val += 50;
	val /= 100;
	WriteTW88( ContrastR, val );
	WriteTW88( ContrastR+1, val );
	WriteTW88( ContrastR+2, val );
	val = ReadTW88( ContrastR );
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}


//=============================================================================
//		uint16_t SetRGBContrast(uint16_t val)
//=============================================================================
uint16_t SetRGBBright(uint16_t val)
{
	WriteTW88Page( PAGE2_IMAGE );
	val *= 255;
	val += 50;
	val /= 100;
	WriteTW88( BrightnessR, val );
	WriteTW88( BrightnessR+1, val );
	WriteTW88( BrightnessR+2, val );
	val = ReadTW88( BrightnessR );
	val *= 100;
	val += 128;
	val /= 255;
	return (val);
}

//=============================================================================
//		void ResetRGBSharp( void )
//=============================================================================
void ResetRGBSharp( void )
{
	WriteTW88Page( PAGE2_IMAGE );

	WriteTW88( Sharpness, (ReadTW88( Sharpness ) & 0xf0) );

	WriteTW88( 0x8B, 0x00 );
}

#endif
