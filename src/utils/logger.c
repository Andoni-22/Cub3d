/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:18:40 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/11/29 20:18:42 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
	fprintf(fd, "%s", buffer);
	fclose(fd);
}
