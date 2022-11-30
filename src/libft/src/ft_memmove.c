/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 10:31:56 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/30 18:52:40 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	unsigned char	*src2;
	unsigned char	*dst2;

	src2 = (unsigned char *) src;
	dst2 = (unsigned char *) dst;
	i = 0;
	if (!dst2 && !src2)
		return (NULL);
	while (len > i && src > dst)
	{
		dst2[i] = src2[i];
		i++;
	}
	while (len-- && src < dst)
		dst2[len] = src2[len];
	return (dst);
}
