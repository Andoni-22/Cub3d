
#include "cub3d.h"
#include "stdio.h"

void	show_map(char **map)
{
    while (*map)
        printf("%s", *map++);
}
