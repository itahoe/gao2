/**
  * @file    fifo.h
  * @brief   FIFO services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef	FIFO_H
#define	FIFO_H


#include <stdint.h>
#include <stddef.h>


typedef struct  fifo16_s
{
        int16_t *               data;
        size_t                  size;
        size_t                  head;
        size_t                  tile;
}	fifo16_t;


static
void    fifo16_init(                            fifo16_t *      p,
                                                int16_t *       data,
                                        const   size_t          size )
{
        p->data         =   data;
        p->size         =   size;
        p->head         =   0;
        p->tile         =   0;
}


static
void    fifo16_flush(                           fifo16_t *      p )
{
        p->tile = p->head;
}


static
int16_t fifo16_get(                             fifo16_t *      p )
{
        int16_t         data    =   *(p->data + p->tile++);

        p->tile         =   p->tile < p->size ? p->tile : 0;

        return( data );
}


static
void    fifo16_put(                             fifo16_t *      p,
                                                int16_t         data )
{
        p->data[ p->head++ ]    =   data;
        p->head                 =   p->head < p->size ? p->head : 0;
}


static
size_t  fifo16_write(                           fifo16_t *      p,
                                        const   int16_t *       data,
                                                size_t          cnt )
{
        size_t  wr_cnt  = 0;


        while( cnt-- )
        {
                p->data[ p->head++ ]    =   *data++;
                p->head                 =   p->head < p->size ? p->head : 0;
                wr_cnt++;
        }

        return( wr_cnt );
}


static
size_t  fifo16_read(                            fifo16_t *      p,
                                                int16_t *       data )
{
        size_t  cnt     = 0;


        while( p->tile != p->head )
        {
/*
                if( cnt++ >= p->size )
                {
                        break;
                }
*/
                *data++         =   *(p->data + p->tile++);
                p->tile         =   p->tile < p->size ? p->tile : 0;
        }

        return( cnt );
}


#endif	//FIFO_H
