/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:19:15 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/11/29 20:21:24 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "custom_errors.h"
#include <stdlib.h>

char	*chr_cut_back(char *str, char c)
{
	int		size;
	int		i;
	char	*new_str;

	size = ft_strlen(str);
	if (str[size - 1] != c)
		return (NULL);
	new_str = (char *) malloc(sizeof(char) * (size));
	i = 0;
	while (i != size - 1)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	**set_error_chr(t_custom_error *c_err, int code, char *str)
{
	set_error(c_err, code, str);
	return (NULL);
}

char 	**set_error_and_free_chr(t_custom_error *c_error, int code, char *str, char **tmp)
{
	free_str_array(tmp);
	set_error(c_error, code, str);
	return (NULL);
}
