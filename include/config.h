#ifndef __CONFIG_H
#define __CONFIG_H

#include <string.h>

typedef struct {
	char ServerName[255];
}CONFIG_DATA;

void parseConfigFile (void);

#endif
