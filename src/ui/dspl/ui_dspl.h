/**
  * @file    ui_dspl.h
  * @brief   User Interface - Display
  * @author  Igor T. <research.tahoe@gmail.com>
  */

//#include <stdint.h>
#include "app_trace.h"
//#include "fifo.h"


#ifndef  UI_DSPL_H
#define  UI_DSPL_H


#define GUI_ID_SCR0_WIN                         (GUI_ID_USER + 0x000)
#define GUI_ID_SCR0_TXT_SENS                    (GUI_ID_USER + 0x012)
#define GUI_ID_SCR0_BTN_HEAD                    (GUI_ID_USER + 0x020)
#define GUI_ID_SCR0_BTN_SHFT_LEFT               (GUI_ID_USER + 0x021)
#define GUI_ID_SCR0_BTN_SHFT_RGHT               (GUI_ID_USER + 0x022)
#define GUI_ID_SCR0_BTN_SHFT_MODE               (GUI_ID_USER + 0x023)
#define GUI_ID_SCR0_BTN_ZOOM_LEFT               (GUI_ID_USER + 0x024)
#define GUI_ID_SCR0_BTN_ZOOM_RGHT               (GUI_ID_USER + 0x025)
#define GUI_ID_SCR0_BTN_ZOOM_MODE               (GUI_ID_USER + 0x026)
#define GUI_ID_SCR0_GRAPH                       (GUI_ID_USER + 0x030)

#define GUI_ID_SCR1_WIN                         (GUI_ID_USER + 0x100)
#define GUI_ID_SCR1_TXT_HEADER                  (GUI_ID_USER + 0x110)
#define GUI_ID_SCR1_BTN_ZOOM_LEFT               (GUI_ID_USER + 0x120)
#define GUI_ID_SCR1_BTN_ZOOM_RGHT               (GUI_ID_USER + 0x121)
#define GUI_ID_SCR1_BTN_ZOOM_MODE               (GUI_ID_USER + 0x122)
#define GUI_ID_SCR1_BTN_SHFT_LEFT               (GUI_ID_USER + 0x123)
#define GUI_ID_SCR1_BTN_SHFT_RGHT               (GUI_ID_USER + 0x124)
#define GUI_ID_SCR1_BTN_SHFT_MODE               (GUI_ID_USER + 0x125)
#define GUI_ID_SCR1_BTN_PREV                    (GUI_ID_USER + 0x126)
#define GUI_ID_SCR1_BTN_NEXT                    (GUI_ID_USER + 0x127)
#define GUI_ID_SCR1_GRAPH                       (GUI_ID_USER + 0x130)

#define GUI_ID_SCR2_WIN                         (GUI_ID_USER + 0x200)
#define GUI_ID_SCR2_TXT_HEADER                  (GUI_ID_USER + 0x210)
#define GUI_ID_SCR2_TXT_SHFT_MODE               (GUI_ID_USER + 0x211)
#define GUI_ID_SCR2_BTN_ZOOM_LEFT               (GUI_ID_USER + 0x220)
#define GUI_ID_SCR2_BTN_ZOOM_RGHT               (GUI_ID_USER + 0x221)
#define GUI_ID_SCR2_BTN_ZOOM_MODE               (GUI_ID_USER + 0x222)
#define GUI_ID_SCR2_BTN_SHFT_LEFT               (GUI_ID_USER + 0x223)
#define GUI_ID_SCR2_BTN_SHFT_RGHT               (GUI_ID_USER + 0x224)
#define GUI_ID_SCR2_BTN_SHFT_MODE               (GUI_ID_USER + 0x225)
#define GUI_ID_SCR2_BTN_SAVE                    (GUI_ID_USER + 0x226)
#define GUI_ID_SCR2_GRAPH                       (GUI_ID_USER + 0x230)

