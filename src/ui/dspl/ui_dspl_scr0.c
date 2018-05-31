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


static  WM_HWIN                 hWin;
static  GRAPH_DATA_Handle       hGraphData;
static  GRAPH_SCALE_Handle      hGraphScaleV;   // Handle of vertical scale
static  GRAPH_SCALE_Handle      hGraphScaleH;   // Handle of horizontal scale
static  int                     graph_data_offset_y;


static
void    _UserDraw(                              WM_HWIN         hWin,
                                                int             Stage   )
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

        GRAPH_SetUserDraw( hItem, _UserDraw );

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
                        Id      =   WM_GetId( pMsg->hWinSrc );                  // Id of widget
                        NCode   =   pMsg->Data.v;                               // Notification code
                        switch( NCode )
                        {
                                case WM_NOTIFICATION_CLICKED:

                                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_GRAPH );

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

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_TEXT_HEADER );
                        TEXT_SetBkColor( hItem, UI_DSPL_HDR_COLOR_BCKGRND );
                        TEXT_SetFont( hItem, &UI_DSPL_HDR_TXT_FONT );

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

/*
void    ui_dspl_scr0_update(                    int16_t *       data,
                                                size_t          size )
*/
void    ui_dspl_scr0_update(                    float *         data,
                                                size_t          size )
{
        WM_HWIN         hTextHeader     = WM_GetDialogItem( hWin, GUI_ID_SCR0_TEXT_HEADER );
        WM_HWIN         hGraph          = WM_GetDialogItem( WM_HBKWIN, GUI_ID_SCR0_GRAPH );
        float           sensor_value;
        int16_t         graph_sample;
        char            str[16];


        while( size-- )
        {
                //sensor_value    =   s10e5_to_s23e8( (int) *data++ );
                //snprintf( str, sizeof(str), "%3.3f %%", sensor_value * 10 );

                //APP_TRACE( "%04X\n", (uint32_t) *data );
                sensor_value    =   *data++;
                sensor_value    *=  UI_DSPL_GRAPH_DATA_SCALE;

                if( sensor_value > 9999 )
                {
                        sensor_value    =   9999;
                }

                snprintf( str, sizeof(str), "%3.2f PPM", sensor_value );
                TEXT_SetText( hTextHeader, str );

                graph_sample    =   (int16_t) sensor_value;
                GRAPH_DATA_YT_AddValue( hGraphData, graph_sample );
       }

        WM_BringToBottom( hGraph );
}
