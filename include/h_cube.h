/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_cube.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:20:31 by calao             #+#    #+#             */
/*   Updated: 2021/03/15 13:47:42 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_CUBE_H
# define H_CUBE_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define TRUE			1
# define FALSE			0
# define MAP_CHAR		"012 WSNE"
# define MINIMAP_SCALE	0.3
# define TILE_SIZE		100.0
# define FOV			60.0
# define INT_MAX		2147483647

# define LEFT_ARROW	65361
# define RIGHT_ARROW 65363
# define W			119
# define A			97
# define S			115
# define D			100
# define ESCAPE		65307

typedef struct	s_inter
{
	float	x_step;
	float	y_step;
	float	x_inter;
	float	y_inter;
	float	next_x;
	float	next_y;
	float	wallhitx;
	float	wallhity;
	float	distance;
}				t_inter;

typedef struct	s_rgb
{
	int state;
	int rgb;
	int r;
	int g;
	int b;
}				t_rgb;

typedef	struct	s_rays
{
	float	angle;
	float	wallhitx;
	float	wallhity;
	float	distance;
	float	wallheight;
	float	wall_start;
	float	wall_end;
	float	fixed_dist;
	int		hitisvertical;
	int		rayisup;
	int		rayisdown;
	int		rayisleft;
	int		rayisright;
}				t_rays;

typedef struct	s_perso
{
	char		cardinal;
	float		x;
	float		y;
	int			vert_walk;
	int			hze_walk;
	int			turn;
	int			exit;
	float		angle;
}				t_perso;

typedef struct	s_cube
{
	int		r_bol;
	int		r_x;
	int		r_y;
	char	*north;
	char	*east;
	char	*west;
	char	*south;
	char	*sprite;
	char	*gnl_leak_proof;
	t_rgb	floor;
	t_rgb	ceil;
	t_perso player_tmp;
	char	*gnl_line;
	char	*m_line;
	int		sprite_count;
	int		max_row;
	int		max_col;
	int		map_start;
	int		map_end;
	char	**map;
	int		info_nbr;
}				t_cube;

typedef struct	s_img
{
	void	*img;
	void	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef	struct	s_text
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
	t_img	sprite;
}				t_text;

typedef	struct	s_sprite
{
	int		id;
	int		hide_color;
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

typedef struct	s_bmp_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}				t_bmp_color;

typedef struct	s_img_header
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
}				t_img_header;

typedef struct	s_file_header
{
	char			signature[2];
	int				size;
	int				reserved;
	int				offset_img;
	t_img_header	img;
}				t_file_header;

typedef	struct	s_vars
{
	float		tile_height;
	float		tile_width;
	float		move_speed;
	float		rot_speed;
	int			bmp_save;
	int			ceil_color;
	int			floor_color;
	int			ray_num;
	int			sprite_count;
	int			win_height;
	int			win_width;
	t_cube		cube;
	t_img		game;
	t_perso		player;
	t_rays		*rays;
	t_sprite	*sprite_tab;
	t_text		text;
	void		*mlx;
	void		*win;
}				t_vars;

char			*ft_text_check_path(char *path);
float			ft_calculate_new_x(float x, t_vars *vars);
float			ft_calculate_new_y(float y, t_vars *vars);
float			ft_get_distance(float x1, float y1, float x2, float y2);
float			ft_radconvert(float degree);
float			ft_within_twopi(float rad);
int				create_trgb(int t, int r, int g, int b);
int				ft_assign_resolution(t_cube *element, char *line);
int				ft_check_file_ext_name(char *filename, char *ext_name);
int				ft_check_fullmap_format(char **map, t_cube *cube);
int				ft_check_mapname(char *name);
int				ft_empty_line(char *str);
int				ft_first_parsing(int fd, t_cube *map_info);
int				ft_get_xpm_pixel_value(t_img *img, int x, int y);
int				ft_init_game(t_cube *cube, t_vars *vars);
int				ft_init_xpm_img(t_vars *vars, t_img *img, char *img_path);
int				ft_is_file_readable(char *file_path);
int				ft_is_maplimit(float x, float y, t_vars *vars);
int				ft_is_sprite(float x, float y, t_vars *vars);
int				ft_is_wall(float x, float y, t_vars *vars);
int				ft_isbase(char c, char *base);
int				ft_make_oneline_map(int fd, t_cube *map_info);
int				ft_map_content(float x, float y, t_vars *vars);
int				ft_parsing_error_msg(int class, int error);
int				ft_parsing_main(char *map_file, t_cube *vars);
int				ft_rbg_rb_format(char *line);
int				ft_reset_player(int keycode, t_vars *vars);
int				ft_rgb_assign(int arrow, t_cube *map_info, char *line);
int				ft_rgb_check_format(char *line);
int				ft_rgb_g_format(char *line);
int				ft_rgb_give_val(t_rgb *ceiloor, char *line);
int				ft_save_bmp(t_vars *d);
int				ft_second_parsing(int fd, t_cube *map_info);
int				ft_text_assign(int arrow, t_cube *map_info, char *line);
int				ft_text_check_format(char *path);
int				ft_text_give_val(char **text, char *path);
int				ft_try_assigning_value(char *line, t_cube *map_info);
int				ft_update_move(int keycode, t_vars *vars);
int				ft_update_player(t_vars *vars);
int				ft_update_screen(t_vars *vars);
void			ft_cast_all_rays(t_vars *vars);
void			ft_cube_null_init(t_cube *cube);
void			ft_cube_null_init(t_cube *element);
void			ft_find_horz_wallhit(t_vars *vars, t_rays *ray, t_inter *horz);
void			ft_find_vert_wallhit(t_vars *vars, t_rays *ray, t_inter *vert);
void			ft_free_cube(t_cube *cube);
void			ft_free_doublearray(char **tab);
void			ft_free_game(t_vars *vars);
void			ft_free_mapinfo(t_cube *element);
void			ft_game_null_init(t_vars *vars);
void			ft_mapinfo_init(t_cube *element);
void			ft_perso_init(t_vars *vars);
void			ft_print_mapinfo(t_cube *element);
void			ft_print_tab(char **tab);
void			ft_render_minimap(t_vars *vars);
void			ft_render_sprite(t_vars *vars);
void			ft_render_walls(t_vars *vars, t_rays ray, int x);
void			ft_reset_sprites_visibility(t_vars *vars, int sprite_count);
void			ft_set_horz_hit(t_inter *horz, t_vars *vars, t_rays *ray);
void			ft_set_ray_angle(t_rays *ray, float ray_angle);
void			ft_set_ray_wallhit(t_rays *ray, t_vars *vars);
void			ft_set_sprite_val(t_sprite *sprite, int i, int j);
void			ft_set_vert_hit(t_inter *vert, t_vars *vars, t_rays *ray);
void			my_mlx_pixel_put(t_vars *data, int x, int y, int color);
#endif
