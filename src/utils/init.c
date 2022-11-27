#include "cub3d.h"
#include "mlx.h"
#include "custom_errors.h"

static int appl_mlx_init(t_mlx *mlx, t_custom_error *c_error)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (set_error(c_error, 50, MLX_DEFAULT_ERROR));
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3d");
	if (!mlx->mlx_win)
		return (set_error(c_error, 50, MLX_DEFAULT_ERROR));
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		return (set_error(c_error, 50, MLX_DEFAULT_ERROR));
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bit_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->img_addr)
		return (set_error(c_error, 50, MLX_DEFAULT_ERROR));
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
static int appl_map_init(t_application *appl, char *path, t_custom_error *c_error)
{
    if (check_path_format(path, FILE_FORMAT_CUB, NULL) < 0)
        return (-1);
    appl->map.map = load_map(appl, path, NULL);
	if (!appl->map.map)
		return (-1);
	return (0);
}

int application_init(t_application *appl, char *path, t_custom_error *c_error)
{
	ft_memset(appl, 0, sizeof(t_application));
	if (appl_mlx_init(&appl->mlx_win, c_error) < 0)
		return (-1);
	if (appl_map_init(appl, path, c_error) < 0)
		return (-1);
	if (!appl->player.exist)
		return (-1);
	return (0);
}

