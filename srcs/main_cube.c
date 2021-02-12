#include "h_cube.h"


int				key_hook(int keycode, t_cube *cube);
void			ft_init_game(t_cube * cube, t_vars *vars);
void			ft_init_color(t_cube *cube, t_vars *vars);
int				ft_update_map(int keycode, t_cube *cube);


int			ras(t_cube *cube)
{
	printf("nothing to do here\n");
	return (0);	
}

int             main(int argc, char **argv)
{
	t_cube		cube;
	t_vars		vars;
	
	if (argc != 2)
		return (printf("Usage : 1 argument\n"));	
	if (ft_parsing_main(argv[1], &cube))
		return (-1);

	ft_init_game(&cube, &vars);	
	ft_print_minimap(&cube, &vars);
	ft_print_player(&cube, &vars);

	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0 , key_hook, &cube);
	mlx_hook(vars.win, 3, 1L<<1 , ft_update_map, &cube);
	mlx_loop(vars.mlx);
	ft_free_mapinfo(&cube);
	printf("\nmain --> return (0);\n");
	return (0);
}

int		key_hook(int keycode, t_cube *cube)
{
	char c;
	int color;
	int x;
	int y;
	int w;
	int z;
	int row;
	int col;
	int diag;
	t_vars *vars;
	vars = cube->cpy_vars;

	c = keycode;
	if (c == 'a')
		cube->player.a_d -= STEP_LEN;
	else if (c == 'd')
		cube->player.a_d += STEP_LEN;
	else if (c == 'w')
		cube->player.w_s -= STEP_LEN;
	else if (c == 's')
		cube->player.w_s += STEP_LEN;
	else
		printf("key_pressed = %d|\n", keycode);
	x = cube->player.x + cube->player.a_d;
	y = cube->player.y + cube->player.w_s;
	row = y / vars->tile_height;
	col = x / vars->tile_width;
	if ((y >= vars->win_height || y < 0) 
			|| (x >= vars->win_width || x < 0)) 
	{
		printf("***BOUNDARIES LIMIT***\n");
		return (1);
	}
	if (cube->map[row][col] != '0')
	{

		printf("CANNOT PASS LAH - map[%d][%d] is :** ", row, col);
		if (cube->map[row][col] == '1')
			printf("WALL**\n");
		else
			printf("SPRITE**\n");
		return (1);
	}
	w = x + vars->tile_width;
	z = y + vars->tile_height;
	row = z / vars->tile_height;
	col = w / vars->tile_width;
	if ((z >= vars->win_height || z < 0) 
			|| (w >= vars->win_width || w < 0)) 
	{
		printf("***BOUNDARIES LIMIT***\n");
		return (1);
	}
	if (cube->map[row][col] != '0')
	{

		printf("CANNOT PASS LAH - map[%d][%d] is :** ", row, col);
		if (cube->map[row][col] == '1')
			printf("WALL**\n");
		else
			printf("SPRITE**\n");
		return (1);
	}
	printf("\n*Player new postion = \n");
	cube->player.x += cube->player.a_d;
	cube->player.y += cube->player.w_s;
	printf("x = %d | y = %d*\n\n", cube->player.x, cube->player.y);
	return (0);
}

int		ft_update_map(int keycode, t_cube *cube)
{
	t_vars *vars;
	vars = cube->cpy_vars;
	ft_print_minimap(cube, cube->cpy_vars);
	ft_print_player(cube, cube->cpy_vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	cube->player.a_d = 0;
	cube->player.w_s = 0;
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
	vars->play_color = create_trgb(0, 255, 0, 0);
	vars->wall_color = create_trgb(0, 0, 204, 0);
	vars->spr_color = create_trgb(0, 102, 255, 178);
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
	cube->map[cube->player.y][cube->player.x] = '0';
	//donne les coord de la TILE du joueur en pixel. 0.0
	cube->player.x = vars->tile_width * cube->player.x;
	cube->player.y = vars->tile_height * cube->player.y;
	cube->player.a_d = 0;
	cube->player.w_s = 0;
	cube->cpy_vars = vars;

	// Init mlx_instances
	vars->mlx = mlx_init();
	vars->img = mlx_new_image(vars->mlx, vars->win_width, vars->win_height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_len,
                               &vars->endian);
    vars->win = mlx_new_window(vars->mlx, vars->win_width, vars->win_height, "Adrien_cube");
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	printf("X_tile = %d | Y_tile = %d\n", vars->tile_width, vars->tile_height);
}


