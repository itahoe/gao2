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


        /*##-1- Configure the RTC peripheral #######################################*/
        /* Configure RTC prescaler and RTC data registers */
        /* RTC configured as follow:
        - Hour Format    = Format 24
        - Asynch Prediv  = Value according to source clock
        - Synch Prediv   = Value according to source clock
        - OutPut         = Output Disable
        - OutPutPolarity = High Polarity
        - OutPutType     = Open Drain */
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


void    app_rtc_date_read(              RTC_DateTypeDef *       date )
{
        HAL_RTC_GetDate( &hrtc, date, FORMAT_BIN );

        if( (date->Date == 0) || (date->Month == 0))
        {
                date->Date = date->Month = 1;
        }
}


void    app_rtc_date_write(             RTC_DateTypeDef *       date )
{
        HAL_RTC_SetDate( &hrtc, date, FORMAT_BIN );
}


void    app_rtc_time_read(              RTC_TimeTypeDef *       time )
{
        HAL_RTC_GetTime( &hrtc, time, FORMAT_BIN );
}


void    app_rtc_time_write(             RTC_TimeTypeDef *       time )
{
        time->StoreOperation    =   0;
        time->SubSeconds        =   0;
        time->DayLightSaving    =   0;
        HAL_RTC_SetTime( &hrtc, time, FORMAT_BIN );
}
