#include "smtpd.h"
#include "become_daemon.h"
#include "errorlog.h"


int main(int argc, char *argv[])
{
        int sockfd;
	struct addrinfo hints, *servinfo, *p;
        int rv; // return value
       	int yes = 1;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; // use my IP
        
	if ((rv = becomeDaemon()) == -1){
		ERROR("becomeDaemon error");
		exit(1);
	}	

        if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
                exit(EXIT_FAILURE);
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			ERROR("server: socket");
			continue;
		}
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			ERROR("setsockopt");
			exit(1);
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			ERROR("server: bind");
			continue;
		}
		break;
	}
       
        if (p == NULL)  {
		ERROR("server: failed to bind");
		exit (EXIT_FAILURE);
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (listen(sockfd, BACKLOG) == -1) {
		ERROR("listen");
		exit(1);
	}

	return 0;
}
