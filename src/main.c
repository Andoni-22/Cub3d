/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:53:48 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/27 16:50:12 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hooks.h"
#include "mlx.h"

#include <stdio.h>
#include <math.h>

int	mouse_hook(int keycode, int x, int y, t_application *a)
{
	double	old_dir_x;
	double	old_plane_x;
	float	side;

	(void)y;
	side = (float)x / (float)WIDTH * 100;
	old_dir_x = a->player.dir_x;
	old_plane_x = a->cam.plane_x;
	if (keycode == LEFT_CLICK && side > 60)
	{
		a->player.dir_x = a->player.dir_x * cos(-R) - a->player.dir_y * sin(-R);
		a->player.dir_y = old_dir_x * sin(-R) + a->player.dir_y * cos(-R);
		a->cam.plane_x = a->cam.plane_x * cos(-R) - a->cam.plane_y * sin(-R);
		a->cam.plane_y = old_plane_x * sin(-R) + a->cam.plane_y * cos(-R);
	}
	else if (keycode == LEFT_CLICK && side < 40)
	{
		a->player.dir_x = a->player.dir_x * cos(R) - a->player.dir_y * sin(R);
		a->player.dir_y = old_dir_x * sin(R) + a->player.dir_y * cos(R);
		a->cam.plane_x = a->cam.plane_x * cos(R) - a->cam.plane_y * sin(R);
		a->cam.plane_y = old_plane_x * sin(R) + a->cam.plane_y * cos(R);
	}
	game_loop(a);
	return(1);
}

int	main(int argc, char **argv)
{
	t_application	appl;
	t_mlx			*mlx_win;
	t_map			*map;

	ft_memset(&appl, 0, sizeof(t_application));
	if (argc != 2 || application_init(&appl, argv[1]) < 0)
    {
        perror("Error");
		application_destory(&appl);
        return (-1);
    }
	mlx_win = &appl.mlx_win;
	map = &appl.map;
	if (!map->map)
		return (-1);
	game_loop(&appl);
	mlx_hook(mlx_win->mlx_win, 2, 1L << 0, key_hook, &appl);
	//mlx_hook(mlx_win->mlx_win, 4, 1L << 1, mouse_hook, &appl);
	mlx_mouse_hook(mlx_win->mlx_win, mouse_hook, &appl);
	mlx_loop(mlx_win->mlx);
	application_destory(&appl);
	return (0);
}
