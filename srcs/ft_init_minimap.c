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
	if (compass == 'N')
		angle = M_PI / 2;
	else if (compass == 'W')
		angle = M_PI;
	else if (compass == 'S')
		angle = (3 * M_PI) / 2;
	else 
		angle = 0.0;
	vars->player.angle = angle;
	vars->player.x = vars->tile_width * vars->cube.player_tmp.x + vars->tile_width  / 2;
	vars->player.y = vars->tile_height * vars->cube.player_tmp.y + vars->tile_height / 2;
}

void			ft_rays_init(t_vars *vars)
{
	int i;

	i = 0;
	while (i < (int)RAY_NUMBER)
	{	
		vars->rays[i].angle = 0;
		vars->rays[i].wallHitX = 0;
		vars->rays[i].wallHitY = 0;
		vars->rays[i].distance = 0;
		vars->rays[i].HitIsVertical = 0;
		vars->rays[i].RayIsUp = 0;
		vars->rays[i].RayIsDown = 0;
		vars->rays[i].RayIsLeft = 0;
		vars->rays[i].RayIsRight = 0;
		vars->rays[i].HitContent = 0;
		i++;
	}
}

void			ft_init_game(t_cube * cube, t_vars *vars)
{
	vars->win_height = cube->r_y ;
	vars->win_width = cube->r_x ;
	vars->tile_width = vars->win_width / cube->max_col;
	vars->tile_height = vars->win_height / cube->max_row;

	// Get color
	ft_init_color(cube, vars);
	ft_perso_init(vars);
	ft_rays_init(vars);
	
	//Get grid proportions
	printf("vars->width = %f | vars->height = %f\n", vars->win_width, vars->win_height);
	//efface le player de la carte
	cube->map[(int)cube->player_tmp.y][(int)cube->player_tmp.x] = '0';
	// Init mlx_instances
	vars->mlx = mlx_init();
	vars->img = mlx_new_image(vars->mlx, vars->win_width, vars->win_height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_len,
                               &vars->endian);
    vars->win = mlx_new_window(vars->mlx, vars->win_width, vars->win_height, "Adrien_cube");
	printf("X_tile = %f | Y_tile = %f\n", vars->tile_width, vars->tile_height);
}
