#include "time_and_date.h"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
char *time_and_date;

char * getTime (void)
{	
	time_t t;
	struct tm *tm;
	int s;
	size_t str_size;

	s = pthread_mutex_lock(&mtx);
	if (s != 0){
		PTHREAD_ERROR("pthread_mutex_lock", s);
		exit(EXIT_FAILURE);
	}

	time_and_date = malloc(27*sizeof(char));

	t = time(NULL);

	tm = localtime(&t);
	if(tm == NULL)
		return NULL;
	
	str_size = strftime(time_and_date, 27, "%b %d %X", tm);

	s = pthread_mutex_unlock(&mtx);
	if (s != 0){
		PTHREAD_ERROR("pthread_mutex_lock", s);
		exit(EXIT_FAILURE);
	}

	return (str_size == 0) ? NULL : time_and_date;
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
