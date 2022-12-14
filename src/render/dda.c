/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:23:08 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/30 20:11:23 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	game_loop(t_application *a)
{
	clear_image(&a->mlx_win, a->rgb);
	a->mlx_win.x = -1;
	a->ray.pos_x = a->player.pos_x;
	a->ray.pos_y = a->player.pos_y;
	while (++a->mlx_win.x <= WIDTH)
	{
		a->cam.coord_x = 2 * a->mlx_win.x / (double)WIDTH - 1;
		set_ray(&a->ray, &a->player, &a->cam);
		wall_hit_case(&a->ray, &a->map, &a->mlx_win, a->tx);
	}
	mlx_put_image_to_window(a->mlx_win.mlx, a->mlx_win.mlx_win,
		a->mlx_win.img, 0, 0);
	return (1);
}
