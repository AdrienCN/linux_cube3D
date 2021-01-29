S_DIR		= srcs/
SRCS	= $(wildcard $(S_DIR)*.c)
OBJ		= $(SRCS:.c=.o)
CC		= gcc
I_DIR	= include/
CFLAGS	= -Wall -Wextra -Werror -I $(I_DIR) -L $(I_DIR) -lft 
NAME	= parseur

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I $(I_DIR) -o $(@) $(OBJ) -L $(I_DIR) -lft

all: $(NAME)
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
