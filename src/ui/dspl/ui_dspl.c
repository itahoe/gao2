/**
  * @file    ui_dspl.c
  * @brief   User Interface - Display
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "DIALOG.h"
#include "app.h"
#include "ui_dspl.h"


void    MainTaskLoop( void );


#define UI_DSPL_SCRN_IDX_MIN    0
#define UI_DSPL_SCRN_IDX_MAX    4

static  int             curr_scrn_idx           =   0;

WM_HWIN         ui_dspl_scrn_hndl[ UI_DSPL_SCRN_IDX_MAX ];


static GUI_WIDGET_CREATE_INFO ui_dspl_scr0_info[] =
{
    { WINDOW_CreateIndirect,    "scr0",         GUI_ID_SCR0_WIN,              0,      0,    800,    480,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "",             GUI_ID_SCR0_BTN_HEAD,       150,      0,    500,     80,      TEXT_CF_HCENTER | TEXT_CF_VCENTER,      0x0,    0 },
    { TEXT_CreateIndirect,      "",             GUI_ID_SCR0_TXT_SENS,         0,     80,    800,    400,      TEXT_CF_HCENTER | TEXT_CF_VCENTER,      0x0,    0 },
    { GRAPH_CreateIndirect,     0,              GUI_ID_SCR0_GRAPH,            0,     80,    UI_DSPL_GRAPH_SIZE_X, UI_DSPL_GRAPH_SIZE_Y},
    { BUTTON_CreateIndirect,    "-",            GUI_ID_SCR0_BTN_ZOOM_LEFT,    0,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "\xAD  1",      GUI_ID_SCR0_BTN_ZOOM_MODE,  100,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "+",            GUI_ID_SCR0_BTN_ZOOM_RGHT,  200,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "\xAE",         GUI_ID_SCR0_BTN_SHFT_LEFT,  500,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "0",            GUI_ID_SCR0_BTN_SHFT_MODE,  600,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "\xAF",         GUI_ID_SCR0_BTN_SHFT_RGHT,  700,    430,    100,     50,      0,      0x0,    0 },
};

static const GUI_WIDGET_CREATE_INFO ui_dspl_scr1_info[] =
{
    { WINDOW_CreateIndirect,    "scr1",         GUI_ID_SCR1_WIN,            800,      0,    800,    480,      0,      0x0,    0 },
    { TEXT_CreateIndirect,      "�����������",  GUI_ID_SCR1_TXT_HEADER,       0,      0,    800,     80,      TEXT_CF_HCENTER | TEXT_CF_VCENTER,      0x0,    0 },
    { GRAPH_CreateIndirect,     0,              GUI_ID_SCR1_GRAPH,            0,     80,    UI_DSPL_GRAPH_SIZE_X, UI_DSPL_GRAPH_SIZE_Y },
    { BUTTON_CreateIndirect,    "-",            GUI_ID_SCR1_BTN_ZOOM_LEFT,    0,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "\xAD 1",       GUI_ID_SCR1_BTN_ZOOM_MODE,  100,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "+",            GUI_ID_SCR1_BTN_ZOOM_RGHT,  200,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "<",            GUI_ID_SCR1_BTN_PREV,       300,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    ">",            GUI_ID_SCR1_BTN_NEXT,       400,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "\xA2",         GUI_ID_SCR1_BTN_SHFT_LEFT,  500,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "0",            GUI_ID_SCR1_BTN_SHFT_MODE,  600,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "\xA1",         GUI_ID_SCR1_BTN_SHFT_RGHT,  700,    430,    100,     50,      0,      0x0,    0 },
};

static const GUI_WIDGET_CREATE_INFO ui_dspl_scr2_info[] =
{
    { WINDOW_CreateIndirect,    "scr2",         GUI_ID_SCR2_WIN,            800,      0,    800,    480,      0,      0x0,    0 },
    { TEXT_CreateIndirect,      "����������",   GUI_ID_SCR2_TXT_HEADER,       0,      0,    800,     80,      TEXT_CF_HCENTER | TEXT_CF_VCENTER,      0x0,    0 },
    { GRAPH_CreateIndirect,     0,              GUI_ID_SCR2_GRAPH,            0,     80,    UI_DSPL_GRAPH_SIZE_X, UI_DSPL_GRAPH_SIZE_Y },
    { BUTTON_CreateIndirect,    "��",           GUI_ID_SCR2_BTN_SAVE,       350,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "\xA2",         GUI_ID_SCR2_BTN_SHFT_LEFT,  500,    430,    100,     50,      0,      0x0,    0 },
    { TEXT_CreateIndirect,      "0",            GUI_ID_SCR2_TXT_SHFT_MODE,  600,    430,    100,     50,      TEXT_CF_HCENTER | TEXT_CF_VCENTER,      0x0,    0 },
    //{ BUTTON_CreateIndirect,    "0",            GUI_ID_SCR2_BTN_SHFT_MODE,  600,    430,    100,     50,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "\xA1",         GUI_ID_SCR2_BTN_SHFT_RGHT,  700,    430,    100,     50,      0,      0x0,    0 },
};

static const GUI_WIDGET_CREATE_INFO ui_dspl_scr3_info[] =
{
    //{ WINDOW_CreateIndirect,    "scr4",         GUI_ID_SCR3_WINDOW,         800,      0,    800,    480,      0,      0x0,    0 },
    { WINDOW_CreateIndirect,    "scr3",         GUI_ID_SCR3_WINDOW,         800,      0,    800,    480,      0,      0x0,    0 },
    //{ TEXT_CreateIndirect,      "���������",    GUI_ID_SCR3_TEXT_HEADER,      0,      0,    800,     50,      TEXT_CF_HCENTER | TEXT_CF_VCENTER,      0x0,    0 },
    { TEXT_CreateIndirect,      "���������",    GUI_ID_SCR3_TEXT_HEADER,      0,      0,    800,     80,      TEXT_CF_HCENTER | TEXT_CF_VCENTER,      0x0,    0 },

    //{ BUTTON_CreateIndirect,    "31/12/1970",   GUI_ID_SCR3_BUTTON_DATE,      0,     60,    220,     60,      0,      0x0,    0 },
    //{ BUTTON_CreateIndirect,    "23:59:59",     GUI_ID_SCR3_BUTTON_TIME,      0,    120,    220,     60,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "--/--/----",   GUI_ID_SCR3_BUTTON_DATE,      0,     80,    220,     60,      0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "--:--:--",     GUI_ID_SCR3_BUTTON_TIME,      0,    140,    220,     60,      0,      0x0,    0 },

    //{ BUTTON_CreateIndirect,    "1. RS-485 115200 HART", GUI_ID_SCR3_BUTTON_CFG_CH1,  250,  60,    550,     50,  0,      0x0,    0 },
    //{ BUTTON_CreateIndirect,    "2. NONE",               GUI_ID_SCR3_BUTTON_CFG_CH2,  250, 110,    550,     50,  0,      0x0,    0 },
    //{ BUTTON_CreateIndirect,    "3. NONE",               GUI_ID_SCR3_BUTTON_CFG_CH3,  250, 160,    550,     50,  0,      0x0,    0 },
    //{ BUTTON_CreateIndirect,    "4. NONE",               GUI_ID_SCR3_BUTTON_CFG_CH4,  250, 210,    550,     50,  0,      0x0,    0 },
    //{ BUTTON_CreateIndirect,    "5. NONE",               GUI_ID_SCR3_BUTTON_CFG_CH5,  250, 260,    550,     50,  0,      0x0,    0 },
    //{ BUTTON_CreateIndirect,    "6. NONE",               GUI_ID_SCR3_BUTTON_CFG_CH6,  250, 310,    550,     50,  0,      0x0,    0 },
    //{ BUTTON_CreateIndirect,    "7. NONE",               GUI_ID_SCR3_BUTTON_CFG_CH7,  250, 360,    550,     50,  0,      0x0,    0 },
    //{ BUTTON_CreateIndirect,    "8. NONE",               GUI_ID_SCR3_BUTTON_CFG_CH8,  250, 410,    550,     50,  0,      0x0,    0 },

    { BUTTON_CreateIndirect,    "--- --- ---",          GUI_ID_SCR3_BUTTON_CFG_CH1,  250,  80,    550,     50,  0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "--- --- ---",          GUI_ID_SCR3_BUTTON_CFG_CH2,  250, 130,    550,     50,  0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "--- --- ---",          GUI_ID_SCR3_BUTTON_CFG_CH3,  250, 180,    550,     50,  0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "--- --- ---",          GUI_ID_SCR3_BUTTON_CFG_CH4,  250, 230,    550,     50,  0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "--- --- ---",          GUI_ID_SCR3_BUTTON_CFG_CH5,  250, 280,    550,     50,  0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "--- --- ---",          GUI_ID_SCR3_BUTTON_CFG_CH6,  250, 330,    550,     50,  0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "--- --- ---",          GUI_ID_SCR3_BUTTON_CFG_CH7,  250, 380,    550,     50,  0,      0x0,    0 },
    { BUTTON_CreateIndirect,    "--- --- ---",          GUI_ID_SCR3_BUTTON_CFG_CH8,  250, 430,    550,     50,  0,      0x0,    0 },
};


static  const   int                             ui_dspl_scr_info_countof[] =
{
        GUI_COUNTOF( ui_dspl_scr0_info ),
        GUI_COUNTOF( ui_dspl_scr1_info ),
        GUI_COUNTOF( ui_dspl_scr2_info ),
        GUI_COUNTOF( ui_dspl_scr3_info ),
};

static  const   GUI_WIDGET_CREATE_INFO *        ui_dspl_scr_info[] =
{
        ui_dspl_scr0_info,
        ui_dspl_scr1_info,
        ui_dspl_scr2_info,
        ui_dspl_scr3_info,
};


static
void    ui_dspl_scrn_move(                      int             dir,
                                                WM_HWIN         scrn_out,
                                                WM_HWIN         scrn_in )
{
        int     step    =   100;
        int     delay   =   1;
        int     i;


        int     xSize   =   WM_GetWindowSizeX( scrn_in );
        int     ySize   =   WM_GetWindowSizeY( scrn_in );

        if( dir )
        {
                WM_SetWindowPos( scrn_in, UI_DSPL_WIN_POS_X0 + UI_DSPL_WIN_SIZE_X, UI_DSPL_WIN_POS_Y0, xSize, ySize );
        }
        else
        {
                WM_SetWindowPos( scrn_in, UI_DSPL_WIN_POS_X0 - UI_DSPL_WIN_SIZE_X, UI_DSPL_WIN_POS_Y0, xSize, ySize );
        }


        for( i = 0; i < UI_DSPL_WIN_SIZE_X; i += step )
        {
                if( scrn_out != NULL )
                {
                        WM_MoveWindow( scrn_out, dir ? -step : step, 0 );
                        WM_Invalidate( WM_HBKWIN );
                }

                GUI_Delay( delay );
        }

        for( i = 0; i < UI_DSPL_WIN_SIZE_X; i += step )
        {
                if( scrn_in != NULL )
                {
                        WM_MoveWindow( scrn_in, dir ? -step : step, 0 );
                }

                GUI_Delay( delay );
        }

        WM_Invalidate( scrn_in );
}


void    ui_dspl_scrn_slide(                     int             dir )
{
        WM_HWIN         hButtonPrev     =   WM_GetDialogItem( WM_HBKWIN, GUI_ID_BUTTON_PREV );
        WM_HWIN         hButtonNext     =   WM_GetDialogItem( WM_HBKWIN, GUI_ID_BUTTON_NEXT );


        WM_DisableWindow( hButtonPrev );
        WM_DisableWindow( hButtonNext );

        if( dir )
        {
                if( curr_scrn_idx < (UI_DSPL_SCRN_IDX_MAX - 1) )
                {
                        ui_dspl_scrn_move(      dir,
                                                ui_dspl_scrn_hndl[ curr_scrn_idx ],
                                                ui_dspl_scrn_hndl[ curr_scrn_idx+1 ] );
                        curr_scrn_idx++;
                }

                if( curr_scrn_idx < (UI_DSPL_SCRN_IDX_MAX - 1) )
                {
                        WM_EnableWindow( hButtonNext );
                }

                WM_EnableWindow( hButtonPrev );
        }
        else
        {
                if( curr_scrn_idx > UI_DSPL_SCRN_IDX_MIN )
                {
                        ui_dspl_scrn_move(      dir,
                                                ui_dspl_scrn_hndl[ curr_scrn_idx ],
                                                ui_dspl_scrn_hndl[ curr_scrn_idx-1 ] );
                        curr_scrn_idx--;
                }

                if( curr_scrn_idx > UI_DSPL_SCRN_IDX_MIN )
                {
                        WM_EnableWindow( hButtonPrev );
                }

                WM_EnableWindow( hButtonNext );
        }

        WM_Update( hButtonPrev );
        WM_Update( hButtonNext );
}


int     ui_dspl_scrn_idx_get( void )
{
        return( curr_scrn_idx );
}


static
void    _cbBackgroundWin(                       WM_MESSAGE *            pMsg )
{
                //WM_HWIN         hItem;
                int             NCode;
                int             Id;
        //static  int             scr0_idx        =   0;

        //APP_TRACE_EMWIN( "_cbBackgroundWin()\t", pMsg->MsgId );

        switch( pMsg->MsgId )
        {

                case WM_PAINT:
                        GUI_Clear();
                        WM_DefaultProc(pMsg);
                        break;

                case WM_NOTIFY_PARENT:
                        Id      =   WM_GetId( pMsg->hWinSrc );      // Id of widget
                        NCode   =   pMsg->Data.v;                 // Notification code
                        switch( NCode )
                        {
                                case WM_NOTIFICATION_CLICKED:
                                //case WM_NOTIFICATION_RELEASED:      // React only if released
                                        if( Id == GUI_ID_BUTTON_PREV )
                                        {
                                                ui_dspl_scrn_slide( 0 );
                                        }

                                        if( Id == GUI_ID_BUTTON_NEXT )
                                        {
                                                ui_dspl_scrn_slide( 1 );
                                        }
/*
                                        if( Id == GUI_ID_BUTTON_HEADER )
                                        {
                                                scr0_idx++;

                                                hItem   =   WM_GetDialogItem( WM_HBKWIN, GUI_ID_SCR0_WINDOW );

                                                ui_dspl_scr0_toggle( hItem, (scr0_idx & 1) );
                                                //ui_dspl_scrn_slide( 1 );
                                        }
*/
                                        break;
                        }
                        break;

                default:
                        WM_DefaultProc( pMsg );
                        break;
        }
}


