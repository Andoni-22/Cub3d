/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andoni <andoni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:42:02 by andoni            #+#    #+#             */
/*   Updated: 2022/10/19 23:01:26 by andoni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "libft.h"
#include "get_next_line.h"

#include "mlx.h"
#include "mlx_int.h"

#define BYTE 8

typedef struct mlx_s
{
	void	*mlx;
	void	*img;
	char	*img_addr;
	void	*mlx_win;
	int		size_y;
	int		size_x;
	int		line_length;
	int		bit_per_pixel;
	int		endian;

}	mlx_t;

typedef struct	s_map
{
	char	**map;
	ssize_t	map_sz;
}	t_map;

typedef struct	application_s {
	t_map	map;
	mlx_t	mlx_win;

} application_t;


int		application_init(application_t *appl);
void	application_destory(application_t *appl);
int		appl_mlx_init(mlx_t	*mlx);
void	appl_mlx_destroy(mlx_t	*mlx);

ssize_t	get_map_size(int);
char	**load_map(ssize_t, int);

#endif
