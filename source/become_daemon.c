#include "become_daemon.h"

int becomeDaemon(void){

	int maxfd, fd;

	switch(fork()){
		case -1: return -1;
		case 0: break;
		default: _exit(EXIT_SUCCESS);
	}

	if (setsid() == -1){
		ERROR("setsid");
		return -1;
	}

	switch (fork()) {
		case -1: return -1;
		case 0: break;
		default: _exit(EXIT_SUCCESS);
	}


	umask(0);
	chdir("/");

	maxfd = sysconf(_SC_OPEN_MAX);	
	if (maxfd == -1)
		maxfd = BD_MAX_CLOSE;

       	for (fd = 0; fd < maxfd; fd++)
		close(fd);

	fd = open ("/dev/null", O_RDONLY);
	if (fd != STDIN_FILENO){
		ERROR("open");
		return -1;
	}

	fd = open (BD_NEW_STDOUT_ERR, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if (fd != STDOUT_FILENO){
		ERROR("open");
		return -1;
	}

	if (dup2(STDOUT_FILENO, STDERR_FILENO) != STDERR_FILENO){
		ERROR("dup2");
		return -1;
	}

	setbuf(stdout,NULL);

	return 0;
}
