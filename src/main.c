#include "cub3d.h"

#include <math.h>

static void	my_pixel_put(t_mlx* mlx, int x, int y, int color)
{
	char	*pix_position;
	int		y_coord_offset;
	int		x_coord_offset;

	y_coord_offset = y * mlx->line_length;
	x_coord_offset = x * (mlx->bit_per_pixel / BYTE);
	pix_position = mlx->img_addr + y_coord_offset + x_coord_offset;
	*(unsigned int*)pix_position = color;
}

static int	get_rgb(int t, int red, int green, int blue)
{
	return (t << 24 | red << 16 | green << 8 | blue);
}

static void	show_map(char **map)
{
	char	buffer[100];

	logger("SHOW MAP\n");
	sprintf(buffer, "MAP ADDR: %p\n", map);
	logger(buffer);
	printf(buffer, "MAP INNER ADDR: %p\n", *map);
	logger(buffer);
	while (*map)
		printf("%s", *map++);
}

void	game(t_player *player, t_map *map)
{
	size_t	x;
	double	camera_x;
	double	ray_dir_y;
	double	ray_dir_x;
	double	delta_dist_x;
	double	delta_dist_y;
	char	buffer[100];
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;

	int		hit = 0;

	x = -1;
	while (++x <= WIDTH)
	{
		sprintf(buffer, "X_POS: %ld\n", x);
		logger(buffer);
		camera_x = 2 * x / (double)WIDTH - 1;
		ray_dir_y = player->dir_y + player->plane_y + camera_x;
		ray_dir_x = player->dir_x + player->plane_x + camera_x;
		delta_dist_x = abs(1 / ray_dir_x);
		delta_dist_y = abs(1 / ray_dir_y);

		sprintf(buffer, "CAMERA_X: %lf\n", camera_x);
		logger(buffer);

		sprintf(buffer, "RAY_COORD_Y: %lf\n", ray_dir_y);
		logger(buffer);
		sprintf(buffer, "RAY_COORD_X: %lf\n", ray_dir_x);
		logger(buffer);

		if (!ray_dir_x)
			delta_dist_x = 1e30;
		if (!ray_dir_y)
			delta_dist_y = 1e30;

		sprintf(buffer, "DELTA_DIST_X: %lf\n", delta_dist_x);
		logger(buffer);
		sprintf(buffer, "DELTA_DIST_Y: %lf\n", delta_dist_y);
		logger(buffer);

		map_x = player->pos_x;
		map_y = player->pos_y;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (player->pos_x + 1.0 - map_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (player->pos_y + 1.0 - map_y) * delta_dist_y;
		}
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 0;
			}
		}
	}
}

int main(int argc, char **argv)
{
	t_application	appl;
	t_mlx			*mlx_win;
	t_map			*map;
	t_player		*player;

	logger("INIT MAIN\n");
	if (argc != 2 || application_init(&appl, argv[1]) < 0)
		return (-1);
	mlx_win = &appl.mlx_win;
	map = &appl.map;
	player = &appl.player;
	if (!map->map)
		return (-1);
	game(player, map);
	//show_map(map.map);
	//mlx_loop(mlx_win.mlx);
	application_destory(&appl);
	return (0);
}
