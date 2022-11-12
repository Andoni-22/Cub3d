
#include "cub3d.h"

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
    if (cont != (i - 1))
        return (-1);
    return (0);
}

//TODO
/**
 * Comprobamos si es una fila de configuracion,
 * color o textura
 * @param line
 * @return
 */
int is_config_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {

        i++;
    }
    return (0);
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
    if (cont != (i - 1))
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
