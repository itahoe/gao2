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


typedef struct  app_mean_u32_s
{
        uint32_t        sum;
        size_t          head;
        uint32_t        buf[ APP_MEAN_BUF_SIZEOF ];
} app_mean_u32_t;


typedef struct  app_mean_i16_s
{
        int16_t         sum;
        size_t          head;
        int16_t         buf[ APP_MEAN_BUF_SIZEOF ];
} app_mean_i16_t;


typedef struct  app_mean_f32_s
{
        float           sum;
        size_t          head;
        float           buf[ APP_MEAN_BUF_SIZEOF ];
} app_mean_f32_t;


uint32_t app_mean(                              app_mean_u32_t *        p,
                                                uint32_t                sample );

int16_t app_mean_i16(                           app_mean_i16_t *        p,
                                                int16_t                 sample );

float   app_mean_f32(                           app_mean_f32_t *        p,
                                                float                   sample );


#endif	//APP_MEAN_H
