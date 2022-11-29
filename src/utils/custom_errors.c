/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:19:00 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/11/29 20:21:24 by afiat-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "stdio.h"
#include "custom_errors.h"
#include <stdlib.h>

int	print_error(int code, char *str)
{
	if (code == -1 || str == NULL)
	{
		printf("Error: Undefied error");
		return (-1);
	}
	printf("Error: %d: %s\n", code, str);
	return (code);
}

int	print_custom_error(t_custom_error *c_error)
{
	if (c_error->code == -1 || c_error->str == NULL)
	{
		printf("Error: Undefied error");
		return (-1);
	}
	print_error(c_error->code, c_error->str);
	if (c_error->str)
		free(c_error->str);
	return (c_error->code);
}

int	set_error_and_free(t_custom_error *c_error, int code, char *str, char **tmp)
{
	free_str_array(tmp);
	set_error(c_error, code, str);
	return (-1);
}

int	custom_error_init(t_custom_error *c_err)
{
	c_err->code = -1;
	c_err->str = NULL;
	return (0);
}

int	set_error(t_custom_error *c_err, int code, char *str)
{
	if (c_err->str != NULL)
		free(c_err->str);
	c_err->code = code;
	c_err->str = ft_strdup(str);
	return (-1);
}
