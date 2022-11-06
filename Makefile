NAME 	= Cub3d

INC 	= -I ./include -I ./include/inc
LIB		= -L ./include/lib -lft -lmlx #-lmlx_Linux -lgnl -lXext -lX11 -lm -lbsd
CC		= gcc
CFLAGS 	= -g3 #-Wall -Werror -Wextra #-Wpedantic
SNTZ	= -fsanitize=address
RM		= rm -rf
RUN		=  ./$(NAME) $(MAP)
FRAME	= -framework OpenGL -framework AppKit

FILES	= src/main \
		  src/hooks/hooks \
		  src/parser/parser \
		  src/render/render \
		  src/render/dda \
		  src/utils/utils \
		  src/utils/logger \
		  src/utils/get_next_line \
		  src/utils/get_next_line_utils \
		  src/utils/init_destroy

SRC		= $(addsuffix .c, $(FILES))
OBJ		= $(addsuffix .o, $(FILES))

.c.o:
	$(CC) $(CFLAGS) $(SNTZ) $(INC) -o $@ -c $^

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SNTZ) -o $(NAME) $(OBJ) $(LIB) $(FRAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	$(RUN)

debug: all
	gdb --args $(RUN)

.PHONY: all clean fclean re run
