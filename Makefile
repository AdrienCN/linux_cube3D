S_DIR		= srcs/
SRCS		= $(wildcard $(S_DIR)*.c)
OBJ			= $(SRCS:.c=.o)
CUBE.H		= include/h_cube.h
LIB_FT		= ./libft/libft.a
LIB_MLX		= ./minilibx-linux/libmlx.a
DEPS		= $(CUBE.H) $(LIB_FT) $(LIB_MLX)
ALL_HEADERS	= -I libft/ -I include/ -I minilibx-linux
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
ALL_LIBS	= -L libft/ -lft -L minilibx-linux/ -lmlx -lm -lX11 -lXext 
NAME		= cube3d 


%.o: %.c $(DEPS) 
	$(CC) $(CFLAGS) $(ALL_HEADERS) -c $< -o $@ 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(@) $(OBJ) $(ALL_LIBS)

$(LIB_FT):
	make bonus -C ./libft/

$(LIB_MLX):
	make -C ./minilibx-linux/
	
clean:
	make clean -C ./libft/
	make clean -C ./minilibx-linux/
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./libft/
	rm -rf $(NAME)

re: fclean all
