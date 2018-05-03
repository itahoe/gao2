/**
  * @file    app_mpu_config.c
  * @brief   Configure MCU clock tree
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdio.h>
#include <stdbool.h>
#include "app.h"


void    app_config_mpu( void )
{
        MPU_Region_InitTypeDef  mpu;

        HAL_MPU_Disable();

        //Configure the MPU attributes as WT for SRAM
        mpu.Enable              =   MPU_REGION_ENABLE;
        mpu.BaseAddress         =   0x20000000;
        mpu.Size                =   MPU_REGION_SIZE_512KB;
        mpu.AccessPermission    =   MPU_REGION_FULL_ACCESS;
        mpu.IsBufferable        =   MPU_ACCESS_NOT_BUFFERABLE;
        mpu.IsCacheable         =   MPU_ACCESS_CACHEABLE;
        mpu.IsShareable         =   MPU_ACCESS_NOT_SHAREABLE;
        mpu.Number              =   MPU_REGION_NUMBER0;
        mpu.TypeExtField        =   MPU_TEX_LEVEL0;
        mpu.SubRegionDisable    =   0x00;
        mpu.DisableExec         =   MPU_INSTRUCTION_ACCESS_ENABLE;

        HAL_MPU_ConfigRegion( &mpu );

        HAL_MPU_Enable( MPU_PRIVILEGED_DEFAULT );
}