#define GUI_ID_SCR3_WINDOW                      (GUI_ID_USER + 0x300)
#define GUI_ID_SCR3_1_WINDOW                    (GUI_ID_USER + 0x301)
#define GUI_ID_SCR3_TEXT_HEADER                 (GUI_ID_USER + 0x302)
#define GUI_ID_SCR3_BUTTON_DATE                 (GUI_ID_USER + 0x303)
#define GUI_ID_SCR3_BUTTON_TIME                 (GUI_ID_USER + 0x304)
#define GUI_ID_SCR3_BUTTON_CFG_CH1              (GUI_ID_USER + 0x305)
#define GUI_ID_SCR3_BUTTON_CFG_CH2              (GUI_ID_USER + 0x306)
#define GUI_ID_SCR3_BUTTON_CFG_CH3              (GUI_ID_USER + 0x307)
#define GUI_ID_SCR3_BUTTON_CFG_CH4              (GUI_ID_USER + 0x308)
#define GUI_ID_SCR3_BUTTON_CFG_CH5              (GUI_ID_USER + 0x309)
#define GUI_ID_SCR3_BUTTON_CFG_CH6              (GUI_ID_USER + 0x30A)
#define GUI_ID_SCR3_BUTTON_CFG_CH7              (GUI_ID_USER + 0x30B)
#define GUI_ID_SCR3_BUTTON_CFG_CH8              (GUI_ID_USER + 0x30C)

#define GUI_ID_SCR3_BTN_BACK                    (GUI_ID_USER + 0x310)

#define GUI_ID_SCR3_DLG_DATE_TXT_DAY            (GUI_ID_USER + 0x311)
#define GUI_ID_SCR3_DLG_DATE_TXT_MON            (GUI_ID_USER + 0x312)
#define GUI_ID_SCR3_DLG_DATE_TXT_YEAR           (GUI_ID_USER + 0x313)
#define GUI_ID_SCR3_DLG_DATE_BTN_YEAR_UP        (GUI_ID_USER + 0x314)
#define GUI_ID_SCR3_DLG_DATE_BTN_YEAR_DN        (GUI_ID_USER + 0x315)
#define GUI_ID_SCR3_DLG_DATE_BTN_MON_UP         (GUI_ID_USER + 0x316)
#define GUI_ID_SCR3_DLG_DATE_BTN_MON_DN         (GUI_ID_USER + 0x317)
#define GUI_ID_SCR3_DLG_DATE_BTN_DAY_UP         (GUI_ID_USER + 0x318)
#define GUI_ID_SCR3_DLG_DATE_BTN_DAY_DN         (GUI_ID_USER + 0x319)

#define GUI_ID_SCR3_DLG_TIME_TXT_HOUR           (GUI_ID_USER + 0x311)
#define GUI_ID_SCR3_DLG_TIME_TXT_MIN            (GUI_ID_USER + 0x312)
#define GUI_ID_SCR3_DLG_TIME_TXT_SEC            (GUI_ID_USER + 0x313)
#define GUI_ID_SCR3_DLG_TIME_BTN_HOUR_UP        (GUI_ID_USER + 0x314)
#define GUI_ID_SCR3_DLG_TIME_BTN_HOUR_DN        (GUI_ID_USER + 0x315)
#define GUI_ID_SCR3_DLG_TIME_BTN_MIN_UP         (GUI_ID_USER + 0x316)
#define GUI_ID_SCR3_DLG_TIME_BTN_MIN_DN         (GUI_ID_USER + 0x317)
#define GUI_ID_SCR3_DLG_TIME_BTN_SEC_UP         (GUI_ID_USER + 0x318)
#define GUI_ID_SCR3_DLG_TIME_BTN_SEC_DN         (GUI_ID_USER + 0x319)

