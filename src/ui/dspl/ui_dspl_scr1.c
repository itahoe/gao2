/**
  * @file    ui_dspl_scr1.c
  * @brief   User Interface - Screen 1
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdlib.h>
#include <string.h>
#include "DIALOG.h"
#include "ui_dspl.h"


//static  GRAPH_Handle    hGraph;

#define MAX_VALUE 250
static GRAPH_DATA_Handle  _ahData[3]; // Array of handles for the GRAPH_DATA objects
static GRAPH_SCALE_Handle _hScaleV;   // Handle of vertical scale
static GRAPH_SCALE_Handle _hScaleH;   // Handle of horizontal scale
static GUI_COLOR _aColor[] = {GUI_RED, GUI_GREEN, GUI_LIGHTGRAY}; // Array of colors for the GRAPH_DATA objects
//static I16 _aValue[3];


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

                GUI_SetFont(&GUI_Font13_ASCII);
                FontSizeY = GUI_GetFontSizeY();
                WM_GetInsideRect(&Rect);
                WM_GetInvalidRect(hWin, &RectInvalid);
                Rect.x1 = Rect.x0 + FontSizeY;
                //GUI_SetColor( GUI_YELLOW );
                GUI_SetColor( GUI_RED );
                GUI_DispStringInRectEx( acText, &Rect, GUI_TA_HCENTER, strlen(acText), GUI_ROTATE_CCW );

                GUI_SetColor( GUI_GRAY );
                //GUI_DrawLine( 400, 0, 400, 480 );
                GUI_DrawLine( UI_DSPL_WIN_SIZE_X/2, 0, UI_DSPL_WIN_SIZE_X/2, UI_DSPL_WIN_SIZE_Y );
        }
}


/*
static
void    ui_dspl_scr1_update( void )
{
        _AddValues();
}
*/

static
void    ui_dspl_scr1_add_graph(         WM_HWIN                 hWin,
                                        int                     id )
{
        WM_HWIN         hItem;
        int             x0      =   UI_DSPL_WIN_POS_X0;
        int             y0      =   UI_DSPL_WIN_POS_Y0;
        int             sizeX   =   UI_DSPL_WIN_SIZE_X;
        int             sizeY   =   UI_DSPL_WIN_SIZE_Y;


        //x0      =   UI_DSPL_WIN_POS_X0;
        //y0      =   UI_DSPL_WIN_POS_Y0;
        //sizeX   =   UI_DSPL_SIZE_X;
        //sizeY   =   UI_DSPL_SIZE_Y;
        //hItem   =   GRAPH_CreateEx( x0, y0, sizeX, sizeY, hWin, UI_DSPL_WIN_STYLE, 0, GUI_ID_SCR1_GRAPH );
        hItem   =   GRAPH_CreateEx( x0, y0, sizeX, sizeY, hWin, UI_DSPL_WIN_STYLE, 0, id );
        GRAPH_SetColor( hItem,  GUI_BLACK,              GRAPH_CI_BK     );
        GRAPH_SetColor( hItem,  GUI_TRANSPARENT,        GRAPH_CI_BORDER );
        GRAPH_SetColor( hItem,  GUI_TRANSPARENT,        GRAPH_CI_FRAME  );
        GRAPH_SetColor( hItem,  GUI_DARKGRAY,           GRAPH_CI_GRID   );

        //
        // Add graphs
        //
        for( int i = 0; i < GUI_COUNTOF(_aColor); i++ )
        {
                //_aValue[i] = rand() % 180;
                _ahData[i] = GRAPH_DATA_YT_Create(_aColor[i], 800, 0, 0);
                GRAPH_AttachData(hItem, _ahData[i]);
        }

        //GRAPH_SetVSizeX( hItem, 1500 );

        //
        // Set graph attributes
        //
        GRAPH_SetGridDistY(     hItem,  25              );
        GRAPH_SetGridVis(       hItem,  1               );
        GRAPH_SetGridFixedX(    hItem,  1               );
        GRAPH_SetUserDraw(      hItem,  _UserDraw       );

        //
        // Create and add vertical scale
        //
        _hScaleV        =   GRAPH_SCALE_Create( 20, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 100 );
        GRAPH_SCALE_SetTextColor( _hScaleV, GUI_DARKCYAN );
        GRAPH_AttachScale( hItem, _hScaleV );

        //
        // Create and add horizontal scale
        //
        _hScaleH        =   GRAPH_SCALE_Create( 20, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 100 );
        GRAPH_SCALE_SetTextColor(_hScaleH, GUI_DARKCYAN );
        GRAPH_AttachScale(hItem, _hScaleH);

        for( int i = 0; i < GUI_COUNTOF(_aColor); i++)
        {
                GRAPH_DATA_YT_SetAlign(_ahData[i], GRAPH_ALIGN_LEFT);
        }

        //GRAPH_SCALE_SetTickDist( _hScaleH, 25 );
        GRAPH_SCALE_SetTickDist( _hScaleH, 100 );
}


