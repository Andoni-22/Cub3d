#include "cub3d.h"
#include <math.h>

static void	clear_image(t_mlx *mlx)
{
	memset(mlx->img_addr, 0, WIDTH * HEIGHT * 4);
}

static void	ray_coord(t_ray *ray, t_player *pl, t_camera *cam)
{
	ray->dir_x = pl->dir_x + cam->plane_x  * cam->coord_x;
	ray->dir_y = pl->dir_y + cam->plane_y  * cam->coord_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
}

static void	ray_next_square_dist(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

static void	ray_delta(t_ray *ray)
{
	if (!ray->dir_x)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (!ray->dir_y)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

static void	set_ray(t_ray *ray, t_player *pl, t_camera *cam)
{
	ray_coord(ray, pl, cam);
	ray_delta(ray);
	ray_next_square_dist(ray);
}

static void	hit_wall_side(t_ray *ray, t_map *map)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map->map[ray->map_x][ray->map_y] != FLOOR)
			break ;
	}
}

static void	draw_wall(t_ray *ray, t_map *map, t_mlx *mlx, int x)
{
	int	start;
	int	end;
	int	rgb;

	start = -map->wall_height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = map->wall_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	if (map->map[ray->map_x][ray->map_y] == '1')
		rgb = 0xff0000;
	else if (map->map[ray->map_x][ray->map_y] == '2')
		rgb = 0x00ff00;
	else if (map->map[ray->map_x][ray->map_y] == '3')
		rgb = 0xffffff;
	else if (map->map[ray->map_x][ray->map_y] == '4')
		rgb = 0x0000ff;
	if (ray->side)
		rgb /= 2;
	while (start != end)
		my_pixel_put(mlx, x, start++, rgb);
}

static int	wall_hit_case(t_ray *ray, t_map *map, t_mlx *mlx, int x)
{
	hit_wall_side(ray, map);

	if (!ray->side)
		map->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		map->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	map->wall_height = (int)HEIGHT / map->perp_wall_dist;

	draw_wall(ray, map, mlx, x);
}

void	game_loop(t_application *appl)//t_player *p, t_map *m, t_camera *cam, t_mlx *mlx)
{
	int		x;

	clear_image(&appl->mlx_win);
	x = -1;
	appl->ray.pos_x = appl->player.pos_x;
	appl->ray.pos_y = appl->player.pos_y;
	while (++x <= WIDTH)
	{
		appl->cam.coord_x = 2 * x / (double)WIDTH - 1;
		set_ray(&appl->ray, &appl->player, &appl->cam);
		wall_hit_case(&appl->ray, &appl->map, &appl->mlx_win, x);
	}
	mlx_put_image_to_window(appl->mlx_win.mlx, appl->mlx_win.mlx_win, appl->mlx_win.img, 0, 0);
}
