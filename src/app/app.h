/**
  * @file    app.c
  * @brief   Application Header
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef APP_H
#define APP_H


#include <time.h>
#include "app_trace.h"
#include "stm32f7xx_hal.h"
#include "GUI.h"

#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_ts.h"
#include "stm32f769i_discovery_sdram.h"
#include "otm8009a.h"



typedef enum    app_rtc_ctl_e
{
        APP_RTC_CTL_YEAR_INCREASE,
        APP_RTC_CTL_YEAR_DECREASE,
        APP_RTC_CTL_MONTH_INCREASE,
        APP_RTC_CTL_MONTH_DECREASE,
        APP_RTC_CTL_DAY_INCREASE,
        APP_RTC_CTL_DAY_DECREASE,
        APP_RTC_CTL_HOUR_INCREASE,
        APP_RTC_CTL_HOUR_DECREASE,
        APP_RTC_CTL_MINUTE_INCREASE,
        APP_RTC_CTL_MINUTE_DECREASE,
        APP_RTC_CTL_SECOND_INCREASE,
        APP_RTC_CTL_SECOND_DECREASE,
} app_rtc_ctl_t;


void    app_clock_config( void );
void    app_mpu_config( void );

void    app_rtc_init(                           void                    );
time_t  app_rtc_get(                            void                    );
void    app_rtc_set(                            time_t *        raw     );
void    app_rtc_ctl(                    const   app_rtc_ctl_t   ctl     );

void    task_ui(                        const   void *          argument );
void    task_recv(                      const   void *          argument );
void    task_xmit(                      const   void *          argument );
void    task_strg(                      const   void *          argument );


#endif  //APP_H
