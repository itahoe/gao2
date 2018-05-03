/**
  * @file    app_stream.c
  * @brief   Stream prototype
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef APP_STREAM_H
#define APP_STREAM_H


#include <stdint.h>
#include <stdio.h>


typedef enum    app_stream_tag_e
{
        APP_PIPE_TAG_ERROR,
        APP_PIPE_TAG_RECV,

        APP_PIPE_TAG_SER1,
        APP_PIPE_TAG_SER2,
        APP_PIPE_TAG_SER3,
        APP_PIPE_TAG_SER4,
        APP_PIPE_TAG_USB_RECV,
        APP_PIPE_TAG_CLI,
        APP_PIPE_TAG_STORAGE_CLOSE,
        APP_PIPE_TAG_STORAGE_OPEN,
        APP_PIPE_TAG_STORAGE_TOGGLE,
} app_stream_tag_t;


typedef	struct	app_stream_s
{
        app_stream_tag_t        tag;
        int16_t *               data;
        size_t                  size;
} app_stream_t;


#endif  //APP_STREAM_H
