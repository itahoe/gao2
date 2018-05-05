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
	time_t          t       =   time( NULL );
	struct tm *     curr    =   localtime( &t );
	int             n       =   0;


	if( curr != NULL )
	{
		n	=   snprintf(   str,
		                        max_len,
		                        "%04d%02d%02d.%02d%02d%02d.%s",
		                        curr->tm_year + 1970,
		                        curr->tm_mon + 1,
		                        curr->tm_mday,
		                        curr->tm_hour,
		                        curr->tm_min,
		                        curr->tm_sec,
		                        ext );
	}

	return( n );
}
