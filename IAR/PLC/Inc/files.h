#ifndef _FILES_H
#define _FILES_H
#include "variables.h"

void WriteNewTextFileSD(uint8_t * buff,  char const * NameOfFile, uint32_t NumberOfBytes); // just write text file buffer to write, Name of File in notation "0:/FILEDIR/filename.ext" and number of bytes to write
#endif