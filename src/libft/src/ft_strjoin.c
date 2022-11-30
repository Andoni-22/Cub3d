/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:36:50 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/30 19:03:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*n_str;
	int		size_s1;
	int		size_s2;
	int		i;

	if ((!s1 || !s2))
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	i = -1;
	n_str = (char *)malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (n_str == NULL)
		return (NULL);
	while (*s1)
		n_str[++i] = *s1++;
	i++;
	while (*s2)
		n_str[i++] = *s2++;
	n_str[i] = '\0';
	return (n_str);
}
