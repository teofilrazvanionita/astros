#include "config.h"

CONFIG_DATA smtpd_config;

void parseConfigFile (void)
{
	memset((void *)&smtpd_config, 0, sizeof(CONFIG_DATA));
}
