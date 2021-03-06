#ifndef __SMTPD_H
#define __SMTPD_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>


#include "errorlog.h"
#include "become_daemon.h"
#include "config.h"
#include "connection_threads.h"

#define PORT "25"
#define BACKLOG 1000

#endif
