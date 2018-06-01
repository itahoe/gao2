/**
  * @file    ui_dspl_scr1.c
  * @brief   User Interface - Screen 1
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdlib.h>
#include <string.h>
#include "DIALOG.h"
#include "ui_dspl.h"
#include "float16.h"
#include <math.h>
#include <float.h>


static  WM_HWIN                 hWin;
//static  GRAPH_DATA_Handle       hGraphData;
//static  GRAPH_SCALE_Handle      hGraphScaleV;   // Handle of vertical scale
//static  GRAPH_SCALE_Handle      hGraphScaleH;   // Handle of horizontal scale
//static  int                     graph_data_offset_y;


void    ui_dspl_scr1_cb(                        WM_MESSAGE *    pMsg )
{
        WM_HWIN         hItem;
        int             NCode;
        int             Id;


        switch( pMsg->MsgId )
        {
                case WM_NOTIFY_PARENT:
                        Id      =   WM_GetId( pMsg->hWinSrc );                  // Id of widget
                        NCode   =   pMsg->Data.v;                               // Notification code
                        switch( NCode )
                        {
                                case WM_NOTIFICATION_CLICKED:
                                        break;
                        };
                        break;

                case WM_INIT_DIALOG:
                        hWin    =   pMsg->hWin;
                        WINDOW_SetBkColor( hWin, GUI_BLACK );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR1_TEXT_HEADER );
                        TEXT_SetBkColor( hItem, UI_DSPL_HDR_COLOR_BCKGRND );
                        TEXT_SetFont( hItem, &UI_DSPL_HDR_TXT_FONT );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR1_TEXT_SENS_VALUE );
                        TEXT_SetBkColor( hItem, UI_DSPL_HDR_COLOR_BCKGRND );
                        TEXT_SetTextColor( hItem, GUI_YELLOW );
                        TEXT_SetFont( hItem, &GUI_FontTahoma255 );

                        //hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR1_GRAPH );
                        //ui_dspl_scr1_graph_init( hItem, GUI_ID_SCR1_GRAPH );
                        //WM_BringToBottom( hItem );
                        ////WM_SetCallback(hItem, _cbGraph);
                        break;

                default:
                        WM_DefaultProc( pMsg );
                        break;
        }
}


void    ui_dspl_scr1_update(                    float *         data,
                                                size_t          size )
{
        WM_HWIN         hTextHeader     = WM_GetDialogItem( hWin, GUI_ID_SCR1_TEXT_SENS_VALUE );
        //WM_HWIN         hGraph          = WM_GetDialogItem( WM_HBKWIN, GUI_ID_SCR1_GRAPH );
        float           sensor_value;
        //int16_t         graph_sample;
        char            str[16];


        while( size-- )
        {
                sensor_value    =   *data++;

                if( sensor_value > 9999 )
                {
                        sensor_value    =   9999;
                }

                snprintf( str, sizeof(str), "%4.2f", sensor_value );
                TEXT_SetText( hTextHeader, str );

        }
}
