/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andoni <andoni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:42:02 by andoni            #+#    #+#             */
/*   Updated: 2022/11/06 18:13:26 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "libft.h"
#include "get_next_line.h"

#define BYTE 	8
#define PLAYER 'P'
#define WIDTH	1080
#define HEIGHT	960
#define	WALL	'1'
#define	FLOOR	'0'

#define BUFFER_SIZE 1000
#define MOVEMENT_K	2
#define ROTATE		0.125f

#define	X		0
#define	Y		1
#define PLUS	1
#define MINUS	-1

#define TEXTURE_WIDTH	64
#define TEXTURE_HEIGHT	64
#define TEXTURE			16384

typedef struct	s_texture
{
	char	texture_set[8][TEXTURE];
	int		xorcolor;
	int		ycolor;
	int		xycolor;
}	t_texture;

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
	int		side;
	int		wall_height;
	double	perp_wall_dist;

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
	int		map_x;
	int		map_y;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;

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
	t_camera	cam;
	t_ray		ray;
	t_texture	texture;

}	t_application;


int		application_init(t_application *, char *);
void	application_destory(t_application *);
//int		appl_mlx_init(t_mlx	*);
void	appl_mlx_destroy(t_mlx *);
void	game_loop(t_application *appl);//t_player *, t_map *, t_mlx *);

char	**load_map(char *);

void	logger(char *);

void	my_pixel_put(t_mlx*, int, int, int);

#endif
