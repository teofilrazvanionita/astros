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

	set_mydomain_Defaults();
	set_myhostname_Defaults();
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


void set_myhostname_Defaults (void)
{
	int rv;
	
	if((rv = gethostname(smtpd_config.myhostname, sizeof(smtpd_config.myhostname))) == -1){
		ERROR("gethostname");
		exit(EXIT_FAILURE);
	}
	
	strncat(smtpd_config.myhostname, smtpd_config.mydomain, sizeof(smtpd_config.myhostname));
	Dprintf("myhostname = %s\n", smtpd_config.myhostname);

}

void set_mydomain_Defaults (void)
{
	int rv;
	char temp_mydomain[256];

	memset(temp_mydomain, 0, 256);

	if((rv = getdomainname(temp_mydomain,sizeof(temp_mydomain))) == -1){
		ERROR("getdomainname");
		exit(EXIT_FAILURE);
	}
	Dprintf("temp_mydomain = %s\n", temp_mydomain);

	if(strcmp(temp_mydomain, "(none)") == 0)
		strcpy(smtpd_config.mydomain, "localdomain");
	else
		strcpy(smtpd_config.mydomain, temp_mydomain);

	Dprintf("mydomain = %s\n", smtpd_config.mydomain);
}

