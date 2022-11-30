/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:26:48 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/30 19:26:59 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*find_player(char *line, const char *set)
{
	char	*player;

	while (*line)
	{
		player = ft_strchr(set, *line);
		if (player)
			return (line);
		line++;
	}
	return (NULL);
}

static void	vertical_player_pos(t_player *player, t_camera *cam, int dir)
{
	if (dir == 'N')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = -0.66;
	}
}

static void	horizontal_player_pos(t_player *player, t_camera *cam, int dir)
{
	if (dir == 'E')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		cam->plane_x = 0.66;
		cam->plane_y = 0;
	}
	else if (dir == 'W')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		cam->plane_x = -0.66;
		cam->plane_y = 0;
	}
}

static void	set_player_pos(t_player *player, t_camera *cam, int dir)
{
	horizontal_player_pos(player, cam, dir);
	vertical_player_pos(player, cam, dir);
}

void	locate_player(t_player *player, t_camera *cam, char *line)
{
	char	*player_pos;

	player_pos = find_player(line, "NSEW");
	if (player_pos && player->exist)
		player->exist = -1;
	if (player->exist)
		return ;
	if (player_pos)
	{
		player->pos_y = player_pos - line;
		set_player_pos(player, cam, *player_pos);
		*player_pos = FLOOR;
		player->exist++;
		player->pos_y += 0.1;
		player->pos_x += 0.1;
	}
	player->pos_x++;
}
