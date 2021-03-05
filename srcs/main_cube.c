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
	printf("Init ok\n");
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

unsigned int	ft_get_xpm_pixel_value(t_img *img, int x, int y)
{
	char *dst;

	dst = img->addr + (y * img->line_len) + (x * 4);
	return (*(unsigned*)dst);
}


void	ft_draw_text_to_box(t_vars *vars, t_img *text_img,
	   	int t_width, int t_height)
{
	float x;
	float y;
	float x_text;
	float y_text;
	unsigned int color;

	x = 0;
	while (x < vars->win_width)
	{
		y = 0;
		while (y < vars->win_height)
		{
			x_text = (x / vars->win_width) * t_width;
			y_text = (y / vars->win_height) * t_height;
			color = ft_get_xpm_pixel_value(text_img, x_text, y_text);
			my_mlx_pixel_put(vars, x, y, color);
			y++;
		}
		x++;
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

//	ft_draw_text_to_box(vars, &vars->text.north, vars->text.north.width, vars->text.north.height);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}


void	fucking_clean(void	*mlx, void *win)
{
	mlx_destroy_window(mlx, win);
//	mlx_destroy_display(mlx);
	free(mlx);
}
