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
#include "app_mean.h"
#include "app_trace.h"
#include "app.h"


#define UI_KEY_CODE_TS100               0x01
#define UI_KEY_CODE_TS101               0x02
#define UI_KEY_CODE_TS102               0x04
#define UI_KEY_CODE_TS103               0x08
#define UI_KEY_CODE_TS104               0x10
#define UI_KEY_CODE_TS105               0x20
#define UI_KEY_CODE_TS106               0x40
#define UI_KEY_CODE_TS107               0x80


extern  void    k_TouchUpdate( void );

extern  QueueHandle_t   que_ui_hndl;

static  TimerHandle_t   tmr_touch_hndl;
static  StaticTimer_t   tmr_touch_alloc;


typedef struct  sens_cal_s
{
        float           x0;
        float           y0;
        float           x1;
        float           y1;
        float           x;
        float           y;
        float           tg;
} sens_cal_t;


sens_cal_t      sens_cal    = { .x0     = 25000,
                                .y0     = 10,
                                .x1     = 209000,
                                .y1     = 200,
                                .x      = 209000 - 25000,
                                .y      = 200 - 10,
                                .tg     = (209000 - 25000) / (200 - 10),
};

/*
sens_cal_t      sens_cal    = { .x0     = 25000,
                                .y0     = 0.01f,
                                .x1     = 209000,
                                .y1     = 0.2f,
                                .x      = 209000 - 25000,
                                .y      = 0.2f - 0.01f,
                                .tg     = (209000 - 25000) / (0.2f - 0.01f),
};
*/

static
float   task_sens_raw_to_uA(            const   int16_t         raw )
{
        const   float           vref_uV                 = 3000000;
        const   float           r_feedback_ohm          = 5600;
        const   float           adc_range               = 65536;
                float           sens_uA;


        sens_uA =   raw * ( vref_uV / (adc_range * r_feedback_ohm) );
        //sens_uA =   (raw *  vref_uV) / (adc_range * r_feedback_ohm);

        return( sens_uA );
}


static
float   task_sens_raw_to_mA(            const   int16_t         raw )
{
        const   float           vref_mV                 = 3000;
        const   float           r_feedback_ohm          = 5600;
        const   float           adc_range               = 65536;
                float           sens_mA;


        sens_mA =   raw * ( vref_mV / (adc_range * r_feedback_ohm) );

        return( sens_mA + 5000 );
}


static
float   task_sens_uA_to_ppm(            const   float                   uA,
                                        const   sens_cal_t *            p )
{
        float           ppm;

        ppm     =   uA / p->tg;
        //ppm     =   uA * p->tg;

        return( ppm - 5000 );
}

static
void    task_sens_cal_1(                const   float                   sens_uA,
                                                sens_cal_t *            p )
{
        p->y1   =   sens_uA;
        p->x    =   p->x1 - p->x0;
        p->y    =   p->y1 - p->y0;
        p->tg   =   p->y / p->x;
}


static
void    task_sens_cal_0(                const   float                   sens_uA,
                                                sens_cal_t *            p )
{
        p->y0   =   sens_uA;
        p->x    =   p->x1 - p->x0;
        p->y    =   p->y1 - p->y0;
        p->tg   =   p->y / p->x;
}


static
void    task_ui_tmr_callback(                   TimerHandle_t           tmr )
{
        k_TouchUpdate();
}


