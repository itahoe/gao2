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
        size_t                  shftX;
        int                     shftY;
        int16_t                 zoom;
        graph_ctl_mode_t        mode;
} scr0_graph_t;

typedef struct  scr0_s
{
        int                     idx;
        int                     idx_max;
        scr0_graph_t            graph;
} scr0_t;


static  WM_HWIN                 hWin;
static  GRAPH_DATA_Handle       hGraphData;
static  GRAPH_SCALE_Handle      hGraphScaleV;   // Handle of vertical scale
//static  WM_HWIN                 hTextZoom;

static  int16_t                 graph_data_buf[ UI_DSPL_GRAPH_VSIZE_X ];

static  scr0_t                  scr0        = { .graph.zoom     = 1,
                                                .idx_max        = 2, };

static  fifo16_t                graph_data  = { .data           =   graph_data_buf,
                                                .size           =   sizeof(graph_data_buf)/sizeof(graph_data_buf[0]),
                                                .tile           =   0,
                                                .head           =   0, };


static
void    ui_dspl_scr0_graph_draw(        const   WM_HWIN         hWin,
                                        const   int             Stage   )
{
        if( Stage == GRAPH_DRAW_LAST )
        {
                GUI_SetColor( GUI_GRAY );
                GUI_DrawLine( UI_DSPL_GRAPH_SIZE_X/2, 0, UI_DSPL_GRAPH_SIZE_X/2, UI_DSPL_WIN_SIZE_Y );
        }
}


static
void    ui_dspl_scr0_graph_text_shft_redraw(    const   WM_HWIN         hTextShft,
                                                        int             i )
{
        char            str[8];

        snprintf( str, sizeof(str), "%d", i );
        TEXT_SetText( hTextShft, str );
}


static
void    ui_dspl_scr0_graph_init(        WM_HWIN                 hWin,
                                        int                     id )
{
        WM_HWIN         hGraph;
        int             x0      =   UI_DSPL_WIN_POS_X0;
        int             y0      =   UI_DSPL_WIN_POS_Y0;
        int             sizeX   =   UI_DSPL_GRAPH_SIZE_X;
        int             sizeY   =   UI_DSPL_GRAPH_SIZE_Y;


        //APP_TRACE( "UI_DSPL_GRAPH_SIZE_X        = %d\n", UI_DSPL_GRAPH_SIZE_X           );
        //APP_TRACE( "UI_DSPL_GRAPH_DATA_SIZE_X   = %d\n", UI_DSPL_GRAPH_DATA_SIZE_X      );
        //APP_TRACE( "WM_HBKWIN                   = %d\n", WM_HBKWIN                      );
        //APP_TRACE( "hWin                        = %d\n", hWin                           );


        hGraph          =   GRAPH_CreateEx( x0, y0, sizeX, sizeY, hWin, UI_DSPL_WIN_STYLE, 0, id );
        GRAPH_SetColor(         hGraph, GUI_BLACK,      GRAPH_CI_BK     );
        GRAPH_SetColor(         hGraph, GUI_BLACK,      GRAPH_CI_BORDER );
        GRAPH_SetColor(         hGraph, GUI_BLACK,      GRAPH_CI_FRAME  );
        GRAPH_SetColor(         hGraph, GUI_DARKGRAY,   GRAPH_CI_GRID   );

        // Add graphs
        //hGraphData      =   GRAPH_DATA_YT_Create( GUI_GREEN, UI_DSPL_GRAPH_VSIZE_X, 0, 0);
        hGraphData      =   GRAPH_DATA_YT_Create( GUI_GREEN, UI_DSPL_GRAPH_SIZE_X, 0, 0);
        GRAPH_DATA_YT_SetAlign( hGraphData, GRAPH_ALIGN_LEFT );
        GRAPH_AttachData(       hGraph, hGraphData );
        //GRAPH_SetVSizeX(        hGraph, UI_DSPL_GRAPH_VSIZE_X );
        //GRAPH_SetVSizeY(        hGraph, UI_DSPL_GRAPH_DATA_SIZE_Y );

        //APP_TRACE( "hGraph                      = %d\n", hGraph                         );
        //APP_TRACE( "hGraphData                  = %d\n", hGraphData                     );

        // Set graph attributes
        GRAPH_SetGridDistY(     hGraph,  50 );
        GRAPH_SetGridDistX(     hGraph, 100 );
        GRAPH_SetGridVis(       hGraph,   1 );
        //GRAPH_SetGridFixedX( hItem, 1 );
        GRAPH_SetLineStyleV(    hGraph, GUI_LS_DASH );
        GRAPH_SetUserDraw(      hGraph, ui_dspl_scr0_graph_draw );

        // Create and add vertical scale
        //hGraphScaleV    =   GRAPH_SCALE_Create( 25, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 100 );
        hGraphScaleV    =   GRAPH_SCALE_Create( 30, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 100 );
        GRAPH_SCALE_SetFont(            hGraphScaleV,   &GUI_FontTahoma20   );
        GRAPH_SCALE_SetTextColor(       hGraphScaleV,   GUI_DARKGREEN       );
        GRAPH_AttachScale(              hGraph,         hGraphScaleV        );

        // Create and add horizontal scale
        //hGraphScaleH    =   GRAPH_SCALE_Create( 20, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 100 );
        //GRAPH_SCALE_SetFont( hGraphScaleH, &GUI_FontTahoma20 );
        //GRAPH_SCALE_SetTextColor( hGraphScaleH, GUI_DARKGREEN);
        //GRAPH_AttachScale( hItem, hGraphScaleH );

        //GRAPH_SCALE_SetTickDist( _hScaleH, 25 );
        //GRAPH_SCALE_SetTickDist( hGraphScaleH, 100 );
}


