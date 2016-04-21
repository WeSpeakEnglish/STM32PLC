#ifndef __LCD_H
#define __LCD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"
#include "variables.h"
/* Include LCD component Driver */

/* Include SDRAM Driver */
 
//#include "stm32746g_discovery.h"
#include "../../../Utilities/Fonts/fonts.h"
  
/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32746G_DISCOVERY
  * @{
  */
    
/** @addtogroup STM32746G_DISCOVERY_LCD
  * @{
  */ 

/** @defgroup STM32746G_DISCOVERY_LCD_Exported_Types STM32746G_DISCOVERY_LCD Exported Types
  * @{
  */  
typedef struct 
{ 
  uint32_t TextColor; 
  uint32_t BackColor;  
  sFONT    *pFont;
}LCD_DrawPropTypeDef;   
   
typedef struct 
{
  int16_t X;
  int16_t Y;
}Point, * pPoint; 
   
/** 
  * @brief  Line mode structures definition  
  */ 
typedef enum
{
  CENTER_MODE             = 0x01,    /* Center mode */
  RIGHT_MODE              = 0x02,    /* Right mode  */
  LEFT_MODE               = 0x03     /* Left mode   */
}Text_AlignModeTypdef;

/**
  * @}
  */ 

/** @defgroup STM32746G_DISCOVERY_LCD_Exported_Constants STM32746G_DISCOVERY_LCD Exported Constants
  * @{
  */ 
#define MAX_LAYER_NUMBER       ((uint32_t)2)

#define LCD_LayerCfgTypeDef    LTDC_LayerCfgTypeDef

#define LTDC_ACTIVE_LAYER	     ((uint32_t)1) /* Layer 1 */
/** 
  * @brief  LCD status structure definition  
  */     
#define LCD_OK                 ((uint8_t)0x00)
#define LCD_ERROR              ((uint8_t)0x01)
#define LCD_TIMEOUT            ((uint8_t)0x02)

/** 
  * @brief  LCD FB_StartAddress  
  */
#define LCD_FB_START_ADDRESS       ((uint32_t)0xC0000000)

/** 
  * @brief  LCD color  
  */ 
#define LCD_COLOR_BLUE          ((uint32_t)0xFF0000FF)
#define LCD_COLOR_GREEN         ((uint32_t)0xFF00FF00)
#define LCD_COLOR_RED           ((uint32_t)0xFFFF0000)
#define LCD_COLOR_CYAN          ((uint32_t)0xFF00FFFF)
#define LCD_COLOR_MAGENTA       ((uint32_t)0xFFFF00FF)
#define LCD_COLOR_YELLOW        ((uint32_t)0xFFFFFF00)
#define LCD_COLOR_LIGHTBLUE     ((uint32_t)0xFF8080FF)
#define LCD_COLOR_LIGHTGREEN    ((uint32_t)0xFF80FF80)
#define LCD_COLOR_LIGHTRED      ((uint32_t)0xFFFF8080)
#define LCD_COLOR_LIGHTCYAN     ((uint32_t)0xFF80FFFF)
#define LCD_COLOR_LIGHTMAGENTA  ((uint32_t)0xFFFF80FF)
#define LCD_COLOR_LIGHTYELLOW   ((uint32_t)0xFFFFFF80)
#define LCD_COLOR_DARKBLUE      ((uint32_t)0xFF000080)
#define LCD_COLOR_DARKGREEN     ((uint32_t)0xFF008000)
#define LCD_COLOR_DARKRED       ((uint32_t)0xFF800000)
#define LCD_COLOR_DARKCYAN      ((uint32_t)0xFF008080)
#define LCD_COLOR_DARKMAGENTA   ((uint32_t)0xFF800080)
#define LCD_COLOR_DARKYELLOW    ((uint32_t)0xFF808000)
#define LCD_COLOR_WHITE         ((uint32_t)0xFFFFFFFF)
#define LCD_COLOR_LIGHTGRAY     ((uint32_t)0xFFD3D3D3)
#define LCD_COLOR_GRAY          ((uint32_t)0xFF808080)
#define LCD_COLOR_DARKGRAY      ((uint32_t)0xFF404040)
#define LCD_COLOR_BLACK         ((uint32_t)0xFF000000)
#define LCD_COLOR_BROWN         ((uint32_t)0xFFA52A2A)
#define LCD_COLOR_ORANGE        ((uint32_t)0xFFFFA500)
#define LCD_COLOR_TRANSPARENT   ((uint32_t)0xFF000000)

/** 
  * @brief LCD default font 
  */ 
#define LCD_DEFAULT_FONT        Font24     
////////////////////////////////////////////////////
#define SDRAM_BANK_ADDR         0xC0000000
#define LAYERS_SIZE         0x00177000
#define LAYER_1_OFFSET          0x00000000
#define LAYER_2_OFFSET          0x00177000  // 800x480x4 layer 1536000 offset
#define LAYER_3_OFFSET          0x002EE000  // 800x480x4 layer 1536000 offset
#define LAYER_BACK_OFFSET       0x00465000  // BACKGROUND
#define IMAGE_1_OFFSET          0x005DC000  // big image 1   
#define IMAGE_2_OFFSET          IMAGE_1_OFFSET + LAYERS_SIZE //big image 2
#define DisplayHEIGHT   480 // pixels
#define DisplayWIDTH    800 // pixels
#define PixelWIDTH      4   // bytes
//////////////////////////////////////////////////////


/** @addtogroup STM32746G_DISCOVERY_LCD_Exported_Functions
  * @{
  */
uint8_t  LCD_Init(void);
uint8_t  LCD_DeInit(void);
uint32_t LCD_GetXSize(void);
uint32_t LCD_GetYSize(void);
void     LCD_SetXSize(uint32_t imageWidthPixels);
void     LCD_SetYSize(uint32_t imageHeightPixels);

/* Functions using the LTDC controller */
void     LCD_LayerDefaultInit(uint16_t LayerIndex, uint32_t FrameBuffer);
void     LCD_LayerRgb565Init(uint16_t LayerIndex, uint32_t FB_Address);
void     LCD_SetTransparency(uint32_t LayerIndex, uint8_t Transparency);
void     LCD_SetLayerAddress(uint32_t LayerIndex, uint32_t Address);
void     LCD_SetColorKeying(uint32_t LayerIndex, uint32_t RGBValue);
void     LCD_ResetColorKeying(uint32_t LayerIndex);
void     LCD_SetLayerWindow(uint16_t LayerIndex, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);

void     LCD_SelectLayer(uint32_t LayerIndex);
void     LCD_SetLayerVisible(uint32_t LayerIndex, FunctionalState State);

void     LCD_SetTextColor(uint32_t Color);
uint32_t LCD_GetTextColor(void);
void     LCD_SetBackColor(uint32_t Color);
uint32_t LCD_GetBackColor(void);
void     LCD_SetFont(sFONT *fonts);
sFONT    *LCD_GetFont(void);

uint32_t LCD_ReadPixel(uint16_t Xpos, uint16_t Ypos);
void     LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t pixel);
void     LCD_Clear(uint32_t Color);
void     LCD_ClearStringLine(uint32_t Line);
void     LCD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr);
void     LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode);
void     LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);

