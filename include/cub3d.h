/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andoni <andoni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:42:02 by andoni            #+#    #+#             */
/*   Updated: 2022/10/12 16:42:56 by andoni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED
# define CUBED

#include <stdlib.h>
#include <stdio.h>

#define BYTE 8

typedef struct s_mlx_tools
{
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	char	*mlx_addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx_tools;


#endif
