#include "cub3d.h"
#include <math.h>

static void	game_loop(t_player *p, t_map *m, t_camera *cam, t_mlx *mlx)
{
	t_ray	ray;
	int		x;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		rgb;
	double	perp_wall_dist;
	FILE	*file;

	memset(&ray, 0, sizeof(t_ray));
	x = -1;
	ray.pos_x = p->pos_x;
	ray.pos_y = p->pos_y;
	for (int i = 0; i <= HEIGHT; i++)
	{
		for (int j = 0; j <= HEIGHT; j++)
			my_pixel_put(mlx, i, j, 0x000000);
	}
	while (++x <= WIDTH)
	{
		cam->coord_x = 2 * x / (double)WIDTH - 1;
		ray.dir_x = p->dir_x + cam->plane_x  * cam->coord_x;
		ray.dir_y = p->dir_y + cam->plane_y  * cam->coord_x;
		ray.map_x = (int)ray.pos_x;
		ray.map_y = (int)ray.pos_y;
		if (!ray.dir_x)
			ray.delta_dist_x = 1e30;
		else
			ray.delta_dist_x = fabs(1 / ray.dir_x);
		if (!ray.dir_y)
			ray.delta_dist_y = 1e30;
		else
			ray.delta_dist_y = fabs(1 / ray.dir_y);

		if (ray.dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (ray.pos_x - ray.map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - ray.pos_x) * ray.delta_dist_x;
		}
		if (ray.dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (ray.pos_y - ray.map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1.0 - ray.pos_y) * ray.delta_dist_y;
		}
		while (!ray.hit)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				ray.side = 1;
			}
			if (m->map[ray.map_x][ray.map_y] != FLOOR)
				ray.hit = 1;
		}
		if (!ray.side)
			perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
		else
			perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;
		wall_height = (int)HEIGHT / perp_wall_dist;
		draw_start = -wall_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = wall_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		if (m->map[ray.map_x][ray.map_y] == '1')
			rgb = 0xff0000;
		else if (m->map[ray.map_x][ray.map_y] == '2')
			rgb = 0x00ff00;
		else if (m->map[ray.map_x][ray.map_y] == '3')
			rgb = 0xffffff;
		else if (m->map[ray.map_x][ray.map_y] == '4')
			rgb = 0x0000ff;
		if (ray.side)
			rgb /= 2;
		while (draw_start != draw_end)
			my_pixel_put(mlx, x, draw_start++, rgb);
		ray.hit = 0;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
}

void	game(t_player *p, t_map *m, t_mlx *mlx)
{
	t_camera	cam;

	memset(&cam, 0, sizeof(t_camera));
	cam.plane_x = 0;
	cam.plane_y = 0.66;
	game_loop(p, m, &cam, mlx);
}
