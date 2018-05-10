/**
  * @file    app_clock.c
  * @brief   Configure MCU clock tree
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdio.h>
#include <stdbool.h>
#include "app.h"


void    app_clock_config( void )
{
        HAL_StatusTypeDef       resp;
        RCC_OscInitTypeDef      osc;
        RCC_ClkInitTypeDef      clk;


        //Enable Power Control clock
        __HAL_RCC_PWR_CLK_ENABLE();

        //The voltage scaling allows optimizing the power consumption when the device is
        //clocked below the maximum system frequency, to update the voltage scaling value
        //regarding system frequency refer to product datasheet.
        __HAL_PWR_VOLTAGESCALING_CONFIG( PWR_REGULATOR_VOLTAGE_SCALE1 );

        //Enable HSE Oscillator and activate PLL with HSE as source
        osc.OscillatorType      =   RCC_OSCILLATORTYPE_HSE;
        osc.HSEState            =   RCC_HSE_ON;
        osc.PLL.PLLState        =   RCC_PLL_ON;
        osc.PLL.PLLSource       =   RCC_PLLSOURCE_HSE;
        osc.PLL.PLLM            =   25;
        osc.PLL.PLLN            =   360;
        osc.PLL.PLLP            =   RCC_PLLP_DIV2;
        osc.PLL.PLLQ            =   7;
        osc.PLL.PLLR            =   6;

        resp    =   HAL_RCC_OscConfig( &osc );
        if( resp != HAL_OK )
        {
                #if defined( NDEBUG )
                NVIC_SystemReset();
                #else
                while( true );
                #endif
        }

        //Activate the OverDrive to reach the 180 MHz Frequency
        resp    =   HAL_PWREx_EnableOverDrive();
        if( resp != HAL_OK )
        {
                #if defined( NDEBUG )
                NVIC_SystemReset();
                #else
                while( true );
                #endif
        }

        //Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
        clk.ClockType           =   ( RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 );
        clk.SYSCLKSource        =   RCC_SYSCLKSOURCE_PLLCLK;
        clk.AHBCLKDivider       =   RCC_SYSCLK_DIV1;
        clk.APB1CLKDivider      =   RCC_HCLK_DIV4;
        clk.APB2CLKDivider      =   RCC_HCLK_DIV2;

        resp    =   HAL_RCC_ClockConfig( &clk, FLASH_LATENCY_5 );
        if( resp != HAL_OK )
        {
                #if defined( NDEBUG )
                NVIC_SystemReset();
                #else
                while( true );
                #endif
        }
}
