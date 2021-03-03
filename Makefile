S_DIR		= srcs/
SRCS	= $(wildcard $(S_DIR)*.c)
OBJ		= $(SRCS:.c=.o)
CC		= gcc
INCL	= -I libft/ -I include/
LIB_FT	= -L libft/ -lft 
CFLAGS	= -Wall -Wextra -Werror 
NAME	= wolf3D 
LIB_X	= -L minilibx-linux/ -lmlx -lm -lX11 -lXext 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCL) -I /usr/Include -I mlx_linux 

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCL) -o $(@) $(OBJ) $(LIB_FT) $(LIB_X)

all: $(NAME)
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
