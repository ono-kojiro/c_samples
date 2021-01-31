#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

#include "userdata.h"
#include "options.h"

int main(int argc, char **argv)
{
	char str[256];
	int i;
	USERDATA *userdata;
	
	OPTION *option;
	int n;
	
	printf("gperf sample\n");
	sprintf(str, "hoge");

	userdata = get_userdata(str, strlen(str));
	if(userdata == NULL){
		fprintf(stderr, "no userdata for '%s'\n", str);
		exit(1);
	}

	printf("value of %s is %d\n", userdata->name, userdata->value);

	userdata->write_value = 3;

	printf("write value of %s is %d\n", userdata->name, userdata->write_value);
	
	print_options();
	set_option("help", "1");
	print_options();
	
	free_options();
	return 0;
}

