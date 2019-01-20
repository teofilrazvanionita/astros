#ifndef __ERRORLOG_H
#define __ERRORLOG_H

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

#include "time_and_date.h"

#define ERROR(msg)	char temp[80]; memset(temp, 0, 64); sprintf(temp, "%s [%s]:%d " msg ": " "errno %d: %s\n", getTime(), __FILE__, __LINE__, errno, strerror(errno)); write(STDERR_FILENO, temp, strlen(temp));
#define PTHREAD_ERROR(msg, err)	char temp[80]; memset(temp, 0, 64); sprintf(temp, "%s [%s]:%d " msg ": " "errnum %d: %s\n", getTime(), __FILE__, __LINE__, err, strerror(err)); write(STDERR_FILENO, temp, strlen(temp));

#ifdef DEBUG
#define Dprintf(msg,...) printf("%s [%s]:%d " msg, getTime(), __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define Dprintf(msg,...)                /* do nothing */
#endif 

#endif

