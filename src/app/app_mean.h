/**
  * @file    app_mean.h
  * @brief   Moving Average Filter
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#ifndef APP_MEAN_H
#define APP_MEAN_H


#include <stdint.h>
#include <string.h>


#define	APP_MEAN_BUF_SIZEOF             16


typedef struct  app_mean_s
{
        uint32_t        sum;
        size_t          head;
        uint32_t        buf[ APP_MEAN_BUF_SIZEOF ];
} app_mean_t;


uint32_t app_mean(                              app_mean_t *    p,
                                                uint32_t        sample );


#endif	//APP_MEAN_H
