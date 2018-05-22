/**
  * @file    bsp_ser1.c
  * @brief   BSP MCU UART6
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "bsp_ser.h"
#include "bsp.h"


//static  UART_HandleTypeDef      huart4;
static  UART_HandleTypeDef      huart6;
static  DMA_HandleTypeDef       hdma_uart4_tx;
static  DMA_HandleTypeDef       hdma_uart6_rx;


static
void bsp_ser1_uart_tx_init(             const   size_t                  baud )
{
        huart4.Instance                 =   UART4;
        huart4.Init.BaudRate            =   baud;
        huart4.Init.WordLength          =   UART_WORDLENGTH_8B;
        huart4.Init.StopBits            =   UART_STOPBITS_1;
        huart4.Init.Parity              =   UART_PARITY_NONE;
        huart4.Init.Mode                =   UART_MODE_TX;
        huart4.Init.HwFlowCtl           =   UART_HWCONTROL_NONE;
        huart4.Init.OverSampling        =   UART_OVERSAMPLING_16;

        __HAL_RCC_UART4_CLK_ENABLE();
        __HAL_RCC_UART4_FORCE_RESET();
        __HAL_RCC_UART4_RELEASE_RESET();

        if( HAL_UART_Init( &huart4 ) != HAL_OK )
        {
                APP_TRACE( "ERROR: %s, %d\r\n", __FILE__, __LINE__ );
        }
}


static
void bsp_ser1_uart_rx_init(             const   size_t                  baud )
{
        huart6.Instance                 =   USART6;
        huart6.Init.BaudRate            =   baud;
        huart6.Init.WordLength          =   UART_WORDLENGTH_8B;
        huart6.Init.StopBits            =   UART_STOPBITS_1;
        huart6.Init.Parity              =   UART_PARITY_NONE;
        huart6.Init.Mode                =   UART_MODE_RX;
        huart6.Init.HwFlowCtl           =   UART_HWCONTROL_NONE;
        huart6.Init.OverSampling        =   UART_OVERSAMPLING_16;


        __HAL_RCC_USART6_CLK_ENABLE();
        __HAL_RCC_USART6_FORCE_RESET();
        __HAL_RCC_USART6_RELEASE_RESET();

        if( HAL_UART_Init( &huart6 ) != HAL_OK )
        {
                _Error_Handler( __FILE__, __LINE__ );
        }
}


static
void bsp_ser1_uart_io_init( void )
{
        GPIO_InitTypeDef        gpio_tx     =   {    .Pin       =    GPIO_PIN_10,
	                                             .Mode      =    GPIO_MODE_AF_PP,
	                                             .Pull      =    GPIO_PULLUP,
	                                             .Speed     =    GPIO_SPEED_FREQ_HIGH,
	                                             .Alternate =    GPIO_AF8_UART4 };

        GPIO_InitTypeDef        gpio_rx     =   {    .Pin       =    GPIO_PIN_7,
	                                             .Mode      =    GPIO_MODE_AF_PP,
	                                             .Pull      =    GPIO_PULLUP,
	                                             .Speed     =    GPIO_SPEED_FREQ_HIGH,
	                                             .Alternate =    GPIO_AF8_USART6 };

        __HAL_RCC_GPIOC_CLK_ENABLE();

        HAL_GPIO_Init( GPIOC, &gpio_tx );
        HAL_GPIO_Init( GPIOC, &gpio_rx );
}


static
void bsp_ser1_uart_dma_tx_init( void )
{
        __HAL_RCC_DMA1_CLK_ENABLE();


        hdma_uart4_tx.Instance                  =   DMA1_Stream4;
        hdma_uart4_tx.Init.Channel              =   DMA_CHANNEL_4;
        hdma_uart4_tx.Init.Direction            =   DMA_MEMORY_TO_PERIPH;
        hdma_uart4_tx.Init.PeriphInc            =   DMA_PINC_DISABLE;
        hdma_uart4_tx.Init.MemInc               =   DMA_MINC_ENABLE;
        hdma_uart4_tx.Init.PeriphDataAlignment  =   DMA_PDATAALIGN_BYTE;
        hdma_uart4_tx.Init.MemDataAlignment     =   DMA_MDATAALIGN_BYTE;
        hdma_uart4_tx.Init.Mode                 =   DMA_NORMAL;
        hdma_uart4_tx.Init.Priority             =   DMA_PRIORITY_HIGH;
        hdma_uart4_tx.Init.FIFOMode             =   DMA_FIFOMODE_DISABLE;

        if( HAL_DMA_Init( &hdma_uart4_tx ) != HAL_OK )
        {
                _Error_Handler(__FILE__, __LINE__);
        }

        __HAL_LINKDMA( &huart4, hdmatx, hdma_uart4_tx );

}


static
void bsp_ser1_uart_dma_rx_init( void )
{
        __HAL_RCC_DMA2_CLK_ENABLE();

        hdma_uart6_rx.Instance                  =   DMA2_Stream1;
        hdma_uart6_rx.Init.Channel              =   DMA_CHANNEL_5;
        hdma_uart6_rx.Init.Direction            =   DMA_PERIPH_TO_MEMORY;
        hdma_uart6_rx.Init.PeriphInc            =   DMA_PINC_DISABLE;
        hdma_uart6_rx.Init.MemInc               =   DMA_MINC_ENABLE;
        hdma_uart6_rx.Init.PeriphDataAlignment  =   DMA_PDATAALIGN_BYTE;
        hdma_uart6_rx.Init.MemDataAlignment     =   DMA_MDATAALIGN_BYTE;
        hdma_uart6_rx.Init.Mode                 =   DMA_CIRCULAR;
        hdma_uart6_rx.Init.Priority             =   DMA_PRIORITY_HIGH;
        hdma_uart6_rx.Init.FIFOMode             =   DMA_FIFOMODE_DISABLE;
        hdma_uart6_rx.Init.FIFOThreshold        =   DMA_FIFO_THRESHOLD_FULL;
        hdma_uart6_rx.Init.MemBurst             =   DMA_MBURST_INC4;
        hdma_uart6_rx.Init.PeriphBurst          =   DMA_PBURST_INC4;

        if( HAL_DMA_Init( &hdma_uart6_rx ) != HAL_OK )
        {
                _Error_Handler(__FILE__, __LINE__);
        }

        __HAL_LINKDMA( &huart6, hdmarx, hdma_uart6_rx );
}


bool bsp_ser1_init(                const   size_t                  baud )
{
        bsp_ser1_uart_tx_init( baud );
        bsp_ser1_uart_rx_init( baud );
        bsp_ser1_uart_io_init();
        bsp_ser1_uart_dma_tx_init();
        bsp_ser1_uart_dma_rx_init();

        HAL_NVIC_SetPriority(   DMA1_Stream4_IRQn,      BSP_NVIC_PRIO_SER1_DMA_TX, 0 );
        HAL_NVIC_EnableIRQ(     DMA1_Stream4_IRQn );

        HAL_NVIC_SetPriority(   DMA2_Stream1_IRQn,      BSP_NVIC_PRIO_SER1_DMA_RX, 0 );
        HAL_NVIC_EnableIRQ(     DMA2_Stream1_IRQn );

        HAL_NVIC_SetPriority(   UART4_IRQn,            BSP_NVIC_PRIO_SER1_UART, 0 );
        HAL_NVIC_EnableIRQ( UART4_IRQn );

        HAL_NVIC_SetPriority(   USART6_IRQn,            BSP_NVIC_PRIO_SER1_UART, 0 );
        HAL_NVIC_EnableIRQ( USART6_IRQn );

        return( false );
}


bool bsp_ser1_recv_start(                       uint8_t *           data,
                                                size_t              size )
{
        HAL_UART_Receive_DMA( &huart6, data, size );

        return( false );
}


bool bsp_ser1_recv_stop( void )
{
        return( false );
}


uint32_t bsp_ser1_dma_recv_ndtr_get( void )
{
        return( huart6.hdmarx->Instance->NDTR );
}


bool bsp_ser1_xmit_start(                       uint8_t *               data,
                                                size_t                  size )
{
        HAL_StatusTypeDef       resp    =   HAL_UART_Transmit_DMA( &huart4, data, size );

        return( resp == HAL_OK ? false : true );
}


void bsp_ser1_tx_isr( void )
{
	HAL_UART_IRQHandler( &huart4 );
}

void bsp_ser1_rx_isr( void )
{
        HAL_UART_IRQHandler( &huart6 );
}


void bsp_ser1_dma_tx_isr(                  void            )
{
	HAL_DMA_IRQHandler( &hdma_uart4_tx );
}


void bsp_ser1_dma_rx_isr( void )
{
	HAL_DMA_IRQHandler( &hdma_uart6_rx );
}
