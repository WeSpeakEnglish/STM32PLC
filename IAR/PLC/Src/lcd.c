#include "lcd.h"
#include "dma2d.h"
#include "ltdc.h"
#include "video.h"
#include "dac.h"
#include "core.h"
#include "variables.h"
#include "fonts.h"

#define POLY_X(Z)              ((int32_t)((Points + Z)->X))
#define POLY_Y(Z)              ((int32_t)((Points + Z)->Y))      

#define ABS(X)  ((X) > 0 ? (X) : -(X))      
    
/* Default LCD configuration with LCD Layer 1 */
static uint32_t            ActiveLayer = 0;
static LCD_DrawPropTypeDef DrawProp[MAX_LAYER_NUMBER];
static uint32_t LayerIndex = 0;
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c, uint16_t SignWide);
static void LL_FillBuffer(uint32_t LayerIndex, void *pDst, uint32_t xSize, uint32_t ySize, uint32_t OffLine, uint32_t ColorIndex);

uint32_t LCD_GetXSize(void)
{
  return hltdc.LayerCfg[ActiveLayer].ImageWidth;
}

uint32_t LCD_GetYSize(void)
{
  return hltdc.LayerCfg[ActiveLayer].ImageHeight;
}

void LCD_SetXSize(uint32_t imageWidthPixels)
{
  hltdc.LayerCfg[ActiveLayer].ImageWidth = imageWidthPixels;
}

void LCD_SetYSize(uint32_t imageHeightPixels)
{
  hltdc.LayerCfg[ActiveLayer].ImageHeight = imageHeightPixels;
}

void LCD_LayerDefaultInit(uint16_t LayerIndex, uint32_t FB_Address)
{     
  LCD_LayerCfgTypeDef  layer_cfg;

  /* Layer Init */
  layer_cfg.WindowX0 = 0;
  layer_cfg.WindowX1 = LCD_GetXSize();
  layer_cfg.WindowY0 = 0;
  layer_cfg.WindowY1 = LCD_GetYSize(); 
  layer_cfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  layer_cfg.FBStartAdress = FB_Address;
  layer_cfg.Alpha = 255;
  layer_cfg.Alpha0 = 0;
  layer_cfg.Backcolor.Blue = 0;
  layer_cfg.Backcolor.Green = 0;
  layer_cfg.Backcolor.Red = 0;
  layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  layer_cfg.ImageWidth = LCD_GetXSize();
  layer_cfg.ImageHeight = LCD_GetYSize();
  
  HAL_LTDC_ConfigLayer(&hltdc, &layer_cfg, LayerIndex); 

  DrawProp[LayerIndex].BackColor = LCD_COLOR_WHITE;
  DrawProp[LayerIndex].pFont     = &GOST_B_23_var;
  DrawProp[LayerIndex].TextColor = LCD_COLOR_BLACK; 
}

void LCD_LayerRgb565Init(uint16_t LayerIndex, uint32_t FB_Address)
{     
  LCD_LayerCfgTypeDef  layer_cfg;

  /* Layer Init */
  layer_cfg.WindowX0 = 0;
  layer_cfg.WindowX1 = LCD_GetXSize();
  layer_cfg.WindowY0 = 0;
  layer_cfg.WindowY1 = LCD_GetYSize(); 
  layer_cfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  layer_cfg.FBStartAdress = FB_Address;
  layer_cfg.Alpha = 255;
  layer_cfg.Alpha0 = 0;
  layer_cfg.Backcolor.Blue = 0;
  layer_cfg.Backcolor.Green = 0;
  layer_cfg.Backcolor.Red = 0;
  layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  layer_cfg.ImageWidth = LCD_GetXSize();
  layer_cfg.ImageHeight = LCD_GetYSize();
  
  HAL_LTDC_ConfigLayer(&hltdc, &layer_cfg, LayerIndex); 

  DrawProp[LayerIndex].BackColor = LCD_COLOR_WHITE;
  DrawProp[LayerIndex].pFont     = &GOST_B_23_var;
  DrawProp[LayerIndex].TextColor = LCD_COLOR_BLACK; 
}

void LCD_SelectLayer(uint32_t LayerIndex)
{
  ActiveLayer = LayerIndex;
} 

void LCD_SetLayerVisible(uint32_t LayerIndex, FunctionalState State)
{
  if(State == ENABLE)
  {
    __HAL_LTDC_LAYER_ENABLE(&hltdc, LayerIndex);
  }
  else
  {
    __HAL_LTDC_LAYER_DISABLE(&hltdc, LayerIndex);
  }
  __HAL_LTDC_RELOAD_CONFIG(&hltdc);
} 

void LCD_SetTransparency(uint32_t LayerIndex, uint8_t Transparency)
{    
  HAL_LTDC_SetAlpha(&hltdc, Transparency, LayerIndex);
}

