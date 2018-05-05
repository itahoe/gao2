/**
  * @file    ui_dspl_scr3.c
  * @brief   User Interface - Screen 3
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <time.h>
#include "app.h"
#include "DIALOG.h"
#include "ui_dspl.h"


extern  GUI_CONST_STORAGE       GUI_FONT        GUI_FontSegoePrint49;


//        WM_HTIMER       hTmr;


/*
static const GUI_WIDGET_CREATE_INFO _aDialogSelect[] = {
  //{ FRAMEWIN_CreateIndirect, "Select vehicle",  0,                 55,  30, 210, 200, 0 },
  //{ WINDOW_CreateIndirect,       "Select vehicle",  0,                 55,  30, 210, 200, 0 },
  //{ WINDOW_CreateIndirect,    "scr31",         GUI_ID_SCR3_1_WINDOW, 0,   0, 800,    430,      0,      0x0,    0 },
  { WINDOW_CreateIndirect,    "scr31",         GUI_ID_SCR3_1_WINDOW, 0,   0, 800,    480,      0,      0x0,    0 },
  //{ TEXT_CreateIndirect,     "Available vehicles:", 0,              9,   6, 120,  20, 0 },
  //{ LISTVIEW_CreateIndirect, NULL,              GUI_ID_LISTVIEW0,   7,  20, 190, 120, 0 },
  { BUTTON_CreateIndirect,   "OK",              GUI_ID_OK,         100, 350,  200,  100, 0 },
  { BUTTON_CreateIndirect,   "Cancel",          GUI_ID_CANCEL,     500, 350,  200,  100, 0 }
};
*/

/*
static void _InitDialogSelect(WM_HWIN hWin) {
  //WM_HWIN hItem;
  //int     i;

  //i = 0;
  //
  // Init framewindow
  //
  //FRAMEWIN_SetFont(hWin, &GUI_Font10_ASCII);
  //FRAMEWIN_SetTitleHeight(hWin, 14);
  //FRAMEWIN_SetMoveable(hWin, 1);
  //
  // Init listbox items
  //
  //hItem = WM_GetDialogItem(hWin, GUI_ID_LISTVIEW0);
  //WM_SetScrollbarV(hItem, 1);
  //LISTVIEW_SetGridVis(hItem, 1);
  //LISTVIEW_SetLBorder(hItem, 3);
  //LISTVIEW_SetRBorder(hItem, 3);
  //LISTVIEW_AddColumn(hItem,  80, "Make",    GUI_TA_LEFT);
  //LISTVIEW_AddColumn(hItem, 100, "Options", GUI_TA_LEFT);
  //while (_acItems[i][0][0]) {
  // _AddListviewItem(hItem, _acItems[i][0], _acItems[i][1]);
  //  i++;
  //}
}
*/

/*
static int _GetVehicle(WM_HWIN hWin) {
  WM_HWIN hItem;
  int     CurSel;
  int     NumItems;

  hItem    = WM_GetDialogItem(hWin, GUI_ID_LISTVIEW0);
  NumItems = LISTVIEW_GetNumRows(hItem);
  CurSel   = LISTVIEW_GetSel(hItem);
  if ((CurSel >= 0) && (CurSel < NumItems)) {
    //strcpy(_acVehicle, _acItems[CurSel][0]);
    //strcat(_acVehicle, " ");
    //strcat(_acVehicle, _acItems[CurSel][1]);

    hItem = WM_GetDialogItem(hWin, GUI_ID_EDIT0);
    //EDIT_SetText(hItem, _acVehicle);
    return 1;
  }
  return 0;
}
*/

