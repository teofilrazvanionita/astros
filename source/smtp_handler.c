#include "smtp_handler.h"

void handleConnection(int remote_sfd, struct sockaddr their_addr)
{
	ssize_t read_count;
	char buffer[1024];

	logConnectFrom(&their_addr);

	while(1){
		memset(buffer, 0 , 1024);
		if((read_count = read(remote_sfd, buffer, sizeof(buffer))) == -1){
			ERROR("read");
			exit(EXIT_FAILURE);
		}
		if (!read_count)
			break;	
	}
}
