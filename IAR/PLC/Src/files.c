#include "files.h"
#include "ff.h"

void WriteNewTextFileSD(u8 * buff, char const * NameOfFile, u32 NumberOfBytes){
u8 res; //variable for return values
FATFS fs; //fat object FATFS
FIL OurFile; // this is our file here

UINT br; //just counter
//try to mount disk
res = f_mount(&fs,"0:",1);
if (res == FR_OK){
  //open the file
  res = f_open(&OurFile,(char const*)NameOfFile,FA_WRITE | FA_CREATE_ALWAYS);
  f_lseek(&OurFile,0); //pointer to the first byte
  f_write(&OurFile,buff, NumberOfBytes, &br); //write the file
  f_close(&OurFile);//close the file
  f_mount(NULL, "0:", 0);//unmount the drive
 }
 else{
   //не удалось смонтировать диск
 }
}


