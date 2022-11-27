#include <stdio.h>
#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "custom_errors.h"

void	get_map_size(char *path, size_t sz[2])
{
	char	*line;
	size_t	len;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return ;
	sz[0] = 0;
	sz[1] = 0;
	while (1)
	{
	line = get_next_line(fd);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > sz[1])
			sz[1] = len;
		free(line);
		sz[0]++;
	}
	close(fd);
}

static void	erase_nl(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			*line = 0;
		line++;
	}
}

static int	return_map_type(t_custom_error *c_error, t_aux_params aux)
{
	if (aux.config_end >= aux.map_end)
		return (set_error(c_error, 43, INVALID_CFG_POS));
	if ((aux.config_end >= 0) && ((aux.config_end + 1) == aux.map_start))
		return (set_error(c_error, 44, INVALID_NL));
	if (aux.config_start == -1 && aux.map_start >= 0)
		return (set_error(c_error, 45, NO_CFG));
	if (aux.config_end < aux.map_start)
		return (1);
	return (255);
}

static void	aux_params_init(t_aux_params *aux)
{
	aux->map_start = -1;
	aux->map_end = -1;
	aux->config_start = -1;
	aux->config_end = -1;
}

/**
 * En esta funcion queremos saber si es solo simple
 * o si es complejo, para eso usaremos map_start y
 * config_start, ambas las inicialiceremos a -1
 * si al final de la funcion map_start es 0 y config_rest
 * -1, quiere decir que tenemos un mapa simplem, en caso de que
 * ambos tengan datos, tendremos que comprobar si config_start es mauor a map_start
 * y que no volavmos a tener lineas de config una vez encontrado el map start
 *
 * @param raw
 * @return
 */
int	get_map_type(char **raw, t_custom_error *c_error)
{
	int				i;
	t_aux_params	aux;

	i = 0;
	aux_params_init(&aux);
	while (raw[i])
	{
		erase_nl(raw[i]);
		if (line_contain_data(raw[i]) == 0)
		{
			if ((aux.map_start == -1) && (map_first_row_chrs(raw[i]) == 0))
				aux.map_start = i;
			if ((aux.map_start >= 0) && (map_first_row_chrs(raw[i]) == 0))
				aux.map_end = i;
			if ((aux.config_start == -1) && (is_config_line(raw[i], NULL) == 0))
				aux.config_start = i;
			if ((aux.config_start >= 0) && (is_config_line(raw[i], NULL) == 0))
				aux.config_end = i;
			if (i != aux.map_end && (is_config_line(raw[i], NULL) == -1))
				return (-1);
			if ((aux.map_start >= 0) && aux.config_start > aux.map_start)
				return (set_error(c_error, 40, INVALID_CFG_START));
			if ((aux.map_start >= 0) && (is_valid_map_line(raw[i]) < 0))
				return (set_error(c_error, 41, INVALID_MAP_LINE));
		}
		i++;
	}
	return (return_map_type(c_error, aux));
}
