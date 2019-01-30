#include "log.h"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void logConnectFrom (struct sockaddr *their_addr_p, char *remote_name)
{
	int log_fd, s;
	char ip_addr[16];
	char connection_from[516], *ptd;

	memset(ip_addr, 0, 16);
	memset(connection_from, 0, 516);

	if((log_fd = open(LOG_FILE, O_WRONLY | O_APPEND)) == -1){
		ERROR("open");
		exit(EXIT_FAILURE);
	}

	ptd = getTime();
	strcpy(ip_addr, inet_ntoa((((struct sockaddr_in *)their_addr_p)->sin_addr)));
	sprintf(connection_from, "%s %s astros/smtpd[%d]: connect from %s[%s]\n", ptd, smtpd_config.myhostname, getpid(), remote_name, ip_addr);
	destructTime(ptd);

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