static
void    _cbButtonNext(                  WM_MESSAGE *            pMsg )
{
        //APP_TRACE_EMWIN( "_cbButtonNext() = ", pMsg->MsgId );
        BUTTON_Callback( pMsg ); // The original callback
}


static
void    _cbButtonPrev(                  WM_MESSAGE *            pMsg )
{
        //APP_TRACE_EMWIN( "_cbButtonPrev() = ", pMsg->MsgId );
        BUTTON_Callback( pMsg ); // The original callback
}


static
void    ui_dspl_header_buttons_init( void )
{
        int             x0, y0, sizeX, sizeY;
        WM_HWIN         hItem;


        sizeX   =   UI_DSPL_HDR_BTN_SIZE_X;
        sizeY   =   UI_DSPL_HDR_BTN_SIZE_Y;
        x0      =   UI_DSPL_HDR_BTN_PREV_POS_X0;
        y0      =   UI_DSPL_HDR_BTN_PREV_POS_Y0;
        hItem   =   BUTTON_CreateEx( x0, y0, sizeX, sizeY,  WM_HBKWIN,  WM_CF_SHOW, 0, GUI_ID_BUTTON_PREV );
        BUTTON_SetBkColor( hItem, BUTTON_CI_DISABLED,   UI_DSPL_HDR_BTN_COLOR_BCKGRND );
        BUTTON_SetBkColor( hItem, BUTTON_CI_PRESSED,    UI_DSPL_HDR_BTN_COLOR_BCKGRND );
        BUTTON_SetBkColor( hItem, BUTTON_CI_UNPRESSED,  UI_DSPL_HDR_BTN_COLOR_BCKGRND );
        BUTTON_SetFrameColor( hItem, UI_DSPL_HDR_BTN_COLOR_FRAME );
        BUTTON_SetFont( hItem, &GUI_FontTahoma60 );
        BUTTON_SetText( hItem, "<" );
        BUTTON_SetFocusable( hItem, 0 );
        WM_DisableWindow( hItem );

        x0      =   UI_DSPL_HDR_BTN_NEXT_POS_X0;
        y0      =   UI_DSPL_HDR_BTN_NEXT_POS_Y0;
        hItem   =   BUTTON_CreateEx( x0, y0, sizeX, sizeY,  WM_HBKWIN,  WM_CF_SHOW, 0, GUI_ID_BUTTON_NEXT );
        BUTTON_SetBkColor( hItem, BUTTON_CI_DISABLED,   UI_DSPL_HDR_BTN_COLOR_BCKGRND );
        BUTTON_SetBkColor( hItem, BUTTON_CI_PRESSED,    UI_DSPL_HDR_BTN_COLOR_BCKGRND );
        BUTTON_SetBkColor( hItem, BUTTON_CI_UNPRESSED,  UI_DSPL_HDR_BTN_COLOR_BCKGRND );
        BUTTON_SetFrameColor( hItem, UI_DSPL_HDR_BTN_COLOR_FRAME );
        BUTTON_SetFont( hItem, &GUI_FontTahoma60 );
        BUTTON_SetText( hItem, ">" );
        BUTTON_SetFocusable( hItem, 0 );

/*
        x0      =   150;
        y0      =   0;
        hItem   =   BUTTON_CreateEx( 150, 0, 500, 80,  WM_HBKWIN,  WM_CF_SHOW, 0, GUI_ID_BUTTON_HEADER );
        BUTTON_SetBkColor( hItem, BUTTON_CI_DISABLED,   UI_DSPL_HDR_BTN_COLOR_BCKGRND );
        BUTTON_SetBkColor( hItem, BUTTON_CI_PRESSED,    UI_DSPL_HDR_BTN_COLOR_BCKGRND );
        BUTTON_SetBkColor( hItem, BUTTON_CI_UNPRESSED,  UI_DSPL_HDR_BTN_COLOR_BCKGRND );
        BUTTON_SetFrameColor( hItem, UI_DSPL_HDR_BTN_COLOR_FRAME );
        BUTTON_SetFont( hItem, &GUI_FontTahoma60 );
        BUTTON_SetText( hItem, "---" );
        BUTTON_SetFocusable( hItem, 0 );
*/

        //WM_DisableWindow( hItem );

        //hItem = BUTTON_CreateEx(700, 0, 100, 100, pMsg->hWin, WM_CF_SHOW, 0, ID_BUTTON_MENU);
        //WM_SetCallback(hItem, _cbButton_menu);

        hItem   =   WM_GetDialogItem( WM_HBKWIN, GUI_ID_BUTTON_NEXT );
        WM_SetCallback( hItem, _cbButtonNext );

        hItem   =   WM_GetDialogItem( WM_HBKWIN, GUI_ID_BUTTON_PREV );
        WM_SetCallback( hItem, _cbButtonPrev );


        //WM_SetCallback( hItem, BUTTON_Callback );
}


