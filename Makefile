# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 20:06:14 by lugonzal          #+#    #+#              #
#    Updated: 2022/11/09 21:54:40 by lugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= Cub3d


CC 			= gcc
CFLAGS 		= -g3 -Wall -Werror -Wextra -Wpedantic
SNTZ		= -fsanitize=address

INC 		= -I ./include -I ./include/inc
LIB			= -L ./include/lib -lft_mac -lmlx
LIB_LINUX 	= -lmlx_Linux -lft_linux -lgnl -lXext -lX11 -lm -lbsd

RM			= rm -rf

UNAME 		= $(shell uname)
MAP			= map/map_first.txt
RUN			=  ./$(NAME) $(MAP)

FRAME		= -framework OpenGL -framework AppKit

FILES		= test/testmap \
			  src/utils/init_destroy \
			  src/parser/parser \
			  src/render/dda \
			  src/utils/logger \
			  src/utils/utils \
			  src/utils/chr_array_utils \
			  src/utils/parser_utils \
			  src/utils/get_next_line \
			  src/utils/get_next_line_utils \
			  #src/hooks/hooks
			  #src/render/render \
			  #src/utils/utils \

SRC		= $(addsuffix .c, $(FILES))
OBJ		= $(addsuffix .o, $(FILES))

.c.o:
	$(CC) $(CFLAGS) $(SNTZ) $(INC) -o $@ -c $^

$(NAME): $(UNAME)

all: $(NAME)

Darwin: $(OBJ)
	$(CC) $(CFLAGS) $(SNTZ) -o $(NAME) $(OBJ) $(LIB) $(FRAME)

Linux: $(OBJ)
	$(CC) $(CFLAGS) $(SNTZ) -o $(NAME) $(OBJ) $(LIB_LINUX)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	$(RUN)

debug: all
	gdb --args $(RUN)

.PHONY: all clean Darwin fclean Linux re run