void LCD_SetLayerAddress(uint32_t LayerIndex, uint32_t Address)
{
  HAL_LTDC_SetAddress(&hltdc, Address, LayerIndex);
}

void LCD_SetLayerWindow(uint16_t LayerIndex, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  /* Reconfigure the layer size */
  HAL_LTDC_SetWindowSize(&hltdc, Width, Height, LayerIndex);
  
  /* Reconfigure the layer position */
  HAL_LTDC_SetWindowPosition(&hltdc, Xpos, Ypos, LayerIndex); 
}

void LCD_SetColorKeying(uint32_t LayerIndex, uint32_t RGBValue)
{  
  /* Configure and Enable the color Keying for LCD Layer */
  HAL_LTDC_ConfigColorKeying(&hltdc, RGBValue, LayerIndex);
  HAL_LTDC_EnableColorKeying(&hltdc, LayerIndex);
}

void LCD_ResetColorKeying(uint32_t LayerIndex)
{   
  /* Disable the color Keying for LCD Layer */
  HAL_LTDC_DisableColorKeying(&hltdc, LayerIndex);
}

void LCD_SetTextColor(uint32_t Color)
{
  DrawProp[ActiveLayer].TextColor = Color;
}

uint32_t LCD_GetTextColor(void)
{
  return DrawProp[ActiveLayer].TextColor;
}

void LCD_SetBackColor(uint32_t Color)
{
  DrawProp[ActiveLayer].BackColor = Color;
}

uint32_t LCD_GetBackColor(void)
{
  return DrawProp[ActiveLayer].BackColor;
}

void LCD_SetFont(sFONT *fonts)
{
  DrawProp[ActiveLayer].pFont = fonts;
}

sFONT *LCD_GetFont(void)
{
  return DrawProp[ActiveLayer].pFont;
}

uint32_t LCD_ReadPixel(uint16_t Xpos, uint16_t Ypos)
{
  uint32_t ret = 0;
  
  if(hltdc.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    /* Read data value from SDRAM memory */
    ret = *(__IO uint32_t*) (hltdc.LayerCfg[ActiveLayer].FBStartAdress + (2*(Ypos*LCD_GetXSize() + Xpos)));
  }
  else if(hltdc.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    /* Read data value from SDRAM memory */
    ret = (*(__IO uint32_t*) (hltdc.LayerCfg[ActiveLayer].FBStartAdress + (2*(Ypos*LCD_GetXSize() + Xpos))) & 0x00FFFFFF);
  }
  else if((hltdc.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_RGB565) || \
          (hltdc.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
          (hltdc.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_AL88))  
  {
    /* Read data value from SDRAM memory */
    ret = *(__IO uint16_t*) (hltdc.LayerCfg[ActiveLayer].FBStartAdress + (2*(Ypos*LCD_GetXSize() + Xpos)));    
  }
  else
  {
    /* Read data value from SDRAM memory */
    ret = *(__IO uint8_t*) (hltdc.LayerCfg[ActiveLayer].FBStartAdress + (2*(Ypos*LCD_GetXSize() + Xpos)));    
  }
  
  return ret;
}

void LCD_Clear(uint32_t Color)
{ 
  /* Clear the LCD */ 
  LL_FillBuffer(ActiveLayer, (uint32_t *)(hltdc.LayerCfg[ActiveLayer].FBStartAdress), LCD_GetXSize(), LCD_GetYSize(), 0, Color);
}

void LCD_ClearStringLine(uint32_t Line)
{
  uint32_t color_backup = DrawProp[ActiveLayer].TextColor;
  DrawProp[ActiveLayer].TextColor = DrawProp[ActiveLayer].BackColor;
  
  /* Draw rectangle with background color */
  LCD_FillRect(0, (Line * DrawProp[ActiveLayer].pFont->Height), LCD_GetXSize(), DrawProp[ActiveLayer].pFont->Height);
  
  DrawProp[ActiveLayer].TextColor = color_backup;
  LCD_SetTextColor(DrawProp[ActiveLayer].TextColor);  
}

void LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii)
{
  DrawChar(Xpos, Ypos, &DrawProp[ActiveLayer].pFont->table[DrawProp[ActiveLayer].pFont->tableInfo[(Ascii-' ')].Offset],(uint16_t)DrawProp[ActiveLayer].pFont->tableInfo[(Ascii-' ')].Wide);
}

void LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode, uint8_t Kerning )
{
  uint32_t ref_column = 1, i = 0;
  uint32_t size = 0, xsize = 0; 
  uint8_t  *ptr = Text;
  
  /* Get the text size */
  while (*ptr++) size ++ ;
  
  /* Characters number per line */
  if(Mode)
  for(i = 0; i < size; i++)
  xsize += DrawProp[ActiveLayer].pFont->tableInfo[(Text[i]-' ')].Wide + Kerning;
  xsize -= Kerning;
  
  switch (Mode)
  {
  case CENTER_MODE:
    {
      ref_column = Xpos - xsize/2;
      Ypos -= (DrawProp[ActiveLayer].pFont->Height)/2;
      break;
    }
  case LEFT_MODE:
    {
      ref_column = Xpos;
      break;
    }
  case RIGHT_MODE:
    {
      ref_column = Xpos - xsize;
      break;
    }    
  default:
    {
      ref_column = Xpos;
      break;
    }
  }
  
  /* Check that the Start column is located in the screen */
  if ((ref_column < 1) || (ref_column >= 0x8000))
  {
    ref_column = 1;
  }

  /* Send the string character by character on LCD */
  while (*Text != 0)
  {
    /* Display one character on LCD */    /* Decrement the column position by 16 */
    
    LCD_DisplayChar(ref_column, Ypos, *Text);
    ref_column += DrawProp[ActiveLayer].pFont->tableInfo[(*Text-' ')].Wide + (uint16_t)Kerning; // display with kerning
    /* Point on the next character */
    Text++;
    i++;
  }  
}

void LCD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr, uint8_t kerning)
{  
  LCD_DisplayStringAt(0, LINE(Line), ptr, LEFT_MODE, kerning);
}

void LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint32_t  Xaddress = 0;
  
  /* Get the line address */
  if(hltdc.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_RGB565)
  { /* RGB565 format */
    Xaddress = (hltdc.LayerCfg[ActiveLayer].FBStartAdress) + 2*(LCD_GetXSize()*Ypos + Xpos);
  }
  else
  { /* ARGB8888 format */
    Xaddress = (hltdc.LayerCfg[ActiveLayer].FBStartAdress) + 4*(LCD_GetXSize()*Ypos + Xpos);
  }
  
  /* Write line */
  LL_FillBuffer(ActiveLayer, (uint32_t *)Xaddress, Length, 1, 0, DrawProp[ActiveLayer].TextColor);
}

void LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint32_t  Xaddress = 0;
  
  /* Get the line address */
  if(hltdc.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_RGB565)
  { /* RGB565 format */
    Xaddress = (hltdc.LayerCfg[ActiveLayer].FBStartAdress) + 2*(LCD_GetXSize()*Ypos + Xpos);
  }
  else
  { /* ARGB8888 format */
    Xaddress = (hltdc.LayerCfg[ActiveLayer].FBStartAdress) + 4*(LCD_GetXSize()*Ypos + Xpos);
  }
  
  /* Write line */
  LL_FillBuffer(ActiveLayer, (uint32_t *)Xaddress, 1, Length, (LCD_GetXSize() - 1), DrawProp[ActiveLayer].TextColor);
}

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, num_add = 0, num_pixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    num_add = deltay;
    num_pixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    num_add = deltax;
    num_pixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= num_pixels; curpixel++)
  {
    //LCD_DrawPixel(x, y, DrawProp[ActiveLayer].TextColor);   /* Draw the current pixel */
    Fast_LCD_DrawPixel(x, y, DrawProp[ActiveLayer].TextColor); /* Draw the current pixel fast*/
    
    num += num_add;                            /* Increase the numerator by the top of the fraction */
    if (num >= den)                           /* Check if numerator >= denominator */
    {
      num -= den;                             /* Calculate the new numerator value */
      x += xinc1;                             /* Change the x as appropriate */
      y += yinc1;                             /* Change the y as appropriate */
    }
    x += xinc2;                               /* Change the x as appropriate */
    y += yinc2;                               /* Change the y as appropriate */
  }
}

void LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  /* Draw horizontal lines */
  LCD_DrawHLine(Xpos, Ypos, Width);
  LCD_DrawHLine(Xpos, (Ypos+ Height), Width);
  
  /* Draw vertical lines */
  LCD_DrawVLine(Xpos, Ypos, Height);
  LCD_DrawVLine((Xpos + Width), Ypos, Height);
}

