/**
  * @file    app_rtc.c
  * @brief   Real Time Clock servives
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdio.h>
#include <stdbool.h>
#include "app.h"


#define RTC_ASYNCH_PREDIV               0x7F    //LSE as RTC clock
#define RTC_SYNCH_PREDIV                0x00FF  //LSE as RTC clock


static  RTC_HandleTypeDef       hrtc;


static
void    app_rtc_date_read(              RTC_DateTypeDef *       date )
{
        HAL_RTC_GetDate( &hrtc, date, FORMAT_BIN );

        if( (date->Date == 0) || (date->Month == 0))
        {
                //date->Date = date->Month = 1;
        }

        //APP_TRACE( "DATE: %04d-%02d-%02d\n", date->Year, date->Month, date->Date );
}


static
void    app_rtc_date_write(             RTC_DateTypeDef *       date )
{
        HAL_RTC_SetDate( &hrtc, date, FORMAT_BIN );
}


static
void    app_rtc_time_read(              RTC_TimeTypeDef *       time )
{
        HAL_RTC_GetTime( &hrtc, time, FORMAT_BIN );

        //APP_TRACE( "TIME: %02d-%02d-%02d\n", time->Hours, time->Minutes, time->Seconds );
}


static
void    app_rtc_time_write(             RTC_TimeTypeDef *       time )
{
        time->StoreOperation    =   0;
        time->SubSeconds        =   0;
        time->DayLightSaving    =   0;
        HAL_RTC_SetTime( &hrtc, time, FORMAT_BIN );
}


void    app_rtc_init( void )
{
        RCC_OscInitTypeDef              osc;
        RCC_PeriphCLKInitTypeDef        clk;


        osc.OscillatorType      =   RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
        osc.PLL.PLLState        =   RCC_PLL_NONE;
        osc.LSEState            =   RCC_LSE_ON;
        osc.LSIState            =   RCC_LSI_OFF;
        if( HAL_RCC_OscConfig(&osc) != HAL_OK )
        {
                return;
        }

        clk.PeriphClockSelection =   RCC_PERIPHCLK_RTC;
        clk.RTCClockSelection   =   RCC_RTCCLKSOURCE_LSE;
        if( HAL_RCCEx_PeriphCLKConfig(&clk) != HAL_OK )
        {
                return;
        }

        __HAL_RCC_RTC_ENABLE();

        hrtc.Instance                   =   RTC;
        hrtc.Init.HourFormat            =   RTC_HOURFORMAT_24;
        hrtc.Init.AsynchPrediv          =   RTC_ASYNCH_PREDIV;
        hrtc.Init.SynchPrediv           =   RTC_SYNCH_PREDIV;
        hrtc.Init.OutPut                =   RTC_OUTPUT_DISABLE;
        hrtc.Init.OutPutPolarity        =   RTC_OUTPUT_POLARITY_HIGH;
        hrtc.Init.OutPutType            =   RTC_OUTPUT_TYPE_OPENDRAIN;

        if( HAL_RTC_Init( &hrtc ) != HAL_OK )
        {
                return;
        }
}


time_t  app_rtc_get( void )
{
                RTC_DateTypeDef         date;
                RTC_TimeTypeDef         time;
                time_t	                raw;
        struct  tm                      s;


        app_rtc_time_read( &time );
        app_rtc_date_read( &date );

        s.tm_sec        =   time.Seconds;
        s.tm_min        =   time.Minutes;
        s.tm_hour       =   time.Hours;
        s.tm_mday       =   date.Date;
        s.tm_mon        =   date.Month;
        s.tm_year       =   date.Year;

        raw             =   mktime( &s );

	return( raw );
}


void    app_rtc_set(                    time_t *                raw     )
{
                RTC_DateTypeDef         date;
                RTC_TimeTypeDef         time;
        struct  tm *                    p;


        p               =   gmtime( raw );

        time.Seconds    =   p->tm_sec;
        time.Minutes    =   p->tm_min;
        time.Hours      =   p->tm_hour;
        date.Date       =   p->tm_mday;
        date.Month      =   p->tm_mon;
        date.Year       =   p->tm_year;

        app_rtc_time_write( &time );
        app_rtc_date_write( &date );
}
