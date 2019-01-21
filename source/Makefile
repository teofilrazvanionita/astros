include ../Makefile.inc 

LINUX_EXE = smtpd

EXE = ${LINUX_EXE}


objects = smtpd.o smtp_handler.o log.o config.o become_daemon.o time_and_date.o connection_threads.o errorlog.o

all : ${EXE}

${EXE}: $(objects)
	${CC} $(objects) -o ${EXE} ${LDLIBS}

smtpd.o: smtpd.c ${ASTROS_INCL_DIR}/smtpd.h ${ASTROS_INCL_DIR}/log.h ${ASTROS_INCL_DIR}/errorlog.h ${ASTROS_INCL_DIR}/smtp_handler.h ${ASTROS_INCL_DIR}/config.h ${ASTROS_INCL_DIR}/connection_threads.h
	${CC} smtpd.c ${CFLAGS} -I${ASTROS_INCL_DIR} -c -o $@

smtp_handler.o: smtp_handler.c ${ASTROS_INCL_DIR}/smtp_handler.h ${ASTROS_INCL_DIR}/log.h
	${CC} smtp_handler.c $(CFLAGS) -I${ASTROS_INCL_DIR} -c -o $@

log.o: log.c ${ASTROS_INCL_DIR}/log.h
	${CC} log.c $(CFLAGS) -I${ASTROS_INCL_DIR} -c -o $@

config.o: config.c ${ASTROS_INCL_DIR}/config.h ${ASTROS_INCL_DIR}/errorlog.h
	${CC} config.c ${CFLAGS} -I${ASTROS_INCL_DIR} -c -o $@

become_daemon.o: become_daemon.c ${ASTROS_INCL_DIR}/become_daemon.h ${ASTROS_INCL_DIR}/errorlog.h
	${CC} become_daemon.c ${CFLAGS} -I${ASTROS_INCL_DIR} -c -o $@

time_and_date.o: time_and_date.c ${ASTROS_INCL_DIR}/time_and_date.h
	${CC} time_and_date.c ${CFLAGS} -I${ASTROS_INCL_DIR} -c -o $@

connection_threads.o: connection_threads.c ${ASTROS_INCL_DIR}/connection_threads.h ${ASTROS_INCL_DIR}/errorlog.h
	${CC} connection_threads.c ${CFLAGS} -I${ASTROS_INCL_DIR} -c -o $@

errorlog.o: errorlog.c ${ASTROS_INCL_DIR}/errorlog.h ${ASTROS_INCL_DIR}/time_and_date.h
	${CC} errorlog.c ${CFLAGS} -I${ASTROS_INCL_DIR} -c -o $@


.PHONY : clean
clean : 
	-${RM} ${EXE} $(objects) *~

showall :
	@ echo ${EXE}
