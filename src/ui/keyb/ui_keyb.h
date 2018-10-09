/**
  * @file    ui_keyb.h
  * @brief   User Interface - Keyboard
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "app_trace.h"


#ifndef  UI_KEYB_H
#define  UI_KEYB_H


void    ui_keyb_init( void );

void    ui_keyb_start( void );

size_t  ui_keyb_poll( void );

void    ui_keyb_error( void );

uint8_t ui_keyb_get( void );


#endif	//UI_KEYB_H
