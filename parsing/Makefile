S_DIR		= srcs/
SRCS	= $(wildcard $(S_DIR)*.c)
OBJ		= $(SRCS:.c=.o)
CC		= gcc
INCL	= -I $(I_DIR)
I_DIR	= include/
LIBFT	= -L $(I_DIR) -lft 
CFLAGS	= -Wall -Wextra -Werror $(INCL)
NAME	= parseur

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(@) $(OBJ) $(LIBFT) 
	rm -rf $(OBJ)

all: $(NAME)
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
