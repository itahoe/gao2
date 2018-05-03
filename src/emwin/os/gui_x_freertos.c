/**
  * @file    gui_x_freertos.c
  * @brief   GUI_X
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include "cmsis_os.h"
#include "GUI.h"
#include "app_trace.h"


//volatile GUI_TIMER_TIME OS_TimeMS;



int     GUI_X_GetTime( void )
{
        return( (int) osKernelSysTick() );
}


void    GUI_X_Delay(            int             ms )
{
        osDelay( ms );
}


void    GUI_X_Init( void )
{
        //GUI_X_Init() is called from GUI_Init is a possibility to init
        //some hardware which needs to be up and running before the GUI.
        //If not required, leave this routine blank.

        BSP_TS_Init( 800, 480 );
}


void    GUI_X_ExecIdle( void )
{
        //Called if WM is in idle state
        taskYIELD();
}


//void    GUI_X_Log(      const   char *  s ) { GUI_USE_PARA(s); }
//void    GUI_X_Warn(     const   char *  s ) { GUI_USE_PARA(s); }
//void    GUI_X_ErrorOut( const   char *  s ) { GUI_USE_PARA(s); }

void    GUI_X_Log(      const   char *  s ) { APP_TRACE( "GUI LOG: %s\n", s ); }
void    GUI_X_Warn(     const   char *  s ) { APP_TRACE( "GUI WARN: %s\n", s ); }
void    GUI_X_ErrorOut( const   char *  s ) { APP_TRACE( "GUI ERR: %s\n", s ); }
