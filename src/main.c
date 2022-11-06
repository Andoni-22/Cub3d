#include "cub3d.h"
#include "hooks.h"
#include "mlx.h"

#include <math.h>
#include <stdio.h>

void	my_pixel_put(t_mlx* mlx, int x, int y, int color)
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
	char	buffer[100];

	//logger("SHOW MAP\n");
	sprintf(buffer, "MAP ADDR: %p\n", map);
	//logger(buffer);
	printf(buffer, "MAP INNER ADDR: %p\n", *map);
	//logger(buffer);
	while (*map)
		printf("%s", *map++);
}

static int	colission(t_map *map, t_ray *ray, t_player *pl, int sign)
{
	int	ret_val;

	if (sign == 1)
		ret_val = map->map[(int)(pl->pos_x + pl->dir_x)][(int)(pl->pos_y + pl->dir_y)] - 48;
	else
		ret_val = map->map[(int)(pl->pos_x - pl->dir_x)][(int)(pl->pos_y - pl->dir_y)] - 48;
	return (!ret_val);
}

static int	key_hook(int keycode, t_application *appl)
{
	int	ret_val;

	//fprintf(stderr, "KEYCODE: %d\n", keycode);
	//fprintf(stderr, "X: %lf\n", appl->player.pos_x);
	//fprintf(stderr, "Y: %lf\n", appl->player.pos_y);
	//fprintf(stderr, "RETVAL: %d\n", ret_val);
	if (keycode == UP)
	{
		ret_val = colission(&appl->map, &appl->ray, &appl->player, PLUS);
		appl->player.pos_y += appl->player.dir_y * ret_val / MOVEMENT_K;
		appl->player.pos_x += appl->player.dir_x * ret_val / MOVEMENT_K;
	}
	if (keycode == DOWN)
	{
		ret_val = colission(&appl->map, &appl->ray, &appl->player, MINUS);
		appl->player.pos_y -= appl->player.dir_y * ret_val / MOVEMENT_K;
		appl->player.pos_x -= appl->player.dir_x * ret_val / MOVEMENT_K;
	}
	if (keycode == RIGHT)
	{
		double oldDirX = appl->player.dir_x;
		appl->player.dir_x = appl->player.dir_x * cos(-ROTATE) - appl->player.dir_y * sin(-ROTATE);
		appl->player.dir_y = oldDirX * sin(-ROTATE) + appl->player.dir_y * cos(-ROTATE);
		double oldPlaneX = appl->cam.plane_x;
		appl->cam.plane_x = appl->cam.plane_x * cos(-ROTATE) - appl->cam.plane_y * sin(-ROTATE);
		appl->cam.plane_y = oldPlaneX * sin(-ROTATE) + appl->cam.plane_y * cos(-ROTATE);
    }
	if (keycode == LEFT)
	{	
		double oldDirX = appl->player.dir_x;
		appl->player.dir_x = appl->player.dir_x * cos(ROTATE) - appl->player.dir_y * sin(ROTATE);
		appl->player.dir_y = oldDirX * sin(ROTATE) + appl->player.dir_y * cos(ROTATE);
		double oldPlaneX = appl->cam.plane_x;
		appl->cam.plane_x = appl->cam.plane_x * cos(ROTATE) - appl->cam.plane_y * sin(ROTATE);
		appl->cam.plane_y = oldPlaneX * sin(ROTATE) + appl->cam.plane_y * cos(ROTATE);
    }
	game_loop(appl);
	return (1);
}

static int	release_hook(int keycode, t_application *appl)
{
	fprintf(stderr, "KEYCODE: %d\n", keycode);
	return (1);
}

int main(int argc, char **argv)
{
	t_application	appl;
	t_mlx			*mlx_win;
	t_map			*map;
	t_player		*player;

	if (argc != 2 || application_init(&appl, argv[1]) < 0)
		return (-1);
	mlx_win = &appl.mlx_win;
	map = &appl.map;
	player = &appl.player;
	if (!map->map)
		return (-1);
	game_loop(&appl);
	//mlx_key_hook(mlx_win->mlx_win, key_hook, &appl);
	mlx_hook(mlx_win->mlx_win, 2, 1L << 0, key_hook, &appl);
	mlx_hook(mlx_win->mlx_win, 3, 1L << 1, release_hook, &appl);
	mlx_loop(mlx_win->mlx);
	application_destory(&appl);
	return (0);
}
