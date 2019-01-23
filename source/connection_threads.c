#include "connection_threads.h"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
CONNECTION *first = NULL, *last = NULL;

void addConnection(int remote_sfd, struct sockaddr their_addr)
{
	CONNECTION *p; 
	int i, s;

	if((p = (CONNECTION *)malloc(sizeof(CONNECTION))) == 0){
		ERROR("insufficient memory at list creation");
		exit(EXIT_FAILURE);	
	}

	s = pthread_mutex_lock(&mtx);
	if(s != 0){
		PTHREAD_ERROR("pthread_mutex_lock", s);
		exit(EXIT_FAILURE);
	}

	if((i=loadNOD(p, remote_sfd, their_addr))!=1){
		freeNOD(p);
		return;
	}

	if(last!=NULL)
		last -> next = p;
	else
		first = p;

	last = p;
	last -> next = NULL;
	
	s = pthread_mutex_unlock(&mtx);
	if(s != 0){
		PTHREAD_ERROR("pthread_mutex_lock", s);
		exit(EXIT_FAILURE);
	}
}

int loadNOD(CONNECTION *p, int remote_sfd, struct sockaddr their_addr)
{
	int s;

	p -> state = TS_ALIVE;
	s = pthread_create(&(p->tid), NULL, threadFunc, p);
	if (s != 0){
		PTHREAD_ERROR("pthread_create", s);
		return 0;
	}
	p -> remote_sfd = remote_sfd;
	p -> their_addr = their_addr;

	return 1;
}

void freeNOD(CONNECTION *p)
{
	free(p);
}

static void * threadFunc(void *arg)
{

	CONNECTION *p = (CONNECTION *) arg;


	if(close(p -> remote_sfd) == -1){
		ERROR("close");
		exit(EXIT_FAILURE);
	}
	p -> state = TS_TERMINATED;

	return NULL;
}
