#ifndef __ERRORLOG_H
#define __ERRORLOG_H

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

#define ERROR(msg) memset(temp, 0, 64); sprintf(temp, "[%s]:%d " msg ":\n" "errnum %d: %s\n", __FILE__, __LINE__, errno, strerror(errno)); write(STDERR_FILENO, temp, strlen(temp));
#define PTHREAD_ERROR(msg,err) memset(temp, 0, 64); sprintf(temp, "[%s]:%d " msg ":\n" "errnum %d: %s\n", __FILE__, __LINE__, err, strerror(err)); write(STDERR_FILENO, temp, strlen(temp));

#ifdef DEBUG
#define Dprintf(msg,...) printf("[%s]:%d" msg, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define Dprintf(msg,...)                /* do nothing */
#endif 

extern char temp[];

#endif

