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

//#define BSP_NVIC_PRIO_SDIO              12
//#define BSP_NVIC_PRIO_SDIO_DMA_RX       13
//#define BSP_NVIC_PRIO_SDIO_DMA_TX       13

#define BSP_NVIC_PRIO_SDIO              3
#define BSP_NVIC_PRIO_SDIO_DMA_RX       4
#define BSP_NVIC_PRIO_SDIO_DMA_TX       4


#endif	//BSP_H
