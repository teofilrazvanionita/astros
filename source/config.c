#include "config.h"


CONFIG_DATA smtpd_config;

void loadConfigs (void)
{
	setDefaults();
	parseConfigFile();
}

void setDefaults (void)
{
	int rv;
	memset((void *)&smtpd_config, 0, sizeof(CONFIG_DATA));

	if((rv = gethostname(smtpd_config.myhostname, sizeof(smtpd_config.myhostname))) == -1){
		ERROR("gethostname");
		exit(EXIT_FAILURE);
	}
	Dprintf("myhostname = %s\n", smtpd_config.myhostname);
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
