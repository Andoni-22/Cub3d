/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andoni <andoni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:42:02 by andoni            #+#    #+#             */
/*   Updated: 2022/11/20 16:19:10 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"

# define BYTE 			8
# define COMA			','
# define PLAYER 		'P'
# define WIDTH			1080
# define HEIGHT			960
# define WALL			'1'
# define FLOOR			'0'

# define BUFFER_SIZE 	1000
# define MOVEMENT_K		4
# define R				0.125f

# define X				0
# define Y				1
# define PLUS			1
# define PLUS_REV 		2
# define MINUS			-1
# define MINUS_REV		2

# define TEXTURE		4096
# define SP				32
# define NL				10

# define F			0
# define C		1

# define FILE_FORMAT_CUB	"cub"
# define FILE_FORMAT_XPM    "xpm"

# define NORTH			"NO"
# define SOUTH			"SO"
# define WEST			"WE"
# define EAST			"EA"

typedef struct s_tx
{
	char	key[3];
	void	*img;
	char	*img_addr;
	int		xorcolor;
	int		ycolor;
	int		xycolor;
	int		width;
	int		height;
	int		line_length;
	int		bit_per_pixel;
	int		endian;
}	t_tx;

typedef struct s_mlx
{
	void	*mlx;
	void	*img;
	char	*img_addr;
	void	*mlx_win;
	int		line_length;
	int		bit_per_pixel;
	int		endian;
	int		x;
}	t_mlx;

typedef struct s_map
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
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	old_dir_x;
	int		exist;
}	t_player;

typedef struct s_ray
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
	double	coord_x;
	double	old_plane_x;
}	t_camera;

typedef struct s_wall_info
{
	int		type;
	int		x;
	int		y;
	double	pos;
	int		start;
	int		end;
	double	x_pos;
	double	step;
	int		color;
}	t_wall_info;

typedef	struct s_rgb
{
	char	key[2];
	int		trgb[4];
}	t_rgb;

typedef struct s_application
{
	t_map		map;
	t_mlx		mlx_win;
	t_player	player;
	t_camera	cam;
	t_ray		ray;
	t_tx		tx[4];
	t_rgb		rgb[2];
}	t_application;

int		application_init(t_application *appl, char *path);
void	application_destory(t_application *appl);
void	appl_mlx_destroy(t_mlx *mlx);
int		game_loop(t_application *appl);

//PARSER
int		check_path_format(char *path, char *term);
char	**load_map(t_application *appl, char *path);
int     map_first_row_chrs(char *line);
int     is_config_line(char *line);
int     is_valid_map_line(char *line);
int     line_contain_data(char *line);

//PARSE_PLAYER
int     is_player_position(char c);
int     process_player(int pos_found, int line, int colum, char **raw);

////PARSE_MAP
void	get_map_size(char *path, size_t	sz[2]);
int     get_map_type(char **raw);
void	logger(char *msg);

//UTILS
char    **str_array_copy(char **src);
int     str_array_get_size(char **src);
char    **free_str_array(char **tmp);
char	*chr_cut_back(char *dir, char c);

//PIXEL UTILS//
void	clear_image(t_mlx *mlx);

//RAY//
void	set_ray(t_ray *ray, t_player *pl, t_camera *cam);

//WALL//
void	wall_hit_case(t_ray *ray, t_map *map, t_mlx *mlx, t_tx *t);

//TEXTURE//
int	set_tx(t_ray *ray);
int	get_tx_color(t_tx t[4], int tx_y, int tx_x, int tx_type);

//PIXEL UTILS
void	set_pixel_color(t_mlx *mlx, int x, int y, int color);
int		get_rgb(int t, int red, int green, int blue);

//HOOKS
int	key_hook(int keycode, t_application *appl);

//INIT
int	application_init(t_application *appl, char *path);
int	process_image(t_tx *t, t_mlx *mlx, char *xpm_file);
void	locate_player(t_player *player, t_camera *cam, char *line);

//SHOW MAP
void	show_map(char **map);

#endif
