#ifndef __MESSAGE_H
#define __MESSAGE_H

#define DATA_CHUNK_SIZE 80

typedef struct RCPT_TO {

	struct RCPT_TO *next;
} RCPT_TO;

typedef struct DATA {

	struct DATA *next;
} DATA;

typedef struct MESSAGE {
	char *from;
	RCPT_TO *to;

	DATA *data;
} MESSAGE;

#endif

