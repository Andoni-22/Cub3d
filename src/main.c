#include "cub3d.h"

#include <math.h>

void	my_pixel_put(t_mlx* mlx, int x, int y, int color)
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
	game(player, map, mlx_win);
	mlx_put_image_to_window(mlx_win->mlx, mlx_win->mlx_win, mlx_win->img, 0, 0);
	//show_map(map.map);
	mlx_loop(mlx_win->mlx);
	application_destory(&appl);
	return (0);
}
