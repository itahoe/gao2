/**
  * @file    task_sensor.c
  * @brief   Sensor data recieve task.
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <math.h>
#include <stdbool.h>
#include "app_pipe.h"
#include "app_fifo.h"
#include "app_trace.h"
#include "cmsis_os.h"
#include "app_fifo.h"
#include "bsp.h"
//#include "bsp_ser.h"
#include "modbus.h"


//#define CONF_SER_POLLING_CYCLE_mSEC     1000
#define CONF_SER_POLLING_CYCLE_mSEC     500
#define CONF_SER4_RECV_BLCK_SIZE_OCT    64


#pragma pack(4)
//static  int16_t         ser4_recv_data[ CONF_SER4_RECV_BLCK_SIZE_OCT ];
static  uint8_t         data_modbus_rqst[ MODBUS_RTU_FRAME_SIZE_MAX_OCT ];
static  uint8_t         data_modbus_resp[ MODBUS_RTU_FRAME_SIZE_MAX_OCT ];
#pragma pack(4)

//static  int16_t         data_sens;
//static  uint32_t        data_sens;
static  uint32_t        data_sens[2];
//static  size_t          offset;

typedef struct  modbus_dev_map_s
{
        modbus_reg_t    device_status;
        modbus_reg_t    alarm_status;
        modbus_reg_t    device_year_month;
        modbus_reg_t    device_day_hour;
        modbus_reg_t    device_minute_second;
        modbus_reg_t    sensor_temperature;
        modbus_reg_t    board_temperature;
        modbus_reg_t    sensor_signal_real;
        modbus_reg_t    sensor_signal_exponent;
        modbus_reg_t    sensor_calc_zero_offset_real;
        modbus_reg_t    sensor_calc_zero_offset_exponent;
        modbus_reg_t    sensor_calc_sensitivity_coef_real;
        modbus_reg_t    sensor_calc_sensitivity_coef_exponent;
        modbus_reg_t    sensor_value;
        modbus_reg_t    sensor_value_high;
        modbus_reg_t    sensor_value_low;
        modbus_reg_t    current_loop_value;
        modbus_reg_t    sensor_id;
        modbus_reg_t    version;
        modbus_reg_t    sensor_scale_min_real;
        modbus_reg_t    sensor_scale_min_exponent;
        modbus_reg_t    sensor_scale_max_real;
        modbus_reg_t    sensor_scale_max_exponent;
        modbus_reg_t    sensor_scale_dimension;
        modbus_reg_t    sensor_threshold_warning_real;
        modbus_reg_t    sensor_threshold_warning_exponent;
        modbus_reg_t    sensor_threshold_alarm_real;
        modbus_reg_t    sensor_threshold_alarm_exponent;
} modbus_dev_map_t;


typedef struct  modbus_dev_s
{
        uint8_t                 addr;
        modbus_dev_map_t        reg;
} modbus_dev_t;


static  const   modbus_dev_t    dev     =
{
        //.addr                                           = 255,
        .addr                                           = 13,
        .reg.device_status                              = { 31001, 1 },
        .reg.alarm_status                               = { 31002, 1 },
        .reg.device_year_month                          = { 31005, 1 },
        .reg.device_day_hour                            = { 31006, 1 },
        .reg.device_minute_second                       = { 31007, 1 },
        .reg.sensor_temperature                         = { 31011, 1 },
        .reg.board_temperature                          = { 31012, 1 },
        .reg.sensor_signal_real                         = { 31021, 1 },
        .reg.sensor_signal_exponent                     = { 31022, 1 },
        .reg.sensor_calc_zero_offset_real               = { 31023, 1 },
        .reg.sensor_calc_zero_offset_exponent           = { 31024, 1 },
        .reg.sensor_calc_sensitivity_coef_real          = { 31025, 1 },
        .reg.sensor_calc_sensitivity_coef_exponent      = { 31026, 1 },
        .reg.sensor_value                               = { 33000, 2 },
        .reg.sensor_value_high                          = { 33000, 1 },
        .reg.sensor_value_low                           = { 33001, 1 },
        .reg.current_loop_value                         = { 33002, 1 },
        .reg.sensor_id                                  = { 40401, 6 },
        .reg.version                                    = { 40417, 3 },
        .reg.sensor_scale_min_real                      = { 41001, 1 },
        .reg.sensor_scale_min_exponent                  = { 41002, 1 },
        .reg.sensor_scale_max_real                      = { 41003, 1 },
        .reg.sensor_scale_max_exponent                  = { 41004, 1 },
        .reg.sensor_scale_dimension                     = { 41005, 1 },
        .reg.sensor_threshold_warning_real              = { 41011, 1 },
        .reg.sensor_threshold_warning_exponent          = { 41012, 1 },
        .reg.sensor_threshold_alarm_real                = { 41013, 1 },
        .reg.sensor_threshold_alarm_exponent            = { 41014, 1 },
};


extern  QueueHandle_t           que_sens_hndl;
extern  QueueHandle_t           que_ui_hndl;
extern  QueueHandle_t           que_strg_hndl;


typedef union
{
        uint32_t        u32;
        float           f;
        uint16_t        u16[ 2 ];
        int16_t         i16[ 2 ];
        uint8_t         u8[  4 ];
} conc_t;


void    task_sensor(                    const   void *          argument )
{
        //TickType_t              polling_cycle_tcks      = CONF_SER_POLLING_CYCLE_mSEC / portTICK_PERIOD_MS;
        //TickType_t              polling_cycle_tcks      = 500 / portTICK_PERIOD_MS;
        TickType_t              polling_cycle_tcks      = 1000 / portTICK_PERIOD_MS;
        bool                    received;
        //bool                    not_empty;
        app_pipe_t              pipe;
        size_t                  len;
        modbus_rtu_t            rtu;
        int                     err;
        conc_t                  c;
        //float                   sens_uA;
        //float                   ppm;


        (void) argument;

        osDelay( 1000 );

        modbus_rtu_init(        &rtu,
                                dev.addr,
                                data_modbus_rqst,
                                data_modbus_resp       );

        bsp_ser1_init( 9600 );


        while( true )
        {
                received        =   xQueueReceive( que_sens_hndl, &pipe, polling_cycle_tcks );

                if( received )
                {
                        switch( pipe.tag )
                        {
                                case APP_PIPE_TAG_SER1_ERR:
                                        //APP_TRACE( "err\n" );
                                        //rtu.resp.offset++;
                                        //bsp_ser1_recv( data_modbus_resp, sizeof( data_modbus_resp ) );
                                        break;

                                case APP_PIPE_TAG_SER1_IDLE:

                                        rtu.resp.len    =   sizeof( data_modbus_resp )- pipe.cnt;
                                        rtu.resp.offset =   0;
                                        err             =   modbus_rtu_resp( &rtu );

                                        if( err == 0 )
                                        {
                                                c.u8[ 0]        =   rtu.resp.data[ 4];
                                                c.u8[ 1]        =   rtu.resp.data[ 3];
                                                c.u8[ 2]        =   rtu.resp.data[ 6];
                                                c.u8[ 3]        =   rtu.resp.data[ 5];

                                                data_sens[0]    =   c.u32;
                                                //data_sens[0]    =   c.f;

                                                c.u8[0]         =   rtu.resp.data[ 8];
                                                c.u8[1]         =   rtu.resp.data[ 7];
                                                c.u8[2]         =   rtu.resp.data[10];
                                                c.u8[3]         =   rtu.resp.data[ 9];
                                                data_sens[1]    =   c.u32;
                                                //data_sens[1]    =   c.f;
                                        }

                                        pipe.tag        =   APP_PIPE_TAG_SENS_01_DATA;
                                        pipe.cnt        =   2;
                                        //pipe.cnt        =   1;
                                        pipe.data       =   &data_sens;
                                        xQueueSend( que_ui_hndl,  &pipe, NULL );
                                        xQueueSend( que_strg_hndl,  &pipe, NULL );

                                        //APP_TRACE( "%X\n", data_sens[1] );
                                        //APP_TRACE( "%04X %04X\n", c.i16[0], c.i16[1] );
                                        //APP_TRACE( "%5d %5d\n", c.i16[0], c.i16[1] );
                                        //APP_TRACE( "%5d %5d\n", c.i16[0], c.i16[0] );

                                        //sens_uA =   task_sens_raw_to_uA( c.i16[0] );
                                        //ppm     =   task_sens_uA_to_ppm( sens_uA, &sens_cal );
                                        //APP_TRACE( "%3.6f uA, %f ppm\n", sens_uA, ppm );


/*
                                        pipe.tag        =   APP_PIPE_TAG_SENSOR;
                                        pipe.cnt        =   ser4.size;
                                        pipe.data       =   ser4.tile;

                                        xQueueSend( que_ui_hndl,  &pipe, NULL );
                                        xQueueSend( que_strg_hndl,  &pipe, NULL );
*/
                                        break;

                                case APP_PIPE_TAG_ERROR:
                                        break;

                                default:
                                        break;
                        }
                }
                else //queue passed by timeout
                {
/*
                        //not_empty       =   0;
                        not_empty       =   create_sin( &ser4 );

                        if( not_empty )
                        {
                                pipe.tag        =   APP_PIPE_TAG_SENSOR;
                                pipe.cnt        =   ser4.size;
                                pipe.data       =   ser4.tile;

                                xQueueSend( que_ui_hndl,  &pipe, NULL );
                                xQueueSend( que_strg_hndl,  &pipe, NULL );
                        }
*/

                        rtu.rqst.func   =   MODBUS_FUNC_READ_INPUT_REGISTERS; //0x04
                        //rtu.rqst.reg    =   &dev.reg.device_status;             // { 31001, 1 },
                        //rtu.rqst.reg    =   &dev.reg.alarm_status;              // { 31002, 1 },
                        //rtu.rqst.reg    =   &dev.reg.device_year_month;         // { 31005, 1 },
                        //rtu.rqst.reg    =   &dev.reg.device_day_hour;           // { 31006, 1 },
                        //rtu.rqst.reg    =   &dev.reg.device_minute_second;      // { 31007, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_temperature;        // { 31011, 1 },
                        //rtu.rqst.reg    =   &dev.reg.board_temperature;         // { 31012, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_signal_real;        // { 31021, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_signal_exponent;    // { 31022, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_calc_zero_offset_real; // { 31023, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_calc_zero_offset_exponent; // { 31024, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_calc_sensitivity_coef_real; // { 31025, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_calc_sensitivity_coef_exponent; // { 31026, 1 },
                        rtu.rqst.reg    =   &dev.reg.sensor_value;              // { 33000, 2 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_value_high;         // { 33000, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_value_low;          // { 33001, 1 },
                        //rtu.rqst.reg    =   &dev.reg.current_loop_value;        // { 33002, 1 },
                        //rtu.rqst.func   =   MODBUS_FUNC_READ_HOLDING_REGISTERS; // 0x03
                        //rtu.rqst.reg    =   &dev.reg.sensor_id;                 // { 40401, 6 };
                        //rtu.rqst.reg    =   &dev.reg.version;                   // { 40417, 3 }
                        //rtu.rqst.reg    =   &dev.reg.sensor_scale_min_real;     // { 41001, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_scale_min_exponent; // { 41002, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_scale_max_real;     // { 41003, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_scale_max_exponent; // { 41004, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_scale_dimension;    // { 41005, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_threshold_warning_real; // { 41011, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_threshold_warning_exponent; // { 41012, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_threshold_alarm_real; // { 41013, 1 },
                        //rtu.rqst.reg    =   &dev.reg.sensor_threshold_alarm_exponent; // { 41014, 1 },

                        len     =   modbus_rtu_rqst( &rtu );
                        //rtu.rqst.data[5] = 2;
/*
                        APP_TRACE( "rqst: " );
                        for( int i = 0; i < len; i++ )
                        {
                                APP_TRACE( "%02X", data_rqst[i] );
                        }
                        APP_TRACE( "\n" );
*/

                        bsp_ser1_xmit( data_modbus_rqst, len );
                        bsp_ser1_recv( data_modbus_resp, sizeof( data_modbus_resp ) );
                }
        }
}
