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
int readCommand (CONNECTION *p, char *RECEIVED_STRING);
void interpretCommand (CONNECTION *p, char *RECEIVED_STRING, char *REPLY_STRING);
void constructReply (char *REPLY_STRING, int no);
void sendReply (CONNECTION *p, char *REPLY_STRING);

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
	const char *SERVICE_CLOSE;
	const char *OK_HOST;
	const char *REQ_OK;
	const char *SYNTAX_ERR_CMD_NOT_RECOGN;
	const char *SYNTAX_ERR_IN_PARAM_ARG;
	const char *CMD_NOT_IMPL;
} SMTP_REPLIES;

#endif
