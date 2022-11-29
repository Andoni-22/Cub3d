/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:19:52 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/11/29 20:21:22 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "custom_errors.h"
#include <stdlib.h>

static void	set_texture_keys(t_tx tx[4], t_rgb rgb[2])
{
	ft_memcpy(tx[0].key, NORTH, 2);
	ft_memcpy(tx[1].key, SOUTH, 2);
	ft_memcpy(tx[2].key, WEST, 2);
	ft_memcpy(tx[3].key, EAST, 2);
	ft_memcpy(rgb[0].key, "F", 1);
	ft_memcpy(rgb[1].key, "C", 1);
}

static int	check_rgb_format(char *line)
{
	int	i;
	int	coma_count;

	i = -1;
	coma_count = 0;
	while (line[++i])
	{
		if (!ft_strchr("0123456789,", line[i]))
			return (1);
		else if (line[i] == COMA)
			coma_count++;
	}
	if (coma_count > 2)
		return (1);
	return (0);
}

static int	set_rgb(t_rgb rgb[2], char **rgb_tab, int pos)
{
	size_t	i;
	int		num;
	char	**tab;

	tab = ft_split(rgb_tab[1], COMA);
	i = -1;
	if (!tab || !tab[0] || !tab[1] || !tab[2]
		|| tab[3] || check_rgb_format(rgb_tab[1]))
	{
		free_str_array(tab);
		return (-1);
	}
	while (tab[++i])
	{
		num = ft_atoi(tab[i]);
		if (num < 0 || num > 255)
		{
			free_str_array(tab);
			return (-1);
		}
		rgb[pos].trgb[i + 1] = num;
	}
	free_str_array(tab);
	return (0);
}

static int	query_texture(t_mlx *mlx, t_tx tx[4], t_rgb rgb[2], char **tx_tab)
{
	size_t	i;

	i = -1;
	while (++i < 4)
	{
		if (!ft_strncmp(tx[i].key, tx_tab[0], 3))
		{
			if (process_image(&tx[i], mlx, tx_tab[1]))
				return (-1);
			return (0);
		}
		else if (!ft_strncmp(rgb[0].key, tx_tab[0], 2))
		{
			if (set_rgb(rgb, tx_tab, C) == -1)
				return (-1);
			return (0);
		}
		else if (!ft_strncmp(rgb[1].key, tx_tab[0], 2))
		{
			if (set_rgb(rgb, tx_tab, F) == -1)
				return (-1);
			return (0);
		}
	}
	return (-1);
}

int	set_textures(t_tx tx[4], t_mlx *mlx, t_rgb rgb[2], char **raw_tab)
{
	char	**tx_tab;
	int		pos;
	int		config_cnt;

	set_texture_keys(tx, rgb);
	config_cnt = 0;
	pos = -1;
	while (raw_tab[++pos] && config_cnt < 6)
	{
		if (raw_tab[pos][0] == '\0')
			continue ;
		tx_tab = ft_split(raw_tab[pos], SP);
		if (!tx_tab || !tx_tab[0] || !tx_tab[1] || tx_tab[2]
			|| query_texture(mlx, tx, rgb, tx_tab) == -1)
		{
			free_str_array(tx_tab);
			return (-1);
		}
		else
			config_cnt++;
		free_str_array(tx_tab);
	}
	if (config_cnt != 6)
		return (-1);
	return (pos);
}
