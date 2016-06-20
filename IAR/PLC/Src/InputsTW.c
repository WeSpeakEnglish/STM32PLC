#include "InputsTW.h"
#include "ImageControl.h"
#include "OSDinitTable.h"
#include "OSDBasic.h"
#include "stm32f7xx_hal.h"
#include "tw8819.h"

#define	INPUT_CHANGE_DELAY	300

#define PAGE1_DECODER		0x01	//0x101::0x142
#define PAGE2_SCALER		0x02	//0x201::0x21E

//------------------------------------
//VInputStdDetectMode
#define AUTO	0

//VInputStd
#define NTSC	1			
#define PAL	2
#define SECAM	3
#define NTSC4	4
#define PALM	5
#define PALN	6
#define PAL60	7
//-----------------------------------------------

uint8_t	InputMainLoss = 0;

 uint16_t  IVF;
 uint32_t	IHF;

uint8_t	DecoderMode = 7;
uint8_t	YUVMode = 7;
uint8_t	TW9900Mode = 7;

extern	uint8_t	InputMain;

//=============================================================================
//	Initialize BACKLIGHT			                                               
//=============================================================================
void	InitBacklight( void )
{
	uint8_t	page;
	page = ReadTW88(0xff);

	WriteTW88Page( PAGE0_LEDC );
	WriteTW88(REG081, 0x0C);
	#ifdef SUPPORT_DELTA_RGB
	WriteTW88(REG089, 0x0D);
	#else
	WriteTW88(REG089, 0x0C);
	#endif
	WriteTW88(REG091, 0);	  		// enable power of LED

	WriteTW88( REG009, ReadTW88(0x09)|1 );	// enable I2C Master

	WaitVBlank(1);	
	//WriteI2C( REG058, 1, ReadI2C(0x58, 1)|5);		// enable External LED controller

	WriteTW88Page(page);
}

//=============================================================================
//	BACKLIGHT Turn On Off			                                               
//=============================================================================
void	BacklightOnOff( uint8_t on )
{
//	WaitVBlank(1);	
//	if ( on )
//		WriteI2C( 0x58, 1, ReadI2C(0x58, 1)|1);			// Turn on backlight
//	else
//		WriteI2C( 0x58, 1, ReadI2C(0x58, 1)& ~1);		// Trun off backlight
}

uint8_t GetVInputStdInx(void)
{
	uint8_t i, std;

	std = ReadVInputSTD();

	switch( std ) {

	case NTSC4:
	case PALM:
	case PAL60:
	case NTSC:		IVF = 60;		IHF = 15723;	break;	// 15734

	case SECAM:
	case PALN:
	case PAL:		IVF = 50;		IHF = 15723;	break;  // 15625
	default:		IVF = 0;		IHF = 0;		break;
	}

	for(i=0; ; i++) {
		if( struct_VInputStd[i].Id ==std )
			return i;
		if( struct_VInputStd[i].Id ==0 )
			break;
	}
	return 0;
}


//=============================================================================
//		uint8_t IsNoInput(void)			                                               
//=============================================================================
uint8_t IsNoInput(void)
{
	uint8_t	page, ret;

	page = ReadTW88(0xff);
	WriteTW88Page(PAGE1_DECODER);
	ret = ReadTW88(CSTATUS) & 0x80; 
	WriteTW88Page(page);
	if ( ret ) return 1;
	else	return 0;
}


//=============================================================================
//		uint8_t ReadVInputSTD(void)			                                               
//=============================================================================
uint8_t ReadVInputSTD(void)
{
	uint8_t std, page, ret;

	page = ReadTW88( 0xff );
	
	if( IsNoInput() ) ret = 1; // Noinput!!
	WriteTW88Page(PAGE1_DECODER);
	std = ReadTW88(SDT) & 0xf0;
	if( std & 0x80 ) ret = 0xff; // Detection in progress..
	else 
		ret = ((( std & 0x70 ) >> 4 ) + 1 );

	WriteTW88Page(page);
	return (ret);
}

void	Mute( uint8_t on )
{
	uint8_t	page;
	page = ReadTW88(0xff);
	WriteTW88Page(PAGE2_SCALER);
	if ( on ) {
		WriteTW88( REG21E, (ReadTW88(REG21E) | 0x01) );						// force Mute
	}
	else {
		WriteTW88( REG21E, (ReadTW88(REG21E) & 0xFE) );						// force Mute off
	}
	WriteTW88Page(page);
}


//=============================================================================
//		uint8_t	ChangeCVBS( void )
//=============================================================================
uint8_t	ChangeCVBS2( void )
{
uint8_t	result=0;

	if ( InputMain == INPUT_CVBS2 ) return(0);
//	Puts("\nChange to CVBS2");
	InputMain = INPUT_CVBS2;

//	SaveInputEE( InputMain );

	BacklightOnOff(0);



	I2CDeviceInitialize( InitCVBSAll );

	//=========== these change for CVBS2 diff input =====================
	WriteTW88( 0xff, PAGE1_DECODER );		// set Decoder page
	WriteTW88( REG102, 0x40 );				// change to Y0
	WriteTW88( REG137, ReadTW88(REG137)&~0x04 );
	WriteTW88( REG139, 0x3F );				// CM Restore Sleep off, On-Transconductance Amp
	//=========== these change for CVBS2 diff input =====================

	// Get Image control register value
	SetYCbCrContrast( GetVideoDatafromEE( 0 ) );
	SetYCbCrBright( GetVideoDatafromEE( 1 ) );
	SetYCbCrSaturation( GetVideoDatafromEE( 2 ) );
	//SetDecoderContrast( GetVideoDatafromEE( 3 ) );
	SetYCbCrHUE( GetVideoDatafromEE( 4 ) );
	SetYCbCrSharp( GetVideoDatafromEE( 5 ) );

	Delay1ms(100);
	result = CheckAndSetDecoderScaler();

	OSDSetDEDelay();

	OSDDisplayInput();
	if ( result ) {
		InputMainLoss = 1;
		DisplayPCInfo("CHECK CVBS2 signal");
	}
	BacklightOnOff(1);
	return(result);
}



