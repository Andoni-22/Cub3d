#include "cub3d.h"
#include "mlx.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int	appl_mlx_init(t_mlx	*mlx)
{
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3d");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bit_per_pixel, &mlx->line_length, &mlx->endian);
	return (0);
}

static int	appl_map_init(t_map *map, char *path)
{
	map->map = load_map(path);
	if (!map->map)
		return (-1);
	return (0);
}

static char	*find_player(char *line, const char *set)
{
	char	*player;

	while (*line)
	{
		player = ft_strchr(set, *line);
		if (player)
			return (line);
		line++;
	}
	return (NULL);
}

static void	set_player_pos(t_player *player, t_camera *cam, int dir)
{
	if (dir == 'N')
	{
		fprintf(stderr, "NORTH");
		player->dir_x = -1;
		player->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = 0.66;
	}
	else if (dir == 'S')
	{
		fprintf(stderr, "SOUTH");
		player->dir_x = 1;
		player->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		fprintf(stderr, "EAST");
		player->dir_x = 0;
		player->dir_y = 1;
		cam->plane_x = 0.66;
		cam->plane_y = 0;
	}
	else if (dir == 'W')
	{
		fprintf(stderr, "EAST");
		player->dir_x = 0;
		player->dir_y = -1;
		cam->plane_x = -0.66;
		cam->plane_y = 0;
	}
}

static void	locate_player(t_player *player, t_map *map, t_camera *cam)
{
	char	*player_pos;
	size_t	i;

	i = -1;
	while (map->map[++i])
	{
		player_pos = find_player(map->map[i], "NSEW");
		if (player_pos)
		{
			player->pos_y = player_pos - map->map[i];
			set_player_pos(player, cam, *player_pos);
			*player_pos = FLOOR;
			break ;
		}
		player->pos_x++;
	}
	if (!player_pos)
		exit(1);
	player->pos_y += 0.1;
	player->pos_x += 0.1;
}

static int	appl_player_init(t_player *player, t_map *map, t_camera *cam)
{
	locate_player(player, map, cam);
	return (0);
}

static int	appl_cam_init(t_camera *cam)
{
	(void)cam;
	return (0);
}

static int	process_image(t_tx *t, t_mlx *mlx, char *xpm_file)
{
	void	*raw_img;

	raw_img = mlx_xpm_file_to_image(mlx->mlx, xpm_file, &t->width, &t->height);
	if (!raw_img)
		return (1);
	t->img = mlx_get_data_addr(raw_img, &t->bit_per_pixel, &t->line_length, &t->endian);
	return (0);
}

static int	appl_tx_init(t_tx t[4], t_mlx *mlx)
{
	int		ret_val;
	size_t	i;
	char	*wall_tx[4];

	wall_tx[0] = "./xpm_images/AnyConv.com__eagle.xpm";
	wall_tx[1] = "./xpm_images/AnyConv.com__redbrick.xpm";
	wall_tx[2] = "./xpm_images/AnyConv.com__colorstone.xpm";
	wall_tx[3] = "./xpm_images/AnyConv.com__greystone.xpm";
	i = -1;
	while (++i < 4)
	{	
		ret_val = process_image(&t[i], mlx, wall_tx[i]);
		if (ret_val)
			return (-1);
	}
	return (0);
}

int	application_init(t_application *appl, char *path)
{
	memset(appl, 0, sizeof(t_application));
	if (appl_mlx_init(&appl->mlx_win) < 0)
		return (-1);
	if (appl_map_init(&appl->map, path) < 0)
		return (-1);
	if (appl_cam_init(&appl->cam) < 0)
		return (-1);
	if (appl_player_init(&appl->player, &appl->map, &appl->cam))
		return (-1);
	if (appl_tx_init(appl->tx, &appl->mlx_win) < 0)
		return (-1);
	return (0);
}

static void	appl_map_destroy(t_map *map)
{
	size_t	i;

	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
}

void	application_destory(t_application *appl)
{
	appl_mlx_destroy(&appl->mlx_win);
	appl_map_destroy(&appl->map);
}

void	appl_mlx_destroy(t_mlx	*mlx)
{
	(void)mlx;
}
