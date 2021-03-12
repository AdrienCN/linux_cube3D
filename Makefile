S_DIR		= srcs/
SRCS		= $(wildcard $(S_DIR)*.c)
OBJ			= $(SRCS:.c=.o)
CC			= gcc
CUBE.H		= include/h_cube.h
ALL_HEADER	= -I libft/ -I include/ -I minilibx-linux
LIB_FT		= ./libft/libft.a
LIB_MLX		= ./minilibx-linux/libmlx.a
DEPS		= $(CUBE.H) $(LIB_FT) $(LIB_MLX)
CFLAGS		= -Wall -Wextra -Werror
NAME		= cube3d 
ALL_LIBS	=  -L libft/ -lft -L minilibx-linux/ -lmlx -lm -lX11 -lXext 


%.o: %.c $(DEPS) 
#	$(CC) $(CFLAGS) $(INCL) -c $< -o $@ -I /usr/Include -I mlx_linux 
	$(CC) $(CFLAGS) $(ALL_HEADER) -c $< -o ${<:.c=.o} 

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
