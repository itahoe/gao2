/**
  * @file    bsp_ser1.c
  * @brief   Serial 1 port services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "app_trace.h"
#include "bsp.h"
#include "bsp_ser.h"


static  USART_TypeDef * const   usart           =   USART6;
static  DMA_TypeDef *   const   dma_rx          =   DMA2;
static  DMA_TypeDef *   const   dma_tx          =   DMA2;


static
void bsp_ser1_io_init( void )
{
        LL_GPIO_InitTypeDef     pin_txd = {     .Pin            = LL_GPIO_PIN_6,
                                                .Mode           = LL_GPIO_MODE_ALTERNATE,
                                                .Speed          = LL_GPIO_SPEED_FREQ_LOW,
                                                .OutputType     = LL_GPIO_OUTPUT_PUSHPULL,
                                                .Pull           = LL_GPIO_PULL_NO,
                                                .Alternate      = LL_GPIO_AF_8 };

        LL_GPIO_InitTypeDef     pin_rxd = {     .Pin            = LL_GPIO_PIN_7,
                                                .Mode           = LL_GPIO_MODE_ALTERNATE,
                                                .Speed          = LL_GPIO_SPEED_FREQ_LOW,
                                                .OutputType     = LL_GPIO_OUTPUT_PUSHPULL,
                                                .Pull           = LL_GPIO_PULL_NO,
                                                .Alternate      = LL_GPIO_AF_8 };

        LL_GPIO_InitTypeDef     pin_dir = {     .Pin            = LL_GPIO_PIN_3,
                                                .Mode           = LL_GPIO_MODE_OUTPUT,
                                                .Speed          = LL_GPIO_SPEED_FREQ_LOW,
                                                .OutputType     = LL_GPIO_OUTPUT_PUSHPULL,
                                                .Pull           = LL_GPIO_PULL_DOWN,
                                                .Alternate      = LL_GPIO_AF_0 };


        LL_AHB1_GRP1_EnableClock( LL_AHB1_GRP1_PERIPH_GPIOC );
        LL_AHB1_GRP1_EnableClock( LL_AHB1_GRP1_PERIPH_GPIOJ );

        LL_GPIO_Init( GPIOC, &pin_txd );
        LL_GPIO_Init( GPIOC, &pin_rxd );
        LL_GPIO_Init( GPIOJ, &pin_dir );
}


static
void    bsp_ser1_dma_init( void )
{
/*
        huart6_dma_tx.Instance                  =   DMA2_Stream6;
        huart6_dma_tx.Init.Channel              =   DMA_CHANNEL_5;
        huart6_dma_tx.Init.Direction            =   DMA_MEMORY_TO_PERIPH;
        huart6_dma_tx.Init.PeriphInc            =   DMA_PINC_DISABLE;
        huart6_dma_tx.Init.MemInc               =   DMA_MINC_ENABLE;
        huart6_dma_tx.Init.PeriphDataAlignment  =   DMA_PDATAALIGN_BYTE;
        huart6_dma_tx.Init.MemDataAlignment     =   DMA_MDATAALIGN_BYTE;
        huart6_dma_tx.Init.Mode                 =   DMA_NORMAL;
        huart6_dma_tx.Init.Priority             =   DMA_PRIORITY_LOW;
        huart6_dma_tx.Init.FIFOMode             =   DMA_FIFOMODE_DISABLE;
        huart6_dma_tx.Init.FIFOThreshold        =   DMA_FIFO_THRESHOLD_FULL;
        huart6_dma_tx.Init.MemBurst             =   DMA_MBURST_INC4;
        huart6_dma_tx.Init.PeriphBurst          =   DMA_PBURST_INC4;
        HAL_DMA_Init( &huart6_dma_tx );
        __HAL_LINKDMA( &huart6, hdmatx, huart6_dma_tx );
        //HAL_NVIC_SetPriority(   DMA2_Stream6_IRQn,      BSP_NVIC_PRIO_SER1_DMA_TX, 0 );
        //HAL_NVIC_EnableIRQ(     DMA2_Stream6_IRQn );
*/

        LL_AHB1_GRP1_EnableClock( LL_AHB1_GRP1_PERIPH_DMA2 );
}


static
void    bsp_ser1_uart_init(             const   size_t          baudrate    )
{
        LL_USART_InitTypeDef    cfg     = {     .BaudRate            = baudrate,
                                                .DataWidth           = LL_USART_DATAWIDTH_8B,
                                                .StopBits            = LL_USART_STOPBITS_1,
                                                .Parity              = LL_USART_PARITY_NONE,
                                                .TransferDirection   = LL_USART_DIRECTION_TX_RX,
                                                .HardwareFlowControl = LL_USART_HWCONTROL_NONE,
                                                .OverSampling        = LL_USART_OVERSAMPLING_16 };


        LL_APB2_GRP1_EnableClock(       LL_APB2_GRP1_PERIPH_USART6      );
        LL_APB2_GRP1_ForceReset(        LL_APB2_GRP1_PERIPH_USART6      );
        LL_APB2_GRP1_ReleaseReset(      LL_APB2_GRP1_PERIPH_USART6      );
        LL_RCC_SetUSARTClockSource(     LL_RCC_USART6_CLKSOURCE_PCLK2   );
        LL_USART_Init(                  usart,  &cfg                    );
        LL_USART_Enable(                usart                           );
}


