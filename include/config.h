#ifndef __CONFIG_H
#define __CONFIG_H

#include <string.h>

#define CONFIG_FILE "../include/astros.conf"

typedef struct {
	char myhostname[255];
	char mydomain[255];
	char myorigin[255];
	char mail_owner[255];
	char setgid_group[255];
	char message_size_limit[255];
	char smtpd_recipient_restrictions[255];
}CONFIG_DATA;

void parseConfigFile (void);

#endif
