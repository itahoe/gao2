/**
  * @file    app_mean.c
  * @brief   Moving Average Filter
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "app_mean.h"

/*
uint32_t app_mean(                              app_mean_t *    p,
                                                uint32_t        sample )
{
	if( ++(p->head) >= APP_MEAN_BUF_SIZEOF )
        {
                p->head =   0;
        }

	p->sum                  +=  sample;
	p->sum                  -=  p->buf[ p->head ];
	p->buf[ p->head ]       =   sample;
	return( p->sum );
}
*/

uint32_t app_mean(                              app_mean_t *    p,
                                                uint32_t        sample )
{
        uint32_t        sum     = 0;


	if( p->head >= APP_MEAN_BUF_SIZEOF )
        {
                p->head =   0;
        }

	p->buf[ p->head++ ]       =   sample;

        for( int i = 0; i < APP_MEAN_BUF_SIZEOF; i++ )
        {
                sum     +=  p->buf[ i ];
        }

        return( sum / APP_MEAN_BUF_SIZEOF );
}
