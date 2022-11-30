/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 19:27:18 by lugonzal          #+#    #+#             */
/*   Updated: 2022/11/30 18:48:35 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	j = 0;
	i = 0;
	str = (char *)haystack;
	if (needle[i] == '\0')
		return (str);
	while (str[j] && len > j)
	{
		i = 0;
		while (str[j + i] == needle[i] && len > j + i)
		{
			i++;
			if (needle[i] == '\0')
			{
				return ((str + j));
			}
		}
		j++;
	}
	return (NULL);
}
