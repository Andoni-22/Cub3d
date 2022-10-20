#include "cub3d.h"

static void	my_pixel_put(mlx_t* mlx, int x, int y, int color)
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
	while (*map)
		printf("%s", *map++);
}

int main(int argc, char **argv)
{
	application_t	appl;
	mlx_t			mlx_win;
	t_map			map;

	if (argc != 2 || application_init(&appl) < 0)
		return (-1);
	mlx_win = appl.mlx_win;
	map = appl.map;
	map.map_sz = get_map_size(open(argv[1], O_RDONLY));
	if (map.map_sz == -1)
		return (-1);
	map.map = load_map(map.map_sz, open(argv[1], O_RDONLY));
	show_map(map.map);

	mlx_loop(mlx_win.mlx);
	//application_destory(&appl);
	return (0);
}