void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t   decision;    /* Decision Variable */ 
  uint32_t  current_x;   /* Current X Value */
  uint32_t  current_y;   /* Current Y Value */
  
  decision = 3 - (Radius << 1);
  current_x = 0;
  current_y = Radius;
  
  while (current_x <= current_y)
  {
    Fast_LCD_DrawPixel((Xpos + current_x), (Ypos - current_y), DrawProp[ActiveLayer].TextColor);
    Fast_LCD_DrawPixel((Xpos - current_x), (Ypos - current_y), DrawProp[ActiveLayer].TextColor);
    Fast_LCD_DrawPixel((Xpos + current_y), (Ypos - current_x), DrawProp[ActiveLayer].TextColor);
    Fast_LCD_DrawPixel((Xpos - current_y), (Ypos - current_x), DrawProp[ActiveLayer].TextColor);
    Fast_LCD_DrawPixel((Xpos + current_x), (Ypos + current_y), DrawProp[ActiveLayer].TextColor);
    Fast_LCD_DrawPixel((Xpos - current_x), (Ypos + current_y), DrawProp[ActiveLayer].TextColor);
    Fast_LCD_DrawPixel((Xpos + current_y), (Ypos + current_x), DrawProp[ActiveLayer].TextColor);
    Fast_LCD_DrawPixel((Xpos - current_y), (Ypos + current_x), DrawProp[ActiveLayer].TextColor);
    
    if (decision < 0)
    { 
      decision += (current_x << 2) + 6;
    }
    else
    {
      decision += ((current_x - current_y) << 2) + 10;
      current_y--;
    }
    current_x++;
  } 
}

void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t radius)
{
	int16_t f = 1 - radius;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * radius;
	int16_t x = 0;
	int16_t y = radius;

        LCD_DrawLine( Xpos + x, Ypos - y, Xpos + x, Ypos + y);//, DrawProp[ActiveLayer].TextColor);
	while(x < y)
	{
		if(f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
                   DrawFastLineVertical(Xpos + x, Ypos - y, Ypos + y);
                   DrawFastLineVertical(Xpos - x, Ypos - y, Ypos + y);
                   DrawFastLineVertical(Xpos + y, Ypos - x, Ypos + x);
                   DrawFastLineVertical(Xpos - y, Ypos - x, Ypos + x);   
	}

//	LCD_DrawCircle(Xpos, Ypos, radius);
}
/**
  * @brief  Draws an poly-line (between many points).
  * @param  Points: Pointer to the points array
  * @param  PointCount: Number of points
  * @retval None
  */
void LCD_DrawPolygon(pPoint Points, uint16_t PointCount)
{
  int16_t x = 0, y = 0;
  
  if(PointCount < 2)
  {
    return;
  }
  
  LCD_DrawLine(Points->X, Points->Y, (Points+PointCount-1)->X, (Points+PointCount-1)->Y);
  
  while(--PointCount)
  {
    x = Points->X;
    y = Points->Y;
    Points++;
    LCD_DrawLine(x, y, Points->X, Points->Y);
  }
}

/**
  * @brief  Draws an ellipse on LCD.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  XRadius: Ellipse X radius
  * @param  YRadius: Ellipse Y radius
  * @retval None
  */
void LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float k = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  k = (float)(rad2/rad1);  
  
  do { 
    LCD_DrawPixel((Xpos-(uint16_t)(x/k)), (Ypos+y), DrawProp[ActiveLayer].TextColor);
    LCD_DrawPixel((Xpos+(uint16_t)(x/k)), (Ypos+y), DrawProp[ActiveLayer].TextColor);
    LCD_DrawPixel((Xpos+(uint16_t)(x/k)), (Ypos-y), DrawProp[ActiveLayer].TextColor);
    LCD_DrawPixel((Xpos-(uint16_t)(x/k)), (Ypos-y), DrawProp[ActiveLayer].TextColor);      
    
    e2 = err;
    if (e2 <= x) {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;     
  }
  while (y <= 0);
}

/**
  * @brief  Draws a pixel on LCD.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  RGB_Code: Pixel color in ARGB mode (8-8-8-8)
  * @retval None
  */
void LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t RGB_Code)
{
  /* Write data value to all SDRAM memory */
  if(hltdc.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_RGB565)
  { /* RGB565 format */
    *(__IO uint16_t*) (hltdc.LayerCfg[ActiveLayer].FBStartAdress + (2*(Ypos*LCD_GetXSize() + Xpos))) = (uint16_t)RGB_Code;
  }
  else
  { /* ARGB8888 format */
    *(__IO uint32_t*) (hltdc.LayerCfg[ActiveLayer].FBStartAdress + (4*(Ypos*LCD_GetXSize() + Xpos))) = RGB_Code;
  }
}


void Fast_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t ARGB_Code)
{
  static uint32_t addressDraw; 
  addressDraw = ProjectionLayerAddress[LayerOfView] + 4 * (Ypos * DisplayWIDTH + Xpos);
  if(addressDraw > ProjectionLayerAddress[LayerOfView]  -1)
   if(addressDraw < ProjectionLayerAddress[LayerOfView] + LAYERS_SIZE)
     *(__IO uint32_t*)(ProjectionLayerAddress[LayerOfView] + 4 * (Ypos * DisplayWIDTH + Xpos)) = ARGB_Code;  //Fast, just write
}
/**
  * @brief  Draws a bitmap picture loaded in the internal Flash in ARGB888 format (32 bits per pixel).
  * @param  Xpos: Bmp X position in the LCD
  * @param  Ypos: Bmp Y position in the LCD
  * @param  pbmp: Pointer to Bmp picture address in the internal Flash
  * @retval None
  */
