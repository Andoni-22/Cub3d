
#include "cub3d.h"
#include "libft.h"

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

static int  posible_color_code(char *str)
{
    int color;
    int i;

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

/**
 * comprobamos si el str que recibimos cumple
 * con los formatos de rgb
 * @param str
 * @return
 */
static int check_color_format(char *str)
{
    char    **tmp;
    int     i;
    int     ret;

    tmp = ft_split(str, ',');
    if (!tmp)
        return (-1);
    if (str_array_get_size(tmp) != 3)
    {
        free_str_array(tmp);
        return (-1);
    }
    i = 0;
    ret = 0;
    while (tmp[i] != NULL)
    {
        if (posible_color_code(tmp[i]) < 0)
        {
            ret = -1;
            break;
        }
        i++;
    }
    free_str_array(tmp);
    if (ret)
        return -1;
    return (0);
}

/**
 * Comprobamos si es una fila de configuracion,
 * en si podriamos comprobar mas cosas, pero
 * de momento solo nos interesa saber si es una posible
 * linea de config
 * @param line
 * @return -1 si hay error, 0 si esta bien
 */
int is_config_line(char *line, t_custom_error *c_error)
{
    char    **tmp;
    int     config_type;
    int     ret;

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
    if (config_type == 1 && check_path_format(tmp[1], FILE_FORMAT_XPM, NULL) < 0)
        ret = set_error(c_error, 98, BAD_PATH_XPM);
    if (config_type == 2 && check_color_format(tmp[1]) < 0)
        ret = set_error(c_error, 97, INVALID_COLOR);
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
    int one_find;
    int dir_cont;

    i = -1;
    cont = 0;
    dir_cont = 0;
    one_find = 0;
    while (line[++i])
    {
        if (line[i] == '1')
            one_find++;
        if (line[i] == '1' || line[i] == '0' || line[i] == ' ')
            cont++;
        else if (is_player_position(line[i]) == 0)
        {
            dir_cont++;
            cont++;
        }
    }
    if (cont != (i))
        return (-1);
    if (dir_cont > 1)
        return (-1);
    if (one_find == 0)
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
    if (!*line)
        return (-1);
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
