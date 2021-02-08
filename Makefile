S_DIR		= srcs/
SRCS	= $(wildcard $(S_DIR)*.c)
OBJ		= $(SRCS:.c=.o)
CC		= gcc
INCL	= -I $(I_DIR)
I_DIR	= include/
LIB_FT	= -L $(I_DIR) -lft 
CFLAGS	= -Wall -Wextra -Werror 
NAME	= maze 
LIB_X	= -Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx_linux -lXext -lX11 -lm

%.o: %.c
	$(CC) $(INCL) -I/usr/Include -Imlx_linux $(LIB_FT) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(INCL) -o $(@) $(OBJ) $(LIB_FT) $(LIB_X)
	rm -rf $(OBJ)

all: $(NAME)
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
