#include "rtc.h"
#include "i2c.h"
// PCF8563.C
// Command Set:
// PCF8563_init(void)
//PCF8563_write_byte(u8 address, u8 data)
// PCF8563_read_byte(u8 address)
// bin2bcd(u8 value)
// bcd2bin(char bcd_value)
// PCF8563_set_datetime(date_time_t *dt)
// PCF8563_read_datetime(date_time_t *dt)
// Set_Alarm(u8 AMode,PCF8563_Alarm *AT)
// config_CLKOUT(u8 mode)
// config_PCF8563_Timer(u8 mode)
// config_PCF8563_Interrupt(u8 mode,ti_tp)

#define PCF8563_WRITE_ADDRESS 0xA2
#define PCF8563_READ_ADDRESS  0xA2
// Register addresses
#define PCF8563_CTRL_STATUS_REG1   0x00
#define PCF8563_CTRL_STATUS_REG2   0x01
#define PCF8563_SECONDS_REG        0x02
#define PCF8563_MINUTES_REG        0x03
#define PCF8563_HOURS_REG          0x04
#define PCF8563_DAY_REG            0x05
#define PCF8563_WEEK_REG           0x06
#define PCF8563_MONTH_REG          0x07
#define PCF8563_YEAR_REG           0x08
#define PCF8563_ALARM_MINS_REG     0x09
#define PCF8563_ALARM_HOURS_REG    0x0A
#define PCF8563_ALARM_DAY_REG      0x0B
#define PCF8563_ALARM_WEEKDAY_REG  0x0C
#define PCF8563_CTRL_CLKOUT_REG    0x0D
#define PCF8563_CTRL_TIMER_REG     0x0E
#define PCF8563_TIMER_REG          0x0F

// Commands for the Control/Status register.
#define PCF8563_START_COUNTING     0x08
#define PCF8563_STOP_COUNTING      0x28
//*************************************  for Set_Alarm()
#define PCF8563_Alarm_off          0x00
#define PCF8563_M_Mode             0x01
#define PCF8563_MH_Mode            0x04
#define PCF8563_MHW_Mode           0x07
#define PCF8563_MHD_Mode           0x0B 

//*************************************  for config_CLKOUT()
#define PCF8563_CLKOUT_off         0x00
#define PCF8563_CLKOUT_32KHz       0x80
#define PCF8563_CLKOUT_1KHz        0x81
#define PCF8563_CLKOUT_32Hz        0x82
#define PCF8563_CLKOUT_1Hz         0x83

//*************************************  for config_PCF8563_Timer()
#define PCF8563_Timer_off          0x00
#define PCF8563_Timer_4KHz         0x80
#define PCF8563_Timer_64Hz         0x81
#define PCF8563_Timer_1Hz          0x82
#define PCF8563_Timer_1_60Hz       0x83

//*************************************  for config_PCF8563_Interrupt()
#define Alarm_Interrupt_Enable     0x01
#define Timer_Interrupt_Enable     0x02
#define A_T_Interrupt_Enable       0x03
#define Timer_INT_Pulse_on         0x10
#define Timer_INT_Pulse_off        0x00

char const weekday_names[7][10] =
{
{"Sunday"},
{"Monday"},
{"Tuesday"},
{"Wednesday"},
{"Thursday"},
{"Friday"},
{"Saturday"}
};   
               
// This structure defines the user's date and time data.
// The values are stored as unsigned integers.  The user
// should declare a structure of this type in the application
// program. Then the address of the structure should be
// passed to the PCF8563 read/write functions in this
// driver, whenever you want to talk to the chip.


u8 LV_sec,C_Mon;
//#bit LowVoltage = LV_sec.7
//#bit Century = C_Mon.7


//----------------------------------------------
void PCF8563_write_byte(u8 address, u8 data)
{
//disable_interrupts(GLOBAL);
   HAL_I2C_Mem_Write(&hi2c2, (uint16_t)PCF8563_WRITE_ADDRESS, (uint16_t)address, I2C_MEMADD_SIZE_8BIT, &data, 1, 200);
//i2c_start();
//i2c_write(PCF8563_WRITE_ADDRESS);
//i2c_write(address);
//i2c_write(data);
//i2c_stop();
//enable_interrupts(GLOBAL);
}   

