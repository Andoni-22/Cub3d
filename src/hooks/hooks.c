/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:07:59 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/27 16:50:12 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "hooks.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static int	cls(t_map *map, t_player *pl, float x, float y)
{
	int	ret_val[3];

	ret_val[0] = map->map[(int)(pl->pos_x + x)]
	[(int)pl->pos_y] - 48;
	ret_val[1] = map->map[(int)pl->pos_x]
	[(int)(pl->pos_y + y)] - 48;
	ret_val[2] = map->map[(int)(pl->pos_x + x)]
	[(int)(pl->pos_y + y)] - 48;
	return (!ret_val[0] * !ret_val[1] * !ret_val[2]);
}

static void	rotate(int keycode, t_application *a)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = a->player.dir_x;
	old_plane_x = a->cam.plane_x;
	if (keycode == ROTATE_RIGHT)
	{
		a->player.dir_x = a->player.dir_x * cos(-R) - a->player.dir_y * sin(-R);
		a->player.dir_y = old_dir_x * sin(-R) + a->player.dir_y * cos(-R);
		a->cam.plane_x = a->cam.plane_x * cos(-R) - a->cam.plane_y * sin(-R);
		a->cam.plane_y = old_plane_x * sin(-R) + a->cam.plane_y * cos(-R);
	}
	else if (keycode == ROTATE_LEFT)
	{
		a->player.dir_x = a->player.dir_x * cos(R) - a->player.dir_y * sin(R);
		a->player.dir_y = old_dir_x * sin(R) + a->player.dir_y * cos(R);
		a->cam.plane_x = a->cam.plane_x * cos(R) - a->cam.plane_y * sin(R);
		a->cam.plane_y = old_plane_x * sin(R) + a->cam.plane_y * cos(R);
	}
}

static void	vertical_key_hook(int keycode, t_application *a)
{
	int	ret_val;

	if (keycode == UP)
	{
		ret_val = cls(&a->map, &a->player, a->player.dir_x, a->player.dir_y);
		a->player.pos_y += a->player.dir_y * ret_val * 0.75;
		a->player.pos_x += a->player.dir_x * ret_val * 0.75;
	}
	else if (keycode == DOWN)
	{
		ret_val = cls(&a->map, &a->player, -a->player.dir_x, -a->player.dir_y);
		a->player.pos_y -= a->player.dir_y * ret_val * 0.75;
		a->player.pos_x -= a->player.dir_x * ret_val * 0.75;
	}
}

static void	horizontal_key_hook(int keycode, t_application *a)
{
	int	ret_val;

	if (keycode == RIGHT)
	{
		ret_val = cls(&a->map, &a->player, a->cam.plane_x, a->cam.plane_y);
		a->player.pos_y += a->cam.plane_y * ret_val * 0.75;
		a->player.pos_x += a->cam.plane_x * ret_val * 0.75;
	}
	else if (keycode == LEFT)
	{
		ret_val = cls(&a->map, &a->player, -a->cam.plane_x, -a->cam.plane_y);
		a->player.pos_y -= a->cam.plane_y * ret_val * 0.75;
		a->player.pos_x -= a->cam.plane_x * ret_val * 0.75;
	}
}

int	key_hook(int keycode, t_application *appl)
{
	fprintf(stderr, "KEYCODE: %d\n", keycode);
	if (keycode == ESC || keycode == EXIT)
	{
		application_destory(appl);
		exit(0);
	}
	vertical_key_hook(keycode, appl);
	horizontal_key_hook(keycode, appl);
	rotate(keycode, appl);
	game_loop(appl);
	return (1);
}
