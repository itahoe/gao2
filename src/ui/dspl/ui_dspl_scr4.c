/**
  * @file    ui_dspl_scr4.c
  * @brief   User Interface - Screen 4
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <time.h>
#include "app.h"
#include "DIALOG.h"
#include "ui_dspl.h"


static  const   char *          date_month[]    = { "ßÍÂ", "ÔÅÂ", "ÌÀÐ", "ÀÏÐ", "ÌÀÉ", "ÈÞÍ", "ÈÞË", "ÀÂÃ", "ÑÅÍ", "ÎÊÒ", "ÍÎß", "ÄÅÊ", };


static
const   GUI_WIDGET_CREATE_INFO  dlg_date[]      =
{
  { WINDOW_CreateIndirect, "",          0,                                    0,  80, 800, 400, 0 },
  { TEXT_CreateIndirect,   "",          GUI_ID_SCR4_DLG_DATE_TXT_DAY,       100, 100, 200, 100, TEXT_CF_HCENTER | TEXT_CF_VCENTER },
  { TEXT_CreateIndirect,   "",          GUI_ID_SCR4_DLG_DATE_TXT_MON,       300, 100, 200, 100, TEXT_CF_HCENTER | TEXT_CF_VCENTER },
  { TEXT_CreateIndirect,   "",          GUI_ID_SCR4_DLG_DATE_TXT_YEAR,      500, 100, 200, 100, TEXT_CF_HCENTER | TEXT_CF_VCENTER },
  { BUTTON_CreateIndirect, "+",         GUI_ID_SCR4_DLG_DATE_BTN_DAY_UP,    100,   0, 200, 100, 0 },
  { BUTTON_CreateIndirect, "-",         GUI_ID_SCR4_DLG_DATE_BTN_DAY_DN,    100, 200, 200, 100, 0 },
  { BUTTON_CreateIndirect, "+",         GUI_ID_SCR4_DLG_DATE_BTN_MON_UP,    300,   0, 200, 100, 0 },
  { BUTTON_CreateIndirect, "-",         GUI_ID_SCR4_DLG_DATE_BTN_MON_DN,    300, 200, 200, 100, 0 },
  { BUTTON_CreateIndirect, "+",         GUI_ID_SCR4_DLG_DATE_BTN_YEAR_UP,   500,   0, 200, 100, 0 },
  { BUTTON_CreateIndirect, "-",         GUI_ID_SCR4_DLG_DATE_BTN_YEAR_DN,   500, 200, 200, 100, 0 },
  { BUTTON_CreateIndirect, "ÍÀÇÀÄ",     GUI_ID_SCR4_BTN_BACK,               300, 300, 200, 100, 0 },
};


static
const   GUI_WIDGET_CREATE_INFO  dlg_time[]      =
{
  { WINDOW_CreateIndirect, "",          0,                                    0,  80, 800, 400, 0 },
  { TEXT_CreateIndirect,   "",          GUI_ID_SCR4_DLG_TIME_TXT_HOUR,      100, 100, 200, 100, TEXT_CF_HCENTER | TEXT_CF_VCENTER },
  { TEXT_CreateIndirect,   "",          GUI_ID_SCR4_DLG_TIME_TXT_MIN,       300, 100, 200, 100, TEXT_CF_HCENTER | TEXT_CF_VCENTER },
  { TEXT_CreateIndirect,   "",          GUI_ID_SCR4_DLG_TIME_TXT_SEC,       500, 100, 200, 100, TEXT_CF_HCENTER | TEXT_CF_VCENTER },
  { BUTTON_CreateIndirect, "+",         GUI_ID_SCR4_DLG_TIME_BTN_HOUR_UP,   100,   0, 200, 100, 0 },
  { BUTTON_CreateIndirect, "-",         GUI_ID_SCR4_DLG_TIME_BTN_HOUR_DN,   100, 200, 200, 100, 0 },
  { BUTTON_CreateIndirect, "+",         GUI_ID_SCR4_DLG_TIME_BTN_MIN_UP,    300,   0, 200, 100, 0 },
  { BUTTON_CreateIndirect, "-",         GUI_ID_SCR4_DLG_TIME_BTN_MIN_DN,    300, 200, 200, 100, 0 },
  { BUTTON_CreateIndirect, "+",         GUI_ID_SCR4_DLG_TIME_BTN_SEC_UP,    500,   0, 200, 100, 0 },
  { BUTTON_CreateIndirect, "-",         GUI_ID_SCR4_DLG_TIME_BTN_SEC_DN,    500, 200, 200, 100, 0 },
  { BUTTON_CreateIndirect, "ÍÀÇÀÄ",     GUI_ID_SCR4_BTN_BACK,               300, 300, 200, 100, 0 },
};


static
const   GUI_WIDGET_CREATE_INFO  dlg_chnl[]      =
{
  { WINDOW_CreateIndirect, "",          0,                                    0,  80, 800, 400, 0 },
  { TEXT_CreateIndirect,   "",          GUI_ID_SCR4_DLG_CHNL_TXT_PHY,       100, 100, 200, 100, TEXT_CF_HCENTER | TEXT_CF_VCENTER },
  { TEXT_CreateIndirect,   "",          GUI_ID_SCR4_DLG_CHNL_TXT_RATE,      300, 100, 200, 100, TEXT_CF_HCENTER | TEXT_CF_VCENTER },
  { TEXT_CreateIndirect,   "",          GUI_ID_SCR4_DLG_CHNL_TXT_PROT,      500, 100, 200, 100, TEXT_CF_HCENTER | TEXT_CF_VCENTER },
  { BUTTON_CreateIndirect, "+",         GUI_ID_SCR4_DLG_CHNL_BTN_UP_PHY,    100,   0, 200, 100, 0 },
  { BUTTON_CreateIndirect, "-",         GUI_ID_SCR4_DLG_CHNL_BTN_DN_PHY,    100, 200, 200, 100, 0 },
  { BUTTON_CreateIndirect, "+",         GUI_ID_SCR4_DLG_CHNL_BTN_UP_RATE,   300,   0, 200, 100, 0 },
  { BUTTON_CreateIndirect, "-",         GUI_ID_SCR4_DLG_CHNL_BTN_DN_RATE,   300, 200, 200, 100, 0 },
  { BUTTON_CreateIndirect, "+",         GUI_ID_SCR4_DLG_CHNL_BTN_UP_PROT,   500,   0, 200, 100, 0 },
  { BUTTON_CreateIndirect, "-",         GUI_ID_SCR4_DLG_CHNL_BTN_DN_PROT,   500, 200, 200, 100, 0 },
  { BUTTON_CreateIndirect, "ÍÀÇÀÄ",     GUI_ID_SCR4_BTN_BACK,               300, 300, 200, 100, 0 },
};


static
void    dlg_date_update(                WM_HWIN                 hWin )
{
                WM_HWIN         hItem;
                char            str[16];
                time_t          t       = time( NULL );
	struct  tm *            ts      = gmtime( &t );


        strftime( str, sizeof(str), "%Y", ts );
        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_DLG_DATE_TXT_YEAR );
        TEXT_SetText( hItem, str );

        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_DLG_DATE_TXT_MON );
        TEXT_SetText( hItem, date_month[ ts->tm_mon ] );

        strftime( str, sizeof(str), "%d", ts );
        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_DLG_DATE_TXT_DAY );
        TEXT_SetText( hItem, str );
}


static
void    dlg_date_cb(                    WM_MESSAGE *            pMsg    )
{
        WM_HWIN         hItem;
        int             NCode;
        int             Id;


        switch( pMsg->MsgId )
        {
                case WM_NOTIFY_PARENT:
                        Id    = WM_GetId(pMsg->hWinSrc);    // Id of widget
                        NCode = pMsg->Data.v;               // Notification code

                        switch( NCode )
                        {
                                case WM_NOTIFICATION_CLICKED:      // React only if clicked
                                        switch( Id )
                                        {
                                                case GUI_ID_SCR4_DLG_DATE_BTN_YEAR_UP:
                                                        app_rtc_ctl( APP_RTC_CTL_YEAR_INCREASE );
                                                        dlg_date_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_DATE_BTN_YEAR_DN:
                                                        app_rtc_ctl( APP_RTC_CTL_YEAR_DECREASE );
                                                        dlg_date_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_DATE_BTN_MON_UP:
                                                        app_rtc_ctl( APP_RTC_CTL_MONTH_INCREASE );
                                                        dlg_date_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_DATE_BTN_MON_DN:
                                                        app_rtc_ctl( APP_RTC_CTL_MONTH_DECREASE );
                                                        dlg_date_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_DATE_BTN_DAY_UP:
                                                        app_rtc_ctl( APP_RTC_CTL_DAY_INCREASE );
                                                        dlg_date_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_DATE_BTN_DAY_DN:
                                                        app_rtc_ctl( APP_RTC_CTL_DAY_DECREASE );
                                                        dlg_date_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_BTN_BACK:
                                                        GUI_EndDialog(pMsg->hWin, 0);
                                                        break;

                                                default:
                                                        break;
                                        } //switch( Id )

                                        break;
                        } //switch( NCode )
                        break;

                case WM_INIT_DIALOG:
                        hItem   =   pMsg->hWin;
                        WINDOW_SetBkColor( hItem, GUI_BLACK );

                        dlg_date_update( pMsg->hWin );

                        WM_Update( pMsg->hWin );
                        break;

                default:
                        WM_DefaultProc(pMsg);
                        break;
        }
}


static
void    dlg_time_update(                WM_HWIN                 hWin )
{
                WM_HWIN         hItem;
                char            str[16];
                time_t          t       = time( NULL );
	struct  tm *            ts      = gmtime( &t );


        strftime( str, sizeof(str), "%H", ts );
        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_DLG_TIME_TXT_HOUR );
        TEXT_SetText( hItem, str );

        strftime( str, sizeof(str), "%M", ts );
        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_DLG_TIME_TXT_MIN );
        TEXT_SetText( hItem, str );

        strftime( str, sizeof(str), "%S", ts );
        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_DLG_TIME_TXT_SEC );
        TEXT_SetText( hItem, str );
}


static
void    dlg_time_cb(                    WM_MESSAGE *            pMsg    )
{
        int     NCode;
        int     Id;


        switch( pMsg->MsgId )
        {
                case WM_TIMER:
                        dlg_time_update( pMsg->hWin );
                        WM_RestartTimer( pMsg->Data.v, 0 );     //pMsg->Data.v contains a handle the expired timer only if the message WM_TIMER is currently processed
                        break;

                case WM_NOTIFY_PARENT:
                        Id    = WM_GetId(pMsg->hWinSrc);        // Id of widget
                        NCode = pMsg->Data.v;                   // Notification code
                        switch( NCode )
                        {
                                case WM_NOTIFICATION_CLICKED:
                                        switch( Id )
                                        {
                                                case GUI_ID_SCR4_DLG_TIME_BTN_HOUR_UP:
                                                        app_rtc_ctl( APP_RTC_CTL_HOUR_INCREASE );
                                                        dlg_time_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_TIME_BTN_HOUR_DN:
                                                        app_rtc_ctl( APP_RTC_CTL_HOUR_DECREASE );
                                                        dlg_time_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_TIME_BTN_MIN_UP:
                                                        app_rtc_ctl( APP_RTC_CTL_MINUTE_INCREASE );
                                                        dlg_time_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_TIME_BTN_MIN_DN:
                                                        app_rtc_ctl( APP_RTC_CTL_MINUTE_DECREASE );
                                                        dlg_time_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_TIME_BTN_SEC_UP:
                                                        app_rtc_ctl( APP_RTC_CTL_SECOND_INCREASE );
                                                        dlg_time_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_TIME_BTN_SEC_DN:
                                                        app_rtc_ctl( APP_RTC_CTL_SECOND_DECREASE );
                                                        dlg_time_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_BTN_BACK:
                                                        GUI_EndDialog(pMsg->hWin, 0);
                                                        break;

                                                default:
                                                        break;
                                        }
                                        break;
                        }
                        break;

                case WM_INIT_DIALOG:
                        WINDOW_SetBkColor( pMsg->hWin, GUI_BLACK );
                        dlg_time_update( pMsg->hWin );
                        WM_CreateTimer( pMsg->hWin, 0, 1000, 0 );
                        break;

                default:
                        WM_DefaultProc(pMsg);
                        break;
        }
}


static
void    dlg_chnl_update(                WM_HWIN                 hWin )
{
                WM_HWIN         hItem;
        const   char *          str;
                size_t          chnl_num        = 0;


        str     =   app_cfg_chnl_phy_str_get( chnl_num );
        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_DLG_CHNL_TXT_PHY );
        TEXT_SetText( hItem, str );

        str     =   app_cfg_chnl_rate_str_get( chnl_num );
        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_DLG_CHNL_TXT_RATE );
        TEXT_SetText( hItem, str );

        str     =   app_cfg_chnl_prot_str_get( chnl_num );
        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_DLG_CHNL_TXT_PROT );
        TEXT_SetText( hItem, str );
}


static
void    dlg_chnl_cb(                    WM_MESSAGE *            pMsg    )
{
        int             NCode;
        int             Id;
        size_t          chnl_num        = 0;

        switch( pMsg->MsgId )
        {
                case WM_NOTIFY_PARENT:
                        Id    = WM_GetId(pMsg->hWinSrc);        // Id of widget
                        NCode = pMsg->Data.v;                   // Notification code
                        switch( NCode )
                        {
                                case WM_NOTIFICATION_CLICKED:
                                        switch( Id )
                                        {
                                                case GUI_ID_SCR4_DLG_CHNL_BTN_UP_PHY:
                                                        app_cfg_ctl( APP_CFG_CTL_PHY_SET_NEXT, chnl_num );
                                                        dlg_chnl_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_CHNL_BTN_DN_PHY:
                                                        app_cfg_ctl( APP_CFG_CTL_PHY_SET_PREV, chnl_num );
                                                        dlg_chnl_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_CHNL_BTN_UP_RATE:
                                                        app_cfg_ctl( APP_CFG_CTL_RATE_SET_NEXT, chnl_num );
                                                        dlg_chnl_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_CHNL_BTN_DN_RATE:
                                                        app_cfg_ctl( APP_CFG_CTL_RATE_SET_PREV, chnl_num );
                                                        dlg_chnl_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_CHNL_BTN_UP_PROT:
                                                        app_cfg_ctl( APP_CFG_CTL_PROT_SET_NEXT, chnl_num );
                                                        dlg_chnl_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_DLG_CHNL_BTN_DN_PROT:
                                                        app_cfg_ctl( APP_CFG_CTL_PROT_SET_PREV, chnl_num );
                                                        dlg_chnl_update( pMsg->hWin );
                                                        WM_Update( pMsg->hWin );
                                                        break;

                                                case GUI_ID_SCR4_BTN_BACK:
                                                        GUI_EndDialog(pMsg->hWin, 0);
                                                        break;

                                                default:
                                                        break;
                                        }
                                        break;
                        }
                        break;

                case WM_INIT_DIALOG:
                        WINDOW_SetBkColor( pMsg->hWin, GUI_BLACK );
                        dlg_chnl_update( pMsg->hWin );
                        break;

                default:
                        WM_DefaultProc(pMsg);
                        break;
        }

}


static
void    scr4_update(                    WM_HWIN                 hWin )
{
                WM_HWIN         hItem;
                char            str[16];
                time_t          t       = time( NULL );
	struct  tm *            ts      = gmtime( &t );
                size_t          chnl_num        = 0;


        strftime( str, sizeof(str), "%d/%m/%Y", ts );
        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_BUTTON_DATE );
        BUTTON_SetText( hItem, str );

        strftime( str, sizeof(str), "%H:%M:%S", ts );
        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_BUTTON_TIME );
        BUTTON_SetText( hItem, str );

        strncpy( str, app_cfg_chnl_phy_str_get( chnl_num ),     sizeof( str ) );
        strncat( str, " ",                                      sizeof( str ) );
        strncat( str, app_cfg_chnl_rate_str_get( chnl_num ),    sizeof( str ) );
        strncat( str, " ",                                      sizeof( str ) );
        strncat( str, app_cfg_chnl_prot_str_get( chnl_num ),    sizeof( str ) );
        hItem   =   WM_GetDialogItem( hWin, GUI_ID_SCR4_BUTTON_CFG_CH1 );
        BUTTON_SetText( hItem, str );
}


void    ui_dspl_scr4_cb(                        WM_MESSAGE *            pMsg )
{
        int             Id;
        WM_HWIN         hItem;
        WM_HWIN         hWin    =   pMsg->hWin;


        switch( pMsg->MsgId )
        {
                case WM_TIMER:
                        scr4_update( pMsg->hWin );
                        WM_Update( hWin );
                        WM_RestartTimer( pMsg->Data.v, 0 );     //pMsg->Data.v contains a handle the expired timer only if the message WM_TIMER is currently processed
                        break;

                case WM_NOTIFY_PARENT:
                        if( pMsg->Data.v == WM_NOTIFICATION_CLICKED )
                        {
                                Id      =   WM_GetId( pMsg->hWinSrc );

                                switch( Id )
                                {
                                        case GUI_ID_SCR4_BUTTON_DATE:
                                                GUI_ExecDialogBox( dlg_date, GUI_COUNTOF(dlg_date), dlg_date_cb, hWin, 0, 0 );
                                                break;

                                        case GUI_ID_SCR4_BUTTON_TIME:
                                                GUI_ExecDialogBox( dlg_time, GUI_COUNTOF(dlg_time), dlg_time_cb, hWin, 0, 0 );
                                                break;

                                        case GUI_ID_SCR4_BUTTON_CFG_CH1:
                                                GUI_ExecDialogBox( dlg_chnl, GUI_COUNTOF(dlg_chnl), dlg_chnl_cb, hWin, 0, 0 );
                                                break;

                                        default:
                                                break;
                                }
                        }
                        break;

                case WM_INIT_DIALOG:
                        hItem   =   pMsg->hWin;
                        WINDOW_SetBkColor( hItem, GUI_BLACK );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR4_TEXT_HEADER );
                        TEXT_SetBkColor( hItem, UI_DSPL_HDR_COLOR_BCKGRND );
                        TEXT_SetFont( hItem, &UI_DSPL_HDR_TXT_FONT );

                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR4_BUTTON_CFG_CH1 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR4_BUTTON_CFG_CH2 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR4_BUTTON_CFG_CH3 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR4_BUTTON_CFG_CH4 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR4_BUTTON_CFG_CH5 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR4_BUTTON_CFG_CH6 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR4_BUTTON_CFG_CH7 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );
                        BUTTON_SetTextAlign( WM_GetDialogItem( hWin, GUI_ID_SCR4_BUTTON_CFG_CH8 ), TEXT_CF_LEFT | TEXT_CF_VCENTER );

                        WM_CreateTimer( hWin, 0, 1000, 0 );

                        break;

                default:
                        WM_DefaultProc( pMsg );
                        break;
        }
}
