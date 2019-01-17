#ifndef __CONFIG_H
#define __CONFIG_H

typedef struct {
	char ServerName[64];
}CONFIG_DATA;

void readConfigFile (void);

#endif
