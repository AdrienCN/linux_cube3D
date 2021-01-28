DIR		= srcs/
SRCS	= $(wildcard $(DIR)*.c)
OBJ		= $(SRCS:.c=.o)
CC		= gcc
INCL	= include/
CFLAGS	= -Wall -Wextra -Werror -L $(INCL) -lft -I $(INCL)
NAME	= parseur

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(@) $(OBJ) 	

all: $(NAME)
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

