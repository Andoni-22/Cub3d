/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 01:38:18 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/27 16:50:10 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

#include <stdio.h>

static char	*find_player(char *line, const char *set)
{
	char	*player;

	while (*line)
	{
		player = ft_strchr(set, *line);
		if (player)
			return (line);
		line++;
	}
	return (NULL);
}

static void	vertical_player_pos(t_player *player, t_camera *cam, int dir)
{
	if (dir == 'N')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = -0.66;
	}
}

static void	horizontal_player_pos(t_player *player, t_camera *cam, int dir)
{
	if (dir == 'E')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		cam->plane_x = 0.66;
		cam->plane_y = 0;
	}
	else if (dir == 'W')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		cam->plane_x = -0.66;
		cam->plane_y = 0;
	}
}

static void	set_player_pos(t_player *player, t_camera *cam, int dir)
{
	horizontal_player_pos(player, cam, dir);
	vertical_player_pos(player, cam, dir);
}

void	locate_player(t_player *player, t_camera *cam, char *line)
{
	char	*player_pos;

	player_pos = find_player(line, "NSEW");
	if (player_pos && player->exist)
		player->exist = -1;
	if (player->exist)
		return ;
	if (player_pos)
	{
		player->pos_y = player_pos - line;
		set_player_pos(player, cam, *player_pos);
		*player_pos = FLOOR;
		player->exist++;
		player->pos_y += 0.1;
		player->pos_x += 0.1;
	}
	player->pos_x++;
}

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
