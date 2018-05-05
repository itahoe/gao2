/**
  * @file    task_dspl.c
  * @brief   Display services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdbool.h>
#include "cmsis_os.h"
#include "ui_dspl.h"
#include "app_stream.h"
#include "app_trace.h"
#include "app.h"


#define CONF_SER_POLLING_CYCLE_mSEC     10

extern  void    k_TouchUpdate( void );

extern  QueueHandle_t           que_ui_hndl;

static  TimerHandle_t   tmr_touch_hndl;
static  StaticTimer_t   tmr_touch_alloc;


static
void    task_ui_tmr_touch_callback(             TimerHandle_t           tmr )
{
        k_TouchUpdate();
}


static
void    task_ui_tmr_touch_init(         const   TickType_t      period_msec )
{
        const   TickType_t      period_tcks     =   pdMS_TO_TICKS( period_msec );


        tmr_touch_hndl  =     xTimerCreateStatic(       "TMR TOUCH",            //Just a text name, not used by the RTOS kernel.
                                                        period_tcks,            //The timer period in ticks, must be greater than 0.
                                                        pdTRUE,                 //The timers will auto-reload themselves when they expire.
                                                        ( void * ) 0,           //The ID is used to store a count of the number of times the timer has expired, which is initialised to 0.
                                                        task_ui_tmr_touch_callback,  //Each timer calls the same callback when it expires.
                                                        &tmr_touch_alloc );     //Pass in the address of a StaticTimer_t variable, which will hold the data associated with the timer being created.

        if( tmr_touch_hndl == NULL )
        {
                APP_TRACE( "<task_ui> failed to create <tmr_touch>\n" );
        }
        else
        {
                //Start the timer.  No block time is specified, and even if one was it would be ignored because the RTOS scheduler has not yet been started.
                if( xTimerStart( tmr_touch_hndl, 0 ) != pdPASS )
                {
                        APP_TRACE( "<task_ui> failed to start <tmr_touch>\n" ); //The timer could not be set into the Active state.
                }
        }
}


void    task_ui(                        const   void *          argument )
{
        bool                    received;
        TickType_t              polling_cycle_tcks      =   CONF_SER_POLLING_CYCLE_mSEC / portTICK_PERIOD_MS;
        app_stream_t            stream;


        GUI_Init();
        GUI_SetBkColor( GUI_GRAY );
        GUI_Clear();
        GUI_SetLayerVisEx( 1, 0 );
        GUI_SelectLayer( 0 );
        WM_MULTIBUF_Enable( 1 );
        WM_SetCreateFlags( WM_CF_MEMDEV );

        task_ui_tmr_touch_init( 40 );

        ui_dspl_init();

        while( true )
        {
                GUI_Exec();
                received        =   xQueueReceive( que_ui_hndl, &stream, polling_cycle_tcks );
                if( received )
                {
                        if( stream.size < /*CONF_SER4_RECV_BLCK_SIZE_OCT*/ 1024 )
                        {
                                ui_dspl_scr0_update( stream.data, stream.size );
                        }
                        else
                        {
                                APP_TRACE( "<task_ui> stream.size: %d\n", stream.size );
                        }

                        //taskENTER_CRITICAL();
                        //taskEXIT_CRITICAL();
                }

        }
}
