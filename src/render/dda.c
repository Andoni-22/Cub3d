#include "cub3d.h"
#include "mlx.h"
#include "cub3d.h"

#include <string.h>
#include <math.h>
#include <stdio.h>

static void	my_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*pix_position;
	int		y_coord_offset;
	int		x_coord_offset;

	y_coord_offset = y * mlx->line_length;
	x_coord_offset = x * (mlx->bit_per_pixel / BYTE);
	pix_position = mlx->img_addr + y_coord_offset + x_coord_offset;
	*(unsigned int *)pix_position = color;
}

static int	get_rgb(int t, int red, int green, int blue)
{
	return (t << 24 | red << 16 | green << 8 | blue);
}

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
	ray->dir_x = pl->dir_x + cam->plane_x * cam->coord_x;
	ray->dir_y = pl->dir_y + cam->plane_y * cam->coord_x;
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

static int	set_tx(t_ray *ray)
{
	int	tx_type;

	if (ray->dir_x >= 0)
	{
		tx_type = 3;
		if (ray->side && ray->dir_y >= 0)
			tx_type = 2;
		else if (ray->side && ray->dir_y < 0)
			tx_type = 1;
	}
	else
	{
		tx_type = 0;
		if (ray->side && ray->dir_y >= 0)
			tx_type = 2;
		else if (ray->side && ray->dir_y < 0)
			tx_type = 1;
	}
	return (tx_type);
}

static void	wall_start_end(t_wall_info *wall, t_ray *ray, t_map *map)
{
	wall->start = -map->wall_height / 2 + HEIGHT / 2;
	if (wall->start < 0)
		wall->start = 0;
	wall->end = map->wall_height / 2 + HEIGHT / 2;
	if (wall->end >= HEIGHT)
		wall->end = HEIGHT - 1;
	if (!ray->side)
		wall->x_pos = ray->pos_y + map->perp_wall_dist * ray->dir_y;
	else
		wall->x_pos = ray->pos_x + map->perp_wall_dist * ray->dir_x;
	wall->x_pos -= floor(wall->x_pos);
}

static void	draw_wall_tx(t_ray *ray, t_map *map, t_mlx *mlx, t_tx *t)
{
	t_wall_info	wall;

	wall.type = set_tx(ray);
	wall_start_end(&wall, ray, map);
	wall.x = (int)(wall.x_pos * (double)t[wall.type].width);
	if (!ray->side && ray->dir_x > 0)
		wall.x = t[wall.type].width - wall.x - 1;
	if (ray->side && ray->dir_y < 0)
		wall.x = t[wall.type].width - wall.x - 1;
	wall.step = 1.0 * t[wall.type].width / map->wall_height;
	wall.pos = (wall.start - HEIGHT / 2 + map->wall_height / 2) * wall.step;
	while (wall.start != wall.end)
	{
		wall.y = (int)wall.pos & (t[wall.type].width - 1);
		wall.pos += wall.step;
		wall.color = get_tx_color(t, wall.y, wall.x, wall.type);
		wall.color = (wall.color >> 1) & 8355711;
		my_pixel_put(mlx, mlx->x, wall.start++, wall.color);
	}
}

static void	wall_hit_case(t_ray *ray, t_map *map, t_mlx *mlx, t_tx *t)
{
	hit_wall_side(ray, map);
	if (!ray->side)
		map->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		map->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	map->wall_height = (int)HEIGHT / map->perp_wall_dist;
	draw_wall_tx(ray, map, mlx, t);
}

int	game_loop(t_application *a)
{
	clear_image(&a->mlx_win);
	a->mlx_win.x = -1;
	a->ray.pos_x = a->player.pos_x;
	a->ray.pos_y = a->player.pos_y;
	while (++a->mlx_win.x <= WIDTH)
	{
		a->cam.coord_x = 2 * a->mlx_win.x / (double)WIDTH - 1;
		set_ray(&a->ray, &a->player, &a->cam);
		wall_hit_case(&a->ray, &a->map, &a->mlx_win, a->tx);
	}
	mlx_put_image_to_window(a->mlx_win.mlx, a->mlx_win.mlx_win,
		a->mlx_win.img, 0, 0);
	return (1);
}
