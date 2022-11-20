/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 01:38:18 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/13 01:47:51 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

#include <string.h>
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

void	locate_player(t_player *player, t_map *map, t_camera *cam)
{
	char	*player_pos;
	size_t	i;

	i = -1;
	while (map->map[++i])
	{
		player_pos = find_player(map->map[i], "NSEW");
		if (player_pos)
		{
			player->pos_y = player_pos - map->map[i];
			set_player_pos(player, cam, *player_pos);
			*player_pos = FLOOR;
			break ;
		}
		player->pos_x++;
	}
	if (!player_pos)
		exit(1);
	player->pos_y += 0.1;
	player->pos_x += 0.1;
}

int	process_image(t_tx *t, t_mlx *mlx, char *xpm_file)
{
	void	*raw_img;

	raw_img = mlx_xpm_file_to_image(mlx->mlx, xpm_file, &t->width, &t->height);
	if (!raw_img)
		return (1);
	t->img = mlx_get_data_addr(raw_img, &t->bit_per_pixel,
			&t->line_length, &t->endian);
	if (!t->img)
		return (1);
	return (0);
}

static void	appl_map_destroy(t_map *map)
{
	size_t	i;

	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
}

void	application_destory(t_application *appl)
{
	appl_mlx_destroy(&appl->mlx_win);
	appl_map_destroy(&appl->map);
}

void	appl_mlx_destroy(t_mlx	*mlx)
{
	(void)mlx;
}
