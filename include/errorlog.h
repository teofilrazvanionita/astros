#ifndef __ERRORLOG_H
#define __ERRORLOG_H

#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

#include "time_and_date.h"

#define ERROR(msg)	printf("%s [%s]:%d " msg ": errno %d: %s\n", getTime(), __FILE__, __LINE__, errno, strerror(errno));
#define PTHREAD_ERROR(msg, err)	printf("%s [%s]:%d " msg ": errnum %d: %s\n", getTime(), __FILE__, __LINE__,  err, strerror(err));




#ifdef DEBUG
#define Dprintf(msg,...) printf("%s [%s]:%d " msg, getTime(), __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define Dprintf(msg,...)                /* do nothing */
#endif 

#endif