void LCD_DrawBitmap(uint32_t Xpos, uint32_t Ypos, uint8_t *pbmp)
{
  uint32_t index = 0, width = 0, height = 0, bit_pixel = 0;
  uint32_t address;
  uint32_t input_color_mode = 0;
  
  /* Get bitmap data address offset */
  index = *(__IO uint16_t *) (pbmp + 10);
  index |= (*(__IO uint16_t *) (pbmp + 12)) << 16;
  
  /* Read bitmap width */
  width = *(uint16_t *) (pbmp + 18);
  width |= (*(uint16_t *) (pbmp + 20)) << 16;
  
  /* Read bitmap height */
  height = *(uint16_t *) (pbmp + 22);
  height |= (*(uint16_t *) (pbmp + 24)) << 16; 
  
  /* Read bit/pixel */
  bit_pixel = *(uint16_t *) (pbmp + 28);   
  
  /* Set the address */
  address = hltdc.LayerCfg[ActiveLayer].FBStartAdress + (((LCD_GetXSize()*Ypos) + Xpos)*(4));
  
  /* Get the layer pixel format */    
  if ((bit_pixel/8) == 4)
  {
    input_color_mode = CM_ARGB8888;
  }
  else if ((bit_pixel/8) == 2)
  {
    input_color_mode = CM_RGB565;   
  }
  else 
  {
    input_color_mode = CM_RGB888;
  }
  
  /* Bypass the bitmap header */
  pbmp += (index + (width * (height - 1) * (bit_pixel/8)));  
  
  /* Convert picture to ARGB8888 pixel format */
  for(index=0; index < height; index++)
  {
    /* Pixel format conversion */
    LL_ConvertLineToARGB8888((uint32_t *)pbmp, (uint32_t *)address, width, input_color_mode);
    
    /* Increment the source and destination buffers */
    address+=  (LCD_GetXSize()*4);
    pbmp -= width*(bit_pixel/8);
  } 
}


void LCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  decision;     /* Decision Variable */ 
  uint32_t  current_x;   /* Current X Value */
  uint32_t  current_y;   /* Current Y Value */
  
  decision = 3 - (Radius << 1);
  
  current_x = 0;
  current_y = Radius;
  
  LCD_SetTextColor(DrawProp[ActiveLayer].TextColor);
  
  while (current_x <= current_y)
  {
    if(current_y > 0) 
    {
      LCD_DrawHLine(Xpos - current_y, Ypos + current_x, 2*current_y);
      LCD_DrawHLine(Xpos - current_y, Ypos - current_x, 2*current_y);
    }
    
    if(current_x > 0) 
    {
      LCD_DrawHLine(Xpos - current_x, Ypos - current_y, 2*current_x);
      LCD_DrawHLine(Xpos - current_x, Ypos + current_y, 2*current_x);
    }
    if (decision < 0)
    { 
      decision += (current_x << 2) + 6;
    }
    else
    {
      decision += ((current_x - current_y) << 2) + 10;
      current_y--;
    }
    current_x++;
  }
  
  LCD_SetTextColor(DrawProp[ActiveLayer].TextColor);
 // LCD_DrawCircle(Xpos, Ypos, Radius);
}

/**
  * @brief  Draws a full poly-line (between many points).
  * @param  Points: Pointer to the points array
  * @param  PointCount: Number of points
  * @retval None
  */
void LCD_FillPolygon(pPoint Points, uint16_t PointCount)
{
  int16_t X = 0, Y = 0, X2 = 0, Y2 = 0, X_center = 0, Y_center = 0, X_first = 0, Y_first = 0, pixelX = 0, pixelY = 0, counter = 0;
  uint16_t  image_left = 0, image_right = 0, image_top = 0, image_bottom = 0;
  
  image_left = image_right = Points->X;
  image_top= image_bottom = Points->Y;
  
  for(counter = 1; counter < PointCount; counter++)
  {
    pixelX = POLY_X(counter);
    if(pixelX < image_left)
    {
      image_left = pixelX;
    }
    if(pixelX > image_right)
    {
      image_right = pixelX;
    }
    
    pixelY = POLY_Y(counter);
    if(pixelY < image_top)
    { 
      image_top = pixelY;
    }
    if(pixelY > image_bottom)
    {
      image_bottom = pixelY;
    }
  }  
  
  if(PointCount < 2)
  {
    return;
  }
  
  X_center = (image_left + image_right)/2;
  Y_center = (image_bottom + image_top)/2;
  
  X_first = Points->X;
  Y_first = Points->Y;
  
  while(--PointCount)
  {
    X = Points->X;
    Y = Points->Y;
    Points++;
    X2 = Points->X;
    Y2 = Points->Y;    
    
    LCD_FillTriangle(X, X2, X_center, Y, Y2, Y_center);
    LCD_FillTriangle(X, X_center, X2, Y, Y_center, Y2);
    LCD_FillTriangle(X_center, X2, X, Y_center, Y2, Y);   
  }
  
  LCD_FillTriangle(X_first, X2, X_center, Y_first, Y2, Y_center);
  LCD_FillTriangle(X_first, X_center, X2, Y_first, Y_center, Y2);
  LCD_FillTriangle(X_center, X2, X_first, Y_center, Y2, Y_first);   
}

