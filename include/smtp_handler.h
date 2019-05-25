#ifndef __SMTP_HANDLER_H
#define __SMTP_HANDLER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#include "connection_threads.h"
#include "errorlog.h"
#include "log.h"
#include "config.h"

void handleConnection (CONNECTION *p);
void readCommand (char *RECEIVED_STRING);
void interpretCommand (char *RECEIVED_STRING);

typedef struct {
	const char *HELO;
	const char *EHLO;
	const char *MAIL;
	const char *RECIPIENT;
	const char *DATA;
	const char *RESET;
	const char *VERIFY;
	const char *EXPAND;
	const char *HELP;
	const char *NOOP;
	const char *QUIT;
} SMTP_COMMANDS;

typedef struct {
	const char *GREETING;
} SMTP_REPLIES;

#endif
