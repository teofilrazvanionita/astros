#include "time_and_date.h"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
char *time_and_date;

char * getTime (void)
{	
	time_t t;
	char *p;
	int s;

	s = pthread_mutex_lock(&mtx);
	if (s != 0){
		PTHREAD_ERROR("pthread_mutex_lock", s);
		exit(EXIT_FAILURE);
	}

	time_and_date = malloc(27*sizeof(char));
	s = pthread_mutex_unlock(&mtx);
	if (s != 0){
		PTHREAD_ERROR("pthread_mutex_lock", s);
		exit(EXIT_FAILURE);
	}

	t = time(NULL);
	ctime_r((const time_t *)&t, time_and_date);

	p = strchr(time_and_date,'\n');
	*p = 0;

	return time_and_date;
}

void destructTime (char *p)
{
	int s;

	s = pthread_mutex_lock(&mtx);
	if (s != 0){
		PTHREAD_ERROR("pthread_mutex_lock", s);
		exit(EXIT_FAILURE);
	}
	free(p);
	s = pthread_mutex_unlock(&mtx);
	if (s != 0){
		PTHREAD_ERROR("pthread_mutex_lock", s);
		exit(EXIT_FAILURE);
	}
}