//----------------------------------------------
u8 PCF8563_read_byte(u8 address)
{
u8 retval;
//disable_interrupts(GLOBAL);
//i2c_start();
 HAL_I2C_Mem_Read(&hi2c2,(uint16_t)PCF8563_WRITE_ADDRESS,(uint16_t)address, I2C_MEMADD_SIZE_8BIT,&retval,1,100);
 
//i2c_write(PCF8563_WRITE_ADDRESS);
//i2c_write(address);
//i2c_start();
//i2c_write(PCF8563_READ_ADDRESS);
//retval = i2c_read(0);
//i2c_stop();
//enable_interrupts(GLOBAL);
return(retval);
}   

//----------------------------------------------
//           PCF8563 Initial             //

void PCF8563_Init(void)
{
PCF8563_write_byte(PCF8563_CTRL_STATUS_REG1,PCF8563_START_COUNTING);
}   

//----------------------------------------------
// This function converts an 8 bit binary value
// to an 8 bit BCD value.
// The input range must be from 0 to 99.

u8 bin2bcd(u8 value)
{
char retval;

retval = 0;

while(1)
  {
   // Get the tens digit by doing multiple subtraction
   // of 10 from the binary value.
   if(value >= 10)
     {
      value -= 10;
      retval += 0x10;
     }
   else // Get the ones digit by adding the remainder.
     {
      retval += value;
      break;
     }
   }

return(retval);
}

//----------------------------------------------
// This function converts an 8 bit BCD value to
// an 8 bit binary value.
// The input range must be from 00 to 99.

char bcd2bin(char bcd_value)
{
char temp;

temp = bcd_value;

// Shifting the upper digit right by 1 is
// the same as multiplying it by 8.
temp >>= 1;

// Isolate the bits for the upper digit.
temp &= 0x78;

// Now return: (Tens * 8) + (Tens * 2) + Ones
return(temp + (temp >> 2) + (bcd_value & 0x0f));

}
//----------------------------------------------
//----------------------------------------------

void PCF8563_set_datetime(date_time_t *dt)
{

union{  
  struct{
    u8 bcd_sec;
    u8 bcd_min;
    u8 bcd_hrs;
    u8 bcd_day;
    u8 wek;   
    u8 bcd_mon;
    u8 bcd_yer;
  }Fields;
  u8 arrWeekDays[7];
}Time;
// Convert the input date/time into BCD values
// that are formatted for the PCF8563 registers.
 
Time.Fields.bcd_sec = bin2bcd(dt->seconds);
Time.Fields.bcd_min = bin2bcd(dt->minutes);
Time.Fields.bcd_hrs = bin2bcd(dt->hours);   
Time.Fields.bcd_day = bin2bcd(dt->day) | (dt->year << 6);
Time.Fields.bcd_mon = bin2bcd(dt->month) | (dt->weekday << 5);
Time.Fields.bcd_yer = bin2bcd(dt->year);
Time.Fields.wek     = dt->weekday;
// Stop the RTC from counting, before we write to
// the date and time registers.
 PCF8563_write_byte(PCF8563_CTRL_STATUS_REG1,PCF8563_STOP_COUNTING);

// Write to the date and time registers.  Disable interrupts
// so they can't disrupt the i2c operations.
//disable_interrupts(GLOBAL);
//i2c_start();
 HAL_I2C_Mem_Write(&hi2c2, (uint16_t)PCF8563_WRITE_ADDRESS, (uint16_t)PCF8563_SECONDS_REG, I2C_MEMADD_SIZE_8BIT, Time.arrWeekDays, 7, 200);
//i2c_write(PCF8563_WRITE_ADDRESS);
//i2c_write(PCF8563_SECONDS_REG);   // Start at seconds reg.   
//i2c_write(bcd_sec);
//i2c_write(bcd_min);
//i2c_write(bcd_hrs);   
//i2c_write(bcd_day);
//i2c_write(wek);
//i2c_write(bcd_mon);
//i2c_write(bcd_yer);
//i2c_stop();
//enable_interrupts(GLOBAL);

// Now allow the PCF8563 to start counting again.

PCF8563_write_byte(PCF8563_CTRL_STATUS_REG1,PCF8563_START_COUNTING);

}
//----------------------------------------------

//----------------------------------------------
// Read the Date and Time from the hardware registers
// in the PCF8563.   We don't have to disable counting
// during read operations, because according to the data
// sheet, if any of the lower registers (1 to 7) is read,
// all of them are loaded into "capture" registers.
// All further reading within that cycle is done from
// those registers.

