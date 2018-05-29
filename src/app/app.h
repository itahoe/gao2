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


typedef enum    app_cfg_ctl_e
{
        APP_CFG_CTL_PHY_SET_NEXT,
        APP_CFG_CTL_PHY_SET_PREV,
        APP_CFG_CTL_RATE_SET_NEXT,
        APP_CFG_CTL_RATE_SET_PREV,
        APP_CFG_CTL_PROT_SET_NEXT,
        APP_CFG_CTL_PROT_SET_PREV,

} app_cfg_ctl_t;

typedef enum    app_cfg_chnl_phy_e
{
        APP_CFG_CHNL_PHY_NONE           = 0,
        APP_CFG_CHNL_PHY_RS485,
        //APP_CFG_CHNL_PHY_ADC,
        APP_CFG_CHNL_PHY_MAX,
} app_cfg_chnl_phy_t;

typedef enum    app_cfg_chnl_rate_e
{
        APP_CFG_CHNL_RATE_NONE          = 0,
        APP_CFG_CHNL_RATE_9600,
        APP_CFG_CHNL_RATE_19200,
        APP_CFG_CHNL_RATE_38400,
        APP_CFG_CHNL_RATE_57600,
        APP_CFG_CHNL_RATE_115200,
        APP_CFG_CHNL_RATE_230400,
        APP_CFG_CHNL_RATE_MAX,
} app_cfg_chnl_rate_t;

typedef enum    app_cfg_chnl_protocol_e
{
        APP_CFG_CHNL_PROTOCOL_NONE      = 0,
        APP_CFG_CHNL_PROTOCOL_MODBUS,
        //APP_CFG_CHNL_PROTOCOL_ANALOG,
        APP_CFG_CHNL_PROTOCOL_MAX,
} app_cfg_chnl_protocol_t;


typedef struct  app_cfg_s
{
        app_cfg_chnl_phy_t              phy;
        app_cfg_chnl_rate_t             rate;
        app_cfg_chnl_protocol_t         protocol;
} app_cfg_t;


typedef struct  app_s
{
        app_cfg_t                       cfg[8];
} app_t;


void    app_clock_config( void );
void    app_mpu_config( void );


//void    app_cfg_read(                           size_t          chnl_num );
//void    app_cfg_write(                          size_t          chnl_num );
const   char *  app_cfg_chnl_phy_str_get(       size_t          chnl_num );
const   char *  app_cfg_chnl_rate_str_get(      size_t          chnl_num );
const   char *  app_cfg_chnl_prot_str_get(      size_t          chnl_num );

void    app_cfg_ctl(                            app_cfg_ctl_t   ctl,
                                                size_t          chnl_num );


void    app_rtc_init(                           void                    );
time_t  app_rtc_get(                            void                    );
void    app_rtc_set(                            time_t *        raw     );
void    app_rtc_ctl(                    const   app_rtc_ctl_t   ctl     );

void    app_rtc_bckp_read(                      uint32_t *      data,
                                                size_t          addr,
                                                size_t          cnt     );

void    app_rtc_bckp_write(                     uint32_t *      data,
                                                size_t          addr,
                                                size_t          cnt     );

void    task_sensor(                    const   void *          argument );
void    task_ui(                        const   void *          argument );
void    task_storage(                   const   void *          argument );
void    task_xmit(                      const   void *          argument );


#endif  //APP_H
