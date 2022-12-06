/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:53:48 by lugonzal          #+#    #+#             */
/*   Updated: 2022/12/06 13:14:27 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "mlx.h"
#include "custom_errors.h"

#include <stdio.h>

static int	destroy_window(t_application *appl)
{
	fprintf(stderr, "DESTROY");
	application_destory(appl);
	exit(1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_application	appl;
	t_mlx			*mlx_win;
	t_map			*map;
	t_custom_error	c_error;

	ft_memset(&c_error, 0, sizeof(t_custom_error));
	ft_memset(&appl, 0, sizeof(t_application));
	custom_error_init(&c_error);
	if (argc != 2 || application_init(&appl, argv[1], &c_error) < 0)
	{
		if (argc != 2)
			set_error(&c_error, 1, ILEGAL_ARGS);
		application_destory(&appl);
		return (print_custom_error(&c_error));
	}
	mlx_win = &appl.mlx_win;
	map = &appl.map;
	if (!map->map)
		return (-1);
	game_loop(&appl);
	mlx_hook(mlx_win->mlx_win, 2, 1L << 0, key_hook, &appl);
	mlx_hook(mlx_win->mlx_win, 17, 0L << 0, destroy_window, &appl);
	mlx_loop(mlx_win->mlx);
	application_destory(&appl);
	return (0);
}
