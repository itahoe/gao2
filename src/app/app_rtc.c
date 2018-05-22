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

        if( date->Year < 70 )
        {
                date->Year      =   70;
        }
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
                time_t	                t;
        struct  tm                      ts;


        app_rtc_time_read( &time );
        app_rtc_date_read( &date );

        ts.tm_sec       =   time.Seconds;
        ts.tm_min       =   time.Minutes;
        ts.tm_hour      =   time.Hours;
        ts.tm_mday      =   date.Date;
        ts.tm_mon       =   date.Month;
        ts.tm_year      =   date.Year;
        ts.tm_isdst     =   0;
        t               =   mktime( &ts );

        //APP_TRACE( "<A> %02d %02d %02d %d\n", time.Hours, time.Minutes, time.Seconds, t );

	return( t );
}


void    app_rtc_set(                    time_t *                t       )
{
                RTC_DateTypeDef         date;
                RTC_TimeTypeDef         time;
        struct  tm *                    ts;


        ts              =   gmtime( t );

        time.Seconds    =   ts->tm_sec;
        time.Minutes    =   ts->tm_min;
        time.Hours      =   ts->tm_hour;
        date.Date       =   ts->tm_mday;
        date.Month      =   ts->tm_mon;
        date.Year       =   ts->tm_year;

        app_rtc_time_write( &time );
        app_rtc_date_write( &date );
}


void    app_rtc_ctl(                    const   app_rtc_ctl_t   ctl     )
{
                time_t	                t;
        struct  tm                      ts;
        struct  tm *                    p;


        RTC_DateTypeDef         date;
        RTC_TimeTypeDef         time;


        app_rtc_time_read( &time );
        app_rtc_date_read( &date );

        //APP_TRACE( "<1> %02d %02d %04d\n", date.Date, date.Month, date.Year );
        //APP_TRACE( "<1> %02d %02d %02d\n", time.Hours, time.Minutes, time.Seconds );

        switch( ctl )
        {
                //case APP_RTC_CTL_YEAR_INCREASE:         date.Year++;    break;
                //case APP_RTC_CTL_YEAR_DECREASE:         date.Year--;    break;
                case APP_RTC_CTL_YEAR_INCREASE:     date.Year       = (date.Year < 136) ? date.Year + 1 :  70;      break;
                case APP_RTC_CTL_YEAR_DECREASE:     date.Year       = (date.Year >  70) ? date.Year - 1 :  70;      break;

                case APP_RTC_CTL_MONTH_INCREASE:        date.Month++;   break;
                case APP_RTC_CTL_MONTH_DECREASE:        date.Month--;   break;
                //case APP_RTC_CTL_MONTH_INCREASE:    date.Month      = (date.Month < 11) ? date.Month + 1 :  0;      break;
                //case APP_RTC_CTL_MONTH_DECREASE:    date.Month      = (date.Month >  0) ? date.Month - 1 : 11;      break;

                case APP_RTC_CTL_DAY_INCREASE:          date.Date++;    break;
                case APP_RTC_CTL_DAY_DECREASE:          date.Date--;    break;

                case APP_RTC_CTL_HOUR_INCREASE:         time.Hours      = (time.Hours < 23) ? time.Hours + 1 :  0;   break;
                case APP_RTC_CTL_HOUR_DECREASE:         time.Hours      = (time.Hours >  0) ? time.Hours - 1 : 23;   break;

                case APP_RTC_CTL_MINUTE_INCREASE:       time.Minutes    = (time.Minutes < 59) ? time.Minutes + 1 :  0; break;
                case APP_RTC_CTL_MINUTE_DECREASE:       time.Minutes    = (time.Minutes >  0) ? time.Minutes - 1 : 59; break;

                case APP_RTC_CTL_SECOND_INCREASE:       time.Seconds    = (time.Seconds < 59) ? time.Seconds + 1 :  0; break;
                case APP_RTC_CTL_SECOND_DECREASE:       time.Seconds    = (time.Seconds >  0) ? time.Seconds - 1 : 59; break;

                default:
                        break;
        }

        //APP_TRACE( "<2> %02d %02d %04d\n", date.Date, date.Month, date.Year );
        //APP_TRACE( "<2> %02d %02d %02d\n", time.Hours, time.Minutes, time.Seconds );

        ts.tm_sec       =   time.Seconds;
        ts.tm_min       =   time.Minutes;
        ts.tm_hour      =   time.Hours;
        ts.tm_mday      =   date.Date;
        ts.tm_mon       =   date.Month;
        ts.tm_year      =   (date.Year < 70) ? 70 : (date.Year >= 135) ? 135 : date.Year;
        ts.tm_isdst     =   0;
        t               =   mktime( &ts );
        p               =   gmtime( &t );
        time.Seconds    =   p->tm_sec;
        time.Minutes    =   p->tm_min;
        time.Hours      =   p->tm_hour;
        date.Date       =   p->tm_mday;
        date.Month      =   p->tm_mon;
        date.Year       =   p->tm_year;

        //APP_TRACE( "<3> %02d %02d %04d\n", date.Date, date.Month, date.Year );
        //APP_TRACE( "<3> %02d %02d %02d\n", time.Hours, time.Minutes, time.Seconds );

        app_rtc_time_write( &time );
        app_rtc_date_write( &date );
}


void    app_rtc_bckp_read(                      uint32_t *      data,
                                                size_t          addr,
                                                size_t          cnt     )
{
        while( cnt-- )
        {
                *data++         = HAL_RTCEx_BKUPRead( &hrtc, addr++ );
        }
}


void    app_rtc_bckp_write(                     uint32_t *      data,
                                                size_t          addr,
                                                size_t          cnt     )
{
        while( cnt-- )
        {
                HAL_RTCEx_BKUPWrite( &hrtc, addr++, *data++ );
        }
}
