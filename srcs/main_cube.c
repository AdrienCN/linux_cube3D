#include "h_cube.h"


#define KEYPRESS	1L<<0
#define KEYRELEASE	1L<<1


int		display_minimap(char *str);

void	ft_dda(t_vars *vars, t_rays ray, float x1, float y1)
{
	int delta_x;
	int delta_y;
	int x2;
	int y2;
	int side_l;
	int i;
	float x_inc;
	float y_inc;
	float cur_x;
	float cur_y;

	x2 = ray.wallhitx;
	y2 = ray.wallhity;
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	cur_x = x1;
	cur_y = y1;
	if (delta_x >= delta_y)
		side_l = delta_x;
	else
		side_l = delta_y;
	if (side_l < 0)
		side_l = -side_l;
	x_inc = delta_x / (float)side_l;
	y_inc = delta_y / (float)side_l;
	i = 0;
	while (i <= side_l)
	{
		if (ft_is_sprite(cur_x, cur_y, vars))
				break;
		my_mlx_pixel_put(vars, round(cur_x) * MINIMAP_SCALE, round(cur_y) * MINIMAP_SCALE, RED);
		cur_x += x_inc;
		cur_y += y_inc;
		i++;
	}
}

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
		//SEUL qui fonctionne
	//	ft_cast_single_ray(x, y, vars, vars->rays[i].angle);
	
		// Fonctionne mais apparence etrange sur cadran sup et gauche	
		ft_dda(vars, vars->rays[i], x, y);
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
	
	// draw 3D cube with my_mlx_pixel_put
	//ft_draw_maze(vars);

	// Draw minimap + rays
	ft_draw_minimap(&vars->cube, vars);
	ft_draw_all_rays(vars);
	ft_draw_player(vars);
	
	// Draw 3d cube with color buffer
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
