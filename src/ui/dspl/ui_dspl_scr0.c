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


static  WM_HWIN                 hWin;
static  GRAPH_DATA_Handle       hGraphData;
static  GRAPH_SCALE_Handle      hGraphScaleV;   // Handle of vertical scale

static  int16_t                 graph_data_buf[ UI_DSPL_GRAPH_VSIZE_X ];

static  scr_t                   scr0        = { .graph.shftX    = UI_DSPL_GRAPH_DATA_DIFF_X,
                                                .graph.zoom     = 1,
                                                .idx_max        = 2, };

static  fifo16_t                graph_data  = { .data           =   graph_data_buf,
                                                .size           =   sizeof(graph_data_buf)/sizeof(graph_data_buf[0]),
                                                .tile           =   0,
                                                .head           =   0, };


static
void    graph_user_draw(                const   WM_HWIN         hWin,
                                        const   int             Stage   )
{
        if( Stage == GRAPH_DRAW_LAST )
        {
                GUI_SetColor( GUI_GRAY );
                GUI_DrawLine( UI_DSPL_GRAPH_SIZE_X/2, 0, UI_DSPL_GRAPH_SIZE_X/2, UI_DSPL_WIN_SIZE_Y );
        }
}


static
void    graph_redraw(                           fifo16_t *      data,
                                       const    scr_t *         scr     )
{
        const   scr_graph_t *   p               = &( scr->graph );
                int16_t         sample;


        fifo16_ofst_tile( data, p->shftX );

        for( int i = 0; i < UI_DSPL_GRAPH_SIZE_X; i++ )
        {
                sample  =   fifo16_get( data );
                GRAPH_DATA_YT_AddValue( hGraphData, sample * p->zoom );
        }

        //fifo16_flush( &graph_data );
        //fifo16_ofst_tile( &graph_data, p->shftX );
}


static
void    graph_update(                   const   WM_HWIN         hData,
                                                fifo16_t *      data,
                                        const   float           sample )
{
        int16_t         i;

        fifo16_put( data, (int16_t) sample );
        i       =   fifo16_get( data );
        GRAPH_DATA_YT_AddValue( hData, (int16_t) (i * scr0.graph.zoom) );
}


