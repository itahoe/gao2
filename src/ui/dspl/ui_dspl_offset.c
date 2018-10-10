/**
  * @file    ui_dspl_offset.c
  * @brief   User Interface - Display
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "DIALOG.h"
#include "app.h"
#include "ui_dspl.h"


extern  int             curr_scrn_idx;

const   int32_t         ui_dspl_offset_min;
const   int32_t         ui_dspl_offset_max;
const   int32_t         ui_dspl_offset_step     = 1000;
static  int32_t         ui_dspl_offset;
static  int32_t         ui_dspl_offset_temp;


int32_t ui_dspl_offset_get( void )
{
        return( ui_dspl_offset );
}


void    ui_dspl_offset_inc( void )
{
        //if( (ui_dspl_offset + ui_dspl_offset_step) < ui_dspl_offset_max )
        {
                ui_dspl_offset  +=  ui_dspl_offset_step;
        }
}

void    ui_dspl_offset_dec( void )
{
        //if( (ui_dspl_offset - ui_dspl_offset_step) > ui_dspl_offset_min )
        {
                ui_dspl_offset  -=  ui_dspl_offset_step;
        }
}
