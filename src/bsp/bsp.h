/**
  * @file    bsp.h
  * @brief   Board Support Package
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#ifndef  BSP_H
#define  BSP_H

#include <stdint.h>
#include <stdbool.h>
#include "config.h"
//#include "app_trace.h"


#define BSP_SYSTICK_HZ                  1000ul

#define BSP_NVIC_PRIO_SER1_DMA_RX       9
#define BSP_NVIC_PRIO_SER1_DMA_TX       9
#define BSP_NVIC_PRIO_SER1_RECV_SMBL    11

#define BSP_NVIC_PRIO_SER2_DMA_RX       9
#define BSP_NVIC_PRIO_SER2_DMA_TX       9
#define BSP_NVIC_PRIO_SER2_UART         11

//#define BSP_NVIC_PRIO_SDIO              12
//#define BSP_NVIC_PRIO_SDIO_DMA_RX       13
//#define BSP_NVIC_PRIO_SDIO_DMA_TX       13

#define BSP_NVIC_PRIO_SDIO              3
#define BSP_NVIC_PRIO_SDIO_DMA_RX       4
#define BSP_NVIC_PRIO_SDIO_DMA_TX       4


void    bsp_ser1_init(                  const   size_t                  baud );

void    bsp_ser1_recv(                          uint8_t *               data,
                                                size_t                  size );

uint32_t bsp_ser1_dma_recv_get_ndtr(            void                         );

bool    bsp_ser1_xmit(                          uint8_t *               data,
                                                size_t                  size );

void    bsp_ser1_recv(                          uint8_t *               data,
                                                size_t                  size );

bool    bsp_ser1_isr( void );

void    bsp_ser1_dma_rx_isr( void );

void    bsp_ser1_dma_tx_isr( void );


void    bsp_ser2_init(                  const   size_t                  baud );

void    bsp_ser2_recv(                          uint8_t *               data,
                                                size_t                  size );

bool    bsp_ser2_xmit(                          uint8_t *               data,
                                                size_t                  size );

uint32_t bsp_ser2_dma_recv_ndtr_get( void );

void    bsp_ser2_uart_isr( void );

void    bsp_ser2_dma_rx_isr( void );

void    bsp_ser2_dma_tx_isr( void );


#endif	//BSP_H
