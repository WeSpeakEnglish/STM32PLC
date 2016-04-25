#ifndef _RTC_H
#define _RTC_H
#include "variables.h"

typedef struct
{
u8 seconds;    // 0 to 59
u8 minutes;    // 0 to 59
u8 hours;      // 0 to 23  (24-hour time)
u8 day;        // 1 to 31
u8 weekday;    // 0 = Sunday, 1 = Monday, etc.
u8 month;      // 1 to 12
u8 year;       // 00 to 99
}date_time_t;

typedef struct
{
u8 minutes;    // 0 to 59
u8 hours;      // 0 to 23  (24-hour time)
u8 day;        // 1 to 31
u8 weekday;    // 0 = Sunday, 1 = Monday, etc.
}PCF8563_Alarm;


void PCF8563_Init(void);
void PCF8563_set_datetime(date_time_t *dt);
void PCF8563_read_datetime(date_time_t *dt);
void Set_Alarm(u8 AMode,PCF8563_Alarm *AT);
void config_CLKOUT(u8 mode);
void config_PCF8563_Timer(u8 mode);
void config_PCF8563_Interrupt(u8 mode, u8 ti_tp);
void GetDateToStr(u8 * StrDstDate, date_time_t * dt);
void GetTimeToStr(u8 * StrDstTime, date_time_t * dt);

#endif