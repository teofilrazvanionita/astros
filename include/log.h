#ifndef __LOG_H
#define __LOG_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "errorlog.h"
#include "time_and_date.h"
#include "config.h"

#define LOG_FILE "/var/log/maillog"

void logConnectFrom (struct sockaddr *their_addr_p);

#endif