void    ui_dspl_init( void )
{
        //WM_HWIN         hItem;


        //GUI_Init();
        //WM_SetCreateFlags( WM_CF_MEMDEV );
        //WM_EnableMemdev( WM_HBKWIN );

        //GUI_SetOrientation( GUI_MIRROR_X | GUI_MIRROR_Y );

        GUI_SetBkColor( GUI_BLACK );
        WM_SetDesktopColor( GUI_BLACK );

        BUTTON_SetDefaultSkinClassic();
        BUTTON_SetDefaultBkColor(       GUI_BLACK,      BUTTON_CI_DISABLED      );
        BUTTON_SetDefaultBkColor(       GUI_BLACK,      BUTTON_CI_PRESSED       );
        BUTTON_SetDefaultBkColor(       GUI_BLACK,      BUTTON_CI_UNPRESSED     );
        BUTTON_SetDefaultTextColor(     GUI_GRAY,       BUTTON_CI_DISABLED      );
        BUTTON_SetDefaultTextColor(     GUI_BLUE,       BUTTON_CI_PRESSED       );
        BUTTON_SetDefaultTextColor(     GUI_LIGHTBLUE,  BUTTON_CI_UNPRESSED     );
        //BUTTON_SetDefaultFocusColor( GUI_GRAY );
        BUTTON_SetDefaultTextAlign( GUI_TA_HCENTER | GUI_TA_VCENTER );
        BUTTON_SetDefaultFont( &UI_DSPL_DFLT_FONT_BUTTON);


        TEXT_SetDefaultTextColor( GUI_LIGHTGRAY );
        TEXT_SetDefaultFont( &GUI_FontTahoma40 );
        //TEXT_SetDefaultFont( &GUI_FontSourceSansPro40 );

        SCROLLBAR_SetDefaultColor(      GUI_LIGHTBLUE,      SCROLLBAR_CI_THUMB      );
        //SCROLLBAR_SetDefaultColor(      GUI_BLACK,      SCROLLBAR_CI_SHAFT      );
        //SCROLLBAR_SetDefaultColor(      GUI_BLACK,      SCROLLBAR_CI_ARROW      );
        //SCROLLBAR_SetDefaultWidth( 40 );

        SCROLLBAR_SetDefaultSkinClassic();
        //SCROLLBAR_SetDefaultColor(      GUI_TRANSPARENT,      SCROLLBAR_CI_THUMB      );
        //SCROLLBAR_SetDefaultColor(      GUI_TRANSPARENT,      SCROLLBAR_CI_SHAFT      );
        //SCROLLBAR_SetDefaultColor(      GUI_TRANSPARENT,      SCROLLBAR_CI_ARROW      );
        //SCROLLBAR_SetDefaultWidth( 0 );



        //ui_dspl_scrn_hndl[ 4 ]  =   GUI_CreateDialogBox( ui_dspl_scr_info[4], ui_dspl_scr_info_countof[4], ui_dspl_scr4_cb, WM_HBKWIN, 0, 0 );
        ui_dspl_scrn_hndl[ 3 ]  =   GUI_CreateDialogBox( ui_dspl_scr_info[3], ui_dspl_scr_info_countof[3], ui_dspl_scr3_cb, WM_HBKWIN, 0, 0 );
        ui_dspl_scrn_hndl[ 2 ]  =   GUI_CreateDialogBox( ui_dspl_scr_info[2], ui_dspl_scr_info_countof[2], ui_dspl_scr2_cb, WM_HBKWIN, 0, 0 );
        ui_dspl_scrn_hndl[ 1 ]  =   GUI_CreateDialogBox( ui_dspl_scr_info[1], ui_dspl_scr_info_countof[1], ui_dspl_scr1_cb, WM_HBKWIN, 0, 0 );
        ui_dspl_scrn_hndl[ 0 ]  =   GUI_CreateDialogBox( ui_dspl_scr_info[0], ui_dspl_scr_info_countof[0], ui_dspl_scr0_cb, WM_HBKWIN, 0, 0 );

        WM_SetCallback( WM_HBKWIN, _cbBackgroundWin );

        ui_dspl_header_buttons_init();
}

