#include "connection_threads.h"

TNOD *first, *last;

void addConnection(int remote_sfd, struct sockaddr their_addr)
{
	TNOD *p; 
		
	if(p = (TNOD *)malloc(sizeof(TNOD)) == 0){
		ERROR("insufficient memory at list creation");
		exit(EXIT_FAILURE);	
	}

	if((i=loadNOD(p))!=1){
		freeNOD(p);
		return i;
	}

	if(last!=NULL)
		last -> next = p;
	else
		first = p;

	last = p;
	last -> next = NULL;
}

int loadNOD(TNOD *p, int remote_sfd, struct sockaddr their_addr)
{
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

void freeNOD(TNOD *p)
{
	free(p);
}


