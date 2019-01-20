#ifndef __CONNECTION_THREADS_H
#define __CONNECTION_THREADS_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "errorlog.h"

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
	
	struct tnod *next;
}TNOD;

void addConnection (int remote_sfd, struct sockaddr their_addr);
int loadNOD (TNOD *p, int remote_sfd, struct sockaddr their_addr);
void freeNOD (TNOD *p);

#endif
