/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:18:24 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/11/29 20:18:27 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "stdio.h"

void	show_map(char **map)
{
	while (*map)
		printf("%s", *map++);
}

void	erase_nl(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			*line = 0;
		line++;
	}
}
