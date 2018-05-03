/**
  * @file    ui_dspl_scr0.c
  * @brief   User Interface - Screen 0
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdlib.h>
#include <string.h>
#include "DIALOG.h"
#include "ui_dspl.h"


//#define MAX_VALUE 200
#define MAX_VALUE 1000
static GRAPH_DATA_Handle  _ahData[3]; // Array of handles for the GRAPH_DATA objects
static GRAPH_SCALE_Handle _hScaleV;   // Handle of vertical scale
static GRAPH_SCALE_Handle _hScaleH;   // Handle of horizontal scale
//static GUI_COLOR _aColor[] = {GUI_RED, GUI_GREEN, GUI_LIGHTGRAY}; // Array of colors for the GRAPH_DATA objects
static GUI_COLOR _aColor[] = { GUI_GREEN }; // Array of colors for the GRAPH_DATA objects
static I16 _aValue[3];


static
void    _UserDraw( WM_HWIN hWin, int Stage )
{
        if( Stage == GRAPH_DRAW_LAST )
        {
                //char acText[] = "Temperature";
                char acText[] = "";
                GUI_RECT Rect;
                GUI_RECT RectInvalid;
                int FontSizeY;

                //GUI_SetFont(&GUI_Font13_ASCII);
                GUI_SetFont( &GUI_Font16B_ASCII );
                FontSizeY = GUI_GetFontSizeY();
                WM_GetInsideRect(&Rect);
                WM_GetInvalidRect(hWin, &RectInvalid);
                Rect.x1 = Rect.x0 + FontSizeY;
                GUI_SetColor( GUI_YELLOW );
                //GUI_SetColor( GUI_RED );
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
        int             sizeY   =   UI_DSPL_WIN_SIZE_Y;


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
        for( int i = 0; i < GUI_COUNTOF(_aColor); i++ )
        {
                _aValue[i] = rand() % 180;
                _ahData[i] = GRAPH_DATA_YT_Create(_aColor[i], 800, 0, 0);
//GRAPH_SetVSizeY( hItem, 2000 );
GRAPH_SetVSizeY( hItem, 400 );
GRAPH_SetVSizeX( hItem, 2000 );
                GRAPH_AttachData(hItem, _ahData[i]);
        }

        //GRAPH_SetVSizeX( hItem, 1500 );

        //
        // Set graph attributes
        //
        //GRAPH_SetGridDistY(hItem, 25);
        GRAPH_SetGridDistY( hItem, 50 );

        GRAPH_SetGridVis(hItem, 1);

        GRAPH_SetGridDistX( hItem, 100 );
        //GRAPH_SetGridFixedX(hItem, 1);

        GRAPH_SetUserDraw(hItem, _UserDraw);

        //
        // Create and add vertical scale
        //
        //GUI_SetFont( &GUI_Font16B_ASCII );
        //_hScaleV        =   GRAPH_SCALE_Create( 20, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 100 );
        _hScaleV        =   GRAPH_SCALE_Create( 25, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 100 );
        GRAPH_SCALE_SetTextColor( _hScaleV, GUI_DARKGREEN );
        GRAPH_AttachScale( hItem, _hScaleV );
        //
        // Create and add horizontal scale
        //
        //_hScaleH        =   GRAPH_SCALE_Create( 20, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 100 );
        _hScaleH        =   GRAPH_SCALE_Create( 20, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 100 );
        GRAPH_SCALE_SetTextColor(_hScaleH, GUI_DARKGREEN);
        GRAPH_AttachScale(hItem, _hScaleH);

        for( int i = 0; i < GUI_COUNTOF(_aColor); i++)
        {
                GRAPH_DATA_YT_SetAlign(_ahData[i], GRAPH_ALIGN_LEFT);
        }

        //GRAPH_SCALE_SetTickDist( _hScaleH, 25 );
        GRAPH_SCALE_SetTickDist( _hScaleH, 100 );

}


void    ui_dspl_scr0_cb(                        WM_MESSAGE *            pMsg )
{
        WM_HWIN         hItem;
        int             NCode;
        int             Id;
        int             pos;
        int             scroll_step     = 75;

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
                                                pos     =   WM_GetScrollPosV( hItem );
                                                WM_SetScrollPosV( hItem, pos + scroll_step );
                                        }

                                        if( Id == GUI_ID_SCR0_BUTTON_DOWN )
                                        {
                                                pos     =   WM_GetScrollPosV( hItem );
                                                WM_SetScrollPosV( hItem, pos - scroll_step);
                                        }

                                        if( Id == GUI_ID_SCR0_BUTTON_LEFT )
                                        {
                                                pos     =   WM_GetScrollPosH( hItem );
                                                WM_SetScrollPosH( hItem, pos - scroll_step );
                                        }

                                        if( Id == GUI_ID_SCR0_BUTTON_RGHT )
                                        {
                                                pos     =   WM_GetScrollPosH( hItem );
                                                WM_SetScrollPosH( hItem, pos + scroll_step );
                                        }

                                        break;
                        };
                        break;

                case WM_INIT_DIALOG:
                        hItem   =   pMsg->hWin;
                        WINDOW_SetBkColor( hItem, GUI_BLACK );

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


void    ui_dspl_scr0_update(                    int16_t *       data,
                                                size_t          size )
{
        WM_HWIN         hItem;
/*
        unsigned        i;

        for( i = 0; i < GUI_COUNTOF(_aColor); i++ )
        {
                int     Add     = ((unsigned)rand()) % (2 + i * i);
                int     Vz      = (((unsigned)(rand()) % 2) << 1) - 1;

                //_aValue[i]      += Add * Vz;

                if( _aValue[i] > MAX_VALUE )
                {
                        _aValue[i]      = MAX_VALUE;
                }
                else if( _aValue[i] < 0 )
                {
                        _aValue[i] = 0;
                }

                _aValue[i]      =   d;

                GRAPH_DATA_YT_AddValue( _ahData[i], _aValue[i] );
        }
*/

        while( size-- )
        {
                _aValue[ 0 ]      =   *data++;
                GRAPH_DATA_YT_AddValue( _ahData[ 0 ], _aValue[ 0 ] );
        }

        hItem   =   WM_GetDialogItem( WM_HBKWIN, GUI_ID_SCR0_GRAPH );
        WM_BringToBottom( hItem );
}