void    ui_dspl_scr0_toggle(            WM_HWIN                 hWin,
                                        int                     idx )
{
        switch( idx )
        {
                case 0:
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SENS        )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_GRAPH           )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_ZOOM_LEFT   )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_ZOOM        )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_ZOOM_RGHT   )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_LEFT   )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SHFT        )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_RGHT   )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_MODE        )  );
                        break;

                case 1:
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_MODE        )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_GRAPH           )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_ZOOM_LEFT   )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_ZOOM        )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_ZOOM_RGHT   )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_LEFT   )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SHFT        )  );
                        WM_HideWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_RGHT   )  );
                        WM_ShowWindow(  WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SENS        )  );
                        break;

                default:
                        break;
        }
}


static
void    ui_dspl_scr0_graph_mode(                WM_HWIN                 hWin )
{
        const   WM_HWIN hButtonMode     = WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_MODE      );
        const   WM_HWIN hButtonShftDn   = WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_LEFT );
        const   WM_HWIN hButtonShftUp   = WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_RGHT );
        const   WM_HWIN hTextShft       = WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SHFT      );
        const   WM_HWIN hGraph          = WM_GetDialogItem( hWin, GUI_ID_SCR0_GRAPH         );
                char    str[ 8 ];


        scr0.graph.mode++;

        if( scr0.graph.mode >= GRAPH_CTL_MODE_LAST )
        {
                scr0.graph.mode =   GRAPH_CTL_MODE_FRST;
        }

        switch( scr0.graph.mode )
        {
                case GRAPH_CTL_MODE_H:
                        BUTTON_SetText( hButtonMode,    "\xAD" );
                        BUTTON_SetText( hButtonShftDn,  "\xA2" );
                        BUTTON_SetText( hButtonShftUp,  "\xA1" );
                        ui_dspl_scr0_graph_text_shft_redraw( hTextShft, scr0.graph.shftY );
                        break;

                case GRAPH_CTL_MODE_V:
                        BUTTON_SetText( hButtonMode,    "\xAC" );
                        BUTTON_SetText( hButtonShftDn,  "\xAE" );
                        BUTTON_SetText( hButtonShftUp,  "\xAF" );
                        ui_dspl_scr0_graph_text_shft_redraw( hTextShft, scr0.graph.shftX );
                        break;

                default:
                        snprintf( str, sizeof(str), "%d", scr0.graph.mode );
                        BUTTON_SetText( hButtonMode, str );
                        break;
        }
}


static
void    ui_dspl_scr0_graph_data_redraw( void )
{
        int16_t         sample;


        fifo16_flush( &graph_data );
        fifo16_ofst_tile( &graph_data, scr0.graph.shftX );

        //for( int i = 0; i < graph_data.size; i++ )
        for( int i = 0; i < UI_DSPL_GRAPH_SIZE_X; i++ )
        {
                sample  =   fifo16_get( &graph_data );
                GRAPH_DATA_YT_AddValue( hGraphData, sample * scr0.graph.zoom );
        }

        //fifo16_flush( &graph_data );
        //fifo16_ofst_tile( &graph_data, scr0.graph.shftX );
}


