#ifndef __SMTP_HANDLER_H
#define __SMTP_HANDLER_H

#include <sys/types.h>
#include <sys/socket.h>

void handleConnection(int remote_sfd, struct sockaddr their_addr);

#endif
