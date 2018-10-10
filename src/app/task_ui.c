/**
  * @file    task_dspl.c
  * @brief   Display services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdbool.h>
#include "cmsis_os.h"
#include "ui_dspl.h"
#include "ui_keyb.h"
#include "config.h"
#include "app_pipe.h"
#include "app_trace.h"
#include "app.h"


//#define CONF_SER_POLLING_CYCLE_mSEC     10

extern  void    k_TouchUpdate( void );

extern  QueueHandle_t   que_ui_hndl;

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
        //TickType_t              polling_cycle_tcks      =   CONF_SER_POLLING_CYCLE_mSEC / portTICK_PERIOD_MS;
        TickType_t              polling_cycle_tcks      =   CFG_SER2_POLLING_CYCLE_mSEC / portTICK_PERIOD_MS;
        app_pipe_t              pipe;
        //int                     resp;
        size_t                  ser2_recv_cnt;
        uint8_t                 key;
        int                     scrn_idx;

        //taskENTER_CRITICAL();
        //taskEXIT_CRITICAL();

        GUI_Init();
        //APP_TRACE( "GUI_Init() %d\n", resp );
        //GUI_Clear();
        //GUI_SetLayerVisEx( 1, 0 );
        //GUI_SelectLayer( 0 );
        WM_MULTIBUF_Enable( 1 );
        //WM_SetCreateFlags( WM_CF_MEMDEV );
        //GUI_SetBkColor( GUI_GRAY );

        task_ui_tmr_touch_init( 40 );

        ui_dspl_init();

	//taskENTER_CRITICAL();
        ui_keyb_init();
	//taskEXIT_CRITICAL();

	//taskENTER_CRITICAL();
        ui_keyb_start();
	//taskEXIT_CRITICAL();


        while( true )
        {
                //BSP_LED_Toggle( LED1 );

                BSP_LED_Off( LED1 );
                GUI_Exec();

                received        =   xQueueReceive( que_ui_hndl, &pipe, polling_cycle_tcks );

                BSP_LED_On( LED1 );

                if( received )
                {
                        switch( pipe.tag )
                        {
                                case APP_PIPE_TAG_SENS_01_DATA:
                                        //if( pipe.size < CONF_SER4_RECV_BLCK_SIZE_OCT )
                                        if( pipe.cnt < 1024 )
                                        {
                                                ui_dspl_scr0_update( (uint32_t *) pipe.data, pipe.cnt );
                                                ui_dspl_scr2_update( (uint32_t *) pipe.data, pipe.cnt );
                                        }
                                        else
                                        {
                                                APP_TRACE( "<task_ui> pipe.size: %d\n", pipe.cnt );
                                        }
                                        break;

                                case APP_PIPE_TAG_SER2:
                                        break;

                                default:
                                        break;
                        }
                }
                else
                {
                        ser2_recv_cnt   =   ui_keyb_poll();

                        if( ser2_recv_cnt > 0 )
                        {
                                //APP_TRACE( "<task_ui> ser2_recv_cnt: %d\n", ser2_recv_cnt );
                                key     =   ui_keyb_get();
                                //APP_TRACE( "cnt=%d %02X\n", ser2_recv_cnt, key );
                                //APP_TRACE( "%02X \n", key );

                                scrn_idx        =   ui_dspl_scrn_idx_get();

                                switch( key )
                                {

                                        case 0x08:
                                                ui_dspl_scrn_slide( 0 );
                                                break;

                                        case 0x10:
                                                ui_dspl_scrn_slide( 1 );
                                                break;

                                        case 0x04:
                                                ui_dspl_btn_header();
                                                break;

                                        case 0x02:
                                                switch( scrn_idx )
                                                {
                                                        case 0: ui_dspl_offset_inc();
                                                        default:
                                                                break;
                                                }
                                                break;

                                        case 0x40:
                                                switch( scrn_idx )
                                                {
                                                        case 0: ui_dspl_offset_dec();
                                                        default:
                                                                break;
                                                }
                                                break;

                                        default:
                                                break;
                                }
                        }
                }

        }
}
