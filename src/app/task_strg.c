/**
  * @file    task_strg.c
  * @brief   Storage services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdbool.h>
#include "storage.h"
#include "cmsis_os.h"
#include "app_pipe.h"
#include "app.h"
#include "app_trace.h"


extern  QueueHandle_t           que_strg_hndl;

static  storage_t               log_ch01        =   { .fext   =  "ch01.log", };


void    task_strg(                      const   void *          argument )
{
                app_pipe_t      pipe;
                bool            ready                   =   false;
                bool            err;
                //bool            write_uart2_active      =   false;
                //bool            write_uart1_active      =   false;
        //const   TickType_t      fopen_err_delay_msec    =   100;


	storage_init();

        while( true )
        {
                xQueueReceive( que_strg_hndl, &pipe, portMAX_DELAY );

                if( ready == false )
                {
                        ready   = storage_open( &log_ch01 );

                        if( ready )
                        {
                                BSP_LED_On( LED2 );
                        }
                        else
                        {
                                BSP_LED_Off( LED2 );
                        }
                }
                else
                {
                        err     =   storage_write( &log_ch01, (uint8_t *) pipe.data, pipe.cnt * 2 );
                        ready   =   err ? false : true;
                }

/*
                write_uart1_active      =   storage_open( &log_ser1 );
                err     =   storage_write( &log_ser1, (uint8_t *) stream.data, stream.size*2 );
                APP_TRACE( "storage_open( &log_ser1 )...%s\n", err ? "FAIL" : "OK" );
                if( err )
                {
                        write_uart1_active      =   false;
                        //storage_close( &log_ser1 );
                }

                APP_TRACE( "storage_close( &log_ser1 )\n" );
                storage_close( &log_ser1 );
*/

/*
                switch( stream.tag )
                {
                        case APP_PIPE_TAG_RECV:
                                break;

                        case APP_PIPE_TAG_ERROR:
                                APP_TRACE( "app_task_storage()::APP_PIPE_TAG_ERROR\n" );
                                break;

                        case APP_PIPE_TAG_SER1:
                                break;

                        case APP_PIPE_TAG_STORAGE_CLOSE:
                                //APP_TRACE( "app_task_storage()::xQueueReceive::APP_PIPE_TAG_STORAGE_CLOSE\n" );
                                //storage_close( &log_ser1 );
                                break;

                        case APP_PIPE_TAG_STORAGE_OPEN:
                                //APP_TRACE( "app_task_storage()::xQueueReceive::APP_PIPE_TAG_STORAGE_OPEN\n" );
                                //write_uart1_active      =   storage_open( &log_ser1 );
                                break;

                        case APP_PIPE_TAG_STORAGE_TOGGLE:
                                break;

                        default:
                                break;
                }
*/
                //ui_led_sd_set(  write_uart2_active || write_uart1_active );
        }
}