static
void    graph_init(                     const   WM_HWIN         hWin,
                                                int             id      )
{
        WM_HWIN         hGraph;
        int             x0      =   UI_DSPL_WIN_POS_X0;
        int             y0      =   UI_DSPL_WIN_POS_Y0;
        int             sizeX   =   UI_DSPL_GRAPH_SIZE_X;
        int             sizeY   =   UI_DSPL_GRAPH_SIZE_Y;


        hGraph          =   GRAPH_CreateEx( x0, y0, sizeX, sizeY, hWin, UI_DSPL_WIN_STYLE, 0, id );
        GRAPH_SetColor(         hGraph, GUI_BLACK,      GRAPH_CI_BK     );
        GRAPH_SetColor(         hGraph, GUI_BLACK,      GRAPH_CI_BORDER );
        GRAPH_SetColor(         hGraph, GUI_BLACK,      GRAPH_CI_FRAME  );
        GRAPH_SetColor(         hGraph, GUI_DARKGRAY,   GRAPH_CI_GRID   );

        // Add graphs
        hGraphData      =   GRAPH_DATA_YT_Create( GUI_GREEN, UI_DSPL_GRAPH_SIZE_X, 0, 0);
        GRAPH_DATA_YT_SetAlign( hGraphData, GRAPH_ALIGN_LEFT );
        GRAPH_AttachData(       hGraph, hGraphData );

        // Set graph attributes
        GRAPH_SetGridDistY(     hGraph,  50 );
        GRAPH_SetGridDistX(     hGraph, 100 );
        GRAPH_SetGridVis(       hGraph,   1 );
        //GRAPH_SetGridFixedX( hItem, 1 );
        GRAPH_SetLineStyleV(    hGraph, GUI_LS_DASH );
        GRAPH_SetUserDraw(      hGraph, graph_user_draw );

        // Create and add vertical scale
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


static
void    text_sens_update(               const   WM_HWIN         hText,
                                                float           sample )
{
        char            str[16];


        snprintf( str, sizeof(str), "%4.2f", sample );
        TEXT_SetText(           hText,  str );
        TEXT_SetBkColor(        hText,  sample < 50 ? GUI_BLACK : GUI_RED   );
        TEXT_SetTextColor(      hText,  sample < 50 ? GUI_GREEN : GUI_BLACK );
}


static
void    text_shft_update(               const   WM_HWIN         hText,
                                                int             i       )
{
        char            str[8];

        snprintf( str, sizeof(str), "%d", i );
        TEXT_SetText( hText, str );
}


static
void    text_zoom_update(               const   WM_HWIN         hText,
                                                int             i       )
{
        char            str[8];

        snprintf( str, sizeof(str), "x%d", i );
        TEXT_SetText( hText, str );
}


static
void    graph_zoom_left(                        scr_t *         scr,
                                                fifo16_t *      data    )
{
        const   WM_HWIN         hText   = WM_GetDialogItem( hWin,       GUI_ID_SCR0_TXT_ZOOM    );
                scr_graph_t *   graph   = &( scr->graph );


        graph->zoom     /=  UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP;

        if( graph->zoom < UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP )
        {
                graph->zoom     =   1;
        }

        text_zoom_update( hText, graph->zoom );
        graph_redraw( data, scr );
}


static
void    graph_zoom_rght(                        scr_t *         scr,
                                                fifo16_t *      data    )
{
        const   WM_HWIN         hText   = WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_ZOOM );
                scr_graph_t *   graph   = &( scr->graph );


        graph->zoom     *=   UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP;

        if( graph->zoom > UI_DSPL_SCR0_GRAPH_DATA_ZOOM_MAX )
        {
                graph->zoom     =   UI_DSPL_SCR0_GRAPH_DATA_ZOOM_MAX;
        }

        text_zoom_update( hText, graph->zoom );
        graph_redraw( data, scr );
}


static
void    graph_shft_left(                        scr_t *         scr,
                                                fifo16_t *      data    )
{
        const   WM_HWIN         hGraph  = WM_GetDialogItem( hWin, GUI_ID_SCR0_GRAPH     );
        const   WM_HWIN         hText   = WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SHFT  );
                scr_graph_t *   graph   = &( scr->graph );


        switch( graph->mode )
        {
                case GRAPH_CTL_MODE_H:
                        graph->shftY    +=  UI_DSPL_GRAPH_DATA_SHFT_Y_STEP;

                        if( graph->shftY >=  UI_DSPL_GRAPH_DATA_YSIZE_MAX )
                        {
                                graph->shftY        =   UI_DSPL_GRAPH_DATA_YSIZE_MAX;
                        }

                        GRAPH_DATA_YT_SetOffY( hGraphData, graph->shftY );
                        text_shft_update( hText, graph->shftY );

                        break;

                case GRAPH_CTL_MODE_V:

                        graph->shftX    +=  UI_DSPL_GRAPH_DATA_SHFT_X_STEP;

                        if( graph->shftX > UI_DSPL_GRAPH_DATA_DIFF_X )
                        {
                                graph->shftX    =   UI_DSPL_GRAPH_DATA_DIFF_X;
                        }

                        text_shft_update( hText, graph->shftX );
                        graph_redraw( data, scr );

                        break;

                default:
                        break;
        }
}


static
void    graph_shft_rght(                        scr_t *         scr,
                                                fifo16_t *      data    )
{
        const   WM_HWIN         hGraph  = WM_GetDialogItem( hWin, GUI_ID_SCR0_GRAPH     );
        const   WM_HWIN         hText   = WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SHFT  );
                scr_graph_t *   graph   = &( scr->graph );


        switch( graph->mode )
        {
                case GRAPH_CTL_MODE_H:

                        graph->shftY    -=  UI_DSPL_GRAPH_DATA_SHFT_Y_STEP;

                        if( graph->shftY <=  UI_DSPL_GRAPH_DATA_YSIZE_MIN )
                        {
                                graph->shftY    =   UI_DSPL_GRAPH_DATA_YSIZE_MIN;
                        }

                        GRAPH_DATA_YT_SetOffY( hGraphData, graph->shftY );
                        text_shft_update( hText, graph->shftY );

                        break;

                case GRAPH_CTL_MODE_V:

                        if( graph->shftX > UI_DSPL_GRAPH_DATA_SHFT_X_STEP )
                        {
                                graph->shftX    -=  UI_DSPL_GRAPH_DATA_SHFT_X_STEP;
                        }
                        else
                        {
                                graph->shftX    =   0;
                        }

                        text_shft_update( hText, graph->shftX );
                        graph_redraw( data, scr );

                        break;

                default:
                        break;
        }
}


