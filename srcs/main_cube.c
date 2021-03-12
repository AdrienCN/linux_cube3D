#include "h_cube.h"


#define KEYPRESS	1L<<0
#define KEYRELEASE	1L<<1

void	ft_render_bmp_file(t_vars *vars);

int				ft_parsing_args(t_vars *vars, int argc, char **argv)
{
	vars->bmp_save = 0;
	if (argc < 2 || argc > 3)
	{
		printf("Usage : 1 or 2 arguments\n");
		return (1);
	}
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save") != 0)
		{
			printf("Error: second argument must be \"--save\"\n");
			return (1);
		}
		vars->bmp_save = 1;
	}
	return (0);
}

int             main(int argc, char **argv)
{
	t_vars		vars;
	
	if (ft_parsing_args(&vars, argc, argv))
		return (-1);
	if (ft_parsing_main(argv[1], &vars.cube)
			|| ft_init_game(&vars.cube, &vars))
	{
		// add free cube_struct
		// free init game
		return (-1);
	}
	
	printf("Init ok\n");

	if (vars.bmp_save)
	{
		ft_render_bmp_file(&vars);
		// Free bmp only stuff
	}
	else
	{

		mlx_loop_hook(vars.mlx, ft_update_screen, &vars);
		mlx_hook(vars.win, 2, KEYPRESS, ft_update_move, &vars);
		mlx_hook(vars.win, 3, KEYRELEASE, ft_reset_player, &vars);
		mlx_loop(vars.mlx);
		//Free game loop only stuff
	}

	// Free common stuff
	ft_free_mapinfo(&vars.cube);
	printf("\nmain --> return (0);\n");
	return (0);
}

void	ft_render_bmp_file(t_vars *vars)
{
	ft_cast_all_rays(vars);
	ft_render_walls(vars, vars->rays);
	ft_render_sprite(vars);
	ft_save_bmp(vars);	
	// Draw minimap + rays
	//ft_render_minimap(vars);
}

int		ft_update_screen(t_vars *vars)
{
	ft_cast_all_rays(vars);
	
	// draw 3D cube with my_mlx_pixel_put
	ft_render_walls(vars, vars->rays);

	ft_render_sprite(vars);
	
	// Draw minimap + rays
	//ft_render_minimap(vars);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	ft_reset_sprites_visibility(vars, vars->sprite_count);
	return (0);
}


void	fucking_clean(void	*mlx, void *win)
{
	mlx_destroy_window(mlx, win);
//	mlx_destroy_display(mlx);
	free(mlx);
}
