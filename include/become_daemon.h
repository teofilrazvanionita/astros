#ifndef __BECOME_DAEMON_H
#define __BECOME_DAEMON_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "errorlog.h"

#define BD_NEW_STDOUT_ERR "/tmp/astros.err"
#define BD_MAX_CLOSE 8192

int becomeDaemon(void);

#endif
