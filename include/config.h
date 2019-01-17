#ifndef __CONFIG_H
#define __CONFIG_H

#include <string.h>

#define CONFIG_FILE "../include/astros.conf"

typedef struct {
	char ServerName[255];
}CONFIG_DATA;

void parseConfigFile (void);

#endif
