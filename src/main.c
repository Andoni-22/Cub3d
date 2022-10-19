#include "cub3d.h"

int main(int argc, char **argv)
{
	application_t	*appl;
	mlx_t			*mlx_win;

	if (application_init(appl) < 0)
		return (-1);
	mlx_win = appl->mlx_win;
	mlx_win->mlx_window = mlx_new_window(mlx_win->mlx, mlx_win->size_x, mlx_win->size_y, "Cub3d");
	(void)argc;
	(void)argv;
	mlx_loop(mlx_win->mlx);
	application_destory(appl);
	return (0);
}
