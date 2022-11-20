#include <stdio.h>
#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void  get_map_size(char *path, size_t sz[2])
{
    char	*line;
    size_t  len;
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

static void erase_nl(char *line)
{
    while (*line)
    {
        if (*line == '\n')
            *line = 0;
        line++;
    }
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
int get_map_type(char **raw)
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
        erase_nl(raw[i]);
        if (line_contain_data(raw[i]) == 0)
        {
            //fprintf(stderr, "RETVAL: %d\n", map_first_row_chrs(raw[i]));
            if ((map_start == -1) && (map_first_row_chrs(raw[i]) == 0))
                map_start = i;
            if ((map_start >= 0) && (map_first_row_chrs(raw[i]) == 0))
                map_end = i;
            if ((config_start == -1) && (is_config_line(raw[i]) == 0))
                config_start = i;
            if ((config_start >= 0) && (is_config_line(raw[i]) == 0))
                config_end = i;
            if ((map_start >= 0) && config_start > map_start)
                return (-1);
            if ((map_start >= 0) && (is_valid_map_line(raw[i]) < 0))
                return (-1);
        }
        i++;
    }
    if (config_end >= map_end)
        return (-1);
    if ((config_end >= 0) && ((config_end + 1) == map_start))
        return (-1);
    if (config_start == -1 && map_start >= 0)
        return (0);
    if (config_end < map_start)
        return (1);
    return (255);
}
