/**
  * @file    app.c
  * @brief   App
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef APP_H
#define APP_H


#include "stm32f7xx_hal.h"
#include "GUI.h"

#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_ts.h"
#include "stm32f769i_discovery_sdram.h"
#include "otm8009a.h"


void    app_config_clock( void );
void    app_config_mpu( void );

void    app_rtc_init( void );
void    app_rtc_date_read(              RTC_DateTypeDef *       date );
void    app_rtc_date_write(             RTC_DateTypeDef *       date );
void    app_rtc_time_read(              RTC_TimeTypeDef *       time );
void    app_rtc_time_write(             RTC_TimeTypeDef *       time );

void    task_ui(                        const   void *          argument );
void    task_recv(                      const   void *          argument );
void    task_xmit(                      const   void *          argument );
void    task_strg(                      const   void *          argument );


#endif  //APP_H
