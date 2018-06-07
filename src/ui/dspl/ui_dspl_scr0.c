/**
  * @file    ui_dspl_scr0.c
  * @brief   User Interface - Screen 0
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <float.h>
#include <string.h>
#include "DIALOG.h"
#include "ui_dspl.h"
#include "fifo.h"


typedef enum    graph_ctl_mode_e
{
        GRAPH_CTL_MODE_FRST     = 0,
        GRAPH_CTL_MODE_H        = 0,
        GRAPH_CTL_MODE_V,
        GRAPH_CTL_MODE_LAST,
} graph_ctl_mode_t;


typedef struct  scr0_graph_s
{
        int                     shftY;
        int16_t                 zoom;
        graph_ctl_mode_t        mode;
} scr0_graph_t;

typedef struct  scr0_s
{
        int                     idx;
        scr0_graph_t            graph;
} scr0_t;


static  WM_HWIN                 hWin;
static  GRAPH_Handle            hGraph;
static  GRAPH_DATA_Handle       hGraphData;
static  GRAPH_SCALE_Handle      hGraphScaleV;   // Handle of vertical scale
static  GRAPH_SCALE_Handle      hGraphScaleH;   // Handle of horizontal scale
static  WM_HWIN                 hTextZoom;
static  WM_HWIN                 hTextShft;
static  int                     scr0_idx_max    = 2;
static  int16_t                 graph_data_buf[ UI_DSPL_GRAPH_XSIZE ];

static  scr0_t                  scr0    =   {   .graph.zoom     = 1, };

static  fifo16_t        graph_data      =   {   .data           =   graph_data_buf,
                                                .size           =   UI_DSPL_GRAPH_XSIZE,
                                                .tile           =   0,
                                                .head           =   0, };


static
void    ui_dspl_scr0_graph_draw(        WM_HWIN                 hWin,
                                        int                     Stage   )
{
        if( Stage == GRAPH_DRAW_LAST )
        {
                GUI_SetColor( GUI_GRAY );
                GUI_DrawLine( UI_DSPL_GRAPH_XSIZE/2, 0, UI_DSPL_GRAPH_XSIZE/2, UI_DSPL_WIN_SIZE_Y );
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
        //sizeY   =   UI_DSPL_SIZE_Y-80;
        sizeY   =   UI_DSPL_SCR0_GRAPH_VSIZE_Y;
        hItem   =   GRAPH_CreateEx( x0, y0, sizeX, sizeY, hWin, UI_DSPL_WIN_STYLE, 0, id );
        GRAPH_SetColor( hItem,  GUI_BLACK,              GRAPH_CI_BK     );
        GRAPH_SetColor( hItem,  GUI_BLACK,              GRAPH_CI_BORDER );
        GRAPH_SetColor( hItem,  GUI_BLACK,              GRAPH_CI_FRAME  );
        GRAPH_SetColor( hItem,  GUI_DARKGRAY,           GRAPH_CI_GRID   );

        //
        // Add graphs
        //
        hGraphData      = GRAPH_DATA_YT_Create( GUI_GREEN, 800, 0, 0);
        GRAPH_SetVSizeY( hItem, UI_DSPL_SCR0_GRAPH_VSIZE_Y );
        //GRAPH_SetVSizeY( hItem, UI_DSPL_SCR0_GRAPH_VSIZE*5 );
        GRAPH_SetVSizeX( hItem, UI_DSPL_GRAPH_XSIZE );
        GRAPH_AttachData( hItem, hGraphData );
        GRAPH_DATA_YT_SetAlign( hGraphData, GRAPH_ALIGN_LEFT );

        //
        // Set graph attributes
        //
        GRAPH_SetGridDistY( hItem, 50 );
        GRAPH_SetGridDistX( hItem, 100 );
        GRAPH_SetGridVis( hItem, 1 );
        //GRAPH_SetGridFixedX( hItem, 1 );

        GRAPH_SetLineStyleV( hItem, GUI_LS_DASH );

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
        //hGraphScaleH    =   GRAPH_SCALE_Create( 20, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 100 );
        //GRAPH_SCALE_SetFont( hGraphScaleH, &GUI_FontTahoma20 );
        //GRAPH_SCALE_SetTextColor( hGraphScaleH, GUI_DARKGREEN);
        //GRAPH_AttachScale( hItem, hGraphScaleH );

        //GRAPH_SCALE_SetTickDist( _hScaleH, 25 );
        GRAPH_SCALE_SetTickDist( hGraphScaleH, 100 );
}


void    ui_dspl_scr0_toggle(            WM_HWIN                 hWin,
                                        int                     idx )
{
        switch( idx )
        {
                case 0:
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SENS    )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_GRAPH       )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_ZOOM_I  )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_ZOOM    )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_ZOOM_O  )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_DN )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SHFT    )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_UP )  );
                        break;

                case 1:
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_GRAPH       )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_ZOOM_I  )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_ZOOM    )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_ZOOM_O  )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_DN )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SHFT    )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_UP )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SENS    )  );
                        break;

                default:
                        break;
        }
}


static
void    ui_dspl_scr0_graph_data_redraw( void )
{
/*
        for( U32 i = 0; i < UI_DSPL_SCR0_GRAPH_VSIZE_X; i++ )
        {
                GRAPH_DATA_YT_GetValue( hGraphData, &graph_data_buf[i], i );
                graph_data_buf[i]       *=  graph_data_scale;
        }
*/

        int16_t         sample;


        fifo16_flush( &graph_data );

        for( int i = 0; i < UI_DSPL_GRAPH_XSIZE; i++ )
        {
/*
                cnt     =   fifo16_get( &graph_data, (int16_t *) &sample );

                if( cnt > 0 )
                {
                        GRAPH_DATA_YT_AddValue( hGraphData, sample * graph_data_scale );
                }
                else
                {
                        //APP_TRACE( "%d\n", i );
                        //break;
                }
*/

                sample  =   fifo16_get( &graph_data );
                GRAPH_DATA_YT_AddValue( hGraphData, sample * scr0.graph.zoom );
        }
}


