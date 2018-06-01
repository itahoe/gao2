/**
  * @file    ui_dspl_scr0.c
  * @brief   User Interface - Screen 0
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdlib.h>
#include <string.h>
#include "DIALOG.h"
#include "ui_dspl.h"
#include "float16.h"
#include <math.h>
#include <float.h>
#include "app.h"


static  WM_HWIN                 hWin;
static  GRAPH_DATA_Handle       hGraphData;
static  GRAPH_SCALE_Handle      hGraphScaleV;   // Handle of vertical scale
static  GRAPH_SCALE_Handle      hGraphScaleH;   // Handle of horizontal scale
static  int                     graph_data_offset_y;
static  int                     scr0_idx        = 0;
static  int                     scr0_idx_max    = 2;


static
void    ui_dspl_scr0_graph_draw(        WM_HWIN                 hWin,
                                        int                     Stage   )
{
        if( Stage == GRAPH_DRAW_LAST )
        {
                //char acText[] = "Temperature";
                char acText[] = "";
                GUI_RECT Rect;
                GUI_RECT RectInvalid;
                int FontSizeY;

                GUI_SetFont( &GUI_Font16B_ASCII );
                FontSizeY = GUI_GetFontSizeY();
                WM_GetInsideRect(&Rect);
                WM_GetInvalidRect(hWin, &RectInvalid);
                Rect.x1 = Rect.x0 + FontSizeY;
                GUI_SetColor( GUI_YELLOW );
                GUI_DispStringInRectEx( acText, &Rect, GUI_TA_HCENTER, strlen(acText), GUI_ROTATE_CCW );

                GUI_SetColor( GUI_GRAY );
                //GUI_DrawLine( 400, 0, 400, 480 );
                GUI_DrawLine( UI_DSPL_WIN_SIZE_X/2, 0, UI_DSPL_WIN_SIZE_X/2, UI_DSPL_WIN_SIZE_Y );
        }
}


static
void    ui_dspl_scr0_graph_init(        WM_HWIN                 hWin,
                                        int                     id )
{
        WM_HWIN         hItem;
        int             x0      =   UI_DSPL_WIN_POS_X0;
        int             y0      =   UI_DSPL_WIN_POS_Y0;
        int             sizeX   =   UI_DSPL_WIN_SIZE_X;
        int             sizeY   =   UI_DSPL_WIN_SIZE_Y - UI_DSPL_BAR_SIZE_Y;


        x0      =   UI_DSPL_WIN_POS_X0;
        y0      =   UI_DSPL_WIN_POS_Y0;
        sizeX   =   UI_DSPL_SIZE_X;
        sizeY   =   UI_DSPL_SIZE_Y-80;
        hItem   =   GRAPH_CreateEx( x0, y0, sizeX, sizeY, hWin, UI_DSPL_WIN_STYLE, 0, id );
        GRAPH_SetColor( hItem,  GUI_BLACK,              GRAPH_CI_BK     );
        GRAPH_SetColor( hItem,  GUI_BLACK,              GRAPH_CI_BORDER );
        GRAPH_SetColor( hItem,  GUI_BLACK,              GRAPH_CI_FRAME  );
        GRAPH_SetColor( hItem,  GUI_DARKGRAY,           GRAPH_CI_GRID   );

        //
        // Add graphs
        //
        hGraphData      = GRAPH_DATA_YT_Create( GUI_GREEN, 800, 0, 0);
        GRAPH_SetVSizeY( hItem, UI_DSPL_SCR0_GRAPH_VSIZE );
        GRAPH_SetVSizeX( hItem, 2000 );
        GRAPH_AttachData( hItem, hGraphData );

        //
        // Set graph attributes
        //
        GRAPH_SetGridDistY( hItem, 50 );
        GRAPH_SetGridDistX( hItem, 100 );
        GRAPH_SetGridVis( hItem, 1 );
        //GRAPH_SetGridFixedX( hItem, 1 );

        GRAPH_SetUserDraw( hItem, ui_dspl_scr0_graph_draw );

        //
        // Create and add vertical scale
        //
        //hGraphScaleV    =   GRAPH_SCALE_Create( 25, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 100 );
        hGraphScaleV    =   GRAPH_SCALE_Create( 30, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 100 );
        GRAPH_SCALE_SetFont( hGraphScaleV, &GUI_FontTahoma20 );
        GRAPH_SCALE_SetTextColor( hGraphScaleV, GUI_DARKGREEN );
        GRAPH_AttachScale( hItem, hGraphScaleV );

        //
        // Create and add horizontal scale
        //
        hGraphScaleH    =   GRAPH_SCALE_Create( 20, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 100 );
        GRAPH_SCALE_SetFont( hGraphScaleH, &GUI_FontTahoma20 );
        GRAPH_SCALE_SetTextColor( hGraphScaleH, GUI_DARKGREEN);
        GRAPH_AttachScale( hItem, hGraphScaleH );

        GRAPH_DATA_YT_SetAlign( hGraphData, GRAPH_ALIGN_LEFT );

        //GRAPH_SCALE_SetTickDist( _hScaleH, 25 );
        GRAPH_SCALE_SetTickDist( hGraphScaleH, 100 );
}


void    ui_dspl_scr0_toggle(            WM_HWIN                 hWin,
                                        int                     idx )
{
        switch( idx )
        {
                case 0:
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TEXT_SENS_VALUE )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_GRAPH       )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BUTTON_LEFT )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BUTTON_RGHT )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BUTTON_DOWN )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BUTTON_UP   )  );
                        break;

                case 1:
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_GRAPH       )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BUTTON_LEFT )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BUTTON_RGHT )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BUTTON_DOWN )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BUTTON_UP   )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TEXT_SENS_VALUE )  );
                        break;

                default:
                        break;
        }
}


static
void    ui_dspl_scr0_graph_shft_up( void )
{
        graph_data_offset_y     +=  UI_DSPL_GRAPH_DATA_Y_SHFT_STEP;

        if( graph_data_offset_y >=  UI_DSPL_GRAPH_DATA_YSIZE_MAX )
        {
                graph_data_offset_y     =   UI_DSPL_GRAPH_DATA_YSIZE_MAX;
        }

        GRAPH_DATA_YT_SetOffY( hGraphData, graph_data_offset_y );
}


static
void    ui_dspl_scr0_graph_shft_dn( void )
{
        graph_data_offset_y     -=  UI_DSPL_GRAPH_DATA_Y_SHFT_STEP;

        if( graph_data_offset_y <=  UI_DSPL_GRAPH_DATA_YSIZE_MIN )
        {
                graph_data_offset_y     =   UI_DSPL_GRAPH_DATA_YSIZE_MIN;
        }

        GRAPH_DATA_YT_SetOffY( hGraphData, graph_data_offset_y );
}


static
void    ui_dspl_scr0_graph_shft_left( void )
{
        unsigned        int     pos     =   WM_GetScrollPosH( hGraphData );

        WM_SetScrollPosH( hGraphData, pos - UI_DSPL_GRAPH_DATA_X_SHFT_STEP );
}


static
void    ui_dspl_scr0_graph_shft_rght( void )
{
        unsigned        int     pos     =   WM_GetScrollPosH( hGraphData );

        WM_SetScrollPosH( hGraphData, pos + UI_DSPL_GRAPH_DATA_X_SHFT_STEP );
}


void    ui_dspl_scr0_cb(                        WM_MESSAGE *    pMsg )
{
        WM_HWIN         hItem;
        int             NCode;
        int             Id;


        switch( pMsg->MsgId )
        {
                case WM_NOTIFY_PARENT:
                        hWin    =   pMsg->hWin;
                        Id      =   WM_GetId( pMsg->hWinSrc );                  // Id of widget
                        NCode   =   pMsg->Data.v;                               // Notification code
                        switch( NCode )
                        {
                                case WM_NOTIFICATION_CLICKED:

                                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_GRAPH );

                                        if( Id == GUI_ID_SCR0_BUTTON_HEADER )
                                        {
                                                if( ++scr0_idx >= scr0_idx_max )
                                                {
                                                        scr0_idx        =   0;
                                                }

                                                ui_dspl_scr0_toggle( hWin, scr0_idx );
                                        }

                                        if( Id == GUI_ID_SCR0_BUTTON_UP )
                                        {
                                                ui_dspl_scr0_graph_shft_up();
                                        }

                                        if( Id == GUI_ID_SCR0_BUTTON_DOWN )
                                        {
                                                ui_dspl_scr0_graph_shft_dn();
                                        }

                                        if( Id == GUI_ID_SCR0_BUTTON_LEFT )
                                        {
                                                ui_dspl_scr0_graph_shft_left();
                                        }

                                        if( Id == GUI_ID_SCR0_BUTTON_RGHT )
                                        {
                                                ui_dspl_scr0_graph_shft_rght();
                                        }

                                        break;
                        };
                        break;

                case WM_INIT_DIALOG:
                        hWin    =   pMsg->hWin;
                        WINDOW_SetBkColor( hWin, GUI_BLACK );

                        //hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_TEXT_HEADER );
                        //TEXT_SetBkColor( hItem, UI_DSPL_HDR_COLOR_BCKGRND );
                        //TEXT_SetFont( hItem, &UI_DSPL_HDR_TXT_FONT );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_BUTTON_HEADER );
                        BUTTON_SetFont( hItem, &UI_DSPL_HDR_TXT_FONT );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_TEXT_SENS_VALUE );
                        TEXT_SetBkColor( hItem, UI_DSPL_HDR_COLOR_BCKGRND );
                        TEXT_SetTextColor( hItem, GUI_GREEN );
                        TEXT_SetFont( hItem, &GUI_FontTahoma255 );
                        WM_HideWindow( hItem );


                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_GRAPH );
                        ui_dspl_scr0_graph_init( hItem, GUI_ID_SCR0_GRAPH );
                        WM_BringToBottom( hItem );
                        //WM_SetCallback(hItem, _cbGraph);
                        break;

                default:
                        WM_DefaultProc( pMsg );
                        break;
        }
}


static
void    ui_dspl_scr0_graph_update(              float           sample )
{
        WM_HWIN         hGraph          = WM_GetDialogItem( WM_HBKWIN, GUI_ID_SCR0_GRAPH );


        GRAPH_DATA_YT_AddValue( hGraphData, (int16_t) sample );
        WM_BringToBottom( hGraph );
}


static
void    ui_dspl_scr0_text_update(               float           sample )
{
        WM_HWIN         hTextHeader     = WM_GetDialogItem( hWin, GUI_ID_SCR0_TEXT_SENS_VALUE );
        char            str[16];


        snprintf( str, sizeof(str), "%4.2f", sample );
        TEXT_SetText(           hTextHeader, str );
        TEXT_SetBkColor(        hTextHeader, sample > 50 ? GUI_RED      : GUI_BLACK );
        TEXT_SetTextColor(      hTextHeader, sample > 50 ? GUI_BLACK    : GUI_GREEN );
}


void    ui_dspl_scr0_update(                    float *         data,
                                                size_t          size )
{
        WM_HWIN         hButtonHeader   = WM_GetDialogItem( hWin, GUI_ID_SCR0_BUTTON_HEADER );
        float           sample;
        char            str[16];


        while( size-- )
        {
                sample  =   *data++;

                if( sample > 9999 )
                {
                        sample  =   9999;
                }

                snprintf( str, sizeof(str), "%4.2f PPM", sample );
                BUTTON_SetText( hButtonHeader, str );

                ui_dspl_scr0_graph_update( sample );
                ui_dspl_scr0_text_update( sample );
        }
}
