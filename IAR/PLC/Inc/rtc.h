#ifndef _RTC_H
#define _RTC_H
#include "variables.h"

typedef struct
{
uint8_t seconds;    // 0 to 59
uint8_t minutes;    // 0 to 59
uint8_t hours;      // 0 to 23  (24-hour time)
uint8_t day;        // 1 to 31
uint8_t weekday;    // 0 = Sunday, 1 = Monday, etc.
uint8_t month;      // 1 to 12
uint8_t year;       // 00 to 99
}date_time_t;

typedef struct
{
uint8_t minutes;    // 0 to 59
uint8_t hours;      // 0 to 23  (24-hour time)
uint8_t day;        // 1 to 31
uint8_t weekday;    // 0 = Sunday, 1 = Monday, etc.
}PCF8563_Alarm;

extern volatile uint8_t TimeIsReady;

void CheckTheTick(void);
void PCF8563_Init(void);
void PCF8563_set_datetime(date_time_t volatile *dt);
void PCF8563_read_datetime(date_time_t volatile *dt);
void Set_Alarm(uint8_t AMode,PCF8563_Alarm *AT);
void config_CLKOUT(uint8_t mode);
void config_PCF8563_Timer(uint8_t mode);
void config_PCF8563_Interrupt(uint8_t mode, uint8_t ti_tp);
void GetDateToStr(uint8_t * StrDstDate, date_time_t volatile * dt);
void GetTimeToStr(uint8_t * StrDstTime, date_time_t volatile * dt);

#endif