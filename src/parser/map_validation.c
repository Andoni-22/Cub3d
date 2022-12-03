/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:20:07 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/12/01 20:40:48 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	valid_map_loop(char chr, int *one_find, int *cont, int *dir_cont)
{
	if (chr == '1')
		(*one_find)++;
	if (chr == '1' || chr == '0' || chr == ' ')
		(*cont)++;
	else if (is_player_position(chr) == 0)
	{
		(*dir_cont)++;
		(*cont)++;
	}
}

int	is_valid_map_line(char *line)
{
	int	i;
	int	cont;
	int	one_find;
	int	dir_cont;

	i = -1;
	cont = 0;
	dir_cont = 0;
	one_find = 0;
	while (line[++i])
		valid_map_loop(line[i], &one_find, &cont, &dir_cont);
	if (cont != (i))
		return (-1);
	if (dir_cont > 1)
		return (-1);
	if (one_find == 0)
		return (-1);
	return (0);
}

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

int	check_path_format(char *path, char *term, t_custom_error *c_error)
{
	char	**tmp;
	int		size;
	int		fd;

	size = 0;
	tmp = ft_split(path, '.');
	if (!tmp)
		return (set_error(c_error, 1, BAD_PATH_CUB));
	while (tmp[size] != NULL)
		size++;
	fd = open(path, O_RDONLY);
	close(fd);
	if (ft_strncmp(term, tmp[size - 1], ft_strlen(term) + 1) != 0)
		return (set_error_and_free(c_error, 2, BAD_PATH_CUB, tmp));
	if (size <= 1 && fd > 0)
		return (set_error_and_free(c_error, 3, EMPTY_FILE, tmp));
	if (fd <= 0)
		return (set_error_and_free(c_error, 4, INCORRECT_FILE, tmp));
	free_str_array(tmp);
	return (0);
}
