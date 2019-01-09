int becomeDaemon(void){

	int maxfd, fd;

	switch(fork()){
		case -1: return -1;
		case 0: break;
		default: _exit(EXIT_SUCCESS);
	}

	if (setsid() == -1)
		return -1;

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

	fd = open ("/dev/null", O_RDWR);
	if (fd != STDIN_FILENO)
		return -1;

	fd = open (NEWSTDOUTERR, O_RDWR);
	if (fd != STDOUT_FILENO)
		return -1;

	if (dup2(STDOUT_FILENO, STDERR_FILENO) != STDERR_FILENO)
		return -1;


	return 0;
}
