#ifndef __ERRORLOG_H
#define __ERRORLOG_H

#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

#include "time_and_date.h"

#define ERROR(msg)	char *p  = getTime(); printf("%s [%s]:%d " msg ": errno %d: %s\n", p,  __FILE__, __LINE__, errno, strerror(errno)); destructTime(p); 
#define PTHREAD_ERROR(msg, err)	char *p = getTime(); printf("%s [%s]:%d " msg ": errnum %d: %s\n", p, __FILE__, __LINE__,  err, strerror(err)); destructTime(p);




#ifdef DEBUG
#define Dprintf(msg,...) char *p = getTime(); printf("%s [%s]:%d " msg, p, __FILE__, __LINE__, ##__VA_ARGS__); destructTime(p);
#else
#define Dprintf(msg,...)                /* do nothing */
#endif 

#endif

