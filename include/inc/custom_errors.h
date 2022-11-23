//
// Created by Andoni Fiat arriola on 11/23/22.
//

#ifndef CUB3D_CUSTOM_ERRORS_H
#define CUB3D_CUSTOM_ERRORS_H

#define BAD_PATH_CUB "Incorrect path, make sure that file termination is .cub"
#define INCORRECT_FILE "Make sure if you can read the file"
#define EMPTY_FILE "File does not contain data"
#define MAP_IS_EMPTY "Map does not contain any data"

typedef struct s_custom_error
{
    int     code;
    char    *str
}   t_custom_error;

#endif //CUB3D_CUSTOM_ERRORS_H
