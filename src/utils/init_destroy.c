#include "cub3d.h"
#include "mlx.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int	appl_mlx_init(t_mlx	*mlx)
{
	void	*raw_img;
	int		width;
	int		height;
	int		bit_per_pixel;
	int		size_line;
	int		endian;

	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3d");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bit_per_pixel, &mlx->line_length, &mlx->endian);

	raw_img = mlx_xpm_file_to_image(mlx->mlx, "./xpm_images/AnyConv.com__eagle.xpm", &width, &height);
	mlx->wall_face[0].img = mlx_get_data_addr(raw_img, &bit_per_pixel, &size_line, &endian);
	//mlx->wall_face[1].img = mlx_xpm_file_to_image(mlx->mlx, "./xpm_images/AnyConv.com__eagle.xpm", &mlx->wall_face[1].width, &mlx->wall_face[1].height);
	//mlx->wall_face[2].img = mlx_xpm_file_to_image(mlx->mlx, "./xpm_images/AnyConv.com__eagle.xpm", &mlx->wall_face[2].width, &mlx->wall_face[2].height);
	//mlx->wall_face[3].img = mlx_xpm_file_to_image(mlx->mlx, "./xpm_images/AnyConv.com__eagle.xpm", &mlx->wall_face[3].width, &mlx->wall_face[3].height);
	return (0);
}

/**
 * map struct initialization method
 * first we control the path,
 * then we read the data
 * @param appl struct with all the data
 * @param path file path string
 * @return -1 if error, 0 if it's correct
 */
int	appl_map_init(t_application *appl, char *path)
{
    if (check_path_format(path) < 0)
        return -1;
    appl->map.map = load_map(appl, path);
	if (!appl->map.map)
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

static int	appl_texture_init(t_texture *t)
{
	size_t	x;
	size_t	y;

	x = -1;
	while (++x < TEXTURE_WIDTH)
	{
		y = -1;
		while (++y < TEXTURE_HEIGHT)
		{
			t->xorcolor = (x * 256 / TEXTURE_WIDTH) ^ (y * 256 / TEXTURE_HEIGHT);
			t->ycolor = y * 256 / TEXTURE_HEIGHT;
			t->xycolor = y * 128 / TEXTURE_HEIGHT + x * 128 / TEXTURE_WIDTH;

			//set_texture_colors(t->texture_set[0], y, x, 65536 * 254 * (x != y && x != TEXTURE_WIDTH - y));//flat red texture with black cross
			//t->texture_set[0][TEXTURE_WIDTH * y + x] =  65536 * 254 * (x != y && x != TEXTURE_WIDTH - y);//flat red texture with black cross
			//set_texture_colors(t->texture_set[1], y, x, t->xycolor + 256 * t->xycolor + 65536 * t->xycolor); //sloped greyscale
			t->texture_set[1][TEXTURE_WIDTH * y + x] = t->xycolor + 256 * t->xycolor + 65536 * t->xycolor; //sloped greyscale
			//set_texture_colors(t->texture_set[2], y, x, 256 * t->xycolor + 65536 * t->xycolor); //sloped yellow gradien
			//set_texture_colors(t->texture_set[3], y, x, t->xorcolor + 256 * t->xorcolor + 65536 * t->xorcolor); //t->xor greyscale;
			//set_texture_colors(t->texture_set[4], y, x, 256 * t->xorcolor); //t->xor green;
			//set_texture_colors(t->texture_set[5], y, x, 65536 * 192 * (x % 16 && y % 16)); //red bricks;
			t->texture_set[0][TEXTURE_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks;
			//set_texture_colors(t->texture_set[6], y, x, 65536 * t->ycolor); //red gradient;
			//set_texture_colors(t->texture_set[7], y, x, 128 + 256 * 128 + 65536 * 128); //flat grey texture;
		}
	}
	return (0);
}

int	application_init(t_application *appl, char *path)
{
	memset(appl, 0, sizeof(t_application));
	if (appl_mlx_init(&appl->mlx_win) < 0)
		return (-1);
	if (appl_map_init(appl, path) < 0)
		return (-1);
	if (appl_cam_init(&appl->cam) < 0)
		return (-1);
	if (appl_player_init(&appl->player, &appl->map, &appl->cam))
		return (-1);
	if (appl_texture_init(&appl->texture) < 0)
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
