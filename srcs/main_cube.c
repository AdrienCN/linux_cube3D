#include "h_cube.h"

typedef		struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		win_height;
	int		win_width;
	int		tile_x;
	int		tile_y;
	int		play_color;
	int		wall_color;
	int		floor_color;
	int		ceil_color;
	int		spr_color;
	int		void_color;
}					t_vars;

int				draw_triangle(t_vars *vars, int x, int y, int color);
int				key_hook(int keycode, t_vars *vars);
void			event_algo(t_vars *vars);
void			ft_init_game(t_cube * cube, t_vars *vars);
void			ft_init_color(t_cube *cube, t_vars *vars);
void            my_mlx_pixel_put(t_vars *data, int x, int y, int color);
int				create_trgb(int t, int r, int g, int b);
void			ft_print_tab(char **tab);

void			ft_fill_pixel(int x, int y, char c, t_vars *vars)
{
	if (c == ' ')
		my_mlx_pixel_put(vars, x, y, vars->void_color);
	else if (c == '0')
		my_mlx_pixel_put(vars, x, y, vars->floor_color);
	else if (c == '1')
		my_mlx_pixel_put(vars, x, y, vars->wall_color);
	else if (ft_isbase(c, "NESW"))
		my_mlx_pixel_put(vars, x, y, vars->play_color);
	else if (c == '2')
		my_mlx_pixel_put(vars, x, y, vars->spr_color);
	else
	{
		my_mlx_pixel_put(vars, x, y, vars->void_color);
		//printf("c = %d | x = %d | y = %d c not recognized...\n", c, x , y);
	}
}

void			ft_print_grid(t_cube *cube, t_vars *vars)
{
	int col;
	int row;
	int	case_row;
	int case_col;
	int	map_col;
	int map_row;
	char **map;

	map = cube->map;
	row = 0;
	case_row = 0;
	while ( case_row < cube->max_row && row < vars->win_height )
	{
		case_col = 0;
		col = 0;
		while (case_col < cube->max_col && col < vars->win_width)
		{
			map_row = row / vars->tile_y;
			map_col = col / vars->tile_x;
			//printf("checking map[%d][%d] = [%c]" ,map_row, map_col, map[map_row][map_col]);
			//printf(" p_row = %d | p_col = %d || ", row, col);
			//printf(" p_row = %d | p_col = %d || ", row, col);
			//printf("map[%d][%d]\n", map_row, map_col);
			ft_fill_pixel(col, row, (map[map_row][map_col]), vars);
			col++;
			if (col % vars->tile_y == 0)
				case_col++;
		}
		row++;
		if (row % vars->tile_y == 0)
			case_row++;

	}
}
int             main(int argc, char **argv)
{
	t_cube		cube;
	t_vars		vars;
	char		**problem;
	
	if (argc != 2)
		return (printf("Usage : 1 argument\n"));	
	if (ft_parsing_main(argv[1], &cube))
		return (-1);

	ft_init_game(&cube, &vars);	
	ft_print_grid(&cube, &vars);
	write(1, "grid ok\n", 7);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_loop(vars.mlx);
	ft_free_mapinfo(&cube);
	printf("\nmain --> return (0);\n");
	return (0);
}

void			event_algo(t_vars *vars)
{
	mlx_hook(vars->win, 33, 1L<<17, mlx_loop_end, vars->mlx);	
	write(1, "rentre\n", 8);
	mlx_hook(vars->win, 2, 1L<<0, key_hook,  vars);
	write(1, "sortir\n", 7);
}	


int		key_hook(int keycode, t_vars *vars)
{
	char c;
	int color;

	c = keycode;
	if (keycode == 65307)
		mlx_loop_end(vars->mlx);
	else if (c == 'a' || c == 'd')
	{
		color = create_trgb(0, keycode, keycode, keycode);
		draw_triangle(vars, vars->win_width, vars->win_height, color);
	}
	else if (c == 'w' || c == 's')
	{
		color = 0x00000FF;
		draw_triangle(vars, vars->win_width / 2, vars->win_height / 2, color);
	}
	else
		printf("key_pressed = %d|\n", keycode);
	return (0);
}


int				draw_triangle(t_vars *vars, int x, int y, int color)
{
	int i;
	int mid;
	int offset;

	offset = 0;
	mid = x / 2;
	while (y > 0)
	{
		i = 0;
		printf("h = %d | wi = %d\n", y, x);
		if (x < 0)
			my_mlx_pixel_put(vars, mid, y, 0x000000FF);
		else
		{
			while (i < x)
			{
				my_mlx_pixel_put(vars, i + offset, y, color);
				i++;
			}
			offset++;
			x -= 2;
		}
		y--;
	}
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (1);
}

void            my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	fucking_clean(void	*mlx, void *win)
{
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
}

void			ft_print_tab(char **tab)
{
	int row;
	int col;

	row = 0;
		while (tab[row])
		{
			col = 0;
			printf("row:%d-", row);
			while (tab[row][col])
			{
				printf("|%c", tab[row][col]);
				col++;
			}
			printf("||\n");
			row++;
		}
}

void			ft_init_color(t_cube *cube, t_vars *vars)
{
	vars->floor_color = create_trgb(0, 192, 192, 192);
	vars->play_color = create_trgb(0, 255, 0, 0);
	vars->wall_color = create_trgb(0, 0, 204, 0);
	vars->spr_color = create_trgb(0, 102, 255, 178);
	vars->void_color = create_trgb(0, 255, 255, 255);
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
	vars->tile_x = vars->win_width / cube->max_col; 
	vars->tile_y = vars->win_height / cube->max_row;
	printf("vars->width = %d | vars->height = %d\n", vars->win_width, vars->win_height);

	// Init mlx_instances
	vars->mlx = mlx_init();
	vars->img = mlx_new_image(vars->mlx, vars->win_width, vars->win_height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_len,
                               &vars->endian);
    vars->win = mlx_new_window(vars->mlx, vars->win_width, vars->win_height, "Adrien_cube");
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	printf("X_tile = %d | Y_tile = %d\n", vars->tile_x, vars->tile_y);
}