#define GUI_ID_SCR3_DLG_CHNL_TXT_PHY            (GUI_ID_USER + 0x311)
#define GUI_ID_SCR3_DLG_CHNL_TXT_RATE           (GUI_ID_USER + 0x312)
#define GUI_ID_SCR3_DLG_CHNL_TXT_PROT           (GUI_ID_USER + 0x313)
#define GUI_ID_SCR3_DLG_CHNL_BTN_UP_PHY         (GUI_ID_USER + 0x314)
#define GUI_ID_SCR3_DLG_CHNL_BTN_DN_PHY         (GUI_ID_USER + 0x315)
#define GUI_ID_SCR3_DLG_CHNL_BTN_UP_RATE        (GUI_ID_USER + 0x316)
#define GUI_ID_SCR3_DLG_CHNL_BTN_DN_RATE        (GUI_ID_USER + 0x317)
#define GUI_ID_SCR3_DLG_CHNL_BTN_UP_PROT        (GUI_ID_USER + 0x318)
#define GUI_ID_SCR3_DLG_CHNL_BTN_DN_PROT        (GUI_ID_USER + 0x319)

#define GUI_ID_BUTTON_PREV                      (GUI_ID_USER + 0xF00)
#define GUI_ID_BUTTON_NEXT                      (GUI_ID_USER + 0xF01)
//#define GUI_ID_BUTTON_HEADER                    (GUI_ID_USER + 0xF02)


#define UI_DSPL_DFLT_FONT_BUTTON                GUI_FontTahoma40
#define UI_DSPL_DFLT_FONT_HEADER                GUI_FontTahoma60


#define UI_DSPL_SIZE_X                          800
#define UI_DSPL_SIZE_Y                          480
#define UI_DSPL_BAR_SIZE_X                      UI_DSPL_SIZE_X
//#define UI_DSPL_BAR_SIZE_Y                      50
#define UI_DSPL_BAR_SIZE_Y                      80
#define UI_DSPL_BAR_POS_X0                      0
#define UI_DSPL_BAR_POS_Y0                      0

#define UI_DSPL_WIN_SIZE_X                      UI_DSPL_SIZE_X
#define UI_DSPL_WIN_SIZE_Y                      UI_DSPL_SIZE_Y
#define UI_DSPL_WIN_POS_X0                      0
#define UI_DSPL_WIN_POS_Y0                      0

#define UI_DSPL_WIN_STYLE                       (WM_CF_SHOW | WM_CF_MEMDEV)
#define UI_DSPL_WIN_NUMEXTRABYTES               0

#define UI_DSPL_HDR_BTN_SIZE_X                  150
#define UI_DSPL_HDR_BTN_SIZE_Y                  UI_DSPL_BAR_SIZE_Y
#define UI_DSPL_HDR_TXT_SIZE_X                  UI_DSPL_BAR_SIZE_X
#define UI_DSPL_HDR_TXT_SIZE_Y                  UI_DSPL_BAR_SIZE_Y
#define UI_DSPL_HDR_COLOR_BCKGRND               GUI_BLACK


#define UI_DSPL_HDR_BTN_PREV_POS_X0             0
#define UI_DSPL_HDR_BTN_PREV_POS_Y0             UI_DSPL_BAR_POS_Y0
#define UI_DSPL_HDR_BTN_NEXT_POS_X0             (UI_DSPL_BAR_SIZE_X - UI_DSPL_HDR_BTN_SIZE_X)
#define UI_DSPL_HDR_BTN_NEXT_POS_Y0             UI_DSPL_BAR_POS_Y0
//#define UI_DSPL_HDR_TXT_POS_X0                  (0 + UI_DSPL_HDR_BTN_SIZE_X)
#define UI_DSPL_HDR_TXT_POS_X0                  0
#define UI_DSPL_HDR_TXT_POS_Y0                  UI_DSPL_BAR_POS_Y0

#define UI_DSPL_HDR_BTN_COLOR_BCKGRND           GUI_BLACK
#define UI_DSPL_HDR_BTN_COLOR_FRAME             GUI_BLACK

