#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "libft.h"

void	logger(char *log_msg)
{
	FILE		*fd;
	char		buffer[100] = {0};
	struct tm	*ts;
	time_t		my_time;

	my_time = time(NULL);
	ts = localtime(&my_time);
	strftime(buffer, 100, "%Y-%m-%d - %H:%D:%S -> ", ts);
	strncpy(buffer + 31, log_msg, sizeof(buffer) - 31);
	fd = fopen("./log/cub3d.log", "a");
	fprintf(fd, buffer);
	fclose(fd);
}
