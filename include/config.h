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
	char myhostname[256];
	char mydomain[256];
	char myorigin[256];
	char mail_owner[256];
	char setgid_group[256];
	char message_size_limit[256];
	char smtpd_recipient_restrictions[256];
}CONFIG_DATA;

extern CONFIG_DATA smtpd_config;

void parseConfigFile (void);
void setDefaults (void);
void loadConfigs (void);

#endif