static
void    ui_dspl_scr0_graph_text_zoom_redraw(    const   WM_HWIN hText )
{
        //const   WM_HWIN hText   = WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_ZOOM );
                char    str[8];

        snprintf( str, sizeof(str), "x%d", scr0.graph.zoom );
        TEXT_SetText( hText, str );
}


static
void    ui_dspl_scr0_graph_zoom_left( void )
{
        //const   WM_HWIN hWin    = WM_GetDialogItem( WM_HBKWIN,  GUI_ID_SCR0_WIN         );
        const   WM_HWIN hText   = WM_GetDialogItem( hWin,       GUI_ID_SCR0_TXT_ZOOM    );


        scr0.graph.zoom /=  UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP;

        if( scr0.graph.zoom < UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP )
        {
                scr0.graph.zoom =   1;
        }

        ui_dspl_scr0_graph_text_zoom_redraw( hText );
        ui_dspl_scr0_graph_data_redraw();
}


static
void    ui_dspl_scr0_graph_zoom_rght( void )
{
        //const   WM_HWIN hWin    = WM_GetDialogItem( WM_HBKWIN,  GUI_ID_SCR0_WIN         );
        const   WM_HWIN hText   = WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_ZOOM );


        scr0.graph.zoom *=   UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP;

        if( scr0.graph.zoom > UI_DSPL_SCR0_GRAPH_DATA_ZOOM_MAX )
        {
                scr0.graph.zoom =   UI_DSPL_SCR0_GRAPH_DATA_ZOOM_MAX;
        }

        ui_dspl_scr0_graph_text_zoom_redraw( hText );
        ui_dspl_scr0_graph_data_redraw();
}


static
void    ui_dspl_scr0_graph_shft_left( void )
{
        //const   WM_HWIN hWin    = WM_GetDialogItem( WM_HBKWIN,  GUI_ID_SCR0_WIN         );
        const   WM_HWIN hGraph  = WM_GetDialogItem( hWin, GUI_ID_SCR0_GRAPH             );
        const   WM_HWIN hText   = WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SHFT          );


        switch( scr0.graph.mode )
        {
                case GRAPH_CTL_MODE_H:
                        scr0.graph.shftY        -=  UI_DSPL_GRAPH_DATA_SHFT_Y_STEP;

                        if( scr0.graph.shftY <=  UI_DSPL_GRAPH_DATA_YSIZE_MIN )
                        {
                                scr0.graph.shftY        =   UI_DSPL_GRAPH_DATA_YSIZE_MIN;
                        }

                        GRAPH_DATA_YT_SetOffY( hGraphData, scr0.graph.shftY );
                        ui_dspl_scr0_graph_text_shft_redraw( hText, scr0.graph.shftY );
                        break;

                case GRAPH_CTL_MODE_V:

                        if( scr0.graph.shftX > UI_DSPL_GRAPH_DATA_SHFT_X_STEP )
                        {
                                scr0.graph.shftX        -=  UI_DSPL_GRAPH_DATA_SHFT_X_STEP;
                        }
                        else
                        {
                                scr0.graph.shftX        =   0;
                        }

                        ui_dspl_scr0_graph_text_shft_redraw( hText, scr0.graph.shftX );
                        ui_dspl_scr0_graph_data_redraw();

                        break;

                default:
                        break;
        }
}


static
void    ui_dspl_scr0_graph_shft_rght( void )
{
        //const   WM_HWIN hWin    = WM_GetDialogItem( WM_HBKWIN,  GUI_ID_SCR0_WIN         );
        const   WM_HWIN hGraph  = WM_GetDialogItem( hWin,       GUI_ID_SCR0_GRAPH       );
        const   WM_HWIN hText   = WM_GetDialogItem( hWin,       GUI_ID_SCR0_TXT_SHFT    );


        switch( scr0.graph.mode )
        {
                case GRAPH_CTL_MODE_H:
                        scr0.graph.shftY        +=  UI_DSPL_GRAPH_DATA_SHFT_Y_STEP;

                        if( scr0.graph.shftY >=  UI_DSPL_GRAPH_DATA_YSIZE_MAX )
                        {
                                scr0.graph.shftY        =   UI_DSPL_GRAPH_DATA_YSIZE_MAX;
                        }

                        GRAPH_DATA_YT_SetOffY( hGraphData, scr0.graph.shftY );
                        ui_dspl_scr0_graph_text_shft_redraw( hText, scr0.graph.shftY );
                        break;

                case GRAPH_CTL_MODE_V:

                        scr0.graph.shftX        +=  UI_DSPL_GRAPH_DATA_SHFT_X_STEP;

                        if( scr0.graph.shftX > UI_DSPL_GRAPH_DATA_DIFF_X )
                        {
                                scr0.graph.shftX        =   UI_DSPL_GRAPH_DATA_DIFF_X;
                        }

                        ui_dspl_scr0_graph_text_shft_redraw( hText, scr0.graph.shftX );
                        ui_dspl_scr0_graph_data_redraw();

                        break;

                default:
                        break;
        }
}


