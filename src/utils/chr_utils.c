//
// Created by Andoni Fiat arriola on 11/15/22.
//

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

char	*chr_cut_back(char *str, char c)
{
    int		size;
    int		i;
    char	*new_str;

    size = 0;
    while (str[size])
        size++;
    if (str[size - 1] != c)
        return (NULL);
    new_str = (char *) malloc(sizeof(char) * (size));
    i = 0;
    while (i < size - 1)
    {
        new_str[i] = str[i];
        i++;
    }
    new_str[i -1] = '\0';
    return (new_str);
}