/*
void    btn_zoom_mode(                  const   WM_HWIN         hButton,
                                                scr_t *         scr     )
{

}
*/
/*
void    ui_dspl_btn_num_update(         const   WM_HWIN         hButton,
                                                int             i       )
{
                char            str[8];

        snprintf( str, sizeof(str), "%d", i );
        BUTTON_SetText( hButton, str );
}
*/
/*
void    ui_dspl_btn_shft_mode_next(             scr_t *         scr     )
{
        scr_graph_t *   graph           = &( scr->graph );


        graph->mode++;

        if( graph->mode >= GRAPH_CTL_MODE_LAST )
        {
                graph->mode     =   GRAPH_CTL_MODE_FRST;
        }

        switch( graph->mode )
        {
                case GRAPH_CTL_MODE_H:
                        BUTTON_SetText( scr->hBtnShftLeft,  "\xA2" );
                        BUTTON_SetText( scr->hBtnShftRgth,  "\xA1" );
                        ui_dspl_btn_num_update( scr->hBtnShftMode, graph->shftY );
                        break;

                case GRAPH_CTL_MODE_V:
                        BUTTON_SetText( scr->hBtnShftLeft,  "\xAE" );
                        BUTTON_SetText( scr->hBtnShftRgth,  "\xAF" );
                        ui_dspl_btn_num_update( scr->hBtnShftMode, graph->shftX );
                        break;

                default:
                        break;
        }
}
*/