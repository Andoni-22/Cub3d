/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:20:07 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/11/29 20:33:23 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void	valid_map_loop(char chr, int *one_find, int *cont, int *dir_cont)
{
	if (chr == '1')
		(*one_find)++;
	if (chr == '1' || chr == '0' || chr == ' ')
		(*cont)++;
	else if (is_player_position(chr) == 0)
	{
		(*dir_cont)++;
		(*cont)++;
	}
}

int	is_valid_map_line(char *line)
{
	int	i;
	int	cont;
	int	one_find;
	int	dir_cont;

	i = -1;
	cont = 0;
	dir_cont = 0;
	one_find = 0;
	while (line[++i])
		valid_map_loop(line[i], &one_find, &cont, &dir_cont);
	if (cont != (i))
		return (-1);
	if (dir_cont > 1)
		return (-1);
	if (one_find == 0)
		return (-1);
	return (0);
}
