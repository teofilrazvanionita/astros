#include "smtp_handler.h"

SMTP_COMMANDS smtp_commands = {"HELO", "EHLO", "MAIL FROM:", "RCPT TO:", "DATA", "RSET", "VRFY", "EXPN", "HELP", "NOOP", "QUIT"};

void handleConnection(CONNECTION *p)
{
	ssize_t read_count;
	char buffer[1024];

	logConnectFrom(&p -> their_addr, p -> remote_name);

	while(1){
		memset(buffer, 0 , 1024);
		if((read_count = read(p -> remote_sfd, buffer, sizeof(buffer))) == -1){
			ERROR("read");
			exit(EXIT_FAILURE);
		}
		if (!read_count)
			break;	
	}
}
