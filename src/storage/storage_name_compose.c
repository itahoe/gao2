/**
  * @file    storage_name_compose.h
  * @brief   Storage - Name Compose
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include	<time.h>
#include	"storage.h"

int storage_name_compose(                       char *                  str,
                                        const   char *			ext,
                                                size_t                  max_len )
{
	time_t          t_raw   =   time( NULL );
	struct tm *     t       =   gmtime( &t_raw );
	int             n       =   0;


	if( t != NULL )
	{
		n	=   snprintf(   str,
		                        max_len,
		                        "%04d%02d%02d.%02d%02d%02d.%s",
		                        t->tm_year + 1970,
		                        t->tm_mon,
		                        t->tm_mday,
		                        t->tm_hour,
		                        t->tm_min,
		                        t->tm_sec,
		                        ext             );
	}

	return( n );
}
