#include "h_cube.h"


#define KEYPRESS	1L<<0
#define KEYRELEASE	1L<<1


int		display_minimap(char *str);
/*
void	ft_init_tmp(t_vars *tmp, t_vars *vars)
{
	tmp->win_height = vars->win_height;
	tmp->win_width = vars->win_width;
	tmp->mlx = mlx_init();
	tmp->img = mlx_new_image(tmp->mlx, tmp->win_width, tmp->win_height);
	tmp->addr = mlx_get_data_addr(tmp->img, &tmp->bpp, &tmp->line_len, &tmp->endian);
	tmp->win = mlx_new_window(tmp->mlx, tmp->win_width, tmp->win_height, "minimap");
}
*/

int             main(int argc, char **argv)
{
	t_vars		vars;
//	t_vars		tmp;
	
	if (argc != 2)
		return (printf("Usage : 1 argument\n"));

	if (ft_parsing_main(argv[1], &vars.cube))
		return (-1);
	ft_init_game(&vars.cube, &vars);
	//ft_init_tmp(tmp, vars);
	write(1,"init ok\n", 8);
	mlx_loop_hook(vars.mlx, ft_update_screen, &vars);
	mlx_hook(vars.win, 2, KEYPRESS, ft_update_move, &vars);
	mlx_hook(vars.win, 3, KEYRELEASE, ft_reset_player, &vars);
	mlx_loop(vars.mlx);
	ft_free_mapinfo(&vars.cube);
	printf("\nmain --> return (0);\n");
	return (0);
}

void	ft_draw_all_rays(t_vars *vars)
{
	int i;
	float x;
	float y;

	i = 0;
	x = vars->player.x;
	y = vars->player.y;

	while (i < vars->ray_num)
	{
		ft_cast_single_ray(x, y, vars, vars->rays[i].angle);
		i++;
	}
}

int		ft_update_screen(t_vars *vars)
{
	ft_cast_all_rays(vars);
	ft_draw_maze(vars);
/*	
	ft_draw_minimap(&vars->cube, vars);
	ft_draw_all_rays(vars);
	ft_draw_player(vars);
*/	
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}


void	fucking_clean(void	*mlx, void *win)
{
	mlx_destroy_window(mlx, win);
//	mlx_destroy_display(mlx);
	free(mlx);
}
