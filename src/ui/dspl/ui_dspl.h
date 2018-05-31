/**
  * @file    ui_dspl.h
  * @brief   User Interface - Display
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include <app_trace.h>


#ifndef  UI_DSPL_H
#define  UI_DSPL_H


#define GUI_ID_SCR0_WINDOW                      (GUI_ID_USER + 0x000)
#define GUI_ID_SCR0_TEXT_HEADER                 (GUI_ID_USER + 0x001)
#define GUI_ID_SCR0_GRAPH                       (GUI_ID_USER + 0x002)
#define GUI_ID_SCR0_BUTTON_RWND                 (GUI_ID_USER + 0x003)
#define GUI_ID_SCR0_BUTTON_FWRD                 (GUI_ID_USER + 0x004)
#define GUI_ID_SCR0_BUTTON_FRST                 (GUI_ID_USER + 0x005)
#define GUI_ID_SCR0_BUTTON_LAST                 (GUI_ID_USER + 0x006)
#define GUI_ID_SCR0_BUTTON_ZOOMOUT              (GUI_ID_USER + 0x007)
#define GUI_ID_SCR0_BUTTON_ZOOMIN               (GUI_ID_USER + 0x008)
#define GUI_ID_SCR0_BUTTON_UP                   (GUI_ID_USER + 0x009)
#define GUI_ID_SCR0_BUTTON_DOWN                 (GUI_ID_USER + 0x00A)
#define GUI_ID_SCR0_BUTTON_LEFT                 (GUI_ID_USER + 0x00B)
#define GUI_ID_SCR0_BUTTON_RGHT                 (GUI_ID_USER + 0x00C)
#define GUI_ID_SCR0_BUTTON_STORAGE              (GUI_ID_USER + 0x00D)

#define GUI_ID_SCR1_WINDOW                      (GUI_ID_USER + 0x100)
#define GUI_ID_SCR1_TEXT_HEADER                 (GUI_ID_USER + 0x101)
#define GUI_ID_SCR1_TEXT_SENS_VALUE             (GUI_ID_USER + 0x102)

#define GUI_ID_SCR2_WINDOW                      (GUI_ID_USER + 0x200)
#define GUI_ID_SCR2_TEXT_HEADER                 (GUI_ID_USER + 0x201)
#define GUI_ID_SCR2_GRAPH                       (GUI_ID_USER + 0x202)
#define GUI_ID_SCR2_BUTTON_RWND                 (GUI_ID_USER + 0x203)
#define GUI_ID_SCR2_BUTTON_FWRD                 (GUI_ID_USER + 0x204)
#define GUI_ID_SCR2_BUTTON_FRST                 (GUI_ID_USER + 0x205)
#define GUI_ID_SCR2_BUTTON_LAST                 (GUI_ID_USER + 0x206)
#define GUI_ID_SCR2_BUTTON_ZOOMOUT              (GUI_ID_USER + 0x207)
#define GUI_ID_SCR2_BUTTON_ZOOMIN               (GUI_ID_USER + 0x208)

#define GUI_ID_SCR3_WINDOW                      (GUI_ID_USER + 0x300)
#define GUI_ID_SCR3_TEXT_HEADER                 (GUI_ID_USER + 0x301)
#define GUI_ID_SCR3_TEXT_TEMP                   (GUI_ID_USER + 0x302)
#define GUI_ID_SCR3_BUTTON_RWND                 (GUI_ID_USER + 0x303)
#define GUI_ID_SCR3_BUTTON_FWRD                 (GUI_ID_USER + 0x304)
#define GUI_ID_SCR3_BUTTON_FRST                 (GUI_ID_USER + 0x305)
#define GUI_ID_SCR3_BUTTON_LAST                 (GUI_ID_USER + 0x306)
#define GUI_ID_SCR3_BUTTON_STRT                 (GUI_ID_USER + 0x307)
#define GUI_ID_SCR3_BUTTON_CLR                  (GUI_ID_USER + 0x308)

#define GUI_ID_SCR4_WINDOW                      (GUI_ID_USER + 0x400)
#define GUI_ID_SCR4_1_WINDOW                    (GUI_ID_USER + 0x401)
#define GUI_ID_SCR4_TEXT_HEADER                 (GUI_ID_USER + 0x402)
#define GUI_ID_SCR4_BUTTON_DATE                 (GUI_ID_USER + 0x403)
#define GUI_ID_SCR4_BUTTON_TIME                 (GUI_ID_USER + 0x404)
#define GUI_ID_SCR4_BUTTON_CFG_CH1              (GUI_ID_USER + 0x405)
#define GUI_ID_SCR4_BUTTON_CFG_CH2              (GUI_ID_USER + 0x406)
#define GUI_ID_SCR4_BUTTON_CFG_CH3              (GUI_ID_USER + 0x407)
#define GUI_ID_SCR4_BUTTON_CFG_CH4              (GUI_ID_USER + 0x408)
#define GUI_ID_SCR4_BUTTON_CFG_CH5              (GUI_ID_USER + 0x409)
#define GUI_ID_SCR4_BUTTON_CFG_CH6              (GUI_ID_USER + 0x40A)
#define GUI_ID_SCR4_BUTTON_CFG_CH7              (GUI_ID_USER + 0x40B)
#define GUI_ID_SCR4_BUTTON_CFG_CH8              (GUI_ID_USER + 0x40C)

#define GUI_ID_SCR4_BTN_BACK                    (GUI_ID_USER + 0x410)

#define GUI_ID_SCR4_DLG_DATE_TXT_DAY            (GUI_ID_USER + 0x411)
#define GUI_ID_SCR4_DLG_DATE_TXT_MON            (GUI_ID_USER + 0x412)
#define GUI_ID_SCR4_DLG_DATE_TXT_YEAR           (GUI_ID_USER + 0x413)
#define GUI_ID_SCR4_DLG_DATE_BTN_YEAR_UP        (GUI_ID_USER + 0x414)
#define GUI_ID_SCR4_DLG_DATE_BTN_YEAR_DN        (GUI_ID_USER + 0x415)
#define GUI_ID_SCR4_DLG_DATE_BTN_MON_UP         (GUI_ID_USER + 0x416)
#define GUI_ID_SCR4_DLG_DATE_BTN_MON_DN         (GUI_ID_USER + 0x417)
#define GUI_ID_SCR4_DLG_DATE_BTN_DAY_UP         (GUI_ID_USER + 0x418)
#define GUI_ID_SCR4_DLG_DATE_BTN_DAY_DN         (GUI_ID_USER + 0x419)

#define GUI_ID_SCR4_DLG_TIME_TXT_HOUR           (GUI_ID_USER + 0x411)
#define GUI_ID_SCR4_DLG_TIME_TXT_MIN            (GUI_ID_USER + 0x412)
#define GUI_ID_SCR4_DLG_TIME_TXT_SEC            (GUI_ID_USER + 0x413)
#define GUI_ID_SCR4_DLG_TIME_BTN_HOUR_UP        (GUI_ID_USER + 0x414)
#define GUI_ID_SCR4_DLG_TIME_BTN_HOUR_DN        (GUI_ID_USER + 0x415)
#define GUI_ID_SCR4_DLG_TIME_BTN_MIN_UP         (GUI_ID_USER + 0x416)
#define GUI_ID_SCR4_DLG_TIME_BTN_MIN_DN         (GUI_ID_USER + 0x417)
#define GUI_ID_SCR4_DLG_TIME_BTN_SEC_UP         (GUI_ID_USER + 0x418)
#define GUI_ID_SCR4_DLG_TIME_BTN_SEC_DN         (GUI_ID_USER + 0x419)

#define GUI_ID_SCR4_DLG_CHNL_TXT_PHY            (GUI_ID_USER + 0x411)
#define GUI_ID_SCR4_DLG_CHNL_TXT_RATE           (GUI_ID_USER + 0x412)
#define GUI_ID_SCR4_DLG_CHNL_TXT_PROT           (GUI_ID_USER + 0x413)
#define GUI_ID_SCR4_DLG_CHNL_BTN_UP_PHY         (GUI_ID_USER + 0x414)
#define GUI_ID_SCR4_DLG_CHNL_BTN_DN_PHY         (GUI_ID_USER + 0x415)
#define GUI_ID_SCR4_DLG_CHNL_BTN_UP_RATE        (GUI_ID_USER + 0x416)
#define GUI_ID_SCR4_DLG_CHNL_BTN_DN_RATE        (GUI_ID_USER + 0x417)
#define GUI_ID_SCR4_DLG_CHNL_BTN_UP_PROT        (GUI_ID_USER + 0x418)
#define GUI_ID_SCR4_DLG_CHNL_BTN_DN_PROT        (GUI_ID_USER + 0x419)

#define GUI_ID_BUTTON_PREV                      (GUI_ID_USER + 0xF00)
#define GUI_ID_BUTTON_NEXT                      (GUI_ID_USER + 0xF01)


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

#define UI_DSPL_SCR0_GRAPH_VSIZE                400
#define UI_DSPL_GRAPH_DATA_Y_SHFT_STEP          50
#define UI_DSPL_GRAPH_DATA_X_SHFT_STEP          50
#define UI_DSPL_GRAPH_DATA_YSIZE_MAX            (UI_DSPL_WIN_SIZE_Y - UI_DSPL_BAR_SIZE_Y)
#define UI_DSPL_GRAPH_DATA_YSIZE_MIN            (-UI_DSPL_GRAPH_DATA_YSIZE_MAX)
#define UI_DSPL_GRAPH_DATA_SCALE                1


extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontCourierNew110;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontCourierNew73;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontCourierNew54;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontCourierNew41;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontRobotoBlack115;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontRobotoBlack77;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontRobotoBlack58;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontRobotoBlack44;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontRobotoBlack50;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontSegoePrint49;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontSegoePrint79;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontVerdana49;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontTahoma20;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontTahoma40;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontTahoma50;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontTahoma60;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontTahoma75;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontTahoma100;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontTahoma255;
extern  GUI_CONST_STORAGE GUI_FONT      GUI_FontSourceSansPro40;


void    ui_dspl_scr4_cb(                        WM_MESSAGE *            pMsg );
void    ui_dspl_scr3_cb(                        WM_MESSAGE *            pMsg );
void    ui_dspl_scr2_cb(                        WM_MESSAGE *            pMsg );
void    ui_dspl_scr1_cb(                        WM_MESSAGE *            pMsg );
void    ui_dspl_scr0_cb(                        WM_MESSAGE *            pMsg );

/*
void    ui_dspl_scr0_update(                    int16_t *               data,
                                                size_t                  size );
*/
void    ui_dspl_scr1_update(                    float *         data,
                                                size_t          size );

void    ui_dspl_scr0_update(                    float *         data,
                                                size_t          size );

WM_HWIN ui_dspl_scr4_init(                      WM_CALLBACK *           cb );
//WM_HWIN ui_dspl_scr3_init(                      WM_CALLBACK *           cb );
WM_HWIN ui_dspl_scr2_init(                      WM_CALLBACK *           cb );
//WM_HWIN ui_dspl_scr1_init(                      WM_CALLBACK *           cb );
//WM_HWIN ui_dspl_scr0_init(                      WM_CALLBACK *           cb );


void    ui_dspl_scrn_slide(                     int                     dir );

void    ui_dspl_init( void );


#endif	//UI_DSPL_H
