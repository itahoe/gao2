/**
  * @file    app.c
  * @brief   Application
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include <time.h>
#include <stdbool.h>
#include "app.h"
#include "app_trace.h"
#include "app_pipe.h"
#include "cmsis_os.h"


#define TASK_STACK_SIZE_UI_WRDS                 512
#define TASK_STACK_SIZE_SENS_WRDS               256
#define TASK_STACK_SIZE_XMIT_WRDS               configMINIMAL_STACK_SIZE
#define TASK_STACK_SIZE_STRG_WRDS               256

#define TASK_PRIO_UI                            osPriorityNormal
#define TASK_PRIO_SENS                          osPriorityHigh
#define TASK_PRIO_XMIT                          osPriorityNormal
#define TASK_PRIO_STRG                          osPriorityNormal

#define QUE_SIZE_SENS_WRDS                      8
#define QUE_SIZE_UI_WRDS                        32
#define QUE_SIZE_STRG_WRDS                      8


        void    k_TouchUpdate( void );

        //app_t                   app;


        //time_t                  time_dat        =   0;

        osThreadId              task_hndl_ui;
        osThreadId              task_hndl_sens;
        osThreadId              task_hndl_xmit;
        osThreadId              task_hndl_strg;

        osStaticThreadDef_t     task_tcb_ui;
        osStaticThreadDef_t     task_tcb_sens;
        osStaticThreadDef_t     task_tcb_xmit;
        osStaticThreadDef_t     task_tcb_strg;

        uint32_t                task_stck_ui[           TASK_STACK_SIZE_UI_WRDS         ];
        uint32_t                task_stck_sens[         TASK_STACK_SIZE_SENS_WRDS       ];
        uint32_t                task_stck_xmit[         TASK_STACK_SIZE_XMIT_WRDS       ];
        uint32_t                task_stck_strg[         TASK_STACK_SIZE_STRG_WRDS       ];

        QueueHandle_t           que_sens_hndl;
        osStaticMessageQDef_t   que_sens_qcb;
        uint8_t                 que_sens_alloc[         QUE_SIZE_SENS_WRDS * sizeof( app_pipe_t ) ];

        QueueHandle_t           que_ui_hndl;
        osStaticMessageQDef_t   que_ui_qcb;
        uint8_t                 que_ui_alloc[           QUE_SIZE_UI_WRDS * sizeof( app_pipe_t ) ];

        //osMessageQId            que_ser4_hndl;
        QueueHandle_t           que_strg_hndl;
        osStaticMessageQDef_t   que_strg_qcb;
        uint8_t                 que_strg_alloc[         QUE_SIZE_STRG_WRDS * sizeof( app_pipe_t ) ];


        uint8_t         SelLayer        =   0;
extern  uint8_t         I2C_Address;
        TS_StateTypeDef TS_State        = {0};


/**
  * @brief  Read the coordinate of the point touched and assign their
  *         value to the variables u32_TSXCoordinate and u32_TSYCoordinate
  * @param  None
  * @retval None
  */
void k_TouchUpdate( void )
{
        static  GUI_PID_STATE   TS_State        = {0, 0, 0, 0};
        __IO    TS_StateTypeDef ts;
                uint16_t        xDiff,
                                yDiff;


        BSP_TS_GetState( (TS_StateTypeDef *) &ts );

        if( (ts.touchX[0] >= LCD_GetXSize()) || (ts.touchY[0] >= LCD_GetYSize()) )
        {
                ts.touchX[0]    =   0;
                ts.touchY[0]    =   0;
        }

        xDiff   = (TS_State.x > ts.touchX[0]) ? (TS_State.x - ts.touchX[0]) : (ts.touchX[0] - TS_State.x);
        yDiff   = (TS_State.y > ts.touchY[0]) ? (TS_State.y - ts.touchY[0]) : (ts.touchY[0] - TS_State.y);

        //if( (TS_State.Pressed != ts.touchDetected ) || (xDiff > 20 ) || (yDiff > 20) )
        if( (TS_State.Pressed != ts.touchDetected ) || (xDiff > 10 ) || (yDiff > 10) )
        {
                TS_State.Pressed        =   ts.touchDetected;
                TS_State.Layer          =   SelLayer;
                if( ts.touchDetected )
                {
                        TS_State.x      =   ts.touchX[0];

                        if( I2C_Address == TS_I2C_ADDRESS )
                        {
/*
                                if( ts.touchY[0] < 240 )
                                {
                                        TS_State.y      =   ts.touchY[0];
                                }
                                else
                                {
                                        TS_State.y      =   (ts.touchY[0] * 480) / 445;
                                }
*/
                                TS_State.y      =   ts.touchY[0];
                        }
                        else
                        {
                                TS_State.y      =   ts.touchY[0];
                        }

                        GUI_TOUCH_StoreStateEx( &TS_State );
                }
                else
                {
                        GUI_TOUCH_StoreStateEx( &TS_State );
                        TS_State.x      =   0;
                        TS_State.y      =   0;
                }
        }
}


