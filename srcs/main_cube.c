#include "h_cube.h"

#define RAY_LEN 50
#define MOVE_SPEED 10
#define ROT_SPEED 90 * (M_PI / 180)
#define LEFT_ARROW 65361
#define RIGHT_ARROW 65363
#define W 119
#define A 97
#define S 115
#define D 100

int				ft_update_player(int keycode, t_vars *vars);
void			ft_init_game(t_cube * cube, t_vars *vars);
void			ft_init_color(t_cube *cube, t_vars *vars);
int				ft_update_map(int keycode, t_vars *vars);
int				ft_is_maplimit(float x, float y, t_vars *vars);
float			ft_calculate_new_x(float x, t_vars *vars);
float			ft_calculate_new_y(float y, t_vars *vars);

float		ft_convert_to_rad(float rad)
{
	float rad2;

	rad2 = rad;
	while (rad2 >= (2 * M_PI))
		rad2 -= 2 * M_PI;
	while (rad2 < 0)
		rad2 += 2 * M_PI;
	return (rad2);
}

int			ras(t_cube *cube)
{
	printf("nothing to do here\n");
	return (0);	
}

int             main(int argc, char **argv)
{
	t_vars		vars;
	
	if (argc != 2)
		return (printf("Usage : 1 argument\n"));	
	if (ft_parsing_main(argv[1], &vars.cube))
		return (-1);

	ft_init_game(&vars.cube, &vars);	
	mlx_hook(vars.win, 2, 1L<<0 , ft_update_player, &vars);
	mlx_hook(vars.win, 3, 1L<<1 , ft_update_map, &vars);
	mlx_loop(vars.mlx);
	ft_free_mapinfo(&vars.cube);
	printf("\nmain --> return (0);\n");
	return (0);
}
int		ft_update_move(int keycode, t_vars *vars)
{
	int c;

	c = keycode;
	if (c == A)
		vars->cube.player.hze_walk += 1;
	else if (c == D)
		vars->cube.player.hze_walk -= 1;
	else if (c == W)
		vars->cube.player.vert_walk += 1;
	else if (c == S)
		vars->cube.player.vert_walk -= 1;
	else if (c == LEFT_ARROW)
		vars->cube.player.turn += 1;
	else if (c == RIGHT_ARROW)
		vars->cube.player.turn -= 1;
	else
	{
		printf("key_pressed = %d|\n", keycode);
		return (0);
	}
	return (1);	
}


float	ft_calculate_new_x(float x, t_vars *vars)
{
	float x_ref;
	float angle;

	x_ref = vars->cube.player.x;
	angle = vars->cube.player.rot_ang;

	if (vars->cube.player.vert_walk == 1)
		x = x_ref + cos(angle) * MOVE_SPEED;
	else if (vars->cube.player.vert_walk == -1)
		x = x_ref - cos(angle) * MOVE_SPEED;
	else if (vars->cube.player.hze_walk == 1)
		x = x_ref + cos(ft_convert_to_rad(angle + (M_PI / 2)))
			* MOVE_SPEED;
	else if (vars->cube.player.hze_walk == -1)
		x = x_ref - cos(ft_convert_to_rad(angle + (M_PI / 2)))
			* MOVE_SPEED;
	return (x);
}

float ft_calculate_new_y(float y, t_vars *vars)
{
	float y_ref;
	float angle;

	y_ref = vars->cube.player.y;
	angle = vars->cube.player.rot_ang;

	if (vars->cube.player.vert_walk == 1)
		y = y_ref - sin(angle) * MOVE_SPEED;
	else if (vars->cube.player.vert_walk == -1)
		y = y_ref + sin(angle) * MOVE_SPEED;
	else if (vars->cube.player.hze_walk == 1)
		y = y_ref - sin(ft_convert_to_rad(angle + (M_PI / 2)))
			* MOVE_SPEED;
	else if (vars->cube.player.hze_walk == -1)
		y = y_ref + sin(ft_convert_to_rad(angle + (M_PI / 2)))
			* MOVE_SPEED;
	return (y);
}