/**
  * @brief  Draws a full ellipse.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  XRadius: Ellipse X radius
  * @param  YRadius: Ellipse Y radius  
  * @retval None
  */
void LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float k = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  k = (float)(rad2/rad1);
  
  do 
  {       
    LCD_DrawHLine((Xpos-(uint16_t)(x/k)), (Ypos+y), (2*(uint16_t)(x/k) + 1));
    LCD_DrawHLine((Xpos-(uint16_t)(x/k)), (Ypos-y), (2*(uint16_t)(x/k) + 1));
    
    e2 = err;
    if (e2 <= x) 
    {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;
  }
  while (y <= 0);
}




/*******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: Line where to display the character shape
  * @param  Ypos: Start column address
  * @param  c: Pointer to the character data
  * @retval None
  */
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c, uint16_t SignWide)
{
  uint32_t i = 0, j = 0, k = 0;
  uint16_t height; 
  uint16_t width;
  uint8_t  BytesWide;
  uint8_t  *pchar;
  uint8_t  position;

  uint8_t ShiftVar = 0;

  
  height = DrawProp[ActiveLayer].pFont->Height;
  width  = (uint16_t)SignWide;
  BytesWide = ((SignWide-1)/8) + 1 ;
  position = 0;
  
  for (k = 0; k < height; k++)
    {
    for (j = 0; j < BytesWide; j++)
    {
      
      for(i = 0; i < 8; i++ ){
       if(position < SignWide){ 
      if(c[j] & (1 << 7-i) ) 
      {
        //LCD_DrawPixel((Xpos + j), Ypos, DrawProp[ActiveLayer].TextColor);
        Fast_LCD_DrawPixel((Xpos + position), Ypos, DrawProp[ActiveLayer].TextColor);
      }
      else
      {
       if(DrawProp[ActiveLayer].BackColor & 0xFF000000) Fast_LCD_DrawPixel((Xpos + position), Ypos, DrawProp[ActiveLayer].BackColor);
      //  LCD_DrawPixel((Xpos + j), Ypos, DrawProp[ActiveLayer].BackColor);
      }
      position++;
      }
      }
    }
    c += BytesWide;
    position = 0;
    Ypos++;
    }
}

/**
  * @brief  Fills a triangle (between 3 points).
  * @param  x1: Point 1 X position
  * @param  y1: Point 1 Y position
  * @param  x2: Point 2 X position
  * @param  y2: Point 2 Y position
  * @param  x3: Point 3 X position
  * @param  y3: Point 3 Y position
  * @retval None
  */
/*
void LCD_FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3)
{ 
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, num_add = 0, num_pixels = 0,
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        // The difference between the x's
  deltay = ABS(y2 - y1);        //The difference between the y's 
  x = x1;                       //Start x off at the first pixel 
  y = y1;                       // Start y off at the first pixel
  
  if (x2 >= x1)                 // The x-values are increasing 
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          // The x-values are decreasing
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 // The y-values are increasing
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          // The y-values are decreasing 
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         // There is at least one x-value for every y-value 
  {
    xinc1 = 0;                  // Don't change the x when numerator >= denominator 
    yinc2 = 0;                  // Don't change the y for every iteration 
    den = deltax;
    num = deltax >> 1;
    num_add = deltay;
    num_pixels = deltax;         // There are more x-values than y-values 
  }
  else                          // There is at least one y-value for every x-value 
  {
    xinc2 = 0;                  // Don't change the x for every iteration 
    yinc1 = 0;                  // Don't change the y when numerator >= denominator 
    den = deltay;
    num = deltay >> 1;
    num_add = deltax;
    num_pixels = deltay;         // There are more y-values than x-values 
  }
  
  for (curpixel = 0; curpixel <= num_pixels; curpixel++)
  {
    LCD_DrawLine(x, y, x3, y3);
  
    num += num_add;              // Increase the numerator by the top of the fraction 
    if (num >= den)             // Check if numerator >= denominator 
    {
      num -= den;               // Calculate the new numerator value 
      x += xinc1;               // Change the x as appropriate 
      y += yinc1;               // Change the y as appropriate 
    }
    x += xinc2;                 // Change the x as appropriate 
    y += yinc2;                 // Change the y as appropriate 
  } 
}

  */

