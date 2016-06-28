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
   
   typedef union {
   uint8_t Bytes[4];
   uint16_t Words[2];
   int32_t DWord;
   }
   _FourBytesS;
   
   typedef union {
   uint8_t Bytes[4];
   uint16_t Words[2];
   uint32_t DWord;
   }
   _FourBytesU;
     
#ifdef __cplusplus
}
#endif

#endif /* __VARIABLES_H */   
