#ifndef __VARIABLES_H
#define __VARIABLES_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
#include <stdint.h>

   typedef union {
   uint8_t Bytes[2];
   int16_t Word;
   }
   _TwoBytesS;
      typedef union {
   uint8_t Bytes[2];
   int16_t Word;
   }
   _TwoBytesU;
   
#ifdef __cplusplus
}
#endif

#endif /* __VARIABLES_H */   
