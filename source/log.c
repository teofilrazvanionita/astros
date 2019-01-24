#include "log.h"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void logConnectFrom (struct sockaddr *their_addr_p)
{
	int log_fd, s;
	char ip_addr[16];
	char connection_from[516];

	memset(ip_addr, 0, 16);
	memset(connection_from, 0, 516);

	if((log_fd = open(LOG_FILE, O_WRONLY | O_APPEND)) == -1){
		ERROR("open");
		exit(EXIT_FAILURE);
	}
	strcpy(ip_addr, inet_ntoa((((struct sockaddr_in *)their_addr_p)->sin_addr)));
	sprintf(connection_from, "%s %s astros/smtpd[%d]: Connect from %s\n", getTime(), smtpd_config.myhostname, getpid(), ip_addr);
	
	s = pthread_mutex_lock(&mtx);
	if (s != 0){
		PTHREAD_ERROR("pthread_mutex_lock", s);
		exit(EXIT_FAILURE);
	}
	if(write(log_fd, connection_from, sizeof(connection_from)) == -1){
		ERROR("write");
		exit(EXIT_FAILURE);
	}
	s = pthread_mutex_unlock(&mtx);
	if (s != 0){
		PTHREAD_ERROR("pthread_mutex_lock", s);
		exit(EXIT_FAILURE);
	}

	if(close(log_fd) == -1){
		ERROR("close");
		exit(EXIT_FAILURE);
	}
}
