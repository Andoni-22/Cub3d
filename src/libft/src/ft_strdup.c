/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 17:31:59 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/30 19:03:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	size;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	size = ft_strlen(s1);
	str = (char *)malloc(size * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{	
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
