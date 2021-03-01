#ifndef H_CUBE_H
# define H_PARSING_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include "get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define TRUE 1

# define FALSE 0

# define MAP_CHAR "012 WSNE"

#define BLACK		0x00000000
#define BLUE		0x000000FF
#define RED			0x00FF0000
#define ORANGE		0x00FF8900
#define GREEN		0x0000FF00	
#define WHITE		0x00FFFFFF

#define STEP_LEN	5

#define FOV			60.0
#define RAY_NUMBER	60.0	
#define RAY_ANGLE	FOV / RAY_NUMBER
#define RAY_STEP	1
#define MOVE_SPEED	10
#define ROT_SPEED	45 * (M_PI / 180)
#define PI			M_PI
#define TWO_PO		M_PI * 2

// for MAC
/*
#define LEFT_ARROW	123
#define RIGHT_ARROW 124
#define W			13
#define A			0
#define S			1
#define D			2
*/

// FOR LINUX
#define LEFT_ARROW	65361
#define RIGHT_ARROW 65363
#define W			119
#define A			97
#define S			115
#define D			100

typedef struct s_rgb
{
	int state;
	int rgb;
	int r;
	int g;
	int b;
}			t_rgb;

typedef struct s_rays
{
	float angle;
	float wallHitX;
	float wallHitY;
	float distance;
	int HitIsVertical;
	int RayIsUp;
	int	RayIsDown;
	int RayIsLeft;
	int RayIsRight;
	int HitContent;
}				t_rays;

typedef struct s_perso
{
	char cardinal;
	float		x;
	float		y;
	int		vert_walk; // si w y + 1 | si  s  y - 1
	int		hze_walk; // pareil avec x
	int		turn;
	float	angle;
}				t_perso;

typedef struct s_cube
{
	int r_bol;
	int r_x;
	int r_y;
	char *north;
	char *east;
	char *west;
	char *south;
	char *sprite;
	t_rgb floor;
	t_rgb ceil;
	t_perso player_tmp;
	char *gnl_line;
	char *m_line;
	int	 max_row;
	int  max_col;
	int	 map_start;
	int  map_end;
	char **map;
	int info_nbr;
}				t_cube;

typedef		struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	t_rays	rays[(int)RAY_NUMBER];
	t_cube	cube;
	t_perso player;
	int		bpp;
	int		line_len;
	int		endian;
	float		win_height;
	float		win_width;
	float		tile_width;
	float		tile_height;
	int		player_color;
	int		wall_color;
	int		floor_color;
	int		ceil_color;
	int		sprite_color;
	int		void_color;
}					t_vars;

		//FIRST PARSING//
int		ft_first_parsing(int fd, t_cube *map_info);
int		ft_try_assigning_value(char *line, t_cube *map_info);
int		ft_assign_resolution(t_cube *element, char *line);
int		ft_check_filename(char *filename, char *ext_name);
int		ft_check_mapname(char *name);

int		ft_rbg_rb_format(char *line);
int		ft_rgb_assign(int arrow, t_cube *map_info, char *line);
int		ft_rgb_check_format(char *line);
int		ft_rgb_g_format(char *line);
int		ft_rgb_give_val(t_rgb *ceiloor, char *line);

int		ft_text_assign(int arrow, t_cube *map_info, char *line);
int		ft_text_check_format(char *path);
int		ft_text_give_val(char **text, char *path);
char 	*ft_text_check_path(char *path);

		//SECOND PARSING//
int		ft_second_parsing(int fd, t_cube *map_info);
int		ft_isbase(char c, char *base);
int		ft_empty_line(char *str);
int		ft_check_fullmap_format(char **map, int max_col, int max_row);
int		ft_make_oneline_map(int fd, t_cube *map_info);


		//MAIN_PARSING//
int		ft_parsing_main(char *map_file, t_cube *vars);
void	ft_mapinfo_init(t_cube *element);
void	ft_print_mapinfo(t_cube *element);
void	ft_free_mapinfo(t_cube *element);
void	ft_free_doublearray(char **tab);



		//***Mini_MAP****
				
				//Minimap_MAKER
int				ft_update_map(t_vars *vars);

				//MINI_MAP_INIT
void	ft_init_color(t_cube *cube, t_vars *vars);
void	ft_perso_init(t_vars *vars);
void	ft_init_game(t_cube *cube, t_vars *vars);
				
				//Player_Movement_algo
int		ft_reset_player(int keycode, t_vars *vars);
int		ft_update_player(t_vars *vars);
int		ft_update_move(int keycode, t_vars *vars);
float	ft_calculate_new_x(float x, t_vars *vars);	
float	ft_calculate_new_y(float y, t_vars *vars);

		//*****UTILS************
void	ft_print_tab(char **tab);

		//CONVERSION UTILS
float			ft_radconvert(float degree);
float			ft_within_twopi(float rad);

		//TMP_UTILS
void			ft_print_tab(char **tab);

		//MLX_UTILS
int		create_trgb(int t, int r, int g, int b);
void    my_mlx_pixel_put(t_vars *data, int x, int y, int color);

		//PRINT_UTILS	
void			ft_choose_tile_color(float x, float y, char c, t_vars *vars);
void			ft_draw_player(t_vars *vars);
void			ft_draw_minimap(t_cube *cube, t_vars *vars);
void			ft_draw_ray_projection(t_vars *vars);

		//RAY_CASTING
void			ft_cast_all_rays(t_vars *vars);
		//SHAPE_PRINT
void			ft_draw_square(t_vars *vars, int p_y, int p_x, int hei, int wid, int color);


		// COLLISION_UTILS
int		ft_map_content(float x, float y, t_vars *vars);
int		ft_is_wall(float x, float y, t_vars *vars);
int		ft_is_maplimit(float x, float y, t_vars *vars);
int		ft_is_sprite(float x, float y, t_vars *vars);
	

#endif
