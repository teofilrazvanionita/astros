#ifndef __CONFIG_H
#define __CONFIG_H

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


#include "errorlog.h"

#define CONFIG_FILE "/etc/astros/main.cf"

typedef struct {
	char myhostname[255];
	char mydomain[255];
	char myorigin[255];
	char mail_owner[255];
	char setgid_group[255];
	char message_size_limit[255];
	char smtpd_recipient_restrictions[255];
}CONFIG_DATA;

extern CONFIG_DATA smtpd_config;

void parseConfigFile (void);
void setDefaults (void);
void loadConfigs (void);

#endif
