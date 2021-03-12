#include "h_cube.h"

void	ft_perso_init(t_vars *vars)
{
	char compass;
	float angle;
	
	vars->player.cardinal = vars->cube.player_tmp.cardinal;
	compass =  vars->player.cardinal;
	vars->player.hze_walk = 0;
	vars->player.vert_walk = 0;
	vars->player.turn = 0;
	vars->player.exit = 0;
	if (compass == 'N')
		angle = M_PI / 2;
	else if (compass == 'W')
		angle = M_PI;
	else if (compass == 'S')
		angle = (3 * M_PI) / 2;
	else 
		angle = 0.0;
	vars->player.angle = angle;
	vars->player.x = TILE_SIZE * vars->cube.player_tmp.x + TILE_SIZE  / 2;
	vars->player.y = TILE_SIZE * vars->cube.player_tmp.y + TILE_SIZE / 2;
}

int			ft_rays_init(t_vars *vars)
{
	int i;

	vars->rays = malloc(sizeof(t_rays) * vars->win_width);
	if (vars->rays == NULL)
		return (1);
	vars->ray_num = vars->win_width;

	// Corriger cette valeur 
	vars->ray_increment = FOV / vars->ray_num;
	i = 0;
	while (i < vars->ray_num)
	{	
		vars->rays[i].angle = 0;
		vars->rays[i].wallhitx = 0;
		vars->rays[i].wallhity = 0;
		vars->rays[i].distance = 0;
		vars->rays[i].hitisvertical = 0;
		vars->rays[i].rayisup = 0;
		vars->rays[i].rayisdown = 0;
		vars->rays[i].rayisleft = 0;
		vars->rays[i].rayisright = 0;
		i++;
	}
	return (0);
}

int			ft_init_xpm_img(t_vars *vars, t_img *img, char *img_path)
{
	img->img = mlx_xpm_file_to_image(vars->mlx, img_path,
				&img->width, &img->height);
	if (img->img == NULL)
		return (1);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, 
			&img->line_len, &img->endian);
	if (img->addr == NULL)
		return (1);
	return (0);
}

int			ft_text_init(t_vars *vars, t_text *text)
{
	if (ft_init_xpm_img(vars, &text->north, vars->cube.north)
			|| ft_init_xpm_img(vars, &text->east, vars->cube.east)
			|| ft_init_xpm_img(vars, &text->south, vars->cube.south)
			|| ft_init_xpm_img(vars, &text->west, vars->cube.west)
			|| ft_init_xpm_img(vars, &text->sprite, vars->cube.sprite))
		return (1);
	return (0);
}

int				ft_count_sprites_in_map(char **map)
{
	int i;
	int j;
	int sprites_found;

	i = 0;
	sprites_found = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				sprites_found++;
			j++;
		}
		i++;
	}
	return (sprites_found);
}

void	ft_set_sprite_val(t_sprite *sprite, int i, int j)
{
				sprite->id = 2;
				sprite->is_visible = 0;
				sprite->dist = -1;
				sprite->row = i;
				sprite->col = j;
				sprite->x = j * TILE_SIZE + (TILE_SIZE / 2);
				sprite->y = i * TILE_SIZE + (TILE_SIZE / 2);
				//printf("sprite_tab[%d]->row = %d | col = %d", count + 1, i, j);
				//printf("|y  = %f | x = %f\n", sprite_tab[count].y,
				//		sprite_tab[count].x);
				//		
}
		

int		ft_init_sprite(t_vars *vars, char **map)
{
	int i;
	int j;
	int count;

	//vars->sprite_count = ft_count_sprites_in_map(map);
	vars->sprite_count = vars->cube.sprite_count;
	vars->sprite_tab = malloc(sizeof(t_sprite) * vars->sprite_count);
	if (vars->sprite_tab == NULL)
		return (1);
	i = 0;
	count = 0;
	while (map[i] && count < vars->sprite_count)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				ft_set_sprite_val(&vars->sprite_tab[count], i, j);
				count++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void			ft_resolution_init(t_vars *vars, t_cube *cube)
{
	int screen_height;
	int screen_width;

	vars->win_width = cube->r_x;
	vars->win_height = cube->r_y;
	if (vars->bmp_save == 0)
	{
		mlx_get_screen_size(vars->mlx, &screen_width, &screen_height);
		if (screen_height < cube->r_y)
			vars->win_height = screen_height;
		if (screen_width < cube->r_x)
			vars->win_width = screen_width;
	}
	printf("win_width = %d | win_height = %d \n", vars->win_width, 
			vars->win_height);
}

int				ft_set_basic_vars_val(t_vars *vars, t_cube *cube)
{
	//verifier que la resolution rentre dans l'ecran
	ft_resolution_init(vars,cube);
	// Mettre vrai valeur pour MINIMAP
	vars->player_color = BLUE;
	vars->wall_color = GREEN;
	vars->sprite_color = ORANGE;
	vars->void_color = BLACK;
	vars->ceil_color = create_trgb(0, cube->ceil.r, cube->ceil.g, cube->ceil.b);
	vars->floor_color = create_trgb(0, cube->floor.r, 
			cube->floor.g, cube->floor.b);
	ft_perso_init(vars);
	cube->map[(int)cube->player_tmp.y][(int)cube->player_tmp.x] = '0';
	if (ft_rays_init(vars)
			|| ft_init_sprite(vars, vars->cube.map)
			||ft_text_init(vars, &vars->text))
		return (1);
	return (0);
}

void			ft_game_null_init(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->rays = NULL;
	vars->sprite_tab = NULL;
	vars->game.addr = NULL;
	vars->game.img = NULL;
	vars->text.north.addr = NULL;
	vars->text.north.img = NULL;
	vars->text.east.addr = NULL;
	vars->text.east.img = NULL;
	vars->text.south.addr = NULL;
	vars->text.south.img = NULL;
	vars->text.west.addr = NULL;
	vars->text.west.img = NULL;
	vars->text.sprite.addr = NULL;
	vars->text.sprite.img = NULL;
	ft_cube_null_init(&vars->cube);
}

int				ft_init_game(t_cube * cube, t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		return (1);
	// init values
	if (ft_set_basic_vars_val(vars, cube))
		return (1);
	vars->game.img = mlx_new_image(vars->mlx, vars->win_width, vars->win_height);
	if (vars->game.img == NULL)
		return (1);
	vars->game.addr = mlx_get_data_addr(vars->game.img, &vars->game.bpp, &vars->game.line_len,
                               &vars->game.endian);
	if (vars->game.addr == NULL)
		return (1);
	if (vars->bmp_save == 0)
	{
		vars->win = mlx_new_window(vars->mlx, vars->win_width, 
			vars->win_height, "Adrien_cube");
		if (vars->win == NULL)
			return (1);
	}
	return (0);
}
