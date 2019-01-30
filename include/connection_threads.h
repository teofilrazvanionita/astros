#ifndef __CONNECTION_THREADS_H
#define __CONNECTION_THREADS_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

#include "errorlog.h"
//#include "smtp_handler.h"

enum tstate {
	TS_ALIVE,
	TS_TERMINATED,
	TS_JOINED
};

typedef struct tnod{
	pthread_t tid;
	enum tstate state;
	int remote_sfd;
	struct sockaddr their_addr;
	char remote_name[256];
	
	struct tnod *next;
}CONNECTION;

int addConnection (int remote_sfd, struct sockaddr their_addr);
int loadNOD (CONNECTION *p, int remote_sfd, struct sockaddr their_addr);
void freeNOD (CONNECTION *p);
void deleteKeyNOD (int KEY_JOINED);
void updateKeyNOD (int KEY_TERMINATED);
void joinNOD (CONNECTION *p);
void getName (char *p, struct sockaddr their_addr);

void handleConnection (CONNECTION *p); // defined in smtp_handler.c; file smtp_handler.h not included to get rid of circular dependencies error; function prototypes from smtp_handler.h redeclared here; ressembles with a class from this perspective...

void * threadFunc (void * arg);
void * threadFree (void * arg);
void * threadJoin (void * arg);
#endif