void    ui_dspl_scr1_cb(                        WM_MESSAGE *            pMsg )
{

        WM_HWIN         hItem;


        //APP_TRACE_EMWIN( "ui_dspl_scr1_cb()\t", pMsg->MsgId );

        switch( pMsg->MsgId )
        {
                case WM_INIT_DIALOG:
                        // Initialization of 'Window'
                        hItem   =   pMsg->hWin;
                        WINDOW_SetBkColor( hItem, GUI_BLACK );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR1_TEXT_HEADER );
                        TEXT_SetBkColor( hItem, UI_DSPL_HDR_COLOR_BCKGRND );
                        TEXT_SetFont( hItem, &UI_DSPL_HDR_TXT_FONT );

                        hItem   =   WM_GetDialogItem( pMsg->hWin, GUI_ID_SCR1_GRAPH );
                        ui_dspl_scr1_add_graph( hItem, GUI_ID_SCR1_GRAPH );

                        //WM_SetCallback(hItem, _cbGraph);

                        break;
/*
                case WM_NOTIFY_PARENT:
                        break;

                case WM_PAINT:
                        break;
*/


case WM_TOUCH_CHILD:
        break;


                default:
                        WM_DefaultProc( pMsg );
                        break;
        }
}


WM_HWIN ui_dspl_scr1_init(              WM_CALLBACK *           cb )
{
        WM_HWIN         hWin;
        WM_HWIN         hItem;

        int     x0      =   UI_DSPL_WIN_POS_X0;
        int     y0      =   UI_DSPL_WIN_POS_Y0;
        int     sizeX   =   UI_DSPL_WIN_SIZE_X;
        int     sizeY   =   UI_DSPL_WIN_SIZE_Y;
        U32     style   =   UI_DSPL_WIN_STYLE;
        int     extra   =   0;


        hWin    =       WM_CreateWindow( x0, y0, sizeX, sizeY, style, cb, extra );
        //hWin    =       WM_CreateWindow( x0+25, y0, sizeX-50, sizeY, style, cb, extra );

        hItem   =       GRAPH_CreateEx( 0, 0, sizeX, sizeY, hWin, UI_DSPL_WIN_STYLE, 0, GUI_ID_SCR1_GRAPH );
        //hItem   =       GRAPH_CreateEx( 50, 50, sizeX-100, sizeY-100, hWin, UI_DSPL_WIN_STYLE, 0, ID_GRAPH_MEASURE );
        //hItem   =       GRAPH_CreateEx( 25, 25, sizeX-50-50, sizeY-50-50, hWin, UI_DSPL_WIN_STYLE, 0, ID_GRAPH_MEASURE );

        //GRAPH_SetColor( hItem, GUI_TRANSPARENT, GRAPH_CI_BK );
        GRAPH_SetColor( hItem,  GUI_BLACK,              GRAPH_CI_BK     );
        GRAPH_SetColor( hItem,  GUI_TRANSPARENT,        GRAPH_CI_BORDER );
        GRAPH_SetColor( hItem,  GUI_TRANSPARENT,        GRAPH_CI_FRAME  );
        GRAPH_SetColor( hItem,  GUI_DARKGRAY,           GRAPH_CI_GRID   );


        //
        // Add graphs
        //
        for( int i = 0; i < GUI_COUNTOF(_aColor); i++ )
        {
                //_aValue[i] = rand() % 180;
                _ahData[i] = GRAPH_DATA_YT_Create(_aColor[i], 800, 0, 0);
                GRAPH_AttachData(hItem, _ahData[i]);
        }

        //GRAPH_SetVSizeX( hItem, 1500 );

        //
        // Set graph attributes
        //
        GRAPH_SetGridDistY(hItem, 25);
        GRAPH_SetGridVis(hItem, 1);
        GRAPH_SetGridFixedX(hItem, 1);
        GRAPH_SetUserDraw(hItem, _UserDraw);
        //
        // Create and add vertical scale
        //
        _hScaleV        =   GRAPH_SCALE_Create( 20, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 100 );
        GRAPH_SCALE_SetTextColor(_hScaleV, GUI_DARKGREEN);
        GRAPH_AttachScale(hItem, _hScaleV);
        //
        // Create and add horizontal scale
        //
        _hScaleH        =   GRAPH_SCALE_Create( 20, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 100 );
        GRAPH_SCALE_SetTextColor(_hScaleH, GUI_DARKGREEN);
        GRAPH_AttachScale(hItem, _hScaleH);

        for( int i = 0; i < GUI_COUNTOF(_aColor); i++)
        {
                GRAPH_DATA_YT_SetAlign(_ahData[i], GRAPH_ALIGN_LEFT);
        }

        //GRAPH_SCALE_SetTickDist( _hScaleH, 25 );
        GRAPH_SCALE_SetTickDist( _hScaleH, 100 );

        //ui_dspl_scr1_add_header( hWin );

        //WM_SetCallback(hItem, _cbGraph);

        sizeX   =   60;
        sizeY   =   60;
        x0      =   UI_DSPL_WIN_SIZE_X/2 - sizeX/2 - 100;
        y0      =   UI_DSPL_WIN_SIZE_Y - sizeY - 10;

        x0      =   0 + sizeX/2 + sizeX*0 + 40;
        hItem   =   BUTTON_CreateEx( x0, y0, sizeX, sizeY,  hWin,  WM_CF_SHOW, 0, GUI_ID_SCR0_BUTTON_ZOOMOUT );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_UNPRESSED,  GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_PRESSED,    GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_DISABLED,   GUI_BLACK );
        BUTTON_SetFrameColor(   hItem, GUI_LIGHTGRAY );
        BUTTON_SetText(         hItem,  "-"  );

        x0      =   0 + sizeX/2 + sizeX*1 + 40;
        hItem   =   BUTTON_CreateEx( x0, y0, sizeX, sizeY,  hWin,  WM_CF_SHOW, 0, GUI_ID_SCR0_BUTTON_ZOOMIN );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_UNPRESSED,  GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_PRESSED,    GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_DISABLED,   GUI_BLACK );
        BUTTON_SetFrameColor(   hItem, GUI_LIGHTGRAY );
        BUTTON_SetText(         hItem,  "+"  );

        x0      =   (UI_DSPL_WIN_SIZE_X/2 - sizeX/2) - 20*1 - sizeX/2;
        hItem   =   BUTTON_CreateEx( x0, y0, sizeX, sizeY,  hWin,  WM_CF_SHOW, 0, GUI_ID_SCR0_BUTTON_RWND);
        BUTTON_SetBkColor(      hItem, BUTTON_CI_UNPRESSED,  GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_PRESSED,    GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_DISABLED,   GUI_BLACK );
        BUTTON_SetFrameColor(   hItem, GUI_LIGHTGRAY );
        BUTTON_SetText(         hItem,  "<<"  );

        x0      =   (UI_DSPL_WIN_SIZE_X/2 - sizeX/2) + 20*1 + sizeX/2;
        hItem   =   BUTTON_CreateEx( x0, y0, sizeX, sizeY,  hWin,  WM_CF_SHOW, 0, GUI_ID_SCR0_BUTTON_FWRD );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_UNPRESSED,  GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_PRESSED,    GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_DISABLED,   GUI_BLACK );
        BUTTON_SetFrameColor(   hItem, GUI_LIGHTGRAY );
        BUTTON_SetText(         hItem,  ">>"  );

        x0      =   (UI_DSPL_WIN_SIZE_X/2 - sizeX/2) - 20*2 - sizeX/2 - sizeX*1;
        hItem   =   BUTTON_CreateEx( x0, y0, sizeX, sizeY,  hWin,  WM_CF_SHOW, 0, GUI_ID_SCR0_BUTTON_FRST );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_UNPRESSED,  GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_PRESSED,    GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_DISABLED,   GUI_BLACK );
        BUTTON_SetFrameColor(   hItem, GUI_LIGHTGRAY );
        BUTTON_SetText(         hItem,  "I<"  );

        x0      =   (UI_DSPL_WIN_SIZE_X/2 - sizeX/2) + 20*2 + sizeX/2 + sizeX*1;
        hItem   =   BUTTON_CreateEx( x0, y0, sizeX, sizeY,  hWin,  WM_CF_SHOW, 0, GUI_ID_SCR0_BUTTON_LAST );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_UNPRESSED,  GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_PRESSED,    GUI_BLACK );
        BUTTON_SetBkColor(      hItem, BUTTON_CI_DISABLED,   GUI_BLACK );
        BUTTON_SetFrameColor(   hItem, GUI_LIGHTGRAY );
        BUTTON_SetText(         hItem,  ">I"  );


        //hButton = WM_GetDialogItem(hDlg, GUI_ID_BUTTON0);
        //WM_SetHasTrans( hItem );              // Set transparency flag for button


        return( hWin );
}
