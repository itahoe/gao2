/**
  * @file    ui_dspl_scr2.c
  * @brief   User Interface - Screen 2
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "app.h"
#include "DIALOG.h"
#include "ui_dspl.h"


void    ui_dspl_scr2_cb(                        WM_MESSAGE *            pMsg )
{
        WM_HWIN         hWin;
        WM_HWIN         hItem;
        int             NCode;
        int             Id;


        hWin    =   pMsg->hWin;

        //APP_TRACE_EMWIN( "ui_dspl_scr2_cb()\t", pMsg->MsgId );

        switch( pMsg->MsgId )
        {
/*
                case WM_PAINT:
                        GUI_SetBkColor( GUI_BLACK );
                        GUI_Clear();
                        break;
*/
                case WM_NOTIFY_PARENT:
                        Id      =   WM_GetId( pMsg->hWinSrc );                  // Id of widget
                        NCode   =   pMsg->Data.v;                               // Notification code
                        switch( NCode )
                        {

                                case WM_NOTIFICATION_CLICKED:
                                //case WM_NOTIFICATION_RELEASED:                  // React only if released
                                        if( Id == GUI_ID_SCR2_BUTTON_STRT )
                                        {
                                                BSP_LED_Toggle( LED1 );
                                                hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR2_TEXT_TEMP );
                                                TEXT_SetText( hItem, "*** ÑÒÀÐÒ ***" );
                                                //WM_Invalidate( hWin );
                                        }

                                        if( Id == GUI_ID_SCR2_BUTTON_CLR )
                                        {
                                                BSP_LED_Toggle( LED2 );
                                                hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR2_TEXT_TEMP );
                                                TEXT_SetText( hItem, "--- ÑÁÐÎÑ ---" );
                                                //WM_Invalidate( hWin );
                                        }
                                        break;
                        };

                        //WM_DefaultProc(pMsg);

                        break;

                case WM_INIT_DIALOG:
                        hItem   =   pMsg->hWin;
                        WINDOW_SetBkColor( hItem, GUI_BLACK );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR2_TEXT_HEADER );
                        TEXT_SetBkColor( hItem, UI_DSPL_HDR_COLOR_BCKGRND );
                        TEXT_SetFont( hItem, &UI_DSPL_HDR_TXT_FONT );

                        //GUI_MEMDEV_Select( hItem );
                        //GUI_SetBkColor( GUI_TRANSPARENT );
                        //GUI_Clear();

                        //hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR2_GRAPH );
                        //ui_dspl_scr0_add_graph( hItem, GUI_ID_SCR0_GRAPH );

                        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR2_BUTTON_STRT );
                        //BUTTON_SetFocusColor( hItem, GUI_YELLOW );
                        BUTTON_SetFocusable( hItem, 0 );

                        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR2_BUTTON_CLR );
                        //BUTTON_SetFocusColor( hItem, GUI_YELLOW );
                        BUTTON_SetFocusable( hItem, 0 );

                        //BUTTON_SetBkColor(      hItem, BUTTON_CI_UNPRESSED,  GUI_DARKGRAY );
                        //BUTTON_SetBkColor(      hItem, BUTTON_CI_PRESSED,    GUI_GRAY );
                        //BUTTON_SetBkColor(      hItem, BUTTON_CI_DISABLED,   GUI_BLACK );
                        //BUTTON_SetFrameColor(   hItem, GUI_YELLOW );

                        break;

                default:
                        WM_DefaultProc(pMsg);
                        break;

        }
}
