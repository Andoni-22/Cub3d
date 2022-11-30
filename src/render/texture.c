/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:25:18 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/30 19:25:20 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_tx(t_ray *ray)
{
	int	tx_type;

	if (ray->dir_x >= 0)
	{
		tx_type = 3;
		if (ray->side && ray->dir_y >= 0)
			tx_type = 2;
		else if (ray->side && ray->dir_y < 0)
			tx_type = 1;
	}
	else
	{
		tx_type = 0;
		if (ray->side && ray->dir_y >= 0)
			tx_type = 2;
		else if (ray->side && ray->dir_y < 0)
			tx_type = 1;
	}
	return (tx_type);
}

int	get_tx_color(t_tx t[4], int tx_y, int tx_x, int tx_type)
{
	int	color[4];
	int	len;

	len = t[tx_type].line_length;
	color[0] = t[tx_type].img_addr[tx_y * len + tx_x * 4 + 0];
	color[1] = t[tx_type].img_addr[tx_y * len + tx_x * 4 + 1];
	color[2] = t[tx_type].img_addr[tx_y * len + tx_x * 4 + 2];
	color[3] = t[tx_type].img_addr[tx_y * len + tx_x * 4 + 3];
	return (get_rgb(color[3], color[2], color[1], color[0]));
}
