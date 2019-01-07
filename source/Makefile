include ../Makefile.inc 

LINUX_EXE = smtpd

EXE = ${LINUX_EXE}


objects = smtpd.o smtp_handler.o log.o

all : ${EXE}

${EXE}: $(objects)
	${CC} $(objects) -o ${EXE} ${LDLIBS}

smtpd.o: smtpd.c ${ASTROS_INCL_DIR}/smtpd.h ${ASTROS_INCL_DIR}/log.h ${ASTROS_INCL_DIR}/smtp_handler.h
	${CC} smtpd.c ${CFLAGS} -I${ASTROS_INCL_DIR} -c -o $@

smtp_handler.o: smtp_handler.c ${ASTROS_INCL_DIR}/smtp_handler.h
	${CC} smtp_handler.c $(CFLAGS) -I${ASTROS_INCL_DIR} -c -o $@

log.o: log.c ${ASTROS_INCL_DIR}/log.h
	${CC} log.c $(CFLAGS) -I${ASTROS_INCL_DIR} -c -o $@

.PHONY : clean
clean : 
	-${RM} ${EXE} $(objects) *~

showall :
	@ echo ${EXE}
