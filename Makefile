S_DIR		= srcs/
SRCS	= $(wildcard $(S_DIR)*.c)
OBJ		= $(SRCS:.c=.o)
CC		= gcc
INCL	= -I $(I_DIR)
I_DIR	= include/
LIB_FT	= -L $(I_DIR) -lft 
CFLAGS	= -Wall -Wextra -Werror $(INCL)
NAME	= parseur
LIB_X	= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm

%.o:%.c
	$(CC) $(CFLAGS) -I/usr/Include -Imlx_linux $(LIB_FT) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(@) $(OBJ) $(LIB_FT) $(LIB_X)
	rm -rf $(OBJ)

all: $(NAME)
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
