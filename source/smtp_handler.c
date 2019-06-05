#include "smtp_handler.h"

SMTP_COMMANDS smtp_commands = {"HELO", "EHLO", "MAIL FROM:", "RCPT TO:", "DATA", "RSET", "VRFY", "EXPN", "HELP", "NOOP", "QUIT"};
SMTP_REPLIES smtp_replies = {"220 %s SMTP Astros", "221 Bye", "250 %s", "250 Ok", "500 Error: Command unrecognized", "501 Syntax : %s", "502 Error: Command not implemented"};

void handleConnection(CONNECTION *p)
{
	char REPLY_STRING[512];
	char RECEIVED_STRING[512];
	LINEOBJ *pLO;

	logConnectFrom(&p -> their_addr, p -> remote_name);

	/* send SMTP GREETING to client */
	constructReply(REPLY_STRING, 1);
	sendReply(p, REPLY_STRING);

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
		pLO = interpretCommand(p, RECEIVED_STRING, REPLY_STRING);
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

LINEOBJ *interpretCommand(CONNECTION *p, char *RECEIVED_STRING, char *REPLY_STRING)
{
	LINEOBJ *pLO;

	Dprintf("RECEIVED_STRING = %s", RECEIVED_STRING);

	if(RECEIVED_STRING[511] != 0 && RECEIVED_STRING[511] != '\n'){
		constructReply(REPLY_STRING, 7);
		sendReply(p, REPLY_STRING);
		return NULL;	
	}
	if((RECEIVED_STRING[0] == '\r' && RECEIVED_STRING[1] == '\n') || RECEIVED_STRING[0] == '\n'){	// Command empty
		constructReply(REPLY_STRING, 5);
		sendReply(p, REPLY_STRING);
		return NULL;
	}

	pLO = splitLine(RECEIVED_STRING);
	if(validateLine(pLO, REPLY_STRING)){
		return pLO;
	}
	else{
		freeLineObj(pLO);
		return NULL;
	}
}

void constructReply (char *REPLY_STRING, int no)
{
	switch (no){
		case 1:
			memset(REPLY_STRING, 0, 512);
			sprintf(REPLY_STRING, smtp_replies.GREETING, smtpd_config.myhostname);
			strcat(REPLY_STRING,"\n");
			Dprintf("REPLY_STRING = %s", REPLY_STRING);
			break;
		case 2:
			memset(REPLY_STRING, 0, 512);
			break;
		case 3:
			memset(REPLY_STRING, 0, 512);
			break;
		case 4:
			memset(REPLY_STRING, 0, 512);
			break;
		case 5:
			memset(REPLY_STRING, 0, 512);
			sprintf(REPLY_STRING, "%s\n", smtp_replies.SYNTAX_ERR_CMD_NOT_RECOGN);
			Dprintf("REPLY_STRING = %s", REPLY_STRING);
			break;
		case 6:
			memset(REPLY_STRING, 0, 512);
			break;
		case 7:
			memset(REPLY_STRING, 0, 512);
			sprintf(REPLY_STRING, "%s\n", smtp_replies.CMD_NOT_IMPL);	
			Dprintf("REPLY_STRING = %s", REPLY_STRING);
			break;
	}
}

void sendReply (CONNECTION *p, char *REPLY_STRING)
{
	if(write(p -> remote_sfd, REPLY_STRING, 512) == -1){
		ERROR("write");
		exit(EXIT_FAILURE);
	}
}
