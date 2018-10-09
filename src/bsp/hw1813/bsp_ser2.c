/**
  * @file    bsp_ser2.c
  * @brief   BSP Serial 2
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "bsp_ser.h"
#include "bsp.h"
#include "app_trace.h"


static  UART_HandleTypeDef      huart5;
static  DMA_HandleTypeDef       hdma_uart5_rx;
static  DMA_HandleTypeDef       hdma_uart5_tx;


static
void bsp_ser2_uart_init(                const   size_t                  baud )
{
        huart5.Instance                 =   UART5;
        huart5.Init.BaudRate            =   baud;
        huart5.Init.WordLength          =   UART_WORDLENGTH_8B;
        huart5.Init.StopBits            =   UART_STOPBITS_1;
        huart5.Init.Parity              =   UART_PARITY_NONE;
        huart5.Init.Mode                =   UART_MODE_TX_RX;
        huart5.Init.HwFlowCtl           =   UART_HWCONTROL_NONE;
        huart5.Init.OverSampling        =   UART_OVERSAMPLING_16;

        __HAL_RCC_UART5_CLK_ENABLE();
        __HAL_RCC_UART5_FORCE_RESET();
        __HAL_RCC_UART5_RELEASE_RESET();

        if( HAL_UART_Init( &huart5 ) != HAL_OK )
        {
                APP_TRACE( "ERROR: %s, %d\r\n", __FILE__, __LINE__ );
        }
}


static
void bsp_ser2_uart_io_init( void )
{
        GPIO_InitTypeDef        gpio_rx     =   {    .Pin       =    GPIO_PIN_2,
	                                             .Mode      =    GPIO_MODE_AF_PP,
	                                             .Pull      =    GPIO_PULLUP,
	                                             .Speed     =    GPIO_SPEED_FREQ_LOW,
	                                             .Alternate =    GPIO_AF8_UART5 };

        GPIO_InitTypeDef        gpio_tx     =   {    .Pin       =    GPIO_PIN_12,
	                                             .Mode      =    GPIO_MODE_AF_PP,
	                                             .Pull      =    GPIO_PULLUP,
	                                             .Speed     =    GPIO_SPEED_FREQ_LOW,
	                                             .Alternate =    GPIO_AF8_UART5 };


        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();

        HAL_GPIO_Init( GPIOD, &gpio_rx );
        HAL_GPIO_Init( GPIOC, &gpio_tx );
}


static
void bsp_ser2_uart_dma_rx_init( void )
{
        __HAL_RCC_DMA1_CLK_ENABLE();

        hdma_uart5_rx.Instance                  =   DMA1_Stream0;
        hdma_uart5_rx.Init.Channel              =   DMA_CHANNEL_4;
        hdma_uart5_rx.Init.Direction            =   DMA_PERIPH_TO_MEMORY;
        hdma_uart5_rx.Init.PeriphInc            =   DMA_PINC_DISABLE;
        hdma_uart5_rx.Init.MemInc               =   DMA_MINC_ENABLE;
        hdma_uart5_rx.Init.PeriphDataAlignment  =   DMA_PDATAALIGN_BYTE;
        hdma_uart5_rx.Init.MemDataAlignment     =   DMA_MDATAALIGN_BYTE;
        hdma_uart5_rx.Init.Mode                 =   DMA_CIRCULAR;
        hdma_uart5_rx.Init.Priority             =   DMA_PRIORITY_HIGH;
        hdma_uart5_rx.Init.FIFOMode             =   DMA_FIFOMODE_DISABLE;
        hdma_uart5_rx.Init.FIFOThreshold        =   DMA_FIFO_THRESHOLD_FULL;
        hdma_uart5_rx.Init.MemBurst             =   DMA_MBURST_INC4;
        hdma_uart5_rx.Init.PeriphBurst          =   DMA_PBURST_INC4;

        if( HAL_DMA_Init( &hdma_uart5_rx ) != HAL_OK )
        {
                APP_TRACE( "ERROR: %s, %d\r\n", __FILE__, __LINE__ );
        }

        __HAL_LINKDMA( &huart5, hdmarx, hdma_uart5_rx );
}


static
void bsp_ser2_uart_dma_tx_init( void )
{
        __HAL_RCC_DMA1_CLK_ENABLE();


        hdma_uart5_tx.Instance                  =   DMA1_Stream7;
        hdma_uart5_tx.Init.Channel              =   DMA_CHANNEL_4;
        hdma_uart5_tx.Init.Direction            =   DMA_MEMORY_TO_PERIPH;
        hdma_uart5_tx.Init.PeriphInc            =   DMA_PINC_DISABLE;
        hdma_uart5_tx.Init.MemInc               =   DMA_MINC_ENABLE;
        hdma_uart5_tx.Init.PeriphDataAlignment  =   DMA_PDATAALIGN_BYTE;
        hdma_uart5_tx.Init.MemDataAlignment     =   DMA_MDATAALIGN_BYTE;
        hdma_uart5_tx.Init.Mode                 =   DMA_NORMAL;
        hdma_uart5_tx.Init.Priority             =   DMA_PRIORITY_HIGH;
        hdma_uart5_tx.Init.FIFOMode             =   DMA_FIFOMODE_DISABLE;

        if( HAL_DMA_Init( &hdma_uart5_tx ) != HAL_OK )
        {
                APP_TRACE( "ERROR: %s, %d\r\n", __FILE__, __LINE__ );
        }

        __HAL_LINKDMA( &huart5, hdmatx, hdma_uart5_tx );

}


void bsp_ser2_init(                     const   size_t                  baud )
{
        bsp_ser2_uart_init( baud );
        bsp_ser2_uart_dma_tx_init();
        bsp_ser2_uart_dma_rx_init();
        bsp_ser2_uart_io_init();

        HAL_NVIC_SetPriority(   DMA1_Stream0_IRQn,      BSP_NVIC_PRIO_SER2_DMA_RX, 0 );
        HAL_NVIC_EnableIRQ(     DMA1_Stream0_IRQn );

        HAL_NVIC_SetPriority(   DMA1_Stream7_IRQn,      BSP_NVIC_PRIO_SER2_DMA_TX, 0 );
        HAL_NVIC_EnableIRQ(     DMA1_Stream7_IRQn );

        HAL_NVIC_SetPriority(   UART5_IRQn,            BSP_NVIC_PRIO_SER2_UART, 0 );
        HAL_NVIC_EnableIRQ( UART5_IRQn );
}


void    bsp_ser2_recv(                          uint8_t *           data,
                                                size_t              size )
{
        HAL_UART_Receive_DMA( &huart5, data, size );
}


uint32_t bsp_ser2_dma_recv_ndtr_get( void )
{
        return( huart5.hdmarx->Instance->NDTR );
}


bool    bsp_ser2_xmit(                          uint8_t *               data,
                                                size_t                  size )
{
        HAL_StatusTypeDef       resp    =   HAL_UART_Transmit_DMA( &huart5, data, size );

        return( resp == HAL_OK ? false : true );
}


void    bsp_ser2_uart_isr( void )
{
	HAL_UART_IRQHandler( &huart5 );
}


void bsp_ser2_dma_rx_isr( void )
{
	HAL_DMA_IRQHandler( &hdma_uart5_rx );
}


void    bsp_ser2_dma_tx_isr( void )
{
	HAL_DMA_IRQHandler( &hdma_uart5_tx );
}
