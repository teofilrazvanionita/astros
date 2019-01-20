#include "connection_threads.h"

CONNECTION *first, *last;

void addConnection(int remote_sfd, struct sockaddr their_addr)
{
	CONNECTION *p; 
	int i;

	if((p = (CONNECTION *)malloc(sizeof(CONNECTION))) == 0){
		ERROR("insufficient memory at list creation");
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
}

int loadNOD(CONNECTION *p, int remote_sfd, struct sockaddr their_addr)
{
	int s;

	p -> state = TS_ALIVE;
	s = pthread_create(&(p->tid), NULL, threadFunc, NULL);
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

	return NULL;
}
