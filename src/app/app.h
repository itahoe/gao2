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
void    task_ui(                        const   void *          argument );
void    task_recv(                      const   void *          argument );
void    task_xmit(                      const   void *          argument );
void    task_strg(                      const   void *          argument );


#endif  //APP_H