/*
static void _cbDialogSelect(            WM_MESSAGE *            pMsg )
{
        WM_HWIN         hWin;
        WM_HWIN         hItem;
        int             Id;


        hWin    =   pMsg->hWin;

        switch( pMsg->MsgId )
        {

                //case WM_PAINT:
                        //GUI_Clear();
                        //WM_DefaultProc(pMsg);
                        //break;

                case WM_INIT_DIALOG:
                        WINDOW_SetBkColor( hWin, GUI_BLACK );
                        //WINDOW_SetBkColor( hWin, GUI_DARKGRAY );

                        WM_SelectWindow( hWin );
                        //GUI_Clear();
                        //_InitDialogSelect(hWin);
                        //WM_SetFocus(  WM_GetDialogItem( hWin, GUI_ID_OK )  );
                        //WM_BringToTop( hWin );
                        //WM_ShowWindow( hWin );
                        //WM_MakeModal( hWin );
                        WM_SetFocus( hWin );
                        break;

                case WM_NOTIFY_PARENT:
                        if( pMsg->Data.v == WM_NOTIFICATION_RELEASED )
                        {
                                Id      =   WM_GetId( pMsg->hWinSrc );

                                switch( Id )
                                {
                                        case GUI_ID_OK:
                                                if( _GetVehicle(hWin) == 0 )
                                                {
                                                        //_MessageBox("You have to select a vehicle!", "ERROR");
                                                        //WM_MakeModal(hWin);
                                                        //WM_SetFocus(hWin);
                                                }
                                                break;

                                        case GUI_ID_CANCEL:
                                                GUI_EndDialog(pMsg->hWin, 0);
                                                break;
                                }
                        }
                        break;

                default:
                        WM_DefaultProc(pMsg);
                        break;
        }
}
*/

void    ui_dspl_scr3_cb(                        WM_MESSAGE *            pMsg )
{
                //int             NCode;
                int             Id;
                WM_HWIN         hItem;
                WM_HWIN         hWin    =   pMsg->hWin;
                //WM_HWIN         hDlg;
                time_t          time_raw;
	struct  tm *            t;
                char            str[16];


        switch( pMsg->MsgId )
        {
                case WM_NOTIFY_PARENT:
                        if( pMsg->Data.v == WM_NOTIFICATION_CLICKED )
                        {
                                Id      =   WM_GetId( pMsg->hWinSrc );

                                switch( Id )
                                {
/*
                                        case GUI_ID_SCR3_BUTTON_DATE:
                                                //hDlg    =   GUI_CreateDialogBox( _aDialogSelect, GUI_COUNTOF(_aDialogSelect), &_cbDialogSelect, WM_HBKWIN, 0, 0 );
                                                hDlg    =   GUI_CreateDialogBox( _aDialogSelect, GUI_COUNTOF(_aDialogSelect), &_cbDialogSelect, hWin, 0, 0 );
                                                //WM_MakeModal( hDlg );
                                                //WM_SetFocus( hDlg );
                                                //WM_MakeModal( hWin );
                                                //WM_SetFocus( hWin );
                                                GUI_ExecCreatedDialog( hDlg );
                                                break;
*/
/*
                                        case GUI_ID_OK:
                                        case GUI_ID_CANCEL:
                                                GUI_EndDialog(hWin, 0);
                                                break;
*/
                                }
                        }
                        break;


                case WM_INIT_DIALOG:
                        hItem   =   pMsg->hWin;
                        WINDOW_SetBkColor( hItem, GUI_BLACK );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR3_TEXT_HEADER );
                        TEXT_SetBkColor( hItem, UI_DSPL_HDR_COLOR_BCKGRND );
                        TEXT_SetFont( hItem, &UI_DSPL_HDR_TXT_FONT );

                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR3_BUTTON_CFG_CH1 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR3_BUTTON_CFG_CH2 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR3_BUTTON_CFG_CH3 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR3_BUTTON_CFG_CH4 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR3_BUTTON_CFG_CH5 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR3_BUTTON_CFG_CH6 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR3_BUTTON_CFG_CH7 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR3_BUTTON_CFG_CH8 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );

                        WM_CreateTimer( hWin, 0, 1000, 0 );

                        break;

                case WM_TIMER:

                        time_raw        =   time( NULL );
                        t               =   gmtime( &time_raw );

                        snprintf( str, sizeof(str), "%02d/%02d/%04d", t->tm_mday, t->tm_mon, t->tm_year + 1970 );
                        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR3_BUTTON_DATE );
                        BUTTON_SetText( hItem, str );

                        snprintf( str, sizeof(str), "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec );
                        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR3_BUTTON_TIME );
                        BUTTON_SetText( hItem, str );

                        WM_Update( hWin );

                        WM_RestartTimer( pMsg->Data.v, 0 );     //pMsg->Data.v contains a handle the expired timer only if the message WM_TIMER is currently processed
                        break;

                default:
                        WM_DefaultProc( pMsg );
                        break;
        }
}
