
#include "cub3d.h"
#include "stdio.h"
#include "custom_errors.h"
#include <stdlib.h>

void	show_map(char **map)
{
    while (*map)
        printf("%s", *map++);
}

int print_error(int code, char *str)
{
    printf("Error: %d: %s\n", code, str);
    return -1;
}

int print_error_and_free(int code, char *str, char **tmp)
{
    free_str_array(tmp);
    printf("Error: %d: %s\n", code, str);
    return -1;
}

int custom_error_init(t_custom_error *c_err)
{
    c_err->code = -1;
    c_err->str = NULL;
    return (0);
}

int set_error(t_custom_error *c_err, int code, char *str)
{
    if (c_err->str != NULL)
        free(c_err->str);
    c_err->code = code;
    c_err->str = ft_strdup(str);
    return (-1);
}

int custom_error(t_custom_error *c_err)
{
    print_error(c_err->code, c_err->str);
    free(c_err->str);
    return (-1);
}