#ifndef __SMTP_HANDLER_H
#define __SMTP_HANDLER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#include "connection_threads.h"
#include "errorlog.h"
#include "log.h"

void handleConnection (CONNECTION *p);

#endif
