#include "h_cube.h"

#define RAY_LEN 50

int				ft_update_player(int keycode, t_vars *vars);
void			ft_init_game(t_cube * cube, t_vars *vars);
void			ft_init_color(t_cube *cube, t_vars *vars);
int				ft_update_map(int keycode, t_vars *vars);
int				ft_is_maplimit(int x, int y, t_vars *vars);


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

int		ft_update_player(int keycode, t_vars *vars)
{
	char c;
	int color;
	int x;
	int y;

	c = keycode;
	if (c == 'a')
		vars->cube.player.hze_walk -= STEP_LEN;
	else if (c == 'd')
		vars->cube.player.hze_walk += STEP_LEN;
	else if (c == 'w')
		vars->cube.player.vert_walk -= STEP_LEN;
	else if (c == 's')
		vars->cube.player.vert_walk += STEP_LEN;
	else
		printf("key_pressed = %d|\n", keycode);
	x = vars->cube.player.x + vars->cube.player.hze_walk;
	y = vars->cube.player.y + vars->cube.player.vert_walk;
	if (ft_is_maplimit(x, y, vars))
			return (1);
	x += vars->tile_width;
	y += vars->tile_height;
	if (ft_is_maplimit(x, y, vars))
			return (1);
	printf("\n*Player new postion = \n");
	vars->cube.player.x += vars->cube.player.hze_walk;
	vars->cube.player.y += vars->cube.player.vert_walk;
	printf("x = %f | y = %f*\n\n", vars->cube.player.x, vars->cube.player.y);
	return (0);
}

void	ft_draw_line(t_vars *vars)
{
	int line_x;
	int line_y;
	int i;
	int j;

	line_x = vars->cube.player.x + vars->tile_width / 2;
	line_y = vars->cube.player.y;

	i = 0;
	j = 0;
	while (j < 3)
	{
		i = 0;
		while (i < RAY_LEN)
		{
			my_mlx_pixel_put(vars, line_x - 1 + j, line_y - i, RED);
		i++;
		}
		j++;
	}
}	

int		ft_update_map(int keycode, t_vars *vars)
{
	ft_draw_minimap(&vars->cube, vars);
	ft_draw_player(&vars->cube, vars);
	ft_draw_line(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	vars->cube.player.hze_walk = 0;
	vars->cube.player.vert_walk = 0;
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
	cube->player.x = vars->tile_width * cube->player.x;
	cube->player.y = vars->tile_height * cube->player.y;
	cube->player.hze_walk = 0;
	cube->player.vert_walk = 0;

	// Init mlx_instances
	vars->mlx = mlx_init();
	vars->img = mlx_new_image(vars->mlx, vars->win_width, vars->win_height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_len,
                               &vars->endian);
    vars->win = mlx_new_window(vars->mlx, vars->win_width, vars->win_height, "Adrien_cube");
	ft_draw_minimap(&vars->cube, vars);
	ft_draw_player(&vars->cube, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	printf("X_tile = %d | Y_tile = %d\n", vars->tile_width, vars->tile_height);
}


int		ft_is_maplimit(int x, int y, t_vars *vars)
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
		printf("X limit is reached\n");
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


