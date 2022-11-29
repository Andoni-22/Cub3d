/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:19:22 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/11/29 20:21:23 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

char	**free_str_array(char **tmp)
{
	int	i;

	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
	return (NULL);
}

int	str_array_get_size(char **src)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	**str_array_copy(char **src)
{
	char	**tmp;
	int		size;
	int		i;

	size = str_array_get_size(src);
	if (size == 0)
		return (NULL);
	tmp = ft_calloc(sizeof(char *), size + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		tmp[i] = ft_strdup(src[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}
