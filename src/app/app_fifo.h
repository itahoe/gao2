/**
  * @file    app_fifo.h
  * @brief   FIFO
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef APP_FIFO_H
#define APP_FIFO_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


typedef uint32_t    ( * comm_dma_get_t )( void );


typedef	struct	app_fifo_s
{
        comm_dma_get_t          dma_get;
        uint32_t                ndtr;
        int16_t *               head;
        int16_t *               tile;
        size_t                  size;
        size_t                  blck_size;
        int16_t *               data;
} app_fifo_t;


bool app_fifo_rx_hook(                  app_fifo_t *            p );


#endif	//APP_FIFO_H
