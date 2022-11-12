
#include "mlx.h"
#include "cub3d.h"

#include <string.h>
#include <math.h>
#include <stdio.h>

static void	clear_image(t_mlx *mlx)
{
	int	x;
	int	y;
	int	color[2];
	
	color[0] = get_rgb(0, 51, 153, 255);
	color[1] = get_rgb(0, 224, 224, 224);
	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			my_pixel_put(mlx, x, y, color[0]);
			my_pixel_put(mlx, x, y + HEIGHT / 2, color[1]);
		}
	}
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
	fprintf(stderr, "RAY_X: %lf\n", ray->dir_x);
	fprintf(stderr, "RAY_Y: %lf\n", ray->dir_x);
}

static int	get_tx_color(t_tx t[4], int tx_y, int tx_x, int tx_type)
{
	int	color[4];
	int	len;

	len = t[tx_type].line_length;

	color[0] = t[tx_type].img[tx_y * len + tx_x * 4 + 0];
	color[1] = t[tx_type].img[tx_y * len + tx_x * 4 + 1];
	color[2] = t[tx_type].img[tx_y * len + tx_x * 4 + 2];
	color[3] = t[tx_type].img[tx_y * len + tx_x * 4 + 3];
	return (get_rgb(color[3], color[2], color[1], color[0]));
}

static void	draw_wall_tx(t_ray *ray, t_map *map, t_mlx *mlx, int x, t_tx *t)
{
	int			tx_type;
	int			tx_x;
	double		tx_pos;
	int			tx_y;
	int			start;
	int			end;
	double		wall_x;
	double		step;
	int			final_color;


	tx_type = 0;//map->map[ray->map_x][ray->map_y] - 49;
	start = -map->wall_height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = map->wall_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;

	if (!ray->side)
		wall_x = ray->pos_y + map->perp_wall_dist * ray->dir_y;
	else
		wall_x = ray->pos_x + map->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);

	tx_x = (int)(wall_x * (double)t[tx_type].width);
	if (!ray->side && ray->dir_x > 0)
		tx_x = t[tx_type].width - tx_x - 1;
	if (ray->side && ray->dir_y < 0)
		tx_x = t[tx_type].width - tx_x - 1;

	step = 1.0 * t[tx_type].width / map->wall_height;
	tx_pos = (start - HEIGHT / 2 + map->wall_height / 2) * step;
	while (start != end)
	{
		tx_y = (int)tx_pos & (t[tx_type].width - 1);
		tx_pos += step;
		final_color = get_tx_color(t, tx_y, tx_x, tx_type);
		if (ray->side)
			final_color = (final_color >> 1) & 8355711;
		my_pixel_put(mlx, x, start++, final_color);
	}
}

static void	wall_hit_case(t_ray *ray, t_map *map, t_mlx *mlx, int x, t_tx *t)
{
	hit_wall_side(ray, map);

	if (!ray->side)
		map->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		map->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	map->wall_height = (int)HEIGHT / map->perp_wall_dist;

	draw_wall_tx(ray, map, mlx, x, t);
}

int	game_loop(t_application *appl)
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
		wall_hit_case(&appl->ray, &appl->map, &appl->mlx_win, x, appl->tx);
	}
	mlx_put_image_to_window(appl->mlx_win.mlx, appl->mlx_win.mlx_win, appl->mlx_win.img, 0, 0);
	return (1);
}
