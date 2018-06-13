/**
  * @file    ui_dspl_scr2.c
  * @brief   User Interface - Screen 2
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "app.h"
#include "DIALOG.h"
#include "ui_dspl.h"
#include "fifo.h"


static  WM_HWIN                 hWin;
static  GRAPH_DATA_Handle       hGraphData;
static  GRAPH_SCALE_Handle      hGraphScaleV;   // Vertical Scale Handle

static  int16_t                 graph_data_buf[ UI_DSPL_GRAPH_SIZE_X ];

static  scr_t                   scr2        = { .graph.x.shft   = UI_DSPL_GRAPH_DATA_DIFF_X,
                                                .graph.y.zoom   = 1,
                                                .idx_max        = 2, };

static  fifo16_t                graph_data  = { .data           =   graph_data_buf,
                                                .size           =   sizeof(graph_data_buf)/sizeof(graph_data_buf[0]),
                                                .tile           =   0,
                                                .head           =   0, };


static
void    graph_user_draw(                const   WM_HWIN         hWin,
                                        const   int             Stage   )
{
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
}


static
void    graph_update(                   const   WM_HWIN         hData,
                                                fifo16_t *      data,
                                        const   float           sample )
{
        int16_t         i;

        fifo16_put( data, (int16_t) sample );
        i       =   fifo16_get( data );
        GRAPH_DATA_YT_AddValue( hData, (int16_t) (i * scr2.graph.y.zoom) );
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
}


static
void    txt_shft_update(                        int             i       )
{
        const   WM_HWIN         hText   = WM_GetDialogItem( hWin, GUI_ID_SCR2_TXT_SHFT_MODE );
        char            str[8];

        snprintf( str, sizeof(str), "%d", i );
        TEXT_SetText( hText, str );
}


static
void    btn_shft_update(                const   int             i       )
{
        const   WM_HWIN         hButton = WM_GetDialogItem( hWin, GUI_ID_SCR2_BTN_SHFT_MODE );
        char            str[8];

        snprintf( str, sizeof(str), "%d", i );
        BUTTON_SetText( hButton, str );
}


static
void    btn_shft_left(                          scr_t *         scr,
                                                fifo16_t *      data    )
{
        const   WM_HWIN         hGraph  = WM_GetDialogItem( hWin, GUI_ID_SCR2_GRAPH     );
                scr_graph_t *   graph   = &( scr->graph );
                scr_graph_data_t *      x       = &( scr->graph.x );
                scr_graph_data_t *      y       = &( scr->graph.y );


        y->shft -=  UI_DSPL_GRPH2_Y_SHFT_STEP;

        if( y->shft <= UI_DSPL_GRAPH_DATA_YSIZE_MIN )
        {
                y->shft =   UI_DSPL_GRAPH_DATA_YSIZE_MIN;
        }

        GRAPH_DATA_YT_SetOffY( hGraphData, y->shft );
        txt_shft_update( y->shft );
        //btn_shft_update( graph->shftY );
}


static
void    btn_shft_rght(                          scr_t *         scr,
                                                fifo16_t *      data    )
{
        const   WM_HWIN         hGraph  = WM_GetDialogItem( hWin, GUI_ID_SCR2_GRAPH     );
                scr_graph_t *   graph   = &( scr->graph );
                scr_graph_data_t *      x       = &( scr->graph.x );
                scr_graph_data_t *      y       = &( scr->graph.y );


        y->shft +=  UI_DSPL_GRPH2_Y_SHFT_STEP;

        if( y->shft >= UI_DSPL_GRAPH_DATA_YSIZE_MAX )
        {
                y->shft =   UI_DSPL_GRAPH_DATA_YSIZE_MAX;
        }

        GRAPH_DATA_YT_SetOffY( hGraphData, y->shft );
        txt_shft_update( y->shft );
        //btn_shft_update( graph->shftY );
}


void    ui_dspl_scr2_update(                    float *         data,
                                                size_t          size )
{
        const   WM_HWIN hText   = WM_GetDialogItem( hWin,       GUI_ID_SCR2_TXT_HEADER  );
        const   WM_HWIN hGraph  = WM_GetDialogItem( hWin,       GUI_ID_SCR2_GRAPH       );
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
                TEXT_SetText( hText, str );

                graph_update( hGraphData, &graph_data, sample );
        }
}


void    ui_dspl_scr2_cb(                        WM_MESSAGE *            pMsg )
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
                                                //case GUI_ID_SCR2_BTN_ZOOM_LEFT: btn_zoom_left(  &scr2, &graph_data  );  break;
                                                //case GUI_ID_SCR2_BTN_ZOOM_RGHT: btn_zoom_rght(  &scr2, &graph_data  );  break;
                                                //case GUI_ID_SCR2_BTN_ZOOM_MODE: btn_zoom_mode(  &scr2, hWin         );  break;
                                                case GUI_ID_SCR2_BTN_SHFT_LEFT: btn_shft_left(  &scr2, &graph_data  );  break;
                                                case GUI_ID_SCR2_BTN_SHFT_RGHT: btn_shft_rght(  &scr2, &graph_data  );  break;
                                                //case GUI_ID_SCR2_BTN_SHFT_MODE: btn_shft_mode(  &scr2, hWin         );  break;
                                                default:
                                                        break;
                                        }
                                        break;

                        }
                        break;

                case WM_INIT_DIALOG:
                        hWin    =   pMsg->hWin;
                        WINDOW_SetBkColor( hWin, GUI_BLACK );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR2_TXT_HEADER );
                        TEXT_SetFont( hItem, &UI_DSPL_DFLT_FONT_HEADER );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR2_GRAPH );
                        graph_init( hItem, GUI_ID_SCR2_GRAPH );
                        graph_redraw( &graph_data, &scr2 );
                        break;

                default:
                        WM_DefaultProc(pMsg);
                        break;

        }
}
