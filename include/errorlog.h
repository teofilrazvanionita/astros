#ifndef __ERRORLOG_H
#define __ERRORLOG_H

#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

#include "time_and_date.h"

#define ERROR(msg)	{char *ERROR_p  = getTime(); printf("%s [%s]:%d " msg ": errno %d: %s\n", ERROR_p,  __FILE__, __LINE__, errno, strerror(errno)); destructTime(ERROR_p); }
#define PTHREAD_ERROR(msg, err)	{char *ERROR_p = getTime(); printf("%s [%s]:%d " msg ": errnum %d: %s\n", ERROR_p, __FILE__, __LINE__,  err, strerror(err)); destructTime(ERROR_p);}




#ifdef DEBUG
#define Dprintf(msg,...) {char *Dprintf_p = getTime(); printf("%s [%s]:%d " msg, Dprintf_p, __FILE__, __LINE__, ##__VA_ARGS__); destructTime(Dprintf_p);}
#else
#define Dprintf(msg,...)                /* do nothing */
#endif 

#endif

