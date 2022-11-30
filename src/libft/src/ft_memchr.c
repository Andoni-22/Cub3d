/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 13:54:26 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/30 18:54:47 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*srch;
	size_t			i;

	i = 0;
	srch = (unsigned char *) s;
	while (i < n)
	{
		if (srch[i] == (unsigned char)c)
			return (srch + i);
		i++;
	}
	return (NULL);
}
