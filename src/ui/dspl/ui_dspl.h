/**
  * @file    ui_dspl.h
  * @brief   User Interface - Display
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include <app_trace.h>


#ifndef  UI_DSPL_H
#define  UI_DSPL_H


#define GUI_ID_SCR0_WINDOW                      (GUI_ID_USER + 0x000)
#define GUI_ID_SCR1_WINDOW                      (GUI_ID_USER + 0x010)
#define GUI_ID_SCR2_WINDOW                      (GUI_ID_USER + 0x020)
#define GUI_ID_SCR3_WINDOW                      (GUI_ID_USER + 0x030)
#define GUI_ID_SCR3_1_WINDOW                    (GUI_ID_USER + 0x031)

#define GUI_ID_SCR0_TEXT_HEADER                 (GUI_ID_USER + 0x100)
#define GUI_ID_SCR1_TEXT_HEADER                 (GUI_ID_USER + 0x110)
#define GUI_ID_SCR2_TEXT_HEADER                 (GUI_ID_USER + 0x120)
#define GUI_ID_SCR2_TEXT_TEMP                   (GUI_ID_USER + 0x121)
#define GUI_ID_SCR3_TEXT_HEADER                 (GUI_ID_USER + 0x130)

#define GUI_ID_SCR0_BUTTON_RWND                 (GUI_ID_USER + 0x200)
#define GUI_ID_SCR0_BUTTON_FWRD                 (GUI_ID_USER + 0x201)
#define GUI_ID_SCR0_BUTTON_FRST                 (GUI_ID_USER + 0x202)
#define GUI_ID_SCR0_BUTTON_LAST                 (GUI_ID_USER + 0x203)
#define GUI_ID_SCR0_BUTTON_ZOOMOUT              (GUI_ID_USER + 0x204)
#define GUI_ID_SCR0_BUTTON_ZOOMIN               (GUI_ID_USER + 0x205)
#define GUI_ID_SCR0_BUTTON_UP                   (GUI_ID_USER + 0x206)
#define GUI_ID_SCR0_BUTTON_DOWN                 (GUI_ID_USER + 0x207)
#define GUI_ID_SCR0_BUTTON_LEFT                 (GUI_ID_USER + 0x208)
#define GUI_ID_SCR0_BUTTON_RGHT                 (GUI_ID_USER + 0x209)
#define GUI_ID_SCR1_BUTTON_RWND                 (GUI_ID_USER + 0x210)
#define GUI_ID_SCR1_BUTTON_FWRD                 (GUI_ID_USER + 0x211)
#define GUI_ID_SCR1_BUTTON_FRST                 (GUI_ID_USER + 0x212)
#define GUI_ID_SCR1_BUTTON_LAST                 (GUI_ID_USER + 0x213)
#define GUI_ID_SCR1_BUTTON_ZOOMOUT              (GUI_ID_USER + 0x214)
#define GUI_ID_SCR1_BUTTON_ZOOMIN               (GUI_ID_USER + 0x215)
#define GUI_ID_SCR2_BUTTON_RWND                 (GUI_ID_USER + 0x220)
#define GUI_ID_SCR2_BUTTON_FWRD                 (GUI_ID_USER + 0x221)
#define GUI_ID_SCR2_BUTTON_FRST                 (GUI_ID_USER + 0x222)
#define GUI_ID_SCR2_BUTTON_LAST                 (GUI_ID_USER + 0x223)
#define GUI_ID_SCR2_BUTTON_STRT                 (GUI_ID_USER + 0x224)
#define GUI_ID_SCR2_BUTTON_CLR                  (GUI_ID_USER + 0x225)
#define GUI_ID_SCR3_BUTTON_DATE                 (GUI_ID_USER + 0x230)
#define GUI_ID_SCR3_BUTTON_TIME                 (GUI_ID_USER + 0x231)
#define GUI_ID_SCR3_BUTTON_CFG_CH1              (GUI_ID_USER + 0x232)
#define GUI_ID_SCR3_BUTTON_CFG_CH2              (GUI_ID_USER + 0x233)
#define GUI_ID_SCR3_BUTTON_CFG_CH3              (GUI_ID_USER + 0x234)
#define GUI_ID_SCR3_BUTTON_CFG_CH4              (GUI_ID_USER + 0x235)
#define GUI_ID_SCR3_BUTTON_CFG_CH5              (GUI_ID_USER + 0x236)
#define GUI_ID_SCR3_BUTTON_CFG_CH6              (GUI_ID_USER + 0x237)
#define GUI_ID_SCR3_BUTTON_CFG_CH7              (GUI_ID_USER + 0x238)
#define GUI_ID_SCR3_BUTTON_CFG_CH8              (GUI_ID_USER + 0x239)


#define GUI_ID_BUTTON_PREV                      (GUI_ID_USER + 0x2F0)
#define GUI_ID_BUTTON_NEXT                      (GUI_ID_USER + 0x2F1)

#define GUI_ID_SCR0_GRAPH                       (GUI_ID_USER + 0x300)
#define GUI_ID_SCR1_GRAPH                       (GUI_ID_USER + 0x310)

#define GUI_ID_SCR3_LSTWHL_YEAR                 (GUI_ID_USER + 0x430)

#define UI_DSPL_SIZE_X                  800
#define UI_DSPL_SIZE_Y                  480
#define UI_DSPL_BAR_SIZE_X              UI_DSPL_SIZE_X
//#define UI_DSPL_BAR_SIZE_Y              50
#define UI_DSPL_BAR_SIZE_Y              80
#define UI_DSPL_BAR_POS_X0              0
#define UI_DSPL_BAR_POS_Y0              0

//#define UI_DSPL_WIN_SIZE_X              UI_DSPL_SIZE_X
//#define UI_DSPL_WIN_SIZE_Y              (UI_DSPL_SIZE_Y - UI_DSPL_BAR_SIZE_Y)
//#define UI_DSPL_WIN_POS_X0              0
//#define UI_DSPL_WIN_POS_Y0              (0 + UI_DSPL_BAR_SIZE_Y)

#define UI_DSPL_WIN_SIZE_X              UI_DSPL_SIZE_X
#define UI_DSPL_WIN_SIZE_Y              UI_DSPL_SIZE_Y
#define UI_DSPL_WIN_POS_X0              0
#define UI_DSPL_WIN_POS_Y0              0

#define UI_DSPL_WIN_STYLE               (WM_CF_SHOW | WM_CF_MEMDEV)
#define UI_DSPL_WIN_NUMEXTRABYTES       0

#define UI_DSPL_HDR_BTN_SIZE_X          150
#define UI_DSPL_HDR_BTN_SIZE_Y          UI_DSPL_BAR_SIZE_Y

//#define UI_DSPL_HDR_TXT_SIZE_X          (UI_DSPL_BAR_SIZE_X - (UI_DSPL_HDR_BTN_SIZE_X * 2))
#define UI_DSPL_HDR_TXT_SIZE_X          UI_DSPL_BAR_SIZE_X
#define UI_DSPL_HDR_TXT_SIZE_Y          UI_DSPL_BAR_SIZE_Y
//#define UI_DSPL_HDR_COLOR_BCKGRND       GUI_DARKGRAY
#define UI_DSPL_HDR_COLOR_BCKGRND       GUI_BLACK

#define UI_DSPL_HDR_TXT_FONT            GUI_FontTahoma60


#define UI_DSPL_HDR_BTN_PREV_POS_X0     0
#define UI_DSPL_HDR_BTN_PREV_POS_Y0     UI_DSPL_BAR_POS_Y0
#define UI_DSPL_HDR_BTN_NEXT_POS_X0     (UI_DSPL_BAR_SIZE_X - UI_DSPL_HDR_BTN_SIZE_X)
#define UI_DSPL_HDR_BTN_NEXT_POS_Y0     UI_DSPL_BAR_POS_Y0
//#define UI_DSPL_HDR_TXT_POS_X0          (0 + UI_DSPL_HDR_BTN_SIZE_X)
#define UI_DSPL_HDR_TXT_POS_X0          0
#define UI_DSPL_HDR_TXT_POS_Y0          UI_DSPL_BAR_POS_Y0

#define UI_DSPL_HDR_BTN_COLOR_BCKGRND   GUI_BLACK
#define UI_DSPL_HDR_BTN_COLOR_FRAME     GUI_BLACK


extern GUI_CONST_STORAGE GUI_FONT GUI_FontCourierNew110;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontCourierNew73;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontCourierNew54;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontCourierNew41;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRobotoBlack115;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRobotoBlack77;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRobotoBlack58;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRobotoBlack44;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRobotoBlack50;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontSegoePrint49;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontSegoePrint79;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontVerdana49;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontTahoma100;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontTahoma75;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontTahoma60;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontTahoma50;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontTahoma40;


void    ui_dspl_scr3_cb(                        WM_MESSAGE *            pMsg );
void    ui_dspl_scr2_cb(                        WM_MESSAGE *            pMsg );
void    ui_dspl_scr1_cb(                        WM_MESSAGE *            pMsg );
void    ui_dspl_scr0_cb(                        WM_MESSAGE *            pMsg );

//void    ui_dspl_scr0_update( void );
//void    ui_dspl_scr0_update(                    short           d );
void    ui_dspl_scr0_update(                    int16_t *       data,
                                                size_t          size );

WM_HWIN ui_dspl_scr3_init(                      WM_CALLBACK *           cb );
WM_HWIN ui_dspl_scr2_init(                      WM_CALLBACK *           cb );
WM_HWIN ui_dspl_scr1_init(                      WM_CALLBACK *           cb );
WM_HWIN ui_dspl_scr0_init(                      WM_CALLBACK *           cb );

void    ui_dspl_scrn_slide(                     int                     dir );

void    ui_dspl_init( void );
//void    ui_dspl_loop( void );

#endif	//UI_DSPL_H
