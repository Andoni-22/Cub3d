#include "cub3d.h"

int	application_init(application_t *appl)
{
	memset(appl, 0, sizeof(application_t));
	if (appl_mlx_init(&appl->mlx_win) < 0)
		return (-1);
	return (0);
}

void	application_destory(application_t *appl)
{
	appl_mlx_destroy(&appl->mlx_win);
	if (appl)
		free(appl);
}

int	appl_mlx_init(mlx_t	*mlx)
{
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 500, 500, "Cub3d");
	mlx->img = mlx_new_image(mlx->mlx, 500, 500);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bit_per_pixel, &mlx->line_length, &mlx->endian);

	mlx->size_x = 500;
	mlx->size_y = 500;
	return (0);
}

void	appl_mlx_destroy(mlx_t	*mlx)
{
	if (mlx)
		free(mlx);
	mlx->size_x = 0;
	mlx->size_y = 0;
}
