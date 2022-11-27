
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
    if (code == -1 || str == NULL)
    {
        printf("Error: Undefied error");
        return (-1);
    }
    printf("Error: %d: %s\n", code, str);
    return (code);
}

int print_custom_error(t_custom_error *c_error)
{
    if (c_error->code == -1 || c_error->str == NULL)
    {
        printf("Error: Undefied error");
        return (-1);
    }
    print_error(c_error->code, c_error->str);
    if (c_error->str)
        free(c_error->str);
    return (c_error->code);
}

int set_error_and_free(t_custom_error *c_error, int code, char *str, char **tmp)
{
    free_str_array(tmp);
    set_error(c_error, code, str);
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

char    **set_error_chr(t_custom_error *c_err, int code, char *str)
{
    set_error(c_err, code, str);
    return (NULL);
}
