/**
  * @file    app_fifo_recv_hook.c
  * @brief   FIFO Recieve Hook
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdio.h>
#include "app_fifo.h"


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
bool app_fifo_rx_hook(                  app_fifo_t *            p )
{
        bool            resp            =   false;
        uint32_t        ndtr            =   p->dma_get();
        int16_t *       head            =   p->data + (p->blck_size - ndtr);


        if( head != p->head )
        {
                if( head < p->head )
                {
                        p->size         =  (p->data + p->blck_size) - p->head;
                        head            =   p->data;
                }
                else
                {
                        p->size         =  head - p->head;
                }

                p->tile         =   p->head;
                p->head         =   head;
                p->ndtr         =   ndtr;
                resp            =   true;
        }

        return( resp );
}
