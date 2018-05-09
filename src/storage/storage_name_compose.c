/**
  * @file    storage_name_compose.h
  * @brief   Storage - Name Compose
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include	<time.h>
#include	"storage.h"
#include	"app_trace.h"


int storage_name_compose(                       char *                  str,
                                        const   char *			ext,
                                                size_t                  max_len )
{
	time_t          t       =   time( NULL );
	struct tm *     ts      =   gmtime( &t );
	int             n       =   0;


	if( t != -1 )
	{
		n	=   snprintf(   str,
		                        max_len,
		                        "%04d%02d%02d.%02d%02d%02d.%s",
		                        ts->tm_year + 1900,
		                        ts->tm_mon + 1,
		                        ts->tm_mday,
		                        ts->tm_hour,
		                        ts->tm_min,
		                        ts->tm_sec,
		                        ext             );
	}

	return( n );
}