static
void    ui_dspl_scr0_graph_text_zoom_redraw( void )
{
        char            str[8];

        snprintf( str, sizeof(str), "x%d", scr0.graph.zoom );
        TEXT_SetText( hTextZoom, str );
}


static
void    ui_dspl_scr0_graph_zoom_i( void )
{
        scr0.graph.zoom /=  UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP;

        if( scr0.graph.zoom < UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP )
        {
                scr0.graph.zoom =   1;
        }

        ui_dspl_scr0_graph_text_zoom_redraw();
        ui_dspl_scr0_graph_data_redraw();
}


static
void    ui_dspl_scr0_graph_zoom_o( void )
{
        scr0.graph.zoom *=   UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP;

        if( scr0.graph.zoom > UI_DSPL_SCR0_GRAPH_DATA_ZOOM_MAX )
        {
                scr0.graph.zoom =   UI_DSPL_SCR0_GRAPH_DATA_ZOOM_MAX;
        }

        ui_dspl_scr0_graph_text_zoom_redraw();
        ui_dspl_scr0_graph_data_redraw();
}


static
void    ui_dspl_scr0_graph_text_shft_redraw( void )
{
        char            str[8];

        snprintf( str, sizeof(str), "%d", scr0.graph.shftY );
        TEXT_SetText( hTextShft, str );
}


static
void    ui_dspl_scr0_graph_shft_up( void )
{
        scr0.graph.shftY        +=  UI_DSPL_GRAPH_DATA_Y_SHFT_STEP;

        if( scr0.graph.shftY >=  UI_DSPL_GRAPH_DATA_YSIZE_MAX )
        {
                scr0.graph.shftY        =   UI_DSPL_GRAPH_DATA_YSIZE_MAX;
        }

        GRAPH_DATA_YT_SetOffY( hGraphData, scr0.graph.shftY );

        ui_dspl_scr0_graph_text_shft_redraw();
}


static
void    ui_dspl_scr0_graph_shft_dn( void )
{
        scr0.graph.shftY        -=  UI_DSPL_GRAPH_DATA_Y_SHFT_STEP;

        if( scr0.graph.shftY <=  UI_DSPL_GRAPH_DATA_YSIZE_MIN )
        {
                scr0.graph.shftY        =   UI_DSPL_GRAPH_DATA_YSIZE_MIN;
        }

        GRAPH_DATA_YT_SetOffY( hGraphData, scr0.graph.shftY );

        ui_dspl_scr0_graph_text_shft_redraw();
}


