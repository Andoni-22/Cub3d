/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:24:29 by lugonzal          #+#    #+#             */
/*   Updated: 2022/12/03 18:15:00 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pixel_color(t_mlx *mlx, int x, int y, int color)
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

void	clear_image(t_mlx *mlx, t_rgb rgb[2])
{
	int	x;
	int	y;
	int	color[2];

	color[0] = get_rgb(
			rgb[0].trgb[0], rgb[0].trgb[1], rgb[0].trgb[2], rgb[0].trgb[3]);
	color[1] = get_rgb(
			rgb[1].trgb[0], rgb[1].trgb[1], rgb[1].trgb[2], rgb[1].trgb[3]);
	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			set_pixel_color(mlx, x, y, color[0]);
			set_pixel_color(mlx, x, y + HEIGHT / 2, color[1]);
		}
	}
}
