#include "cub3d.h"
#include "hooks.h"

#include <math.h>

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

static int	key_hook(int keycode, t_application *appl)
{
	fprintf(stderr, "KEYCODE: %d\n", keycode);
	if (keycode == UP)
	{
		appl->player.pos_y += appl->player.dir_y;
		appl->player.pos_x += appl->player.dir_x;
	}
	else if (keycode == DOWN)
	{
		appl->player.pos_y -= appl->player.dir_y;
		appl->player.pos_x -= appl->player.dir_x;
	}
	/*else if (keycode == LEFT)
	{
		//appl->player.pos_x += 0.1f;
		//both camera direction and camera plane must be rotated
		double oldDirX = appl->player.dir_x;
		appl->player.dir_x = appl->player.dir_x * cos(-1) - appl->player.dir_y * sin(-1);
		appl->player.dir_y = oldDirX * sin(-1) + appl->player.dir_y * cos(-1);
		double oldPlaneX = appl->cam.plane_x;
		appl->cam.plane_x = appl->cam.plane_x * cos(-1) - appl->cam.plane_y * sin(-1);
		appl->cam.plane_y = oldPlaneX * sin(-1) + appl->cam.plane_y * cos(-1);
    }
    //rotate to the left
	else if (keycode == RIGHT)
	{	
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(1);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(1);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(1);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(1);
    }*/

	game_loop(appl);
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
	mlx_key_hook(mlx_win->mlx_win, key_hook, &appl);
	mlx_loop(mlx_win->mlx);
	application_destory(&appl);
	return (0);
}
