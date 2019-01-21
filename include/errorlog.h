#ifndef __ERRORLOG_H
#define __ERRORLOG_H

#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

#include "time_and_date.h"

void ERROR (const char *msg);
void PTHREAD_ERROR (const char *msg, int err);

#ifdef DEBUG
#define Dprintf(msg,...) printf("%s [%s]:%d " msg, getTime(), __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define Dprintf(msg,...)                /* do nothing */
#endif 

#endif