static void LL_FillBuffer(uint32_t LayerIndex, void *pDst, uint32_t xSize, uint32_t ySize, uint32_t OffLine, uint32_t ColorIndex) 
{
  /* Register to memory mode with ARGB8888 as color Mode */ 
  hdma2d.Init.Mode         = DMA2D_R2M;
  if(hltdc.LayerCfg[ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_RGB565)
  { /* RGB565 format */ 
    hdma2d.Init.ColorMode    = DMA2D_RGB565;
  }
  else
  { /* ARGB8888 format */
    hdma2d.Init.ColorMode    = DMA2D_ARGB8888;
  }
  hdma2d.Init.OutputOffset = OffLine;      
  
  hdma2d.Instance = DMA2D;
   hdma2d.XferCpltCallback = Transfer_DMA2D_Completed;
   
  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK) 
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d, LayerIndex) == HAL_OK) 
    {
      if (HAL_DMA2D_Start_IT(&hdma2d, ColorIndex, (uint32_t)pDst, xSize, ySize) == HAL_OK)
      {
        /* Polling For DMA transfer */  
       HAL_DMA2D_PollForTransfer(&hdma2d, 10);
      }
    }
  } 
}

/**
  * @brief  Converts a line to an ARGB8888 pixel format.
  * @param  pSrc: Pointer to source buffer
  * @param  pDst: Output color
  * @param  xSize: Buffer width
  * @param  ColorMode: Input color mode   
  * @retval None
  */
void LL_ConvertLineToARGB8888(void *pSrc, void *pDst, uint32_t xSize, uint32_t ColorMode)
{    
  /* Configure the DMA2D Mode, Color Mode and output offset */
  hdma2d.Init.Mode         = DMA2D_M2M_PFC;
  hdma2d.Init.ColorMode    = DMA2D_ARGB8888;
  hdma2d.Init.OutputOffset = 0;     
  
  /* Foreground Configuration */
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0xFF;
  hdma2d.LayerCfg[1].InputColorMode = ColorMode;
  hdma2d.LayerCfg[1].InputOffset = 0;
  
  hdma2d.Instance = DMA2D; 
  
  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK) 
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK) 
    {
      if (HAL_DMA2D_Start(&hdma2d, (uint32_t)pSrc, (uint32_t)pDst, xSize, 1) == HAL_OK)
      {
        /* Polling For DMA transfer */  
        HAL_DMA2D_PollForTransfer(&hdma2d, 10);
      }
    }
  } 
}

void LL_ConvertImageToARGB8888(void *pSrc, void *pDst, uint32_t xSize, uint32_t ySize, uint32_t ColorMode)
{    
  /* Configure the DMA2D Mode, Color Mode and output offset */
  hdma2d.Init.Mode         = DMA2D_M2M_PFC;
  hdma2d.Init.ColorMode    = DMA2D_ARGB8888;
  hdma2d.Init.OutputOffset = 0;     
  
  /* Foreground Configuration */
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0xFF;
  hdma2d.LayerCfg[1].InputColorMode = ColorMode;
  hdma2d.LayerCfg[1].InputOffset = 0;
  
  hdma2d.Instance = DMA2D; 
  
  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK) 
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK) 
    {
      if (HAL_DMA2D_Start(&hdma2d, (uint32_t)pSrc, (uint32_t)pDst, xSize, ySize) == HAL_OK)
      {
        /* Polling For DMA transfer */  
        HAL_DMA2D_PollForTransfer(&hdma2d, 10);
      }
    }
  } 
}

void LCD_InitParams(uint32_t LayerIndexGet, uint32_t BackColor, uint32_t TextColor, sFONT* pFont){
  LayerIndex = LayerIndexGet;
  DrawProp[LayerIndex].BackColor = BackColor; 
  DrawProp[LayerIndex].pFont     = pFont;
  DrawProp[LayerIndex].TextColor = TextColor; 
}



void LCD_SetColorPixel(uint32_t Color){
DrawProp[LayerIndex].TextColor = Color;
}
      
uint8_t LCD_Init(void){
 LCD_SetLayerVisible(1, DISABLE);  // if I comment THIS line the 0 layer will be displayed fine 
 LCD_SetXSize(800);
 LCD_SetYSize(480);
 LCD_LayerDefaultInit(0, LAYER_1_OFFSET + SDRAM_BANK_ADDR);
 LCD_SelectLayer(0);
 LCD_InitParams(0, 0, 0xFFFF0000, &GOST_B_23_var);
return 0;
}