int		ft_update_player(int keycode, t_vars *vars)
{
	float x;
	float y;
	if (!ft_update_move(keycode, vars))
			return (0);
	if (vars->cube.player.turn)
	{
		
		vars->cube.player.rot_ang = ft_convert_to_rad(vars->cube.player.rot_ang
				+ vars->cube.player.turn * ROT_SPEED);
	printf("NEW ANGLE = %f\n", vars->cube.player.rot_ang);
		return (0);
	}
	// get new coord
	x = ft_calculate_new_x(x, vars);
	y = ft_calculate_new_y(y, vars);
	// check if wall
	if (ft_is_maplimit(x, y, vars))
			return (1);
	printf("\n*Player new postion = \n");
	vars->cube.player.x = x;
	vars->cube.player.y = y;
	printf("x = %f | y = %f* | ", x, y);
	printf("rot_angle = %f\n", vars->cube.player.rot_ang);
	return (0);
}

void	ft_draw_line(t_vars *vars)
{
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	int i;
	int j;

	start_x = vars->cube.player.x;
	start_y = vars->cube.player.y;

	i = 0;
	j = 0;
	while (j < 3)
	{
		i = 0;
		while (i < RAY_LEN)
		{
			my_mlx_pixel_put(vars, start_x - 1 + j, start_y - i, RED);
		i++;
		}
		j++;
	}
}	

int		ft_update_map(int keycode, t_vars *vars)
{
	ft_draw_minimap(&vars->cube, vars);
	ft_draw_line(vars);
	ft_draw_player(&vars->cube, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	vars->cube.player.hze_walk = 0;
	vars->cube.player.vert_walk = 0;
	vars->cube.player.turn = 0;
	return (0);
}

void	fucking_clean(void	*mlx, void *win)
{
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
}

void			ft_init_color(t_cube *cube, t_vars *vars)
{
	vars->floor_color = create_trgb(0, 192, 192, 192);
	vars->player_color = create_trgb(0, 255, 0, 0);
	vars->wall_color = create_trgb(0, 0, 204, 0);
	vars->sprite_color = create_trgb(0, 102, 255, 178);
	vars->void_color = create_trgb(0, 0, 0, 0);
	vars->ceil_color = create_trgb(0, cube->ceil.r, cube->ceil.g,
									cube->ceil.b);
}

void			ft_init_game(t_cube * cube, t_vars *vars)
{
	// Get color
	ft_init_color(cube, vars);

	//Get grid proportions
	vars->win_height = cube->r_y ;
	vars->win_width = cube->r_x ;
	vars->tile_width = vars->win_width / cube->max_col; 
	vars->tile_height = vars->win_height / cube->max_row;
	
	printf("vars->width = %d | vars->height = %d\n", vars->win_width, vars->win_height);
	//efface le player de la carte
	cube->map[(int)cube->player.y][(int)cube->player.x] = '0';
	//donne les coord de la TILE du joueur en pixel. 0.0
	cube->player.x = vars->tile_width * cube->player.x + vars->tile_width  / 2;
	cube->player.y = vars->tile_height * cube->player.y + vars->tile_height / 2;
	cube->player.hze_walk = 0;
	cube->player.vert_walk = 0;
	cube->player.turn = 0;
	cube->player.rot_ang = M_PI / 2;

	// Init mlx_instances
	vars->mlx = mlx_init();
	vars->img = mlx_new_image(vars->mlx, vars->win_width, vars->win_height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_len,
                               &vars->endian);
    vars->win = mlx_new_window(vars->mlx, vars->win_width, vars->win_height, "Adrien_cube");
	ft_draw_minimap(&vars->cube, vars);
	ft_draw_line(vars);
	ft_draw_player(&vars->cube, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	printf("X_tile = %d | Y_tile = %d\n", vars->tile_width, vars->tile_height);
}


int		ft_is_maplimit(float x, float y, t_vars *vars)
{
	int row;
	int col;
	char item;

	row =  y / vars->tile_height;
	col = x / vars->tile_width;
	if (y >= vars->win_height || y <= 0)
	{
		printf("Y limit is reached\n");
		return (1);
	}
	if (x >= vars->win_width || x <= 0)
	{
		printf("X limit is reached x = %f\n", x);
			return (1);
	}
	item = vars->cube.map[row][col];
	if (item != '0')
	{
		if (item == '1')
			printf("Wall touched\n");
		else if (item == '2')
			printf("Sprite touched\n");
		else
			printf("WTF did I touch? look in main line 64\n");
		return (1);
	}
	return (0);
}


