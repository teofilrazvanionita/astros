#include "connection_threads.h"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
CONNECTION *first = NULL, *last = NULL;

int addConnection(int remote_sfd, struct sockaddr their_addr)
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
		return -1; /* error return */
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

	return 0; /* normal return */
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

void * threadFunc(void *arg)
{

	CONNECTION *p = (CONNECTION *) arg;


	if(close(p -> remote_sfd) == -1){
		ERROR("close");
		exit(EXIT_FAILURE);
	}
	p -> state = TS_TERMINATED;

	return NULL;
}

void deleteKeyNOD (int KEY_TERMINATED)
{
	CONNECTION *q, *q1;

	q1 = NULL;
	q = first;

	while(q){
		if(q -> state == KEY_TERMINATED)
			break;
		q1 = q;
		q = q -> next;
	}

	if(q == NULL)
		return;

	if(q == first){
		first = first -> next;
		freeNOD(q);
		if(first == NULL)
			last = NULL;
	}
	else{
		q1 -> next = q -> next;
		if(q == last)
			last = q1;
		freeNOD(q);
	}
}

void * threadFree(void *arg)
{
	int s;

	while(1){
		s = pthread_mutex_lock(&mtx);
		if(s != 0){
			PTHREAD_ERROR("pthread_mutex_lock", s);
			exit(EXIT_FAILURE);
		}
		deleteKeyNOD(TS_JOINED);
		s = pthread_mutex_unlock(&mtx);
		if(s != 0){
			PTHREAD_ERROR("pthread_mutex_lock", s);
			exit(EXIT_FAILURE);
		}
		sleep(5);
	}
}

