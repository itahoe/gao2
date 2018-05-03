/**
  * @file    task_recv.c
  * @brief   Recieve Task services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdbool.h>
#include "app_stream.h"
#include "app_fifo.h"
#include "app_trace.h"
#include "cmsis_os.h"
//#include "app.h"
#include <math.h>


#define CONF_SER_POLLING_CYCLE_mSEC     1000
#define CONF_SER4_RECV_BLCK_SIZE_OCT    1024


static  int16_t         ser4_recv_data[ CONF_SER4_RECV_BLCK_SIZE_OCT ];


static
uint32_t bsp_ser4_dma_recv_ndtr_get( void )
{
        return( 0 );
        //return( 1 );
}


static  app_fifo_t      ser4   =    {   .dma_get        =   bsp_ser4_dma_recv_ndtr_get,
                                        .blck_size      =   CONF_SER4_RECV_BLCK_SIZE_OCT,
                                        .ndtr           =   CONF_SER4_RECV_BLCK_SIZE_OCT,
                                        .data           =   ser4_recv_data,
                                        .tile           =   ser4_recv_data,
                                        .head           =   ser4_recv_data, };


extern  QueueHandle_t           que_recv_hndl;
extern  QueueHandle_t           que_ui_hndl;
extern  QueueHandle_t           que_strg_hndl;


#define MATH_PI         ((double) 3.1415926535897932384626433832795)

static
bool    create_sin(                             app_fifo_t *    p )
{

        const   size_t          smpl_rate_hz    = 500;
        const   size_t          sgnl_freq_hz    = 1;
        const   size_t          period          = smpl_rate_hz / sgnl_freq_hz;
        static  int16_t         phase           = 0;
                int16_t         data;


        p->size         =  0;

p->tile = (p->head >= (p->data + p->blck_size) ? p->data : p->head );

        for( int i = 0; i < 8; i++ )
        {
                if( phase >= period )
                {
                        phase   =   0;
                }

                //data    =   (int16_t) ( sin( 2 * AUDIO_BEEP_MATH_PI * i / lookup_size ) * pow( 2, 12 ) - 1 );
                //data    =   (int16_t) ( sin( 2 * MATH_PI * phase / period ) * pow( 2, 8 ) - 1 );
                data    =   (int16_t) ( sin( 2 * MATH_PI * phase / period ) * 198 - 1 ) + 200;
                phase++;

                if( p->head >= (p->data + p->blck_size) )
                {
                        p->head         =   p->data;
                }

                *( p->head++ )    =   data;

                p->size++;
        }


/*
                //bool            resp            =   false;
                uint32_t        ndtr            =   p->dma_get();
                uint8_t *       head            =   p->data + (p->blck_size - ndtr);


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
                //resp            =   true;
        }
*/

/*
        data            +=  8;
        if( data >= 400 )
        {
                data    =   0;
        }
*/

        return( true );
}


void    task_recv(                      const   void *          argument )
{
        TickType_t              polling_cycle_tcks      =   CONF_SER_POLLING_CYCLE_mSEC / portTICK_PERIOD_MS;
        bool                    received;
        bool                    not_empty;
        app_stream_t            stream;


        (void) argument;
/*
        taskENTER_CRITICAL();
        bsp_ser4_init( CONF_SER4_BAUDRATE );
        bsp_ser4_recv_start( ser4.data, ser4.blck_size );
        taskEXIT_CRITICAL();
*/


        //osDelay( 1000 );


        while( true )
        {
                BSP_LED_Off( LED1 );

                received        =   xQueueReceive( que_recv_hndl, &stream, polling_cycle_tcks );


                if( received )
                {

                        switch( stream.tag )
                        {
                                case APP_PIPE_TAG_SER1:
                                case APP_PIPE_TAG_CLI:
                                        //task_ser4_xmit( stream.head, stream.size );
                                        break;

                                case APP_PIPE_TAG_ERROR:
                                        //taskENTER_CRITICAL();
                                        //bsp_ser4_recv_start( ser4.data, ser4.blck_size );
                                        //taskEXIT_CRITICAL();
                                        break;

                                default:
                                        break;
                        }
                }
                else //queue passed by timeout
                {
                        BSP_LED_On( LED1 );
                        //not_empty       =   app_fifo_rx_hook( &ser4 );
                        not_empty       =   create_sin( &ser4 );

                        if( not_empty )
                        {
                                stream.tag      =   APP_PIPE_TAG_RECV;
                                stream.size     =   ser4.size;
                                stream.data     =   ser4.tile;

                                //APP_TRACE( "%0Xh %d\n", stream.data, stream.size );

                                //for( int try = 0; try < 8; try++ )
                                {
                                        if( pdTRUE != xQueueSend( que_ui_hndl,  &stream, NULL ) )
                                        {
                                                //APP_TRACE( "<task_recv> xQueueSend( que_ui_hndl ) try: %d\n", try );
                                                //APP_TRACE( "<task_recv> xQueueSend( que_ui_hndl ) FAIL\n" );
                                        }
                                        else
                                        {
                                                //break;
                                        }
                                }


                                //for( int try = 0; try < 2; try++ )
                                {
                                        if( pdTRUE != xQueueSend( que_strg_hndl,  &stream, NULL ) )
                                        {
                                                //APP_TRACE( "<task_recv> xQueueSend( que_strg_hndl ) try: %d\n", try );
                                        }
                                        else
                                        {
                                                //break;
                                        }
                                }


                                //xQueueSend( que_cli_hndl,   &stream, NULL );
                        }
                }


        }
}