static
void    task_ui_tmr_init(               const   TickType_t      period_msec )
{
        const   TickType_t      period_tcks     =   pdMS_TO_TICKS( period_msec );


        tmr_touch_hndl  =     xTimerCreateStatic(       "TMR UI",               //Just a text name, not used by the RTOS kernel.
                                                        period_tcks,            //The timer period in ticks, must be greater than 0.
                                                        pdTRUE,                 //The timers will auto-reload themselves when they expire.
                                                        ( void * ) 0,           //The ID is used to store a count of the number of times the timer has expired, which is initialised to 0.
                                                        task_ui_tmr_callback,   //Each timer calls the same callback when it expires.
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
        //app_mean_t              sample_filter;
        //app_mean_f32_t          mean_f32;
        app_mean_i16_t          mean_i16;
        //uint32_t                sample_0;
        //uint32_t                sample_1;
        float                   sens_uA;
        float                   sens_ppm;
        int16_t                 sens_i16_raw0;
        int16_t                 sens_i16_raw1;
        int32_t                 ppm;


        GUI_Init();
        //APP_TRACE( "GUI_Init() %d\n", resp );
        //GUI_Clear();
        //GUI_SetLayerVisEx( 1, 0 );
        //GUI_SelectLayer( 0 );
        WM_MULTIBUF_Enable( 1 );
        //WM_SetCreateFlags( WM_CF_MEMDEV );
        //GUI_SetBkColor( GUI_GRAY );

        task_ui_tmr_init( 500 );
        ui_dspl_init();
        ui_keyb_init();
        ui_keyb_start();


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
                                                sens_i16_raw0   =   *( (int16_t *) pipe.data + 2 );
                                                sens_i16_raw1   =   app_mean_i16( &mean_i16, sens_i16_raw0 );

                                                sens_uA         =   task_sens_raw_to_uA( sens_i16_raw1 );
                                                //sens_uA         =   task_sens_raw_to_mA( sens_i16_raw1 );
                                                sens_ppm        =   task_sens_uA_to_ppm( sens_uA, &sens_cal );
                                                ppm             =   (int32_t) sens_ppm;

                                                APP_TRACE( "%3.6f uA, %f ppm, tg:%f, x:%f y:%f\n", sens_uA, sens_ppm, sens_cal.tg, sens_cal.x, sens_cal.y );

                                                ui_dspl_scr0_update( &ppm, 1 );
                                                ui_dspl_scr2_update( &ppm, 1 );
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
                                key             =   ui_keyb_get();
                                //APP_TRACE( "cnt=%d %02X\n", ser2_recv_cnt, key );
                                //APP_TRACE( "%02X \n", key );

                                scrn_idx        =   ui_dspl_scrn_idx_get();

                                switch( key )
                                {
                                        case UI_KEY_CODE_TS103: //0x08:
                                                ui_dspl_scrn_slide( 0 );
                                                break;

                                        case UI_KEY_CODE_TS104: //0x10:
                                                ui_dspl_scrn_slide( 1 );
                                                break;

                                        case UI_KEY_CODE_TS102: //0x04:
                                                ui_dspl_btn_header();
                                                break;

                                        case UI_KEY_CODE_TS101:// 0x02:
                                                switch( scrn_idx )
                                                {
                                                        //case 2: ui_dspl_offset_inc();           break;
                                                        default:                                break;
                                                }
                                                break;

                                        case UI_KEY_CODE_TS106: //0x40:
                                                switch( scrn_idx )
                                                {
                                                        //case 2: ui_dspl_offset_dec();           break;
                                                        default:                                break;
                                                }
                                                break;

                                        case UI_KEY_CODE_TS107: //0x80:
                                                switch( scrn_idx )
                                                {
                                                        //case 2: ui_dspl_offset_mode_toggle();   break;
                                                        case 2: ui_dspl_scr2_mode_next();       break;
                                                        default:                                break;
                                                }
                                                break;

                                        case UI_KEY_CODE_TS100:

                                                switch( ui_dspl_scr2_mode_get() )
                                                {
                                                        case 2:
                                                                task_sens_cal_1( sens_uA, &sens_cal );
                                                                break;

                                                        case 1:
                                                                task_sens_cal_0( sens_uA, &sens_cal );
                                                                break;

                                                        case 0:
                                                        default:
                                                                break;
                                                }

                                                break;

                                        case UI_KEY_CODE_TS105:
                                        default:
                                                break;
                                }
                        }
                }

        }
}
