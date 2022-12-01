/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:22:27 by afiat-ar          #+#    #+#             */
/*   Updated: 2022/12/01 19:03:07 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOM_ERRORS_H
# define CUSTOM_ERRORS_H

# define BAD_PATH_CUB "Incorrect path, make sure that file termination is .cub"
# define BAD_PATH_XPM "Incorrect path, make sure that file termination is .xpm"
# define INCORRECT_FILE "Make sure if you can read the file"
# define EMPTY_FILE "File does not contain data"
# define MAP_IS_EMPTY "Map does not contain any data"
# define MLX_DEFAULT_ERROR "Something goes wrong with MLX init methods"
# define INVALID_MALLOC "Could not allocate memory"
# define INVALID_CFG_START "Cfg lines may not be on a correct position"
# define INVALID_MAP_LINE "MAP line contain ilegal arguments"
# define INVALID_CFG_POS "Configurations needs to be before map"
# define INVALID_NL "You need to add a newline between cofig and map"
# define NO_CFG "There is not any configuration"
# define INVALID_PARAM "Invalid congirutaion parameter"
# define INVALID_COLOR "Color code is not correct"
# define BAP_PLAYER "Something goes wrong with player..."
# define MAP_IS_OPEN "Map is open"
# define MAP_NL "I do not like that nl -_-"

typedef struct s_custom_error
{
	int		code;
	char	*str;
}	t_custom_error;

int		custom_error_init(t_custom_error *c_err);
int		set_error(t_custom_error *c_err, int code, char *str);
char	**set_error_chr(t_custom_error *c_err, int code, char *str);
char	**set_error_and_free_chr(t_custom_error *c_error,
							  int code, char *str, char **tmp);
int		set_error_and_free(t_custom_error *c_error,
			int code, char *str, char **tmp);
int		print_error(int code, char *str);
int		print_custom_error(t_custom_error *c_error);

#endif // CUB3D_CUSTOM_ERRORS_H
