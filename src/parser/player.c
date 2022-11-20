//
// Created by Andoni Fiat arriola on 11/18/22.
//

#include "cub3d.h"

int is_player_position(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (0);
    return (-1);
}

//TODO
int process_player(int pos_found, int line, int colum, char **raw)
{
    int i;
    int x;

    (void)x;
    (void)line;
    (void)colum;
    (void)raw;
    if (pos_found >= 1)
        return (-1);
    i = 0;
    while (raw[i])
    {
        x = 0;
        //while (raw)
        i++;
    }

    return (0);
}
