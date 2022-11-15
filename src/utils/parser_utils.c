
#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

/**
 * Buscamos saber si la linea recibida
 * coincide con el formato de la linea recibida
 * @param line linea del map
 * @return 0 si es correcto, -1 si no lo es
 */
int map_first_row_chrs(char *line)
{
    int i;
    int cont;

    i = 0;
    cont = 0;
    while (line[i])
    {
        if (line[i] == '1' || line[i] == ' ')
            cont++;
        i++;
    }
    if (cont != (i))
        return (-1);
    return (0);
}

static int  is_config_param(char *str)
{
    int size;

    size = ft_strlen(str);
    if (size == 1 || size == 2)
    {
        if (ft_strncmp(str, "NO", 2) == 0)
            return (0);
        if (ft_strncmp(str, "SO", 2) == 0)
            return (0);
        if (ft_strncmp(str, "EA", 2) == 0)
            return (0);
        if (ft_strncmp(str, "WE", 2) == 0)
            return (0);
        if (ft_strncmp(str, "F", 1) == 0)
            return (0);
        if (ft_strncmp(str, "C", 1) == 0)
            return (0);
    }
    return (-1);
}

//TODO
/**
 * Comprobamos si es una fila de configuracion,
 * en si podriamos comprobar mas cosas, pero
 * de momento solo nos interesa saber si es una posible
 * linea de config
 * @param line
 * @return -1 si hay error, 0 si esta bien
 */
int is_config_line(char *line)
{
    char    **tmp;
    int     i;
    int     ret;

    tmp = ft_split(line, ' ');
    ret = 0;
    if (!tmp)
        ret = -1;
    if (is_config_param(tmp[0]) < 0)
        ret = -1;
    i = -1;
    free_str_array(tmp);
    return (ret);
}

/**
 * A esta funcion solo entramos cuando sabemos
 * que el mapa ya a empezado, comprobaremos si
 * los unicos valores dentro de la linea son
 * los validos
 * @param line
 * @return -1 si hay algun error, 0 si va bien
 */
int is_valid_map_line(char *line)
{
    int i;
    int cont;
    int dir_cont;

    i = -1;
    cont = 0;
    dir_cont = 0;
    while (line[++i])
    {
        if (line[i] == '1' || line[i] == '0' || line[i] == ' ')
        {
            cont++;
        }
        else if (line[i] == 'N' || line[i] == 'S' ||
                 line[i] == 'E' || line[i] == 'W')
        {
            dir_cont++;
            cont++;
        }
    }
    if (cont != (i))
        return (-1);
    if (dir_cont > 1)
        return (-1);
    return (0);
}

/**
 * Comprobamos si la linea esta formada por espacios
 * o tabulaciones
 * @param line
 * @return -1 si esta hecha de espacios y tabs, 0 si tienes mas datos
 */
int line_contain_data(char *line)
{
    int i;
    int cont;

    i = 0;
    cont = 0;
    while (line[i])
    {
        if (line[i] == ' ' || line[i] == 9)
            cont++;
        i++;
    }
    if (cont == i - 1)
        return (-1);
    return (0);
}
