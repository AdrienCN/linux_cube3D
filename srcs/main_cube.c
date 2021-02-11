#include "h_cube.h"

#define BLACK 0x00000000
#define RED	  0x00FF0000
#define STEP_LEN 1
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
	int		tile_width;
	int		tile_height;
	int		play_color;
	int		wall_color;
	int		floor_color;
	int		ceil_color;
	int		spr_color;
	int		void_color;
}					t_vars;

int				key_hook(int keycode, t_cube *cube);
void			ft_init_game(t_cube * cube, t_vars *vars);
void			ft_init_color(t_cube *cube, t_vars *vars);
void            my_mlx_pixel_put(t_vars *data, int x, int y, int color);
int				create_trgb(int t, int r, int g, int b);
void			ft_print_tab(char **tab);
int				ft_update_map(int keycode, t_cube *cube);

void			ft_fill_pixel(int x, int y, char c, t_vars *vars)
{
	if (y % vars->tile_height == 0 || x % vars->tile_width == 0)
	{
		my_mlx_pixel_put(vars, x, y, BLACK);
		return;
	}
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
	int pixel_x;
	int pixel_y;
	int	map_col;
	int map_row;
	char **map;

	map = cube->map;
	pixel_y = 0;
	map_row = 0;
	map_col = 0;
	while (map_row < cube->max_row && pixel_y < vars->win_height )
	{
		pixel_x = 0;
		map_col = 0;
		while (map_col < cube->max_col && pixel_x < vars->win_width)
		{
			ft_fill_pixel(pixel_x, pixel_y, (map[map_row][map_col]), vars);
			map_col = pixel_x / vars->tile_width;
			pixel_x++;
		}
	//	printf("map[%d][%d]\n", map_row, map_col);
		pixel_y++;
		map_row = pixel_y / vars->tile_height;
	}
	printf("max_pixel_Y = %d | max_pixel_X = %d\n", pixel_y, pixel_x);
}

void			ft_print_square(t_vars *vars, int p_y, int p_x, int hei, int wid)
{
	int i;
	int j;

	i = 0;
	while (i < hei)
	{
		j = 0;
		while (j < wid)
		{
			my_mlx_pixel_put(vars, p_x + j, p_y + i, RED);
			j++;
		}
		i++;
	}
}

void			ft_print_player(t_cube *cube, t_vars *vars)
{
	int square_h;
	int square_w;
	int middle_y;
	int middle_x;
	square_h = vars->tile_height;
	square_w = vars->tile_width;
	middle_y = cube->player.y;
	middle_x = cube->player.x;
	ft_print_square(vars, middle_y, middle_x, square_h, square_w);
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
	ft_print_grid(&cube, &vars);
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
	if ((y > vars->win_height || y < 0) 
			|| (x > vars->win_width || x < 0)) 
			 //*cube->map[row][col] != '0')
	{
		printf("***BOUNDARIES LIMIT***\n");
		return (1);
	}
	w = x + vars->tile_width;
	z = y + vars->tile_height;
	printf("player x = %d | player y = %d\n", x, y);
	printf("player w = %d | player z = %d\n", w, z);


	row = y / vars->tile_height;
	col = x / vars->tile_width;
	if ((z < vars->win_height || y < 0) 
			|| (w < vars->win_width || x < 0)) 
			//|| cube->map[row][col] != '0')
	{

		printf("__***BOUNDARIES LIMIT***__:\n");
		printf("map[%d][%d] = [%c]\n", row, col, cube->map[row][col]);

		return (1);
	}
	cube->player.x += cube->player.a_d;
	cube->player.y += cube->player.w_s;
	printf("player x = %d | player y = %d\n", cube->player.x, cube->player.y);
	printf("player w = %d | player z = %d\n", w, z);
	return (0);
}

int		ft_update_map(int keycode, t_cube *cube)
{
	t_vars *vars;
	vars = cube->cpy_vars;
	ft_print_grid(cube, cube->cpy_vars);
	ft_print_player(cube, cube->cpy_vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	cube->player.a_d = 0;
	cube->player.w_s = 0;
	return (0);
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
			printf("row:%3d", row);
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