void PCF8563_read_datetime(date_time_t *dt)
{
union{  
  struct{
    u8 bcd_sec;
    u8 bcd_min;
    u8 bcd_hrs;
    u8 bcd_day;
    u8 wek;   
    u8 bcd_mon;
    u8 bcd_yer;
  }Fields;
  u8 arrWeekDays[7];
}Time;
u8 data = 0;

//  LowVoltage = VL_sec.7
//  Century    = C_Mon.7

// Disable interrupts so the i2c process is not disrupted.
data = PCF8563_SECONDS_REG;

 HAL_I2C_Master_Transmit(&hi2c2, PCF8563_WRITE_ADDRESS, &data, 1, 200);
// Read the date/time registers inside the PCF8563.
//i2c_start();
//i2c_write(PCF8563_WRITE_ADDRESS);
//i2c_write(PCF8563_SECONDS_REG);   // Start at seconds reg.
HAL_I2C_Master_Receive(&hi2c2, PCF8563_READ_ADDRESS, Time.arrWeekDays, 7, 100); 
 
//i2c_start();
//i2c_write(PCF8563_READ_ADDRESS);

//LV_sec  = i2c_read();     
//bcd_min = i2c_read();     
//bcd_hrs = i2c_read();
//bcd_day = i2c_read();
//wek     = i2c_read();
//C_Mon   = i2c_read();
//bcd_yer = i2c_read(0);

//i2c_stop();

//enable_interrupts(GLOBAL);

// Convert the date/time values from BCD to
// unsigned 8-bit integers.  Unpack the bits
// in the PCF8563 registers where required.
//bcd_sec     = LV_sec & 0x7F;
 Time.Fields.bcd_sec &= 0x7F;
 //bcd_mon     = C_Mon  & 0x7F;
 Time.Fields.bcd_mon &= 0x7F;
 
dt->seconds = bcd2bin(Time.Fields.bcd_sec);   
dt->minutes = bcd2bin(Time.Fields.bcd_min);     
dt->hours   = bcd2bin(Time.Fields.bcd_hrs & 0x3F);
dt->day     = bcd2bin(Time.Fields.bcd_day & 0x3F);
dt->month   = bcd2bin(Time.Fields.bcd_mon & 0x1F);
dt->weekday =    Time.Fields.wek & 0x07;
dt->year    = bcd2bin(Time.Fields.bcd_yer);   

}
//----------------------------------------------
//void Set_Alarm(u8 AMode)
//{
//if (AMode == 0x00)
//   {
  //  disable_interrupts(GLOBAL);
 //   i2c_start();
 //   i2c_write(PCF8563_WRITE_ADDRESS);
 //   i2c_write(PCF8563_ALARM_MINS_REG);   // Start at alarm min reg.   
 //   i2c_write(0x80);
 //   i2c_write(0x80);
 //   i2c_write(0x80);   
 //  i2c_write(0x80);
 //   i2c_stop();
 //   enable_interrupts(GLOBAL);
//   }
//}
void Set_Alarm(u8 AMode,PCF8563_Alarm *AT)
{
u8 min = 0x80;
u8 hrs = 0x80;
u8 day = 0x80;
u8 wek = 0x80;
 
switch (AMode){
          case 0x01: min = AT->minutes;
                     break;
          case 0x04: min = AT->minutes;
                     hrs = AT->hours;
                     break;
          case 0x07: min = AT->minutes;
                     hrs = AT->hours;
                     wek = AT->weekday;
                     break;
          case 0x0B: min = AT->minutes;
                     hrs = AT->hours;
                     day = AT->day;
                     break;
               }

//disable_interrupts(GLOBAL);
//i2c_start();
//i2c_write(PCF8563_WRITE_ADDRESS);
//i2c_write(PCF8563_ALARM_MINS_REG);   // Start at alarm min reg.   
//i2c_write(min);
//i2c_write(hrs);
//i2c_write(day);   
//i2c_write(wek);
//i2c_stop();
//enable_interrupts(GLOBAL);

}

//----------------------------------------------

void config_CLKOUT(u8 mode)
{
PCF8563_write_byte(PCF8563_CTRL_CLKOUT_REG, mode);
}

//----------------------------------------------

void config_PCF8563_Timer(u8 mode)
{
PCF8563_write_byte(PCF8563_CTRL_TIMER_REG, mode);
}

//----------------------------------------------

void config_PCF8563_Interrupt(u8 mode, u8 ti_tp)
{
mode = mode | ti_tp;
PCF8563_write_byte(PCF8563_CTRL_STATUS_REG2, mode);
} 



