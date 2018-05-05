/**
  * @file    time.c
  * @brief   CLIB time() implementation
  * @brief   The "time" function returns the current calendar time.
  * @brief   The time is measured in seconds since the first of January 1970.
  * @brief   (time_t)-1 should be returned if the calendar time is not available.
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <time.h>
#include "app.h"


#pragma module_name = "?time"


__time32_t (__time32)(__time32_t *t)
{
                RTC_DateTypeDef         rtc_date;
                RTC_TimeTypeDef         rtc_time;
        struct  tm                      s;
                time_t	                time_raw;


        app_rtc_time_read( &rtc_time );
        app_rtc_date_read( &rtc_date );

        s.tm_year       =   rtc_date.Year;
        s.tm_mon        =   rtc_date.Month;
        s.tm_mday       =   rtc_date.Date;
        s.tm_hour       =   rtc_time.Hours;
        s.tm_min        =   rtc_time.Minutes;
        s.tm_sec        =   rtc_time.Seconds;

        time_raw        =   mktime( &s );

	return( time_raw );
}