static
void    ui_dspl_scr0_graph_mode( void )
{
        WM_HWIN         hButtonMode     = WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_MODE );
        char            str[4];


        scr0.graph.mode++;

        if( scr0.graph.mode >= GRAPH_CTL_MODE_LAST )
        {
                scr0.graph.mode =   GRAPH_CTL_MODE_FRST;
        }

        switch( scr0.graph.mode )
        {
                case GRAPH_CTL_MODE_H:  strncpy( str, "--",     sizeof(str) );  break;
                case GRAPH_CTL_MODE_V:  strncpy( str, "|",      sizeof(str) );  break;
                default:
                        snprintf( str, sizeof(str), "%d", scr0.graph.mode );
                        break;
        }

        BUTTON_SetText( hButtonMode, str );
}


static
void    ui_dspl_scr0_graph_update(              float           sample )
{
        const   WM_HWIN hGraph  = WM_GetDialogItem( WM_HBKWIN, GUI_ID_SCR0_GRAPH );


        fifo16_put( &graph_data, (int16_t) sample );
        GRAPH_DATA_YT_AddValue( hGraphData, (int16_t) ( sample * scr0.graph.zoom ) );
}


static
void    ui_dspl_scr0_text_update(               float           sample )
{
        WM_HWIN         hTextHeader     = WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SENS );
        char            str[16];


        snprintf( str, sizeof(str), "%4.2f", sample );
        TEXT_SetText(           hTextHeader, str );
        TEXT_SetBkColor(        hTextHeader, sample < 50 ? GUI_BLACK    : GUI_RED   );
        TEXT_SetTextColor(      hTextHeader, sample < 50 ? GUI_GREEN    : GUI_BLACK );
}


void    ui_dspl_scr0_update(                    float *         data,
                                                size_t          size )
{
        WM_HWIN         hButtonHeader   = WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_HEADER );
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

                                        if( Id == GUI_ID_SCR0_BTN_HEADER )
                                        {
                                                if( ++(scr0.idx) >= scr0_idx_max )
                                                {
                                                        scr0.idx        =   0;
                                                }

                                                ui_dspl_scr0_toggle( hWin, scr0.idx );
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_SHFT_UP )
                                        {
                                                ui_dspl_scr0_graph_shft_up();
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_SHFT_DN )
                                        {
                                                ui_dspl_scr0_graph_shft_dn();
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_ZOOM_I )
                                        {
                                                ui_dspl_scr0_graph_zoom_i();
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_ZOOM_O )
                                        {
                                                ui_dspl_scr0_graph_zoom_o();
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_MODE )
                                        {
                                                ui_dspl_scr0_graph_mode();
                                        }

                                        break;
                        };
                        break;

                case WM_INIT_DIALOG:
                        hWin    =   pMsg->hWin;
                        WINDOW_SetBkColor( hWin, GUI_BLACK );

                        hItem           =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_BTN_HEADER );
                        BUTTON_SetFont( hItem, &UI_DSPL_HDR_TXT_FONT );

                        hItem           =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_TXT_SENS );
                        TEXT_SetBkColor( hItem, UI_DSPL_HDR_COLOR_BCKGRND );
                        TEXT_SetTextColor( hItem, GUI_GREEN );
                        TEXT_SetFont( hItem, &GUI_FontTahoma255 );
                        WM_HideWindow( hItem );

                        hTextZoom       =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_TXT_ZOOM );
                        TEXT_SetFont( hTextZoom, &UI_DSPL_DFLT_FONT_BUTTON );
                        ui_dspl_scr0_graph_text_zoom_redraw();

                        hTextShft       =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_TXT_SHFT );
                        TEXT_SetFont( hTextShft, &UI_DSPL_DFLT_FONT_BUTTON );
                        ui_dspl_scr0_graph_text_shft_redraw();

                        hGraph          =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_GRAPH );
                        ui_dspl_scr0_graph_init( hGraph, GUI_ID_SCR0_GRAPH );
                        ui_dspl_scr0_graph_data_redraw();
                        break;

                default:
                        WM_DefaultProc( pMsg );
                        break;
        }
}
