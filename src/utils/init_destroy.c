#include "cub3d.h"
#include "mlx.h"

#include <string.h>
#include <stdlib.h>

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
	memset(cam, 0, sizeof(t_camera));
	cam->plane_x = 0;
	cam->plane_y = 0.66;
	return (0);
}

static void	set_texture_colors(char *texture, int y, int x, int color)
{
	char	*offset;

	offset = texture + x + y;
	*(unsigned char *)texture = color;
}

static int	appl_texture_init(t_texture *t)
{
	size_t	x;
	size_t	y;

	memset(t, 0, sizeof(t_texture));
	x = -1;
	while (++x < TEXTURE_WIDTH)
	{
		y = -1;
		while (++y < TEXTURE_HEIGHT)
		{
			t->xorcolor = (x * 256 / TEXTURE_WIDTH) ^ (y * 256 / TEXTURE_HEIGHT);
			t->ycolor = y * 256 / TEXTURE_HEIGHT;
			t->xycolor = y * 128 / TEXTURE_HEIGHT + x * 128 / TEXTURE_WIDTH;

			set_texture_colors(t->texture_set[0], y, x, 65536 * 254 * (x != y && x != TEXTURE_WIDTH - y));//flat red texture with black cross
			set_texture_colors(t->texture_set[1], y, x, t->xycolor + 256 * t->xycolor + 65536 * t->xycolor); //sloped greyscale
			set_texture_colors(t->texture_set[2], y, x, 256 * t->xycolor + 65536 * t->xycolor); //sloped yellow gradien
			set_texture_colors(t->texture_set[3], y, x, t->xorcolor + 256 * t->xorcolor + 65536 * t->xorcolor); //t->xor greyscale;
			set_texture_colors(t->texture_set[4], y, x, 256 * t->xorcolor); //t->xor green;
			set_texture_colors(t->texture_set[5], y, x, 65536 * 192 * (x % 16 && y % 16)); //red bricks;
			set_texture_colors(t->texture_set[6], y, x, 65536 * t->ycolor); //red gradient;
			set_texture_colors(t->texture_set[7], y, x, 128 + 256 * 128 + 65536 * 128); //flat grey texture;
		}
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
	if (appl_player_init(&appl->player, &appl->map))
		return (-1);
	if (appl_cam_init(&appl->cam) < 0)
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
