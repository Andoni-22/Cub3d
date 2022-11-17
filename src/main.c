/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:53:48 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/09 20:07:37 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hooks.h"
#include "mlx.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

int	cls(t_map *map, t_player *pl, float x, float y)
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

static int	key_hook(int keycode, t_application *a)
{
	vertical_key_hook(keycode, a);
	horizontal_key_hook(keycode, a);
	rotate(keycode, a);
	game_loop(a);
	return (1);
}

int	main(int argc, char **argv)
{
	t_application	appl;
	t_mlx			*mlx_win;
	t_map			*map;

	if (argc != 2 || application_init(&appl, argv[1]) < 0)
    {
        fprintf(stderr, ".Error\n");
        return (-1);
    }
	mlx_win = &appl.mlx_win;
	map = &appl.map;
	if (!map->map)
		return (-1);
	game_loop(&appl);
	mlx_hook(mlx_win->mlx_win, 2, 1L << 0, key_hook, &appl);
	mlx_loop(mlx_win->mlx);
	application_destory(&appl);
	return (0);
}
