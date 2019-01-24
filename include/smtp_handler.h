#ifndef __SMTP_HANDLER_H
#define __SMTP_HANDLER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#include "errorlog.h"
#include "log.h"

void handleConnection(int remote_sfd, struct sockaddr their_addr);

#endif
