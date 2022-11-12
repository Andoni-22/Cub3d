
#include "cub3d.h"
#include "stdio.h"

void	my_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    char	*pix_position;
    int		y_coord_offset;
    int		x_coord_offset;

    //fprintf(stderr, "X: %d\n", x);
    //fprintf(stderr, "Y: %d\n", y);
    y_coord_offset = y * mlx->line_length;
    x_coord_offset = x * (mlx->bit_per_pixel / BYTE);
    pix_position = mlx->img_addr + y_coord_offset + x_coord_offset;
    *(unsigned int *)pix_position = color;
}

int	get_rgb(int t, int red, int green, int blue)
{
    return (t << 24 | red << 16 | green << 8 | blue);
}

void	show_map(char **map)
{
    while (*map)
        printf("%s", *map++);
}
