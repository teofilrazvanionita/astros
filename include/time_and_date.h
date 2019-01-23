#ifndef __TIME_AND_DATE_H
#define __TIME_AND_DATE_H

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "errorlog.h"

char * getTime (void);
void destructTime(char *p);

#endif
