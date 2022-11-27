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
#include "mlx.h"

#include <stdio.h>

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
	mlx_loop(mlx_win->mlx);
	application_destory(&appl);
	return (0);
}
