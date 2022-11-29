/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:18:31 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/11/29 20:18:33 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	is_config_param(char *str)
{
	int	size;

	size = ft_strlen(str);
	if (size == 1 || size == 2)
	{
		if (ft_strncmp(str, "NO", 3) == 0)
			return (1);
		if (ft_strncmp(str, "SO", 3) == 0)
			return (1);
		if (ft_strncmp(str, "EA", 3) == 0)
			return (1);
		if (ft_strncmp(str, "WE", 3) == 0)
			return (1);
		if (ft_strncmp(str, "F", 2) == 0)
			return (2);
		if (ft_strncmp(str, "C", 2) == 0)
			return (2);
	}
	return (-1);
}

static int	posible_color_code(char *str)
{
	int	color;
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] <= '0' || str[i] >= '9')
			return (-1);
		i++;
	}
	color = ft_atoi(str);
	if (color == 0 && str[0] != '0')
		return (-1);
	if (color < 0 || color > 255)
		return (-1);
	return (0);
}

static int	check_color_format(char *str)
{
	char	**tmp;
	int		i;
	int		ret;

	tmp = ft_split(str, ',');
	if (!tmp || str_array_get_size(tmp) != 3)
	{
		if (tmp)
			free_str_array(tmp);
		return (-1);
	}
	i = -1;
	ret = 0;
	while (tmp[++i] != NULL)
	{
		if (posible_color_code(tmp[i]) < 0)
		{
			ret = -1;
			break ;
		}
	}
	free_str_array(tmp);
	if (ret)
		return (-1);
	return (0);
}

int	is_config_line(char *line, t_custom_error *c_error)
{
	char	**tmp;
	int		config_type;
	int		ret;

	tmp = ft_split(line, ' ');
	if (!tmp)
		return (-1);
	ret = 0;
	if (!tmp[0] || !tmp[1])
	{
		free_str_array(tmp);
		return (-1);
	}
	config_type = is_config_param(tmp[0]);
	if (config_type < 0)
		ret = set_error(c_error, 99, INVALID_PARAM);
	if (config_type == 1
		&& check_path_format(tmp[1], FILE_FORMAT_XPM, c_error) < 0)
		ret = set_error(c_error, 98, BAD_PATH_XPM);
	if (config_type == 2 && check_color_format(tmp[1]) < 0)
		ret = set_error(c_error, 97, INVALID_COLOR);
	free_str_array(tmp);
	return (ret);
}
