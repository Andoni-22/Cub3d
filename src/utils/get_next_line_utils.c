/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 01:36:49 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/13 01:36:50 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

int	len_c(char	*str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*gnl_strchr(char *str, char c)
{
	int	i;

	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == c)
			return (str + i);
	}
	return (NULL);
}

char	*strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*n_str;

	i = -1;
	j = -1;
	if (!str1)
	{
		str1 = malloc(1);
		str1[0] = '\0';
	}
	n_str = malloc(len_c(str1, 0) + len_c(str2, 0) + 1);
	if (!n_str)
		return (NULL);
	while (str1[++i])
		n_str[i] = str1[i];
	while (str2[++j])
		n_str[i + j] = str2[j];
	n_str[j + i] = '\0';
	free(str1);
	return (n_str);
}

char	*cutstr(char *str, int start, int len, int on)
{
	int		i;
	char	*n_str;

	i = 0;
	if (!gnl_strchr(str, '\n') && on)
	{
		free(str);
		return (NULL);
	}
	n_str = malloc(len + 1);
	if (!n_str)
		return (NULL);
	while (i < len && str[start + i])
	{
		n_str[i] = str[start + i];
		i++;
	}
	n_str[i] = '\0';
	if (on)
		free(str);
	return (n_str);
}
