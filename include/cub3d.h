/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andoni <andoni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:42:02 by andoni            #+#    #+#             */
/*   Updated: 2022/10/19 23:01:26 by andoni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>

#include "libft.h"

#include "mlx.h"
#include "mlx_int.h"

typedef struct	application_s {
	struct mlx_s	*mlx_win;

} application_t;

typedef struct mlx_s
{
	void	*mlx;
	void	*mlx_window;
	int		size_y;
	int		size_x;

}	mlx_t;

int		application_init(application_t *appl);
void	application_destory(application_t *appl);
int		appl_mlx_init(mlx_t	*mlx);
void	appl_mlx_destroy(mlx_t	*mlx);

#endif