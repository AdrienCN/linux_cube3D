#include "h_cube.h"


#define KEYPRESS	1L<<0
#define KEYRELEASE	1L<<1


int             main(int argc, char **argv)
{
	t_vars		vars;
	
	if (argc != 2)
		return (printf("Usage : 1 argument\n"));

	if (ft_parsing_main(argv[1], &vars.cube))
		return (-1);
	ft_init_game(&vars.cube, &vars);
	printf("Init ok\n");

	mlx_loop_hook(vars.mlx, ft_update_screen, &vars);
	mlx_hook(vars.win, 2, KEYPRESS, ft_update_move, &vars);
	mlx_hook(vars.win, 3, KEYRELEASE, ft_reset_player, &vars);
	mlx_loop(vars.mlx);
	
	ft_free_mapinfo(&vars.cube);
	printf("\nmain --> return (0);\n");
	return (0);
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
