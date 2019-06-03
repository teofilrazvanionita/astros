#include "smtp_handler.h"

SMTP_COMMANDS smtp_commands = {"HELO", "EHLO", "MAIL FROM:", "RCPT TO:", "DATA", "RSET", "VRFY", "EXPN", "HELP", "NOOP", "QUIT"};
SMTP_REPLIES smtp_replies = {"220 %s SMTP Astros", "221 Bye", "250 %s", "250 Ok", "500 Error: Command unrecognized", "501 Syntax : %s", "502 Error: Command not implemented"};

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
		int i;
		if((i = readCommand(p, RECEIVED_STRING)) == -1){ // Command too long; discard rest of the line
			char ch;
			while(read(p -> remote_sfd, &ch, 1) == 1 && ch != '\n'){
				int count = 0;
				count++;
				if(count > 10000000){ // TODO: send reply, close connection
					
				}
			}
		}
		if(i == 0) // EOF
			break;
		interpretCommand(RECEIVED_STRING);
	}
}

int readCommand(CONNECTION *p, char *RECEIVED_STRING)
{
	char buf;
	ssize_t bytes_read;
	int count = 0;
	
	memset(RECEIVED_STRING, 0, 512);
	while(1){
		if((bytes_read = read(p -> remote_sfd, &buf, 1)) != 1){
			if(bytes_read == -1){
				ERROR("read");
				exit(EXIT_FAILURE);
			}
			if(!bytes_read){ // EOF (connection closed on remote end)
				return 0;
			}
		}
		count++;
		strncat(RECEIVED_STRING, &buf, 1);
		if(count == 512 && buf != '\n')
			return -1;
		if(buf == '\n')
			return 1;
	}
}

void interpretCommand(char *RECEIVED_STRING)
{
	Dprintf("RECEIVED_STRING = %s", RECEIVED_STRING);
}
