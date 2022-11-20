#include "cub3d.h"
#include "mlx.h"

//DEPRECATED//
/*static int	appl_tx_init(t_tx t[4], t_mlx *mlx)
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
}*/

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

static int	appl_player_init(t_player *player, t_map *map, t_camera *cam)
{
	locate_player(player, map, cam);
	return (0);
}

int	application_init(t_application *appl, char *path)
{
	ft_memset(appl, 0, sizeof(t_application));
	if (appl_mlx_init(&appl->mlx_win) < 0)
		return (-1);
	if (appl_map_init(appl, path) < 0)
		return (-1);
	if (appl_player_init(&appl->player, &appl->map, &appl->cam))
		return (-1);
	//if (appl_tx_init(appl->tx, &appl->mlx_win) < 0)
	//	return (-1);
	return (0);
}

