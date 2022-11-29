/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:51:30 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/11/29 18:53:17 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "custom_errors.h"
#include <unistd.h>
#include <sys/fcntl.h>

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

char	**process_raw_data(
		t_application *appl, char **raw, size_t sz[2], t_custom_error *c_error)
{
	int		map_type;
	char	**map;

	map_type = get_map_type(raw, c_error);
	if (map_type == 0 || map_type == -1)
		return (NULL);
	map = complex_map(appl, raw, sz);
	return (map);
}

char	**load_raw_file_data(char *path, size_t sz, t_custom_error *c_error)
{
	char	**map;
	char	*line;
	int		fd;

	map = ft_calloc(sizeof(char *), sz + 1);
	if (!map)
		return (set_error_chr(c_error, 20, INVALID_MALLOC));
	sz = 0;
	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map[sz++] = line;
	}
	close(fd);
	return (map);
}

int	line_contain_data(char *line)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	if (!*line)
		return (-1);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == 9)
			cont++;
		i++;
	}
	if (cont == i - 1)
		return (-1);
	return (0);
}

int	map_first_row_chrs(char *line)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == ' ')
			cont++;
		i++;
	}
	if (cont != (i))
		return (-1);
	return (0);
}
