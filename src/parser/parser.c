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

char **load_raw_file_data(char *path, size_t	sz)
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

//static int  process_line(char *line)
//{
//    int i;
//
//    i = 0;
//    while (line[i])
//    {
//        if (line[i])
//        i++;
//    }
//}

/**
 * ME HE BLOQUEADOOOOOOOOOOOO
 * me caguen la puta xD
 * @param raw
 * @return
 */
static int get_map_type(char **raw)
{
    int i;
    int ret;

    i = 0;
    while (raw[i])
    {
        //process_line();
        i++;
    }
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
    int map_type;

    map_type = get_map_type(raw);
    if (map_type == 0)
    {
        //error
    }
    else if (map_type == 1)
    {

    }
    else
    {
        //error
    }

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
    char    **map;

	sz = get_map_size(path);
	if (!sz)
		return (NULL);
    tmp = load_raw_file_data(path, sz);
    map = process_raw_data(&appl->texture, tmp);
    if (!map)
        return (NULL);
	return (tmp);
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
