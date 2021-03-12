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

# define TRUE			1

# define FALSE			0

# define MAP_CHAR		"012 WSNE"

// True Blue
# define BLUE			0x000000FF
// Green_BLUE
//# define BLUE			0x0000FF00	
# define GREEN			0x0000FF00	
# define BLACK			0x00000000
# define RED			0x00FF0000
# define ORANGE			0x00FF8900
# define WHITE			0x00FFFFFF
# define GREY			0x00D3D3D3

# define MINIMAP_SCALE	0.3	
# define STEP_LEN		5
# define TILE_SIZE		200.0

# define FOV			66.0
# define RAY_STEP		0.5	
# define MOVE_SPEED		0.1 * TILE_SIZE
# define ROT_SPEED		10 * (M_PI / 180)
# define PI				M_PI
# define TWO_PO			M_PI * 2
# define INT_MAX		2147483647

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
#define ESCAPE		65307

typedef struct s_inter
{
	float	x_step;
	float	y_step;
	float	x_inter;
	float	y_inter;
	float	next_x;
	float	next_y;
	int		found_wall;
	float	wallhitx;
	float	wallhity;
	float	distance;
}			t_inter;

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
	float wallhitx;
	float wallhity;
	float distance;
	float wallheight;
	float wall_start;
	float wall_end;
	float fixed_dist;
	int hitisvertical;
	int rayisup;
	int	rayisdown;
	int rayisleft;
	int rayisright;
}				t_rays;

typedef struct s_perso
{
	char cardinal;
	float		x;
	float		y;
	int		vert_walk; // si w y + 1 | si  s  y - 1
	int		hze_walk; // pareil avec x
	int		turn;
	int		exit;
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

typedef		struct s_img
{
	void	*img;
	void	*addr;
	char	*path;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef		struct s_text
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
	t_img	sprite;
}				t_text;

typedef		struct s_sprite
{
	int		id;
	int		is_visible;
	int		row;
	int		col;
	float	start_y;
	float	end_y;
	float	right_x;
	float	left_x;
	float	x;
	float	y;
	float	dist;
	float	angle;
	float	height;
	float	width;
}				t_sprite;

typedef struct		s_bmp_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_bmp_color;

typedef struct		s_img_header
{
	int				size_img_header;
	int				width;
	int				length;
	short			nb_planes;
	short			bpp;
	int				compression;
	int				size_img_total;
	int				res_ver;
	int				res_hor;
	int				color_array;
	int				img_array;
}					t_img_header;

typedef struct		s_file_header
{
	char			signature[2];
	int				size;
	int				reserved;
	int				offset_img;
	t_img_header	img;
}					t_file_header;

typedef		struct s_vars
{
	// Instance mlx
	void		*mlx;
	void		*win;

	// Img de l'instance mx soit du jeu globale
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;

	//BMP
	int			bmp_save;

	// raycasting utils	
	int			sprite_count;
	int			ray_num;
	int			*colorbuf;
	int			player_color;
	int			wall_color;
	int			floor_color;
	int			ceil_color;
	int			sprite_color;
	int			void_color;
	int			win_height;
	int			win_width;
	float		ray_increment;
	float		tile_width;
	float		tile_height;

	//struct
	t_text		text;
	t_cube		cube;
	t_perso		player;
	t_rays		*rays;
	t_sprite	*sprite_tab;
}					t_vars;

		//MAIN_PARSING//
int		ft_parsing_main(char *map_file, t_cube *vars);
void	ft_mapinfo_init(t_cube *element);
void	ft_print_mapinfo(t_cube *element);
void	ft_free_mapinfo(t_cube *element);
void	ft_free_doublearray(char **tab);


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


		//***********RAY_CASTING*************
void	ft_cast_all_rays(t_vars *vars);
void	ft_set_ray_angle(t_rays *ray, float ray_angle);
void	ft_set_ray_wallhit(t_rays *ray, t_vars *vars);
			//RAY_algebra
void		ft_find_vert_wallhit(t_vars *vars, t_rays *ray, t_inter *vert);
void		ft_find_horz_wallhit(t_vars *vars, t_rays *ray, t_inter *horz);
void		ft_set_horz_hit(t_inter *horz, t_vars *vars, t_rays *ray);
void		ft_set_vert_hit(t_inter *vert, t_vars *vars, t_rays *ray);

		//*************3D_RENDERERING*********
void	ft_render_walls(t_vars *vars, t_rays *ray);
void	ft_render_sprite(t_vars *vars);
void	ft_render_minimap(t_vars *vars);


		//***Mini_MAP****
				//Minimap_MAKER
int		ft_update_screen(t_vars *vars);
				//MINI_MAP_INIT
void	ft_init_color(t_cube *cube, t_vars *vars);
void	ft_perso_init(t_vars *vars);
void	ft_init_game(t_cube *cube, t_vars *vars);
				//Player_Movement_algo
int		ft_update_player(t_vars *vars);
int		ft_update_move(int keycode, t_vars *vars);
float	ft_calculate_new_x(float x, t_vars *vars);	
float	ft_calculate_new_y(float y, t_vars *vars);

		//****BMP****
int		ft_save_bmp(t_vars *d);

		//*****UTILS************
void	ft_print_tab(char **tab);

		
		//RESET VAL
int			ft_reset_player(int keycode, t_vars *vars);
void		ft_reset_sprites_visibility(t_vars *vars, int sprite_count);

		//MATHS UTILS
float	ft_radconvert(float degree);
float	ft_within_twopi(float rad);
float	ft_get_distance(float x1, float y1, float x2, float y2);

		//MLX_UTILS
int		create_trgb(int t, int r, int g, int b);
void    my_mlx_pixel_put(t_vars *data, int x, int y, int color);
int		ft_get_xpm_pixel_value(t_img *img, int x, int y);

		//PRINT_UTILS	

		//SHAPE_PRINT
void	ft_draw_square(t_vars *vars, int p_y, int p_x, int hei, int wid, int color);
void	ft_render_line_gpetit(float x, float y, t_vars *vars, float ray_angle);
void	ft_render_line_dda(t_vars *vars, t_rays ray, float x1, float y1);

		// COLLISION_UTILS
int		ft_map_content(float x, float y, t_vars *vars);
int		ft_is_wall(float x, float y, t_vars *vars);
int		ft_is_maplimit(float x, float y, t_vars *vars);
int		ft_is_sprite(float x, float y, t_vars *vars);
	
		//TMP_UTILS
void	ft_print_tab(char **tab);
void	print_ray_info(t_rays *ray);

#endif
