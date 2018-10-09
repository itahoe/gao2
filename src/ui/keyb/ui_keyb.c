/**
  * @file    ui_keyb.c
  * @brief   User Interface - Keyboard
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "DIALOG.h"
#include "app.h"
#include "ui_keyb.h"
#include "bsp.h"


static  uint8_t                 ui_keyb[ CFG_SER2_RECV_BLCK_SIZE_OCT ];


void    ui_keyb_init( void )
{
        bsp_ser2_init( CFG_SER2_BAUDRATE );
}


void    ui_keyb_start( void )
{
        bsp_ser2_recv( ui_keyb, CFG_SER2_RECV_BLCK_SIZE_OCT );
}


size_t  ui_keyb_poll( void )
{
        static  size_t          ndtr[2] = { CFG_SER2_RECV_BLCK_SIZE_OCT, CFG_SER2_RECV_BLCK_SIZE_OCT };
                size_t          cnt;

        ndtr[0] =   ndtr[1];
        ndtr[1] =   bsp_ser2_dma_recv_ndtr_get();


        if(             ndtr[0] > ndtr[1] )
        {
                cnt     =   ndtr[0] - ndtr[1];
        }
        else if(        ndtr[0] < ndtr[1] )
        {
                cnt     =   ndtr[1] - ndtr[0];
        }
        else
        {
                cnt     =   0;
        }

        return( cnt );
}


void    ui_keyb_error( void )
{
        ui_keyb_start();
}


uint8_t ui_keyb_get( void )
{
        uint32_t        offset  =   CFG_SER2_RECV_BLCK_SIZE_OCT - bsp_ser2_dma_recv_ndtr_get();

        return( ui_keyb[ offset-1 ] );
}