void    bsp_ser1_init(                  const   size_t          baud )
{
        bsp_ser1_uart_init( baud );
        bsp_ser1_io_init();
        bsp_ser1_dma_init();

        LL_USART_EnableIT_IDLE(         usart                           );
        LL_USART_EnableIT_ERROR(        usart                           );

        NVIC_SetPriority(               USART6_IRQn, BSP_NVIC_PRIO_SER1_RECV_SMBL );
        NVIC_EnableIRQ(                 USART6_IRQn                     );

        NVIC_SetPriority(               DMA2_Stream6_IRQn, BSP_NVIC_PRIO_SER1_DMA_TX );
        NVIC_EnableIRQ(                 DMA2_Stream6_IRQn                            );

        NVIC_SetPriority(               DMA2_Stream2_IRQn, BSP_NVIC_PRIO_SER1_DMA_RX );
        NVIC_EnableIRQ(                 DMA2_Stream2_IRQn                            );
}


static
void    bsp_ser1_xfer_dir_set(          bool            dir_tx  )
{
        if( dir_tx )
        {
                LL_USART_DisableDirectionRx( usart );
                LL_USART_EnableDirectionTx( usart );
                LL_GPIO_SetOutputPin( GPIOJ, LL_GPIO_PIN_3 );
        }
        else
        {
                LL_GPIO_ResetOutputPin( GPIOJ, LL_GPIO_PIN_3  );
                LL_USART_DisableDirectionTx( usart );
                LL_USART_EnableDirectionRx( usart );
        }
}


/******************************************************************************/
/* Transmit related                                                           */
/******************************************************************************/

bool bsp_ser1_xmit(                             uint8_t *               data,
                                                size_t                  size )
{
        bsp_ser1_xfer_dir_set( true );

        while( size-- )
        {
                while( !LL_USART_IsActiveFlag_TXE( usart ) );
                LL_USART_TransmitData8( usart, *data++ );
        }

        while( !LL_USART_IsActiveFlag_TC( usart ) );

        bsp_ser1_xfer_dir_set( false );

        return( false );
}


/******************************************************************************/
/* Receive related                                                            */
/******************************************************************************/

void    bsp_ser1_recv(                          uint8_t *           data,
                                                size_t              size )
{
        //const   uint32_t        stream  =   LL_DMA_STREAM_1;
        const   uint32_t        stream  =   LL_DMA_STREAM_2;

        LL_DMA_InitTypeDef      cfg     = {     .PeriphOrM2MSrcAddress  = (uint32_t) LL_USART_DMA_GetRegAddr( usart, LL_USART_DMA_REG_DATA_RECEIVE ),
                                                .MemoryOrM2MDstAddress  = (uint32_t) data,
                                                .Direction              = LL_DMA_DIRECTION_PERIPH_TO_MEMORY,
                                                .Mode                   = LL_DMA_MODE_NORMAL,
                                                .PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT,
                                                .MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT,
                                                .PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE,
                                                .MemoryOrM2MDstDataSize = LL_DMA_PDATAALIGN_BYTE,
                                                .NbData                 = size,
                                                .Priority               = LL_DMA_PRIORITY_HIGH,
                                                .FIFOMode               = LL_DMA_FIFOMODE_DISABLE,
                                                .Channel                = LL_DMA_CHANNEL_5 };


        bsp_ser1_xfer_dir_set( false );

        LL_DMA_DeInit(                  dma_rx, stream                  );
        LL_DMA_Init(                    dma_rx, stream, &cfg            );
        LL_DMA_EnableIT_TE(             dma_rx, stream                  );
        LL_USART_EnableDMAReq_RX(       usart                           );
        LL_DMA_EnableStream(            dma_rx, stream                  );
}


uint32_t bsp_ser1_dma_recv_get_ndtr( void )
{
        //return( DMA2_Stream1->NDTR );
        return( DMA2_Stream2->NDTR );
}


/******************************************************************************/
/* Interrupt Service Routines                                                 */
/******************************************************************************/

bool bsp_ser1_isr( void )
{
        bool    valid   = false;


        if( LL_USART_IsActiveFlag_IDLE( usart ) )
        {
                LL_USART_ClearFlag_IDLE( usart );
                valid   = true;
        }

        if( LL_USART_IsActiveFlag_FE( usart ) )
        {
                LL_USART_ClearFlag_FE( usart );
                valid   = false;
        }

        if( LL_USART_IsActiveFlag_PE( usart ) )
        {
                LL_USART_ClearFlag_PE( usart );
                valid   = false;
        }

        if( LL_USART_IsActiveFlag_NE( usart ) )
        {
                LL_USART_ClearFlag_NE( usart );
                valid   = false;
        }

        return( valid );
}


void bsp_ser1_dma_tx_isr( void )
{
        //HAL_DMA_IRQHandler( huart6.hdmatx );
        APP_TRACE( "bsp_ser1_dma_tx_isr()\n" );
}


void bsp_ser1_dma_rx_isr( void )
{
        //HAL_DMA_IRQHandler( huart6.hdmarx );
        APP_TRACE( "bsp_ser1_dma_rx_isr()\n" );
}
