#include <math.h>
#include "cub3d.h"

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
		set_pixel_color(mlx, mlx->x, wall.start++, wall.color);
	}
}

void	wall_hit_case(t_ray *ray, t_map *map, t_mlx *mlx, t_tx *t)
{
	hit_wall_side(ray, map);
	if (!ray->side)
		map->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		map->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	map->wall_height = (int)HEIGHT / map->perp_wall_dist;
	draw_wall_tx(ray, map, mlx, t);
}
