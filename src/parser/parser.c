/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:48:29 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/11/29 18:53:17 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "custom_errors.h"
#include <stdlib.h>

static int	is_open(char **map, int i)
{
	int	sum[2];
	int	col;

	col = 1;
	while (map[i][col] && map[i + 1][col])
	{
		sum[0] = map[i + 1][col] + map[i][col];
		sum[1] = map[i][col + 1] + map[i][col];
		if (sum[0] == 80 || sum[1] == 80 || sum[0] == 48 || sum[1] == 48)
			return (1);
		col++;
	}
	if (map[i + 1][col] == '0' || map[i][col] == '0')
		return (1);
	return (0);
}

static char	**get_map(char **raw, int start, size_t sz[2], t_application *appl)
{
	char	**map;
	int		i;

	map = ft_calloc(sizeof(char *), (sz[0] - start + 3));
	map[0] = ft_calloc(sizeof(char), (sz[1] + 1));
	ft_memset(map[0], SP, sz[1]);
	map[sz[0] - start + 1] = ft_calloc(sizeof(char), (sz[1] + 1));
	ft_memset(map[sz[0] - start + 1], SP, sz[1]);
	i = 0;
	while (raw[start])
	{
		locate_player(&appl->player, &appl->cam, raw[start]);
		map[i + 1] = ft_calloc(sizeof(char), (sz[1] + 1));
		ft_memset(map[i + 1], SP, sz[1]);
		ft_memcpy(map[i + 1], raw[start], ft_strlen(raw[start]));
		free(raw[start]);
		raw[start++] = NULL;
		if (is_open(map, i++))
			return (set_error_and_free_chr(appl->aux_error, 22, MAP_IS_OPEN, map));
	}
	if (is_open(map, i))
		return (set_error_and_free_chr(appl->aux_error, 22, MAP_IS_OPEN, map));
	if (appl->player.exist != 1)
		return (set_error_and_free_chr(appl->aux_error, 22, BAP_PLAYER, map));
	return (map);
}

char	**complex_map(t_application *appl, char **raw_tab, size_t sz[2])
{
	int	pos;

	pos = set_textures(appl->tx, &appl->mlx_win, appl->rgb, raw_tab);
	if (pos == -1)
		return (NULL);
	while (raw_tab[pos]
		&& ft_strchr(raw_tab[pos], '1') == 0)
		pos++;
	if (!raw_tab[pos])
		return (NULL);
	return (get_map(raw_tab, pos, sz, appl));
}

char	**load_map(t_application *appl, char *path, t_custom_error *c_error)
{
	size_t	sz[2];
	char	**tmp;
	char	**map;

	get_map_size(path, sz);
	if (!sz[0])
		return (set_error_chr(c_error, 5, MAP_IS_EMPTY));
	tmp = load_raw_file_data(path, sz[0], c_error);
	map = process_raw_data(appl, tmp, sz, c_error);
	free_str_array(tmp);
	if (!map)
		return (NULL);
	return (map);
}
