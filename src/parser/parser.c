#include "cub3d.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


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

static char **process_map(char **raw, t_player *player)
{
    char    **tmp;
    int     size;
    int     line;
    int     column;
    int     pos_found;

    pos_found = 0;
    size = str_array_get_size(raw);
    if (size == 0)
        return (NULL);
    tmp = malloc(sizeof(char*) * size);
    if (!tmp)
        return (NULL);
    line = 0;
    while (raw[line])
    {
        column = 0;
        while (raw[line][column] != '\0')
        {
            if (is_player_position(raw[line][column]) == 0)
            {
                if (process_player(pos_found, line, column, raw) < 0)
                    return (NULL);
                player->pos_y = line;
                player->dir_x = column;
                pos_found++;
            }
            column++;
        }
        tmp[line] = ft_strdup(raw[line]);
        line++;
    }
    if (pos_found > 1)
        return (NULL);
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
static char **process_raw_data(t_application *appl, char **raw)
{
    int     map_type;
    char    **map;

    map_type = get_map_type(raw);
    if (map_type == 0)
    {
        map = process_map(raw, &(appl->player));
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
    appl = NULL;
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
    map = process_raw_data(appl, tmp);
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
int check_path_format(char *path, char *term)
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
    if (ft_strncmp(term, tmp[size - 1], ft_strlen(term) - 1) != 0)
        return (-1);
    fd = open(path, O_RDONLY);
    if (fd <= 0)
        return (-1);
    close(fd);
    return (0);
}
