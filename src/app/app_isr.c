/**
  * @file    app_isr.c
  * @brief   App - Interrupt Service Routines
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "cmsis_os.h"
#include "app_trace.h"
//#include "app_isr.h"
#include "app_pipe.h"
#include "app.h"
#include "bsp_ser.h"
//#include "bsp.h"


extern  LTDC_HandleTypeDef      hltdc;
extern  TIM_HandleTypeDef       TimHandle;
extern  SD_HandleTypeDef        uSdHandle;

extern  QueueHandle_t           que_sens_hndl;


void    NMI_Handler( void );
void    HardFault_Handler( void );
void    MemManage_Handler( void );
void    BusFault_Handler( void );
void    UsageFault_Handler( void );
void    DebugMon_Handler( void );
void    SysTick_Handler( void );

void    SDMMC2_IRQHandler( void );
void    DMA2_Stream5_IRQHandler( void );
void    DMA2_Stream0_IRQHandler( void );

void    LTDC_IRQHandler( void );
void    TIM3_IRQHandler( void );
void    USART6_IRQHandler( void );
void    DMA2_Stream6_IRQHandler( void );
void    DMA2_Stream1_IRQHandler( void );

void    hard_fault_handler(                     uint32_t *      arg     );


/**
 * @brief Hard Fault handler
 */
void    hard_fault_handler(                     uint32_t *      arg     )
{
	volatile uint32_t stack_ptr;
	volatile uint32_t stacked_r0;
	volatile uint32_t stacked_r1;
	volatile uint32_t stacked_r2;
	volatile uint32_t stacked_r3;
	volatile uint32_t stacked_r12;
	volatile uint32_t stacked_lr;
	volatile uint32_t stacked_pc;
	volatile uint32_t stacked_psr;

	stack_ptr = (uint32_t)arg;
	stacked_r0 = arg[0];
	stacked_r1 = arg[1];
	stacked_r2 = arg[2];
	stacked_r3 = arg[3];
	stacked_r12 = arg[4];
	stacked_lr = arg[5];
	stacked_pc = arg[6];
	stacked_psr = arg[7];

	APP_TRACE("\r\n--- Hard fault handler ---\n");
	APP_TRACE("\nstck_ptr\t= 0x%08X", stack_ptr);
	APP_TRACE("\nR0\t= 0x%08X", stacked_r0);
	APP_TRACE("\nR1\t= 0x%08X", stacked_r1);
	APP_TRACE("\nR2\t= 0x%08X", stacked_r2);
	APP_TRACE("\nR3\t= 0x%08X", stacked_r3);
	APP_TRACE("\nR12\t= 0x%08X", stacked_r12);
	APP_TRACE("\nLR[R14]\t= 0x%08X\tsubroutine call return address", stacked_lr);
	APP_TRACE("\nPC[R15]\t= 0x%08X\tprogram counter", stacked_pc);
	APP_TRACE("\nPSR\t= 0x%08X", stacked_psr);
	APP_TRACE("\nBFAR\t= 0x%08X", (uint32_t)(*((volatile uint32_t *)(0xE000ED38))));
	APP_TRACE("\nCFSR\t= 0x%08X", (uint32_t)(*((volatile uint32_t *)(0xE000ED28))));
	APP_TRACE("\nHFSR\t= 0x%08X", (uint32_t)(*((volatile uint32_t *)(0xE000ED2C))));
	APP_TRACE("\nDFSR\t= 0x%08X", (uint32_t)(*((volatile uint32_t *)(0xE000ED30))));
	APP_TRACE("\nAFSR\t= 0x%08X", (uint32_t)(*((volatile uint32_t *)(0xE000ED3C))));
	APP_TRACE("\nSCB_SHCSR\t= 0x%08X", SCB->SHCSR);
	// memstat();
	__asm volatile ("bkpt #0\n");         // Break into the debugger
	while(1);
}


/******************************************************************************/
/*            Cortex-M7 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void    NMI_Handler( void )
{
	#ifdef  NDEBUG
	NVIC_SystemReset();
	#else
        while( 1 );
	#endif //NDEBUG
}


/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void    HardFault_Handler( void )
{
        BSP_LED_On( LED2 );

	#ifdef  NDEBUG
	NVIC_SystemReset();
	#else
	asm volatile
	(
	        "TST	LR,		#4			\n"
	        "ITE	EQ					\n"
	        "MRSEQ	R0,		MSP			\n"
	        "MRSNE	R0,		PSP			\n"
	        "B		hard_fault_handler"
	);
	#endif //NDEBUG
}


/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void    MemManage_Handler( void )
{
	#ifdef  NDEBUG
	NVIC_SystemReset();
	#else
        while( 1 );
	#endif //NDEBUG
}


/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void    BusFault_Handler( void )
{
	#ifdef  NDEBUG
	NVIC_SystemReset();
	#else
        while( 1 );
	#endif //NDEBUG
}


/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void    UsageFault_Handler( void )
{
	#ifdef  NDEBUG
	NVIC_SystemReset();
	#else
        while( 1 );
	#endif //NDEBUG
}


/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void    DebugMon_Handler( void )
{
	#ifdef  NDEBUG
	NVIC_SystemReset();
	#else
        while( 1 );
	#endif //NDEBUG
}


/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void    SysTick_Handler( void )
{
        osSystickHandler();
}


/******************************************************************************/
/*                 STM32F7xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f7xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void    TIM3_IRQHandler( void )
{
        HAL_TIM_IRQHandler( &TimHandle );
}


/**
  * @brief  This function handles LTDC global interrupt request.
  * @param  None
  * @retval None
  */
void    LTDC_IRQHandler( void )
{
        HAL_LTDC_IRQHandler( &hltdc );
}


/******************************************************************************/
/* uSD Card Interrupt Handler's                                               */
/******************************************************************************/
/**
 * @brief Handles SD2 card interrupt request.
 * @retval None
 */
void    SDMMC2_IRQHandler( void )
{
        //HAL_SD_IRQHandler( &uSdHandle );
}


/**
 * @brief Handles SDMMC2 DMA Tx transfer interrupt request.
 * @retval None
 */
void    DMA2_Stream5_IRQHandler( void )
{
        //HAL_DMA_IRQHandler( uSdHandle.hdmatx );
}


/**
 * @brief Handles SDMMC2 DMA Rx transfer interrupt request.
 * @retval None
 */
void    DMA2_Stream0_IRQHandler( void )
{
        //HAL_DMA_IRQHandler( uSdHandle.hdmarx );
}



/******************************************************************************/
/* SER1 Interrupt Handler's                                                   */
/******************************************************************************/
void    USART6_IRQHandler( void )
{
        app_pipe_t      pipe    =   {   .tag            =   APP_PIPE_TAG_SER1_IDLE,
                                        .data           =   (void *) 0,
                                        .cnt            =   0 };

        bool    valid;

        valid           =   bsp_ser1_isr();

        pipe.cnt        =   bsp_ser1_dma_recv_get_ndtr();

        if( valid )
        {
                pipe.tag        =   APP_PIPE_TAG_SER1_IDLE;
                xQueueSendFromISR( que_sens_hndl, &pipe, NULL );
        }
        else
        {
                pipe.tag        =   APP_PIPE_TAG_SER1_ERR;
                xQueueSendFromISR( que_sens_hndl, &pipe, NULL );
        }
}


void    DMA2_Stream6_IRQHandler( void )
{
        bsp_ser1_dma_tx_isr();
}


void    DMA2_Stream1_IRQHandler( void )
{
        bsp_ser1_dma_rx_isr();
}
