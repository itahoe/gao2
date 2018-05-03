/**
  * @file    task_xmit.c
  * @brief   Xmit Task services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdbool.h>
#include "cmsis_os.h"
#include "app.h"


void    task_xmit(                      const   void *          argument )
{
        (void) argument;


        while( true )
        {
                osThreadSuspend( NULL );
        }
}
