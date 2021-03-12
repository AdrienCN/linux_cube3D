S_DIR	= srcs/
SRCS	= $(wildcard $(S_DIR)*.c)
OBJ		= $(SRCS:.c=.o)
CC		= gcc
INCL	= -I libft/ -I include/ -I minilibx-linux
LIB_FT	= -L libft/ -lft 
CFLAGS	= -Wall -Wextra -Werror 
NAME	= wolf3D 
LIB_X	= -L minilibx-linux/ -lmlx -lm -lX11 -lXext 

.c.o: 
#	$(CC) $(CFLAGS) $(INCL) -c $< -o $@ -I /usr/Include -I mlx_linux 
	$(CC) $(CFLAGS) $(INCL) -c $< -o ${<:.c=.o} 

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(@) $(OBJ) $(LIB_FT) $(LIB_X)

all: $(NAME)
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
