/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:20:02 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/12/01 19:10:47 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "custom_errors.h"

void	get_map_size(char *path, size_t sz[2])
{
	char	*line;
	size_t	len;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return ;
	sz[0] = 0;
	sz[1] = 0;
	while (1)
	{
	line = get_next_line(fd);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > sz[1])
			sz[1] = len;
		free(line);
		sz[0]++;
	}
	close(fd);
}

static int	return_map_type(t_custom_error *c_error, t_aux_params aux)
{
	if (aux.config_end >= aux.map_end)
		return (set_error(c_error, 43, INVALID_CFG_POS));
	if ((aux.config_end >= 0) && ((aux.config_end + 1) == aux.map_start))
		return (set_error(c_error, 44, INVALID_NL));
	if (aux.config_start == -1 && aux.map_start >= 0)
		return (set_error(c_error, 45, NO_CFG));
	if (aux.config_end < aux.map_start)
		return (1);
	return (255);
}

static int	aux_params_init(t_aux_params *aux)
{
	aux->map_start = -1;
	aux->map_end = -1;
	aux->config_start = -1;
	aux->config_end = -1;
	aux->map_line = -1;
	return (-1);
}

int static	map_control_lop(
		t_aux_params *aux, int i, char *raw, t_custom_error *c_error)
{
	if ((aux->map_start == -1) && (map_first_row_chrs(raw) == 0))
		aux->map_start = i;
	if ((aux->map_start >= 0) && (map_row_chrs(raw) == 0))
		aux->map_line = i;
	if ((aux->map_start >= 0) && (map_first_row_chrs(raw) == 0))
		aux->map_end = i;
	if ((aux->config_start == -1) && (is_config_line(raw, c_error) == 0))
		aux->config_start = i;
	if ((aux->map_line != i)
		&& (aux->config_start >= 0) && (is_config_line(raw, c_error) == 0))
		aux->config_end = i;
	if ((aux->map_start >= 0) && aux->config_start > aux->map_start)
		return (set_error(c_error, 40, INVALID_CFG_START));
	if ((aux->map_start >= 0) && (is_valid_map_line(raw) < 0))
		return (set_error(c_error, 41, INVALID_MAP_LINE));
	return (0);
}

int	get_map_type(char **raw, t_custom_error *c_error)
{
	int				i;
	int 			x;
	t_aux_params	aux;

	i = aux_params_init(&aux);
	while (raw[++i])
	{
		erase_nl(raw[i]);
		if (line_contain_data(raw[i]) == 0)
		{
			if (map_control_lop(&aux, i, raw[i], c_error) < 0)
				return (-1);
		}
		else if (aux.map_start != -1)
		{
			x = i -1;
			while (raw[++x])
			{
				if (line_contain_data(raw[x]) == 0)
					return (set_error(c_error, 122, MAP_NL));
			}
		}
	}
	return (return_map_type(c_error, aux));
}
