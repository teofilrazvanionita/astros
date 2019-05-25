#include "smtp_handler.h"

SMTP_COMMANDS smtp_commands = {"HELO", "EHLO", "MAIL FROM:", "RCPT TO:", "DATA", "RSET", "VRFY", "EXPN", "HELP", "NOOP", "QUIT"};
SMTP_REPLIES smtp_replies = {"220 %s SMTP Astros"};

void handleConnection(CONNECTION *p)
{
	char REPLY_STRING[512];
	char RECEIVED_STRING[512];

	logConnectFrom(&p -> their_addr, p -> remote_name);

	/* send SMTP GREETING to client */
	memset(REPLY_STRING, 0, sizeof(REPLY_STRING));
	sprintf(REPLY_STRING, smtp_replies.GREETING, smtpd_config.myhostname);
	strcat(REPLY_STRING,"\n");
	Dprintf("REPLY_STRING = %s", REPLY_STRING);
	if(write(p -> remote_sfd, REPLY_STRING, sizeof(REPLY_STRING)) == -1){
		ERROR("write");
		exit(EXIT_FAILURE);
	}

	while(1){
		readCommand(RECEIVED_STRING);
		interpretCommand(RECEIVED_STRING);
	}
}

void readCommand(char *RECEIVED_STRING)
{

}

void interpretCommand(char *RECEIVED_STRING)
{

}
