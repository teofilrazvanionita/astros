#include "smtpd.h"


int main(int argc, char *argv[])
{
        int sockfd;
	struct addrinfo hints, *servinfo, *p;
        int rv ,s; // return value
       	int yes = 1;
	pthread_t tid_free, tid_join;

	memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; // use my IP
        
	if ((rv = becomeDaemon()) == -1){
		ERROR("becomeDaemon error");
		exit(1);
	}

	/* initialization */
        loadConfigs();
	
	/* create a thread for removing all the joined threads */
	s = pthread_create(&tid_free, NULL, threadFree, NULL);
	if (s != 0){
		PTHREAD_ERROR("pthread_create", s);
		return 0;
	}
	/* create a thread for joining all terminated connections */
	s = pthread_create(&tid_join, NULL, threadJoin, NULL);
	if (s != 0){
		PTHREAD_ERROR("pthread_create", s);
		return 0;
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

        while (1){
        	int remote_sfd;
	        socklen_t sin_size;
        	struct sockaddr their_addr; // connector's address information
                
		remote_sfd = accept(sockfd, &their_addr, &sin_size);
                if(remote_sfd == -1){
                    	perror("accept");
			continue;
                }

		if(addConnection(remote_sfd, their_addr) == -1){
			if(close(remote_sfd) == -1){
				ERROR("close");
				exit(EXIT_FAILURE);
			}
			continue;
		}
        }

	return 0;
}


