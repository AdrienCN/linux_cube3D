SRCS		= srcs/ft_cast_rays.c \
	srcs/ft_collision_utils.c \
	srcs/ft_error_msg_parsing.c \
	srcs/ft_init_game_values.c \
	srcs/ft_init_utils.c \
	srcs/ft_parsing_first_half_main.c \
	srcs/ft_parsing_first_half_rgb.c \
	srcs/ft_parsing_first_half_texture.c \
	srcs/ft_parsing_main.c \
	srcs/ft_parsing_second_half_main.c \
	srcs/ft_parsing_second_half_mapcheck_format.c \
	srcs/ft_parsing_second_half_onelinemap.c \
	srcs/ft_ray_hit_algebra.c \
	srcs/ft_render_minimap.c \
	srcs/ft_render_sprite.c \
	srcs/ft_render_walls.c \
	srcs/ft_reset_game_values.c \
	srcs/ft_save_bmp.c \
	srcs/ft_update_player_move.c \
	srcs/ft_utils_free.c \
	srcs/ft_utils_math.c \
	srcs/ft_utils_mlx.c \
	srcs/ft_utils_parsing.c \
	srcs/main_cube.c

OBJ			= $(SRCS:.c=.o)
CUBE.H		= include/h_cube.h
LIB_FT		= ./libft/libft.a
LIB_MLX		= ./minilibx-linux/libmlx.a
DEPS		= $(CUBE.H) $(LIB_FT) $(LIB_MLX)
ALL_HEADERS	= -I libft/ -I include/ -I minilibx-linux
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
ALL_LIBS	= -L libft/ -lft -L minilibx-linux/ -lmlx -lm -lX11 -lXext 
NAME		= cub3D 


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