void     LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void     LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     LCD_DrawPolygon(pPoint Points, uint16_t PointCount);
void     LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius);
void     LCD_DrawBitmap(uint32_t Xpos, uint32_t Ypos, uint8_t *pbmp);

void     LCD_FillRect(u32 x1, u32 y1, u32 x2, u32 y2);
void     LCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     LCD_FillPolygon(pPoint Points, uint16_t PointCount);
void     LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius);
void     LCD_FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3);

void     LCD_DisplayOff(void);
void     LCD_DisplayOn(void);
void     LCD_SetColorPixel(uint32_t Color);
//void     LCD_InitParams(void);
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t radius);
void LCD_InitParams(uint32_t LayerIndex, uint32_t BackColor, uint32_t TextColor, sFONT* pFont);
void Fast_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t ARGB_Code);
void LCD_SetLight(uint16_t);
void DrawFastLineVertical(uint16_t x1, uint16_t y1, uint16_t y2);
void DrawFastLineHorizontal(uint16_t y1, uint16_t x1, uint16_t x2);
void LCD_Fill_Image(u32 ImageAddress, u32 x, u32 y, u32 xSize, u32 ySize);
void FillImageSoft(u32 ImageAddress, u32 address, u32 xSize, u32 ySize);
void LL_ConvertLineToARGB8888(void *pSrc, void *pDst, uint32_t xSize, uint32_t ColorMode);
#endif /* __LCD_H */