static
void    ui_dspl_scr0_update_graph(      const   WM_HWIN         hGraphData,
                                                float           sample )
{
        int16_t         i;

        fifo16_put( &graph_data, (int16_t) sample );
        i       =   fifo16_get( &graph_data );
        GRAPH_DATA_YT_AddValue( hGraphData, (int16_t) ( i * scr0.graph.zoom ) );
}


static
void    ui_dspl_scr0_update_text(       const   WM_HWIN         hText,
                                                float           sample )
{
        char            str[16];


        snprintf( str, sizeof(str), "%4.2f", sample );
        TEXT_SetText(           hText,  str );
        TEXT_SetBkColor(        hText,  sample < 50 ? GUI_BLACK : GUI_RED   );
        TEXT_SetTextColor(      hText,  sample < 50 ? GUI_GREEN         : GUI_BLACK );
}


void    ui_dspl_scr0_update(                    float *         data,
                                                size_t          size )
{
        //const   WM_HWIN hWin    = WM_GetDialogItem( WM_HBKWIN,  GUI_ID_SCR0_WIN         );
        const   WM_HWIN hButton = WM_GetDialogItem( hWin,       GUI_ID_SCR0_BTN_HEADER  );
        const   WM_HWIN hGraph  = WM_GetDialogItem( hWin,       GUI_ID_SCR0_GRAPH       );
        const   WM_HWIN hText   = WM_GetDialogItem( hWin,       GUI_ID_SCR0_TXT_SENS    );
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
                BUTTON_SetText( hButton, str );

                ui_dspl_scr0_update_graph(      hGraphData,     sample );
                ui_dspl_scr0_update_text(       hText,          sample );
        }
}


void    ui_dspl_scr0_cb(                        WM_MESSAGE *    pMsg )
{
        //WM_HWIN         hWin;
        WM_HWIN         hItem;
        WM_HWIN         hTextShft;
        WM_HWIN         hTextZoom;
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

                                        if( Id == GUI_ID_SCR0_BTN_HEADER )
                                        {
                                                if( ++(scr0.idx) >= scr0.idx_max )
                                                {
                                                        scr0.idx        =   0;
                                                }

                                                ui_dspl_scr0_toggle( hWin, scr0.idx );
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_MODE )
                                        {
                                                ui_dspl_scr0_graph_mode( hWin );
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_ZOOM_LEFT )
                                        {
                                                ui_dspl_scr0_graph_zoom_left();
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_ZOOM_RGHT )
                                        {
                                                ui_dspl_scr0_graph_zoom_rght();
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_SHFT_LEFT )
                                        {
                                                ui_dspl_scr0_graph_shft_left();
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_SHFT_RGHT )
                                        {
                                                ui_dspl_scr0_graph_shft_rght();
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
                        TEXT_SetBkColor(        hItem, UI_DSPL_HDR_COLOR_BCKGRND );
                        TEXT_SetTextColor(      hItem, GUI_GREEN                );
                        TEXT_SetFont(           hItem, &GUI_FontTahoma255       );
                        WM_HideWindow( hItem );

                        hTextZoom       =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_TXT_ZOOM );
                        TEXT_SetFont( hTextZoom, &UI_DSPL_DFLT_FONT_BUTTON );
                        ui_dspl_scr0_graph_text_zoom_redraw( hTextZoom );

                        hTextShft       =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_TXT_SHFT );
                        TEXT_SetFont( hTextShft, &UI_DSPL_DFLT_FONT_BUTTON );
                        ui_dspl_scr0_graph_text_shft_redraw( hTextShft, 0 );

                        hItem           =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_GRAPH );
                        ui_dspl_scr0_graph_init( hItem, GUI_ID_SCR0_GRAPH );
                        ui_dspl_scr0_graph_data_redraw();
                        break;

                default:
                        WM_DefaultProc( pMsg );
                        break;
        }
}
