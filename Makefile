# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 20:06:14 by lugonzal          #+#    #+#              #
#    Updated: 2022/12/01 19:26:31 by lugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= Cub3d
LIBFT		= Libft


CC 			= gcc
CFLAGS 		= -g3 -Wall -Werror -Wextra -Wpedantic
#SNTZ		= -fsanitize=address
FRAME		= -framework OpenGL -framework AppKit

INC 		= -I include -I include/inc -I $(MINILIB_PATH) -I $(LIBFT_PATH)
LIB			= -L include/lib -lft -lmlx
RM			= rm -rf

MAP			= map/map_first.cub
RUN			=  ./$(NAME) $(MAP)

MINILIB_PATH	= src/minilibx
LIBFT_PATH 		= src/libft/src
LIB_PATH		= include/lib

FILES		= src/main \
			  src/utils/init_destroy \
			  src/parser/map \
			  src/parser/map_validation \
			  src/parser/parser \
			  src/parser/player \
			  src/parser/file \
			  src/parser/textures \
			  src/render/dda \
			  src/render/ray \
			  src/render/wall \
			  src/render/texture \
			  src/render/pixel_utils \
			  src/utils/init \
			  src/utils/utils \
			  src/utils/custom_errors \
			  src/utils/chr_utils \
			  src/utils/chr_array_utils \
			  src/utils/parser_utils \
			  src/utils/locate_player \
			  src/utils/get_next_line \
			  src/utils/get_next_line_utils \
			  src/hooks/hooks

SRC		= $(addsuffix .c, $(FILES))
OBJ		= $(addsuffix .o, $(FILES))

.c.o:
	$(CC) $(CFLAGS) $(SNTZ) $(INC) -o $@ -c $^

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_PATH)
	$(MAKE) -C $(MINILIB_PATH)
	mv $(LIBFT_PATH)/libft.a $(LIB_PATH)
	mv $(MINILIB_PATH)/libmlx.a $(LIB_PATH)
	$(CC) $(CFLAGS) $(SNTZ) -o $(NAME) $(LIB) $(FRAME) $(OBJ)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MINILIB_PATH) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIB_PATH)/libft.a
	$(RM) $(LIB_PATH)/libmlx.a

re: fclean all

run: all
	$(RUN)

.PHONY: all clean Darwin fclean Linux re run Darwin Linux
