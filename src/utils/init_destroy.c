#include "cub3d.h"

int	application_init(application_t *appl)
{
	appl = malloc(sizeof(application_t));
	if (!appl)
		return (-1);
	appl->mlx_win = malloc(sizeof(mlx_t));
	if (!appl->mlx_win)
		return (-1);
	if (appl_mlx_init(appl->mlx_win) < 0)
		return (-1);
	return (0);
}

void	application_destory(application_t *appl)
{
	appl_mlx_destroy(appl->mlx_win);
	if (appl)
		free(appl);
}

int	appl_mlx_init(mlx_t	*mlx)
{
	mlx->mlx = mlx_init();
	mlx->mlx_window = NULL;
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