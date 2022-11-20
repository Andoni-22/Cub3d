#include "cub3d.h"
#include "mlx.h"

static int	appl_mlx_init(t_mlx	*mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (-1);
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3d");
	if (!mlx->mlx_win)
		return (-1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		return (-1);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bit_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->img_addr)
		return (-1);
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
static int	appl_map_init(t_application *appl, char *path)
{
    if (check_path_format(path, FILE_FORMAT_CUB) < 0)
        return (-1);
    appl->map.map = load_map(appl, path);
	if (!appl->map.map)
		return (-1);
	return (0);
}

int	application_init(t_application *appl, char *path)
{
	ft_memset(appl, 0, sizeof(t_application));
	if (appl_mlx_init(&appl->mlx_win) < 0)
		return (-1);
	if (appl_map_init(appl, path) < 0)
		return (-1);
    locate_player(&appl->player, &appl->map, &appl->cam);
	return (0);
}

