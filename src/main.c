#include <stdio.h>

#include "libft.h"

#include "mlx.h"
#include "mlx_int.h"

int main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_window;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 500, 500, "Cub3d");
	(void)argc;
	(void)argv;
	mlx_loop(mlx);
	return (0);
}