#define UI_DSPL_GRAPH_SIZE_X                    UI_DSPL_WIN_SIZE_X
#define UI_DSPL_GRAPH_VSIZE_X                   (2 * UI_DSPL_GRAPH_SIZE_X)
#define UI_DSPL_GRAPH_DATA_DIFF_X               (UI_DSPL_GRAPH_VSIZE_X - UI_DSPL_GRAPH_SIZE_X)


#define UI_DSPL_GRAPH_SIZE_Y                    350
#define UI_DSPL_GRAPH_DATA_SIZE_Y               (UI_DSPL_GRAPH_SIZE_Y - 15)

#define UI_DSPL_GRAPH_DATA_SHFT_X_STEP          (UI_DSPL_GRAPH_SIZE_X / 4)
#define UI_DSPL_GRAPH_DATA_SHFT_Y_STEP          100

//#define UI_DSPL_GRAPH_DATA_YSIZE_MAX            (UI_DSPL_WIN_SIZE_Y - UI_DSPL_BAR_SIZE_Y)
#define UI_DSPL_GRAPH_DATA_YSIZE_MAX            1000
#define UI_DSPL_GRAPH_DATA_YSIZE_MIN            (-UI_DSPL_GRAPH_DATA_YSIZE_MAX)

#define UI_DSPL_GRAPH_DATA_SCALE                1

#define UI_DSPL_SCR0_GRAPH_DATA_ZOOM_STEP       2
#define UI_DSPL_SCR0_GRAPH_DATA_ZOOM_MAX        4

// SCR2
#define UI_DSPL_GRPH2_Y_SHFT_STEP               10


typedef enum    graph_shft_mode_e
{
        GRAPH_SHFT_MODE_FRST    = 0,
        GRAPH_SHFT_MODE_X       = 0,
        GRAPH_SHFT_MODE_Y,
        GRAPH_SHFT_MODE_LAST,
} graph_shft_mode_t;


typedef struct  scr_graph_zoom_s
{
        int16_t                 zoom;
} scr_graph_zoom_t;

typedef struct  scr_graph_shft_s
{
        int                     x;
        int                     y;
        int                     step;
        graph_shft_mode_t       mode;
} scr_graph_shft_t;

typedef struct  scr_graph_data_s
{
        int                     shft;
        int                     step;
        int16_t                 zoom;
} scr_graph_data_t;

typedef struct  scr_graph_s
{
        int16_t                 zoomX;
        //int16_t                 zoomY;
        //scr_graph_shft_t        shft;
        graph_shft_mode_t       shft_mode;
        scr_graph_data_t        x;
        scr_graph_data_t        y;
} scr_graph_t;

typedef struct  scr_s
{
        int                     idx;
        int                     idx_max;
        scr_graph_t             graph;
} scr_t;


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





void    ui_dspl_scr3_cb(                        WM_MESSAGE *            pMsg );
void    ui_dspl_scr2_cb(                        WM_MESSAGE *            pMsg );
void    ui_dspl_scr1_cb(                        WM_MESSAGE *            pMsg );
void    ui_dspl_scr0_cb(                        WM_MESSAGE *            pMsg );

void    ui_dspl_scr2_update(                    uint32_t *      data,
                                                size_t          size );

void    ui_dspl_scr1_update(                    float *         data,
                                                size_t          size );

void    ui_dspl_scr0_update(                    uint32_t *      data,
                                                size_t          size );

WM_HWIN ui_dspl_scr2_init(                      WM_CALLBACK *   cb );
WM_HWIN ui_dspl_scr1_init(                      WM_CALLBACK *   cb );

void    ui_dspl_scrn_slide(                     int             dir );

int     ui_dspl_scrn_idx_get( void );

void    ui_dspl_init( void );

void    ui_dspl_btn_header( void );

int32_t ui_dspl_offset_get( void );

void    ui_dspl_offset_inc( void );

void    ui_dspl_offset_dec( void );


#endif	//UI_DSPL_H
