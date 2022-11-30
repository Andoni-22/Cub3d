/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 01:38:18 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/30 19:27:02 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

#include <stdio.h>

int	process_image(t_tx *t, t_mlx *mlx, char *xpm_file)
{
	t->img = mlx_xpm_file_to_image(mlx->mlx, xpm_file, &t->width, &t->height);
	if (!t->img)
		return (1);
	t->img_addr = mlx_get_data_addr(t->img, &t->bit_per_pixel,
			&t->line_length, &t->endian);
	if (!t->img_addr)
		return (1);
	return (0);
}

void	appl_map_destroy(t_map *map)
{
	size_t	i;

	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
}

void	application_destory(t_application *appl)
{
	appl_mlx_destroy(&appl->mlx_win, appl->tx);
	if (appl->map.map)
		appl_map_destroy(&appl->map);
}

static void	destroy_textures(t_mlx *mlx, t_tx tx[4])
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (tx[i].img)
		{
			mlx_destroy_image(mlx->mlx, tx[i].img);
			tx[i].img = NULL;
		}
	}
}

void	appl_mlx_destroy(t_mlx	*mlx, t_tx tx[4])
{
	destroy_textures(mlx, tx);
	if (mlx->mlx)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	}
	free(mlx->mlx);
}
