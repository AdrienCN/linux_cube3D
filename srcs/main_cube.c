#include "h_cube.h"


#define KEYPRESS	1L<<0
#define KEYRELEASE	1L<<1


int		display_minimap(char *str);

int             main(int argc, char **argv)
{
	t_vars		vars;
	
	if (argc != 2)
		return (printf("Usage : 1 argument\n"));

	if (ft_parsing_main(argv[1], &vars.cube))
		return (-1);
	
	ft_init_game(&vars.cube, &vars);
	write(1,"init ok\n", 8);
	printf("RAY_NUMBER = %f\n", RAY_NUMBER);
	mlx_loop_hook(vars.mlx, ft_update_map, &vars);
	mlx_hook(vars.win, 2, KEYPRESS, ft_update_move, &vars);
	mlx_hook(vars.win, 3, KEYRELEASE, ft_reset_player, &vars);
	mlx_loop(vars.mlx);
	ft_free_mapinfo(&vars.cube);
	printf("\nmain --> return (0);\n");
	return (0);
}

int		ft_update_map(t_vars *vars)
{
	ft_draw_minimap(&vars->cube, vars);
	ft_draw_player(vars);
	ft_cast_all_rays(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}


void	fucking_clean(void	*mlx, void *win)
{
	mlx_destroy_window(mlx, win);
//	mlx_destroy_display(mlx);
	free(mlx);
}
