#include "cub3d.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static size_t	get_map_size(char *path)
{
	size_t	map_sz;
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	map_sz = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		map_sz++;
	}
	close(fd);
	return (map_sz);
}

/**
 * Abrimos el fichero y leemos todo la informacion
 * @param path ruta del fichero
 * @param sz numero de filas del fichero
 * @return NULL si sale mal, el mapa en un char ** si sale bien
 */
char **load_raw_file_data(char *path, size_t sz)
{
	char	**map;
	char	*line;
	int		fd;

	map = ft_calloc(sizeof(char *), sz + 1);
	if (!map)
		return (NULL);
	sz = 0;
	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map[sz++] = line;
	}
	close(fd);
	return (map);
}

/**
 * En esta funcion queremos saber si es solo simple
 * o si es complejo, para eso usaremos map_start y
 * config_start, ambas las inicialiceremos a -1
 * si al final de la funcion map_start es 0 y config_rest
 * -1, quiere decir que tenemos un mapa simplem, en caso de que
 * ambos tengan datos, tendremos que comprobar si config_start es mallor a map_start
 * y que no volavmos a tener lineas de config una vez encontrado el map start
 *
 * @param raw
 * @return
 */
static int get_map_type(char **raw)
{
    int i;
    int map_start;
    int map_end;
    int config_start;
    int config_end;

    i = 0;
    map_start = -1;
    map_end = -1;
    config_start = -1;
    config_end = -1;
    while (raw[i])
    {
        if (line_contain_data(raw[i]) == 0)
        {
            if ((map_start == -1) && (map_first_row_chrs(raw[i]) == 0))
                map_start = i;
            if ((map_start >= 0) && (map_first_row_chrs(raw[i]) == 0))
                map_end = i;
            if ((config_start == -1) && (is_config_line(raw[i]) == 0))
                config_start = i;
            if ((config_start >= 0) && (is_config_line(raw[i]) == 0))
                config_end = i;
            if (config_start > map_start)
                return (-1);
            if ((map_start >= 0) && (is_valid_map_line(raw[i]) < 0))
                return (-1);
        }
        i++;
    }
    if (config_end > map_end)
        return (-1);
    if (config_start == -1 && map_start >= 0)
        return (0);
    if (config_end < map_start)
        return (1);
    return (255);
}

static char **process_map(char **raw)
{
    char    **tmp;
    int     size;
    int     i;

    size = str_array_get_size(raw);
    if (size == 0)
        return (NULL);
    tmp = malloc(sizeof(char*) * size);
    if (!tmp)
        return (NULL);
    i = 0;
    while (raw[i])
    {
        //TODO la logica del mapa tendria que ir aqui, en caso
        //TODO de que sea correcta, copiaremos la linea
        tmp[i] = ft_strdup(raw[i]);
        i++;
    }
    return (tmp);
}

/**
 * First we are going to check if it is a simple map
 * or a complex one. If the first row with data is formed
 * by 1 or 'sp' we know that the map is simple, otherwise
 * map is complex
 * @param texture struct with data about textures and colors
 * @param raw map raw data
 * @return
 */
static char **process_raw_data(t_texture *texture, char **raw)
{
    int     map_type;
    char    **map;

    map_type = get_map_type(raw);
    if (map_type == 0)
    {
        map = process_map(raw);
        printf("Mapa de tipo simple\n");
        return (map);
    }
    else if (map_type == 1)
    {
        printf("Mapa de tipo complejo\n");
        return (NULL);
        //MAPA COMPLEJO
    }
    else if (map_type == -1)
        return (NULL);
    texture = NULL;
    return (NULL);
}

/**
 * We take all the data on the file to start the
 * parse process
 * @param appl struct with all the data
 * @param path file path string
 * @return NULL if file is not correct or a char**
 *          with the map
 */
char    **load_map(t_application *appl, char *path)
{
	size_t	sz;
    char    **tmp;
    char    **tmp_tmp;
    char    **map;
    int     i;

    i = -1;
    sz = get_map_size(path);
    if (!sz)
        return (NULL);
    tmp = load_raw_file_data(path, sz);
    tmp_tmp = str_array_copy(tmp);
    free_str_array(tmp);
    tmp = ft_calloc(sizeof(char *), sz + 1);
    while (tmp_tmp[++i])
        tmp[i] = chr_cut_back(tmp_tmp[i], 10);
    map = process_raw_data(&appl->texture, tmp);
    free_str_array(tmp);
    if (!map)
        return (NULL);
	return (map);
}

/**
 * We get the map path and we try to make first checks:
 *      - File format needs to be .cub
 *      - File have to exist
 *      - We need to have permission
 *        to open and read
 * @param path la ruta del mapa
 * @return -1 if any error, 0 if it is correct
 */
int  check_path_format(char *path)
{
    char    **tmp;
    int     size;
    int     fd;

    size = 0;
    tmp = ft_split(path, '.');
    fprintf(stderr, "COMNPLETE PATH: %s\n", path);
    while (tmp[size] != NULL)
        size++;
    for (int i = 0; tmp[i]; i++)
        fprintf(stderr, "tmp[%d] -> %s\n", i, tmp[i]);
    if (size == 1)
        return (-1);
    if (ft_strncmp(FILE_FORMAT, tmp[size - 1], ft_strlen(FILE_FORMAT) - 1) != 0)
        return (-1);
    fd = open(path, O_RDONLY);
    if (fd <= 0)
        return (-1);
    close(fd);
    return (0);
}
