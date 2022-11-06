#include "cub3d.h"

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
	if (!map->map == -1)
		return (-1);
	return (0);
}

static void	locate_player(t_player *player, t_map *map)
{
	char	*player_pos;
	size_t	i;

	i = -1;
	while (map->map[++i])
	{
		player_pos = ft_strchr(map->map[i], PLAYER);
		if (player_pos)
		{
			player->pos_y = player_pos - map->map[i];
			*player_pos = FLOOR;
			break ;
		}
		player->pos_x++;
	}
	player->pos_y += 0.1;
	player->pos_x += 0.1;
}

static int	appl_player_init(t_player *player, t_map *map)
{
	memset(player, 0, sizeof(t_player));
	player->dir_x = -1;
	player->dir_y = 0;
	locate_player(player, map);
	return (0);
}

static int	appl_cam_init(t_camera *cam)
{
	memset(cam, 0, sizeof(cam));
	cam->plane_x = 0;
	cam->plane_y = 0.66;
	return (0);
}

int	application_init(t_application *appl, char *path)
{
	memset(appl, 0, sizeof(t_application));
	if (appl_mlx_init(&appl->mlx_win) < 0)
		return (-1);
	if (appl_map_init(&appl->map, path) < 0)
		return (-1);
	if (appl_player_init(&appl->player, &appl->map))
		return (-1);
	if (appl_cam_init(&appl->cam) < 0)
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
