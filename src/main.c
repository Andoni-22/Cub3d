/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:53:48 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/07 21:11:19 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hooks.h"
#include "mlx.h"

#include <math.h>
#include <stdio.h>

void	my_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*pix_position;
	int		y_coord_offset;
	int		x_coord_offset;

	y_coord_offset = y * mlx->line_length;
	x_coord_offset = x * (mlx->bit_per_pixel / BYTE);
	pix_position = mlx->img_addr + y_coord_offset + x_coord_offset;
	*(unsigned int *)pix_position = color;
}

int	get_rgb(int t, int red, int green, int blue)
{
	return (t << 24 | red << 16 | green << 8 | blue);
}

static void	show_map(char **map)
{
	char	buffer[100];

	sprintf(buffer, "MAP ADDR: %p\n", map);
	printf(buffer, "MAP INNER ADDR: %p\n", *map);
	while (*map)
		printf("%s", *map++);
}

static int	colission(t_map *map, t_ray *ray, t_player *pl, int sign)
{
	int	ret_val[2];

	if (sign == 1)
	{
		ret_val[0] = map->map[(int)(pl->pos_x + pl->dir_x / 2)]
			[(int)pl->pos_y] - 48;
		ret_val[1] = map->map[(int)pl->pos_x]
			[(int)(pl->pos_y + pl->dir_y / 2)] - 48;
	}
	else
	{
		ret_val[0] = map->map[(int)pl->pos_x]
			[(int)(pl->pos_y - pl->dir_y / 2)] - 48;
		ret_val[1] = map->map[(int)(pl->pos_x - pl->dir_x / 2)]
			[(int)pl->pos_y] - 48;
	}
	return (!ret_val[0] * !ret_val[1]);
}

//fprintf(stderr, "KEYCODE: %d\n", keycode);
//fprintf(stderr, "X: %lf\n", appl->player.pos_x);
//fprintf(stderr, "Y: %lf\n", appl->player.pos_y);
//fprintf(stderr, "MAP: %d\n", appl->map.map[appl->ray.map_x][appl->ray.map_y]);
//fprintf(stderr, "RETVAL: %d\n", ret_val);
static int	key_hook(int keycode, t_application *appl)
{
	int	ret_val;

	if (keycode == UP)
	{
		ret_val = colission(&appl->map, &appl->ray, &appl->player, PLUS);
		appl->player.pos_y += appl->player.dir_y * ret_val / MOVEMENT_K;
		appl->player.pos_x += appl->player.dir_x * ret_val / MOVEMENT_K;
	}
	if (keycode == DOWN)
	{
		ret_val = colission(&appl->map, &appl->ray, &appl->player, MINUS);
		appl->player.pos_y -= appl->player.dir_y * ret_val / MOVEMENT_K;
		appl->player.pos_x -= appl->player.dir_x * ret_val / MOVEMENT_K;
	}
	if (keycode == RIGHT)
	{
		double oldDirX = appl->player.dir_x;
		appl->player.dir_x = appl->player.dir_x * cos(-ROTATE) - appl->player.dir_y * sin(-ROTATE);
		appl->player.dir_y = oldDirX * sin(-ROTATE) + appl->player.dir_y * cos(-ROTATE);
		double oldPlaneX = appl->cam.plane_x;
		appl->cam.plane_x = appl->cam.plane_x * cos(-ROTATE) - appl->cam.plane_y * sin(-ROTATE);
		appl->cam.plane_y = oldPlaneX * sin(-ROTATE) + appl->cam.plane_y * cos(-ROTATE);
    }
	if (keycode == LEFT)
	{	
		double oldDirX = appl->player.dir_x;
		appl->player.dir_x = appl->player.dir_x * cos(ROTATE) - appl->player.dir_y * sin(ROTATE);
		appl->player.dir_y = oldDirX * sin(ROTATE) + appl->player.dir_y * cos(ROTATE);
		double oldPlaneX = appl->cam.plane_x;
		appl->cam.plane_x = appl->cam.plane_x * cos(ROTATE) - appl->cam.plane_y * sin(ROTATE);
		appl->cam.plane_y = oldPlaneX * sin(ROTATE) + appl->cam.plane_y * cos(ROTATE);
    }
	fprintf(stderr, "DIR_X: %lf\n", appl->player.dir_x);
	fprintf(stderr, "DIR_Y: %lf\n", appl->player.dir_y);
	fprintf(stderr, "PLANE_X: %lf\n", appl->cam.plane_x);
	fprintf(stderr, "PLANE_Y: %lf\n", appl->cam.plane_y);
	game_loop(appl);
	return (1);
}

static int	release_hook(int keycode, t_application *appl)
{
	fprintf(stderr, "KEYCODE: %d\n", keycode);
	return (1);
}

int main(int argc, char **argv)
{
	t_application	appl;
	t_mlx			*mlx_win;
	t_map			*map;
	t_player		*player;

	if (argc != 2 || application_init(&appl, argv[1]) < 0)
		return (-1);
	mlx_win = &appl.mlx_win;
	map = &appl.map;
	player = &appl.player;
	if (!map->map)
		return (-1);
	game_loop(&appl);
	mlx_hook(mlx_win->mlx_win, 2, 1L << 0, key_hook, &appl);
	//mlx_hook(mlx_win->mlx_win, 3, 1L << 1, release_hook, &appl);
	mlx_loop(mlx_win->mlx);
	application_destory(&appl);
	return (0);
}
