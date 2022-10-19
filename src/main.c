#include <stdio.h>
#include <stdint.h>

#include "libft.h"
#include "get_next_line.h"
#include "cub3d.h"

#include "mlx.h"
#include "mlx_int.h"

/*
 MY PIXEL PUT

MLX_ADDR ES EL BUFFER DONDE SE GUARDA LA IMAGEN.
BIT_PER_PIXEL REPRESENTA RGB
LINE_LENGTH ES EL TAMANO DE Y EN BYTES
ENDIAN ?

EJEMPLO:
	CREAR UNA IMAGEN 1X1
		LINE_LENGTH = 4 (SIEMPRE SERA, NxN -> 4*N = LINE LENGTH)
		BIT_PER_PIXEL = (RGB, ES UNA CONSTANTE, 32)
		ENDIAN ?

	LLAMADA A FUNCION MY_PUT_PIXEL(X, Y, COLOR)
	PASO 1:
		Y_OFFSET: POSICION DE Y * LINE_LENGTH
		I.E
			Y = 0
			Y_OFFSET = 0Y * 4 = 0

			Y = 1
			Y_OFFSET = 1Y * 4 = 4

			Y_OFFSET = NY * 4 = N*4Y

	PASO 2:
		X_OFFSET: POSICION DE X * BIT_PER_PIXEL / 8
		I.E
			X = 0
			X_OFFSET = 0X * 32 / 8 = 0
			
			X = 1
			X_OFFSET = 1X * 32 / 8 = 4

	PASO 3 -> PASO 1 Y PASO 2 SENTIDO
			QUIERO PINTAR EN LA POSICION 0 DE MI IMAGEN UN PIXEL ROJO.
			SE CALCULA EL OFFSET, QUE ES 0.
			PASO COMO ARGUMENTO LA REPRESENTACION HEXADECIMAL DEL COLOR 0XFF0000
			DESPLAZO EL PUNTERO DE LA DIRECCION DE LA IMAGEN EN MEMORIA.
				addr_offset = img_addr + offset(PASO 1 + PASO 2)
				*(uint *)addr_offset = color

	REPRESENTACION BINARIA DE LA IMAGEN
		  BYTE 1    BYTE 2   BYTE 3    BYTE 4
		0000 0000 0000 0000 0000 0000 0000 0000

		0xFF0000 = 1111 1111 0000 0000 0000

		GUARDAR COLOR EN OFFSET

		  BYTE 1    BYTE 2   BYTE 3    BYTE 4
		1111 1111 0000 0000 0000 0000 0000 0000
 */

static void	my_pixel_put(t_mlx_tools* mlx_tools, int x, int y, int color)
{
	char	*pix_position;
	int		y_coord_offset;
	int		x_coord_offset;

	y_coord_offset = y * mlx_tools->line_length;
	x_coord_offset = x * (mlx_tools->bit_per_pixel / BYTE);
	pix_position = mlx_tools->mlx_addr + y_coord_offset + x_coord_offset;
	*(unsigned int*)pix_position = color;
}

static void	init_mlx_tools(t_mlx_tools *mlx_tools)
{
	mlx_tools->mlx = mlx_init();
	mlx_tools->mlx_win = mlx_new_window(mlx_tools->mlx, 500, 500, "Cub3d");
	mlx_tools->mlx_img = mlx_new_image(mlx_tools->mlx, 500, 500);
	mlx_tools->mlx_addr = mlx_get_data_addr(mlx_tools->mlx_img, &mlx_tools->bit_per_pixel, &mlx_tools->line_length, &mlx_tools->endian);
}

static int	get_rgb(int t, int red, int green, int blue)
{
	return (t << 24 | red << 16 | green << 8 | blue);
}

#define GET_SIZE 1
#define FILL_MAP 2

int	load_map(void *var, char *map_path, int flag)
{
	int		fd;
	size_t	map_size;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (1);
	map_size = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (flag == GET_SIZE)
			(*(size_t *)var)++;
		else if (flag == FILL_MAP)
		{
			(*(char **)var) = line;
			(*(char **)var);
		}
	}
	close(fd);
	return (0);
}

static void	show_map(char **map)
{
	while (*map)
		printf("%s\n", *map++);
}

int main(int argc, char **argv)
{
	char	**map;
	size_t	map_sz;

	if (argc != 2)
		return (1);
	map_sz = 0;
	load_map(&map_sz, argv[1], GET_SIZE);
	map = ft_calloc(map_sz + 1, sizeof(char **));
	load_map(map, argv[1], FILL_MAP);
	show_map(map);
	return (0);
	t_mlx_tools	mlx_tools;
	int			x;
	int			y;

	ft_bzero(&mlx_tools, sizeof(mlx_tools));

	init_mlx_tools(&mlx_tools);

	y = 124;
	while (++y < 375)
	{
		x = 124;
		while (++x < 375)
			my_pixel_put(&mlx_tools, y, x, get_rgb(255, 255, 0, 0));
	}
	printf("BIT PER PIXEL: %d\n", mlx_tools.bit_per_pixel);
	printf("LINE LENGTH: %d\n", mlx_tools.line_length);
	printf("ENDIAN %d\n", mlx_tools.endian);
	
	mlx_put_image_to_window(mlx_tools.mlx, mlx_tools.mlx_win, mlx_tools.mlx_img, 0, 0);


	mlx_loop(mlx_tools.mlx);
	return (0);
}
