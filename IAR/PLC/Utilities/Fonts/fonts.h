#ifndef __FONTS_H
#define __FONTS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

struct FONT_CHAR_INFO{
 uint8_t Wide;
 uint16_t Offset;
};
typedef struct _tFont
{    
  const uint8_t *table;
  const struct FONT_CHAR_INFO *tableInfo;
//  uint16_t Width;
  uint16_t Height;
  
} sFONT;

extern sFONT GOST_B_23_var;


#define LINE(x) ((x) * (((sFONT *)LCD_GetFont())->Height))


#ifdef __cplusplus
}
#endif
  
#endif /* __FONTS_H */
 
