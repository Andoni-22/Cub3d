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

#ifndef CUB3D_H
# define CUB3D_H

#include "libft.h"
#include "get_next_line.h"

#include "mlx.h"
#include "mlx_int.h"

#define BYTE 8
#define PLAYER 'P'
#define WIDTH	500
#define HEIGHT	500

typedef struct	s_mlx
{
	void	*mlx;
	void	*img;
	char	*img_addr;
	void	*mlx_win;
	int		line_length;
	int		bit_per_pixel;
	int		endian;
}	t_mlx;

typedef struct	s_map
{
	char	**map;
	int		hit;
	int		side;
}	t_map;

/*
 * POS_X Y POS_Y -> POSICION INICIAL DEL JUGADOR EN EL MAPA
 *
 * DIR_X Y DIR_Y -> PRIMER VECTOR DE DIRECCION
 *
 * TIME -> TIEMPO DEL FRAME ACTUAL
 * OLD_TIME -> TIEMPO DEL FRAME ANTERIOR
 *
 */
typedef struct	s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;

}	t_player;

typedef struct	s_ray
{
	int		sq_pos_x;
	int		sq_pos_y;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	step_x;
	double	step_y;
}	t_ray;

typedef struct s_camera
{
	double	plane_x;
	double	plane_y;
	double	past;
	double	now;
	double	coord_x;
}	t_camera;

typedef struct	s_application {
	t_map		map;
	t_mlx		mlx_win;
	t_player	player;

}	t_application;


int		application_init(t_application *, char *);
void	application_destory(t_application *);
//int		appl_mlx_init(t_mlx	*);
void	appl_mlx_destroy(t_mlx *);
void	game(t_player *, t_map *);

char	**load_map(char *);

void	logger(char *);

#endif