//=============================================================================
//		uint8_t	ChangeSVIDEO( void )
//=============================================================================
uint8_t	ChangeSVIDEO( void )
{
uint8_t	result=0;

	if ( InputMain == INPUT_SVIDEO ) return(0);
	InputMain = INPUT_SVIDEO;
	SaveInputEE( InputMain );

	BacklightOnOff(0);

	InitCVBSRegister( );

	WriteTW88Page( PAGE1_DECODER );		// set Decoder page
	WriteTW88( REG102, 0x54 );

	// Get Image control register value
//	SetYCbCrContrast( GetVideoDatafromEE( 0 ) );
//	SetYCbCrBright( GetVideoDatafromEE( 1 ) );
//	SetYCbCrSaturation( GetVideoDatafromEE( 2 ) );
	//SetDecoderContrast( GetVideoDatafromEE( 3 ) );
//	SetYCbCrHUE( GetVideoDatafromEE( 4 ) );
//	SetYCbCrSharp( GetVideoDatafromEE( 5 ) );

	HAL_Delay(100);

	result = CheckAndSetDecoderScaler();

	OSDSetDEDelay();

	OSDDisplayInput();
	if ( result ) {
		InputMainLoss = 2;
		DisplayPCInfo("CHECK S-Video signal");
	}
	BacklightOnOff(1);
	return(result);
}


//=============================================================================
//		void	InputModeNext( void )
//=============================================================================
void	InputModeNext( void )
{

	if ( InputMain == INPUT_CVBS )
		DisplayInput( INPUT_CVBS2 );
	else
		DisplayInput( INPUT_CVBS );
}

//=============================================================================
//		void	InputModeNext( void )
//=============================================================================
void	DisplayInput( uint8_t mode )
{
	switch ( mode ) {
		case INPUT_CVBS:
			ChangeCVBS();
			break;
		case INPUT_CVBS2:
			ChangeCVBS2();
			break;
		case INPUT_SVIDEO:
			ChangeSVIDEO();
			break;
		default:
			ChangeCVBS();
			break;
	}
}

//=============================================================================
//		void	CheckInput( void )
//=============================================================================
void	CheckInput( void )
{
uint8_t	mode;
static	uint8_t 	cnt=0;

	cnt++;
	if ( cnt )	return;
	switch ( InputMain ) {
		case INPUT_CVBS:
			if ( InputMainLoss ) {
				if ( !CheckDecoderVDLOSS(1) ) {
					ClearPCInfo();
					CheckAndSetDecoderScaler();
					InputMainLoss = 0;
				}
			}
			else {
				if ( CheckDecoderVDLOSS(20) ) {
					DisplayPCInfo("CHECK CVBS signal");
					InputMainLoss = 1;
				}
				else {
					mode = CheckDecoderSTD(20);
					mode >>= 4;
					if ( mode != DecoderMode ) {
						dPrintf("\n mode: 0x%02bx, DecoderMode: 0x%02bx", mode, DecoderMode );
						InputMain = INPUT_YUV;
						ChangeCVBS();
					}
				}
			}
			break;
		case INPUT_CVBS2:
			if ( InputMainLoss ) {
				if ( !CheckDecoderVDLOSS(1) ) {
					ClearPCInfo();
					CheckAndSetDecoderScaler();
					InputMainLoss = 0;
				}
			}
			else {
				if ( CheckDecoderVDLOSS(20) ) {
					DisplayPCInfo("CHECK CVBS signal");
					InputMainLoss = 1;
				}
				else {
					mode = CheckDecoderSTD(20);
					mode >>= 4;
					if ( mode != DecoderMode ) {
						dPrintf("\n mode: 0x%02bx, DecoderMode: 0x%02bx", mode, DecoderMode );
						InputMain = INPUT_YUV;
						ChangeCVBS();
					}
				}
			}
			break;
		case INPUT_SVIDEO:
			if ( InputMainLoss ) {
				if ( !CheckDecoderVDLOSS(1) ) {
					ClearPCInfo();
					CheckAndSetDecoderScaler();
					InputMainLoss = 0;
				}
			}
			else {
				if ( CheckDecoderVDLOSS(20) ) {
					DisplayPCInfo("CHECK S-Video signal");
					InputMainLoss = 2;
				}
				else {
					mode = CheckDecoderSTD(20);
					mode >>= 4;
					if ( mode != DecoderMode ) {
						InputMain = INPUT_YUV;
						ChangeSVIDEO();
					}
				}
			}
			break;
		default:
			ChangeCVBS();
			break;
	}
}
