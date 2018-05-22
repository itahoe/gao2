/**
  * @file    app_cfg.c
  * @brief   App Configuration
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdio.h>
#include <stdbool.h>
#include "app.h"


#define APP_CFG_CHNL_MAX                        8

#define APP_CFG_CHNL_NUM_IS_CORRECT( ch_num )   ((ch_num) < APP_CFG_CHNL_MAX)


static          app_cfg_t       cfg[ APP_CFG_CHNL_MAX ];

static  const   char            cfg_str_error[]         = { "_ERR_" };

static  const   char *          cfg_chnl_phy_str[]      =
{
        { "---"         },
        { "RS-485"      },
        { "ADC"         },
};

static  const   char *          cfg_chnl_rate_str[]     =
{
        { "---"         },
        { "9600"        },
        { "19200"       },
        { "38400"       },
        { "57600"       },
        { "115200"      },
        { "230400"      },
};


static  const   char *          cfg_chnl_prot_str[]     =
{
        { "---"         },
        { "MODBUS"      },
        { "ANALOG"      },
};


static
app_cfg_t *     app_cfg_get_chnl(               size_t          n       )
{
        app_cfg_t *     p       = NULL;


        if( APP_CFG_CHNL_NUM_IS_CORRECT( n ) )
        {
                p       =   &cfg[ n ];
        }

        return( p );
}


static
void    app_cfg_read(                           size_t          chnl_num    )
{
        size_t          cfg_sizeof      = 4;
        app_cfg_t *     addr_src        = app_cfg_get_chnl( chnl_num );
        size_t          addr_dst        = chnl_num * cfg_sizeof;

        app_rtc_bckp_read( (uint32_t *) addr_src, addr_dst, cfg_sizeof );
}


static
void    app_cfg_write(                          size_t          chnl_num    )
{
        size_t          cfg_sizeof      = 4;
        size_t          addr_src        = chnl_num * cfg_sizeof;
        app_cfg_t *     addr_dst        = app_cfg_get_chnl( chnl_num );

        app_rtc_bckp_write( (uint32_t *) addr_dst, addr_src, cfg_sizeof );
}


const   char *  app_cfg_chnl_phy_str_get(       size_t          chnl_num )
{
        const   char *          str     = cfg_str_error;
                app_cfg_t *     p       = app_cfg_get_chnl( chnl_num );


        if( (p != NULL) && (p->phy < APP_CFG_CHNL_PHY_MAX) )
        {
                app_cfg_read( chnl_num );
                str     =   cfg_chnl_phy_str[ p->phy ];
        }

        return( str );
}


const   char *  app_cfg_chnl_rate_str_get(      size_t          chnl_num )
{
        const   char *          str     = cfg_str_error;
                app_cfg_t *     p       = app_cfg_get_chnl( chnl_num );


        if( (p != NULL) && (p->phy < APP_CFG_CHNL_PHY_MAX) )
        {
                app_cfg_read( chnl_num );
                str     =   cfg_chnl_rate_str[ p->rate ];
        }

        return( str );
}


const   char *  app_cfg_chnl_prot_str_get(      size_t          chnl_num )
{
        const   char *          str     = cfg_str_error;
                app_cfg_t *     p       = app_cfg_get_chnl( chnl_num );


        if( (p != NULL) && (p->phy < APP_CFG_CHNL_PHY_MAX) )
        {
                app_cfg_read( chnl_num );
                str     =   cfg_chnl_prot_str[ p->protocol ];
        }

        return( str );
}


void    app_cfg_ctl(                            app_cfg_ctl_t   ctl,
                                                size_t          chnl_num )
{
        app_cfg_t *     p       = app_cfg_get_chnl( chnl_num );


        if( p == NULL )
        {
                return;
        }

        switch( ctl )
        {
                case APP_CFG_CTL_PHY_SET_NEXT:
                        if( p->phy < (APP_CFG_CHNL_PHY_MAX-1) )
                        {
                                p->phy++;
                        }
                        break;

                case APP_CFG_CTL_PHY_SET_PREV:
                        if( p->phy > 0 )
                        {
                                p->phy--;
                        }
                        break;

                case APP_CFG_CTL_RATE_SET_NEXT:
                        if( p->rate < (APP_CFG_CHNL_RATE_MAX-1) )
                        {
                                p->rate++;
                        }
                        break;

                case APP_CFG_CTL_RATE_SET_PREV:
                        if( p->rate > 0 )
                        {
                                p->rate--;
                        }
                        break;

                case APP_CFG_CTL_PROT_SET_NEXT:
                        if( p->protocol < (APP_CFG_CHNL_PROTOCOL_MAX-1) )
                        {
                                p->protocol++;
                        }
                        break;

                case APP_CFG_CTL_PROT_SET_PREV:
                        if( p->protocol > 0 )
                        {
                                p->protocol--;
                        }
                        break;

                default:
                        break;
        }

        app_cfg_write( chnl_num );
}
