#include "time_and_date.h"

char * getTime(void)
{	
	time_t t;
	char *p;
	char *time_and_date = malloc(27*sizeof(char));

	t = time(NULL);
	ctime_r((const time_t *)&t, time_and_date);

	p = strchr(time_and_date,'\n');
	*p = 0;

	return time_and_date;
}