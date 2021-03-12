#include "h_cube.h"

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

void			ft_rays_init(t_vars *vars)
{
	int i;

	vars->rays = malloc(sizeof(t_rays) * vars->win_width);
	vars->colorbuf = malloc(sizeof(int) * (vars->win_width * vars->win_height));
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
}
void			ft_text_init(t_vars *vars, t_text *text)
{
	// Assign an Image instance for each text
	text->north.img = mlx_xpm_file_to_image(vars->mlx, vars->cube.north,
				&text->north.width, &text->north.height);
	text->east.img = mlx_xpm_file_to_image(vars->mlx, vars->cube.east,
				&text->east.width, &text->east.height);
	text->south.img = mlx_xpm_file_to_image(vars->mlx, vars->cube.south,
				&text->south.width, &text->south.height);
	text->west.img = mlx_xpm_file_to_image(vars->mlx, vars->cube.west,
				&text->west.width, &text->west.height);
	text->sprite.img = mlx_xpm_file_to_image(vars->mlx, vars->cube.sprite,
				&text->sprite.width, &text->sprite.height);
	// Assign addr for each text & text_img
	text->north.addr = mlx_get_data_addr(text->north.img, &text->north.bpp,
			&text->north.line_len, &text->north.endian);
	text->east.addr = mlx_get_data_addr(text->east.img, &text->east.bpp,
			&text->east.line_len, &text->north.endian);
	text->south.addr = mlx_get_data_addr(text->south.img, &text->south.bpp,
			&text->south.line_len, &text->south.endian);
	text->west.addr = mlx_get_data_addr(text->west.img, &text->west.bpp,
			&text->west.line_len, &text->west.endian);
	text->sprite.addr = mlx_get_data_addr(text->sprite.img, &text->sprite.bpp,
			&text->sprite.line_len, &text->sprite.endian);
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
		

void	ft_init_sprite_array(t_vars *vars, char **map)
{
	int i;
	int j;
	int count;

	vars->sprite_count = ft_count_sprites_in_map(map);
	vars->sprite_tab = malloc(sizeof(t_sprite) * vars->sprite_count);
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
}

void			ft_resolution_init(t_vars *vars, t_cube *cube)
{
	int screen_height;
	int screen_width;

	vars->win_width = cube->r_x;
	vars->win_height = cube->r_y;
	if (vars->bmp_save == 1)
		return;
	else
	{
		mlx_get_screen_size(vars->mlx, &screen_width, &screen_height);
		if (screen_height < cube->r_y)
			vars->win_height = screen_height;
		if (screen_width < cube->r_x)
			vars->win_width = screen_width;
	}
}

void			ft_init_game(t_cube * cube, t_vars *vars)
{
	vars->mlx = mlx_init();
	ft_resolution_init(vars,cube);

	printf("win_width = %d | win_height = %d \n", vars->win_width, vars->win_height);
	// init values
	ft_init_color(cube, vars);
	ft_perso_init(vars);
	ft_rays_init(vars);
	ft_init_sprite_array(vars, vars->cube.map);

	printf("sprite_count = %d\n", vars->sprite_count);
	
	//efface le player de la carte
	cube->map[(int)cube->player_tmp.y][(int)cube->player_tmp.x] = '0';

	// Init mlx_instances
	vars->img = mlx_new_image(vars->mlx, vars->win_width, vars->win_height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_len,
                               &vars->endian);
	if (vars->bmp_save == 0)
	{
		vars->win = mlx_new_window(vars->mlx, vars->win_width, 
			vars->win_height, "Adrien_cube");
	}

	// Init text
	ft_text_init(vars, &vars->text);
}