static
void    graph_mode_next(                const   WM_HWIN         hWin,
                                                scr_t *         scr     )
{
        const   WM_HWIN         hButtonMode     = WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_MODE      );
        const   WM_HWIN         hButtonShftDn   = WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_LEFT );
        const   WM_HWIN         hButtonShftUp   = WM_GetDialogItem( hWin, GUI_ID_SCR0_BTN_SHFT_RGHT );
        const   WM_HWIN         hTextShft       = WM_GetDialogItem( hWin, GUI_ID_SCR0_TXT_SHFT      );
        const   WM_HWIN         hGraph          = WM_GetDialogItem( hWin, GUI_ID_SCR0_GRAPH         );
                scr_graph_t *   graph           = &( scr->graph );
                char            str[ 8 ];


        graph->mode++;

        if( graph->mode >= GRAPH_CTL_MODE_LAST )
        {
                graph->mode     =   GRAPH_CTL_MODE_FRST;
        }

        switch( graph->mode )
        {
                case GRAPH_CTL_MODE_H:
                        BUTTON_SetText( hButtonMode,    "\xAD" );
                        BUTTON_SetText( hButtonShftDn,  "\xA2" );
                        BUTTON_SetText( hButtonShftUp,  "\xA1" );
                        text_shft_update( hTextShft, graph->shftY );
                        break;

                case GRAPH_CTL_MODE_V:
                        BUTTON_SetText( hButtonMode,    "\xAC" );
                        BUTTON_SetText( hButtonShftDn,  "\xAE" );
                        BUTTON_SetText( hButtonShftUp,  "\xAF" );
                        text_shft_update( hTextShft, graph->shftX );
                        break;

                default:
                        snprintf( str, sizeof(str), "%d", graph->mode );
                        BUTTON_SetText( hButtonMode, str );
                        break;
        }
}


static
void    scr0_toggle(                            WM_HWIN         hWin,
                                                scr_t *         scr     )
{
        if( ++(scr->idx) >= scr->idx_max )
        {
                scr->idx        =   0;
        }

        switch( scr->idx )
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

                graph_update( hGraphData, &graph_data, sample );
                text_sens_update( hText, sample );
        }
}


void    ui_dspl_scr0_cb(                        WM_MESSAGE *    pMsg )
{
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
                                                scr0_toggle( hWin, &scr0 );
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_MODE )
                                        {
                                                graph_mode_next( hWin, &scr0 );
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_ZOOM_LEFT )
                                        {
                                                graph_zoom_left( &scr0, &graph_data );
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_ZOOM_RGHT )
                                        {
                                                graph_zoom_rght( &scr0, &graph_data );
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_SHFT_LEFT )
                                        {
                                                graph_shft_left( &scr0, &graph_data );
                                        }

                                        if( Id == GUI_ID_SCR0_BTN_SHFT_RGHT )
                                        {
                                                graph_shft_rght( &scr0, &graph_data );
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
                        text_zoom_update( hTextZoom, scr0.graph.zoom );

                        hTextShft       =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_TXT_SHFT );
                        TEXT_SetFont( hTextShft, &UI_DSPL_DFLT_FONT_BUTTON );
                        text_shft_update( hTextShft, 0 );

                        hItem           =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR0_GRAPH );
                        graph_init( hItem, GUI_ID_SCR0_GRAPH );
                        graph_redraw( &graph_data, &scr0 );
                        break;

                default:
                        WM_DefaultProc( pMsg );
                        break;
        }
}
