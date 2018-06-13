/**
  * @file    ui_dspl_scr1.c
  * @brief   User Interface - Screen 1
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdlib.h>
#include <string.h>
#include "DIALOG.h"
#include "ui_dspl.h"
#include "fifo.h"


static  int16_t                 graph_data_buf[ UI_DSPL_GRAPH_SIZE_X ];

static  scr_t                   scr1        = { .graph.x.shft   = UI_DSPL_GRAPH_DATA_DIFF_X,
                                                .graph.y.zoom   = 1,
                                                .idx_max        = 2, };

static  fifo16_t                graph_data  = { .data           =   graph_data_buf,
                                                .size           =   sizeof(graph_data_buf)/sizeof(graph_data_buf[0]),
                                                .tile           =   0,
                                                .head           =   0, };

static  WM_HWIN                 hWin;
static  GRAPH_DATA_Handle       hGraphData;
static  GRAPH_SCALE_Handle      hGraphScaleV;   // Handle of vertical scale


static
void    btn_shft_update(                const   int             i       )
{
        const   WM_HWIN         hButton = WM_GetDialogItem( hWin, GUI_ID_SCR1_BTN_SHFT_MODE );
        char            str[8];

        snprintf( str, sizeof(str), "%d", i );
        BUTTON_SetText( hButton, str );
}


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


        fifo16_ofst_tile( data, p->x.shft );

        for( int i = 0; i < UI_DSPL_GRAPH_SIZE_X; i++ )
        {
                sample  =   fifo16_get( data );
                GRAPH_DATA_YT_AddValue( hGraphData, sample * p->y.zoom );
        }

        //fifo16_flush( &graph_data );
        //fifo16_ofst_tile( &graph_data, p->shftX );
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
void    btn_zoom_left(                          scr_t *         scr,
                                                fifo16_t *      data    )
{
        const   WM_HWIN         hButton = WM_GetDialogItem( hWin, GUI_ID_SCR1_BTN_ZOOM_MODE );
                scr_graph_t *   graph   = &( scr->graph );
                char            str[8];
                scr_graph_data_t *      x       = &( scr->graph.x );
                scr_graph_data_t *      y       = &( scr->graph.y );


        y->zoom /=  UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP;

        if( y->zoom < UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP )
        {
                y->zoom =   1;
        }

        //zoom_mode_update( graph->zoom );
        snprintf( str, sizeof(str), "\xAD %d", y->zoom );
        BUTTON_SetText( hButton, str );

        graph_redraw( data, scr );
}


static
void    btn_zoom_rght(                          scr_t *         scr,
                                                fifo16_t *      data    )
{
        const   WM_HWIN         hButton = WM_GetDialogItem( hWin, GUI_ID_SCR1_BTN_ZOOM_MODE );
                scr_graph_t *   graph   = &( scr->graph );
                char            str[8];
                scr_graph_data_t *      x       = &( scr->graph.x );
                scr_graph_data_t *      y       = &( scr->graph.y );


        y->zoom *=   UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP;

        if( y->zoom > UI_DSPL_SCR0_GRAPH_DATA_ZOOM_MAX )
        {
                y->zoom =   UI_DSPL_SCR0_GRAPH_DATA_ZOOM_MAX;
        }

        //zoom_mode_update( graph->zoom );
        snprintf( str, sizeof(str), "\xAD %d", y->zoom );
        BUTTON_SetText( hButton, str );

        graph_redraw( data, scr );
}


static
void    btn_zoom_mode(                          scr_t *         scr,
                                        const   WM_HWIN         hWin    )
{
}


static
void    btn_shft_left(                          scr_t *         scr,
                                                fifo16_t *      data    )
{
        const   WM_HWIN         hGraph  = WM_GetDialogItem( hWin, GUI_ID_SCR1_GRAPH     );
        //const   WM_HWIN         hText   = WM_GetDialogItem( hWin, GUI_ID_SCR1_TXT_SHFT  );
                scr_graph_t *   graph   = &( scr->graph );
                scr_graph_data_t *      x       = &( scr->graph.x );
                scr_graph_data_t *      y       = &( scr->graph.y );


        switch( graph->shft_mode )
        {
                case GRAPH_SHFT_MODE_X:

                        y->shft -=  UI_DSPL_GRAPH_DATA_SHFT_Y_STEP;

                        if( y->shft <= UI_DSPL_GRAPH_DATA_YSIZE_MIN )
                        {
                                y->shft =   UI_DSPL_GRAPH_DATA_YSIZE_MIN;
                        }

                        GRAPH_DATA_YT_SetOffY( hGraphData, y->shft );
                        btn_shft_update( y->shft );

                        break;

                case GRAPH_SHFT_MODE_Y:

                        if( x->shft > UI_DSPL_GRAPH_DATA_SHFT_X_STEP )
                        {
                                x->shft -=  UI_DSPL_GRAPH_DATA_SHFT_X_STEP;
                        }
                        else
                        {
                                x->shft =   0;
                        }

                        btn_shft_update( x->shft );
                        graph_redraw( data, scr );

                        break;

                default:
                        break;
        }
}


static
void    btn_shft_rght(                          scr_t *         scr,
                                                fifo16_t *      data    )
{
        const   WM_HWIN         hGraph  = WM_GetDialogItem( hWin, GUI_ID_SCR1_GRAPH     );
        //const   WM_HWIN         hText   = WM_GetDialogItem( hWin, GUI_ID_SCR1_TXT_SHFT  );
                scr_graph_t *   graph   = &( scr->graph );
                scr_graph_data_t *      x       = &( scr->graph.x );
                scr_graph_data_t *      y       = &( scr->graph.y );


        switch( graph->shft_mode )
        {
                case GRAPH_SHFT_MODE_X:
                        y->shft +=  UI_DSPL_GRAPH_DATA_SHFT_Y_STEP;

                        if( y->shft >=  UI_DSPL_GRAPH_DATA_YSIZE_MAX )
                        {
                                y->shft =   UI_DSPL_GRAPH_DATA_YSIZE_MAX;
                        }

                        GRAPH_DATA_YT_SetOffY( hGraphData, y->shft );
                        btn_shft_update( y->shft );

                        break;

                case GRAPH_SHFT_MODE_Y:

                        x->shft +=  UI_DSPL_GRAPH_DATA_SHFT_X_STEP;

                        if( x->shft > UI_DSPL_GRAPH_DATA_DIFF_X )
                        {
                                x->shft =   UI_DSPL_GRAPH_DATA_DIFF_X;
                        }

                        btn_shft_update( x->shft );
                        graph_redraw( data, scr );

                        break;

                default:
                        break;
        }
}


static
void    btn_shft_mode(                          scr_t *         scr,
                                        const   WM_HWIN         hWin    )
{
        const   WM_HWIN         hButtonShftDn   = WM_GetDialogItem( hWin, GUI_ID_SCR1_BTN_SHFT_LEFT );
        const   WM_HWIN         hButtonShftUp   = WM_GetDialogItem( hWin, GUI_ID_SCR1_BTN_SHFT_RGHT );
        const   WM_HWIN         hGraph          = WM_GetDialogItem( hWin, GUI_ID_SCR1_GRAPH         );
                scr_graph_t *   graph           = &( scr->graph );
                scr_graph_data_t *      x       = &( scr->graph.x );
                scr_graph_data_t *      y       = &( scr->graph.y );


        graph->shft_mode++;

        if( graph->shft_mode >= GRAPH_SHFT_MODE_LAST )
        {
                graph->shft_mode     =   GRAPH_SHFT_MODE_FRST;
        }

        switch( graph->shft_mode )
        {
                case GRAPH_SHFT_MODE_X:
                        BUTTON_SetText( hButtonShftDn,  "\xA2" );
                        BUTTON_SetText( hButtonShftUp,  "\xA1" );
                        btn_shft_update( y->shft );
                        break;

                case GRAPH_SHFT_MODE_Y:
                        BUTTON_SetText( hButtonShftDn,  "\xAE" );
                        BUTTON_SetText( hButtonShftUp,  "\xAF" );
                        btn_shft_update( x->shft );
                        break;

                default:
                        break;
        }
}


void    ui_dspl_scr1_cb(                        WM_MESSAGE *            pMsg )
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
                                        switch( Id )
                                        {
                                                case GUI_ID_SCR1_BTN_SHFT_LEFT: btn_shft_left(  &scr1, &graph_data  );  break;
                                                case GUI_ID_SCR1_BTN_SHFT_RGHT: btn_shft_rght(  &scr1, &graph_data  );  break;
                                                case GUI_ID_SCR1_BTN_SHFT_MODE: btn_shft_mode(  &scr1, hWin         );  break;
                                                case GUI_ID_SCR1_BTN_ZOOM_LEFT: btn_zoom_left(  &scr1, &graph_data  );  break;
                                                case GUI_ID_SCR1_BTN_ZOOM_RGHT: btn_zoom_rght(  &scr1, &graph_data  );  break;
                                                case GUI_ID_SCR1_BTN_ZOOM_MODE: btn_zoom_mode(  &scr1, hWin         );  break;
                                                default:
                                                        break;
                                        }
                                        break;
                        };
                        break;

                case WM_INIT_DIALOG:
                        hWin    =   pMsg->hWin;
                        WINDOW_SetBkColor( hWin, GUI_BLACK );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR1_TXT_HEADER        );
                        TEXT_SetFont( hItem, &UI_DSPL_DFLT_FONT_HEADER );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR1_GRAPH );
                        graph_init( hItem, GUI_ID_SCR1_GRAPH );
                        graph_redraw( &graph_data, &scr1 );

                        break;

                default:
                        WM_DefaultProc(pMsg);
                        break;

        }
}