void LCD_SetLight(uint16_t Volume){ 

  switch(Volume){
    case 10: 
      Volume = 10; break;
    case 9 : Volume = 20; break;
    case 8 : Volume = 30; break;
    case 7 : Volume = 40; break;
    case 6 : Volume = 50; break;
    case 5 : Volume = 60; break;
    case 4 : Volume = 70; break;
    case 3 : Volume = 80; break; 
    case 2 : Volume = 100; break;
    case 1 : Volume = 150; break;
    case 0 : Volume = 200; break;
 
  }  
   HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, Volume);
 
}

void DrawFastLineVertical(uint16_t x1, uint16_t y1, uint16_t y2){
 static uint32_t temp;
 static uint32_t color;
 static uint32_t address;
 
 address = ProjectionLayerAddress[LayerOfView];
 color = DrawProp[ActiveLayer].TextColor;
 if (y1  > y2){
  temp = y1;
  y1 = y2;
  y2 = temp;
 }
 temp = 4*x1;
  while(y1 <= y2)
    *(__IO uint32_t*)(address + 4 * (y1++) * DisplayWIDTH + temp) = color;
}

void DrawFastLineHorizontal(uint16_t y1, uint16_t x1, uint16_t x2){
 static uint32_t temp;
 static uint32_t color;
 static uint32_t address;
 
 address = ProjectionLayerAddress[LayerOfView];
 color = DrawProp[ActiveLayer].TextColor;
  
 if (x1  > x2){
  temp = x1;
  x1 = x2;
  x2 = temp;
 }
 temp = 4 * y1 * DisplayWIDTH;
  while(x1 <= x2)
    *(__IO uint32_t*)(address + temp + 4*(x1++)) = color;
}

void LCD_FillRect(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){

 uint16_t temp;
 if (y1  > y2){
  temp = y1;
  y1 = y2;
  y2 = temp;
 }


 while(y1 <= y2)
    DrawFastLineHorizontal(y1++, x1, x2);
}

void LCD_Fill_Image(uint32_t ImageAddress, uint32_t x, uint32_t y, uint32_t xSize, uint32_t ySize){
  static uint32_t address;
 
 address = ProjectionLayerAddress[LayerOfView] + 4 * y * DisplayWIDTH + 4 * x;
 FillImageSoft(ImageAddress, address, xSize, ySize);

}

void FillImageSoft(uint32_t ImageAddress, uint32_t address, uint32_t xSize, uint32_t ySize){
uint32_t S_Y, data, i , j;
uint32_t* pImageAddress = (uint32_t*)ImageAddress;
 
 for(j = 0; j < ySize; j++){
   S_Y = 4 * j * DisplayWIDTH;
  for(i = 0; i < xSize; i++){
       data = *pImageAddress++;
       if(data & 0xFF000000) // is it not transparent?
       *(__IO uint32_t*)(address + i * 4 + S_Y) = data;
   }
 }
}
 /// -- try to draw triangle
void LCD_FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3){
 
struct point{
 uint16_t x;
 uint16_t y; 
};

struct point A, B, C;
static uint8_t i, indexA, indexB, indexC;
static uint16_t sy, tmp;

indexA = 1; //let A is first point
if((y2 < y1) && (y2 < y3)) indexA = 2;
if((y3 < y2) && (y3 < y1)) indexA = 3;

switch (indexA){
	case 1: A.y = y1; A.x = x1;
			break;
	case 2: A.y = y2; A.x = x2;
			break;
	case 3: A.y = y3; A.x = x3;
			break;
}

indexC = 1; //let C is first point
if((y2 > y1) && (y2 > y3)) indexC = 2;
if((y3 > y2) && (y3 > y1)) indexC = 3;

switch (indexC){
	case 1: C.y = y1; C.x = x1;
			break;
	case 2: C.y = y2; C.x = x2;
			break;
	case 3: C.y = y3; C.x = x3;
			break;
}

for (i = 1; i < 4; i++)	
	if((i != indexA) && (i != indexC)) indexB = i;

switch (indexB){
	case 1: B.y = y1; B.x = x1;
			break;
	case 2: B.y = y2; B.x = x2;
			break;
	case 3: B.y = y3; B.x = x3;
			break;
}

for (sy = A.y; sy <= C.y; sy++) {
  x1 = A.x + (sy - A.y) * (C.x - A.x) / (C.y - A.y);
  if (sy < B.y)
    x2 = A.x + (sy - A.y) * (B.x - A.x) / (B.y - A.y);
  else {
    if (C.y == B.y)
      x2 = B.x;
    else
      x2 = B.x + (sy - B.y) * (C.x - B.x) / (C.y - B.y);
  }
  if (x1 > x2) { tmp = x1; x1 = x2; x2 = tmp; }
   DrawFastLineHorizontal(sy, x1, x2);
}

}

