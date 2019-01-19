#include "config.h"


CONFIG_DATA smtpd_config;

void loadConfigs (void)
{
	setDefaults();
	parseConfigFile();
}

void setDefaults (void)
{
	memset((void *)&smtpd_config, 0, sizeof(CONFIG_DATA));
}

void parseConfigFile (void)
{
	int fd_config_file;

	fd_config_file = open((const char *)CONFIG_FILE, O_RDONLY);
	if(fd_config_file == -1){
		ERROR("open");
		exit(EXIT_FAILURE);
	}
}
