#include "cub3d.h"

static void	game_loop(t_player *p, t_map *m, t_camera *cam)
{
	t_ray	ray;
	int		x;
	double	perp_wall_dist;

	x = -1;
	memset(&ray, 0, sizeof(t_ray));
	ray.pos_x = p->pos_x;
	ray.pos_y = p->pos_y;
	while (++x <= WIDTH)
	{
		cam->coord_x = 2 * x / (double)WIDTH - 1;
		ray.dir_x = p->dir_x + cam->plane_x  * cam->coord_x;
		ray.dir_y = p->dir_y + cam->plane_y  * cam->coord_x;
		ray.sq_pos_x = (int)ray.pos_x;
		ray.sq_pos_y = (int)ray.pos_y;
		if (!ray.dir_x)
			ray.delta_dist_x = 1e30;
		else
			ray.delta_dist_x = abs(1 / ray.dir_x);
		if (!ray.dir_y)
			ray.delta_dist_y = 1e30;
		else
			ray.delta_dist_y = abs(1 / ray.dir_y);

		if (ray.dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (ray.pos_x - ray.sq_pos_x) * ray.delta_dist_x;
		}

		//printf("\nRAY_DIR_X = PLAYER_DIR_X %lf + PLANE_X %lf * CAM_X %lf => %lf\n", p->dir_x, cam->plane_x, cam->coord_x, ray.dir_x);
		//printf("RAY_DIR_Y = PLAYER_DIR_Y %lf + PLANE_Y %lf * CAM_X %lf => %lf\n", p->dir_y, cam->plane_y, cam->coord_x, ray.dir_y);
	}
}

void	game(t_player *p, t_map *m)
{
	t_camera	cam;

	memset(&cam, 0, sizeof(t_camera));
	cam.plane_x = 0;
	cam.plane_x = 0.66;

	game_loop(p, m, &cam);
}
