# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afiat-ar <afiat-ar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 20:06:14 by lugonzal          #+#    #+#              #
#    Updated: 2022/11/29 18:53:16 by afiat-ar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= Cub3d
LIBFT		= Libft


CC 			= gcc
CFLAGS 		= -g3 -Wall -Werror -Wextra -Wpedantic
#SNTZ		= -fsanitize=address

INC 		= -I ./include -I ./include/inc
LIB			= -L ./include/lib -lft_mac -lmlx
LIB_LINUX 	= -L ./include/lib -lmlx_Linux -lft_linux -lgnl -lXext -lX11 -lm -lbsd

RM			= rm -rf

UNAME 		= $(shell uname)
MAP			= map/map_first.cub
RUN			=  ./$(NAME) $(MAP)

FRAME		= -framework OpenGL -framework AppKit

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
			  src/utils/get_next_line \
			  src/utils/get_next_line_utils \
			  src/hooks/hooks
			  #src/utils/logger \
			  #src/render/render \
			  #src/utils/utils \

SRC		= $(addsuffix .c, $(FILES))
OBJ		= $(addsuffix .o, $(FILES))

.c.o:
	$(CC) $(CFLAGS) $(SNTZ) $(INC) -o $@ -c $^

$(NAME): $(LIBFT) $(UNAME)

all: $(NAME)

Libft:
	$(MAKE) -C src/libft/src

Darwin: $(OBJ)
	mv src/libft/src/libft.a include/lib/libft_mac.a
	$(CC) $(CFLAGS) $(SNTZ) -o $(NAME) $(OBJ) $(LIB) $(FRAME)

Linux: $(OBJ)
	mv src/libft/src/libft.a include/lib/libft_linux.a
	$(CC) $(CFLAGS) $(SNTZ) -o $(NAME) $(OBJ) $(LIB_LINUX)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C src/libft/src clean

fclean: clean
	$(RM) $(NAME)
	$(RM) include/lib/libft_*.a

re: fclean all

run: all
	$(RUN)

debug: all
	gdb --args $(RUN)

.PHONY: all clean Darwin fclean Linux re run Darwin Linux