/**
  * @brief  Initializes the STM32F469I-DISCO's LCD and LEDs resources.
  * @param  None
  * @retval None
  */
static
void    BSP_Config( void )
{
        BSP_LED_Init( LED1 );
        BSP_LED_Init( LED2 );

        __HAL_RCC_CRC_CLK_ENABLE();     //Enable CRC to Unlock GUI
        __HAL_RCC_BKPSRAM_CLK_ENABLE(); //Enable Back up SRAM
}


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main( void )
{
        app_mpu_config();

        //@brief  CPU L1-Cache enable.
        //SCB_EnableICache();     //Enable I-Cache
        //SCB_EnableDCache();     //Enable D-Cache

        //      STM32F7xx HAL library initialization:
        //      - Configure the Flash prefetch, instruction and Data caches
        //      - Configure the Systick to generate an interrupt each 1 msec
        //      - Set NVIC Group Priority to 4
        //      - Global MSP (MCU Support Package) initialization
        HAL_Init();

        app_clock_config();     //Configure the system clock to 180 MHz

        BSP_Config();           //Initialize LCD and LEDs

        app_rtc_init();

        //HAL_InitTick( 0xFF );

        BSP_SDRAM_Init();

        osMessageQStaticDef( SENS, 8, app_pipe_t , que_sens_alloc, &que_sens_qcb );
        que_sens_hndl           =   osMessageCreate( osMessageQ( SENS ), NULL );

        osMessageQStaticDef( UI,   8, app_pipe_t , que_ui_alloc, &que_ui_qcb );
        que_ui_hndl             =   osMessageCreate( osMessageQ( UI   ), NULL );

        osMessageQStaticDef( STRG, 8, app_pipe_t , que_strg_alloc, &que_strg_qcb );
        que_strg_hndl           =   osMessageCreate( osMessageQ( STRG ), NULL );


        osThreadStaticDef( UI,   task_ui,       TASK_PRIO_UI,     0, TASK_STACK_SIZE_UI_WRDS,   task_stck_ui,   &task_tcb_ui   );
        task_hndl_ui            =   osThreadCreate( osThread( UI   ),   NULL );

        osThreadStaticDef( SENS, task_sensor,   TASK_PRIO_SENS,   0, TASK_STACK_SIZE_SENS_WRDS, task_stck_sens, &task_tcb_sens );
        task_hndl_sens          =   osThreadCreate( osThread( SENS ),   NULL );

        osThreadStaticDef( XMIT, task_xmit,     TASK_PRIO_XMIT,   0, TASK_STACK_SIZE_XMIT_WRDS, task_stck_xmit, &task_tcb_xmit );
        task_hndl_xmit          =   osThreadCreate( osThread( XMIT ),   NULL );

        osThreadStaticDef( STRG, task_storage,  TASK_PRIO_STRG,   0, TASK_STACK_SIZE_STRG_WRDS, task_stck_strg, &task_tcb_strg );
        task_hndl_strg          =   osThreadCreate( osThread( STRG ),   NULL );

        osKernelStart();        //Start scheduler

        while( true )
        {
                #ifdef  NDEBUG
                NVIC_SystemReset();
                #else
                __asm volatile ("bkpt #0\n");   // Break into the debugger
                while( true );
                #endif //NDEBUG
        }
}
