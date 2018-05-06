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


__time32_t (__time32)( __time32_t *     t )
{
        time_t	                raw     =   app_rtc_get();


        if( t != NULL )
        {
                *t      =   raw;
        }

        return( raw );
}
