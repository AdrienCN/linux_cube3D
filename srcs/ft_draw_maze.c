/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_maze.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:13:14 by calao             #+#    #+#             */
/*   Updated: 2021/03/05 11:08:34 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void	ft_clear_colorbuf_to_color(t_vars *vars, int *colorbuf, int color)
{
	int x;
	int y;
	int i;

	x = 0;
	i = 0;
	while (x < vars->win_width)
	{
		y = 0;
		while (y < vars->win_height)
		{
			i = y * vars->win_width + x;
			colorbuf[i] = color;
			//printf("i = %d\n", i);
			y++;
		}
		x++;
	}
}

void	ft_display_color_buffer(int *colorbuf, t_vars *vars)
{
	int x;
	int y;
	int color;
	int i;

	x = 0;
	while (x < vars->win_width)
	{
		y = 0;
		while (y < vars->win_height)
		{
			i = y * vars->win_width + x;
			color = colorbuf[i];
			//printf("i = %d | color = %u\n", i, color);
			my_mlx_pixel_put(vars, x, y, color);
		   y++;
		}
		x++;
	}
}

void	ft_what_is_texture(t_vars *vars, t_rays *ray)
{
	//Choisir texture selon: 
		//is hit_vert ou horz?
		//is ray up / down / left / right ?
}



void	ft_draw_wall(t_vars *vars, int x, int x, t_rays *ray)
{
	int				x_text;
	int				y_text;
	unsigned int	t_pixel_color;
	t_img			*final_text;

	//final_text = ft_what_is_texture(vars, ray + x);
	final_text = vars->text.north;
	x_text = ft_get_x_text_coord(vars, final_text, x, y);
	y_text = ft_get_y_text_coord(vars, final_text, x, y);
	
	t_pixel_color = ft_get_xpm_pixel_value(final_text, x_text, y_text);
	my_mlx_pixel_put(vars, x, y, t_pixel_color)
	//vars->colorbuf[y * vars->win_width + x] = t_pixel_color;
}

void	ft_fill_colorbuf(t_vars *vars, t_rays *ray, int *colorbuf)
{
	int y;
	int x;
	float x_text;
	float y_text;
//	int pos;

	x = 0;
	while (x < vars->ray_num)
	{
		y = 0;
		while (y < vars->win_height)
		{
			//pos = y * vars->win_width + x;
			if (y <	ray[x].walluplimit)
				my_mlx_pixel_put(vars, i, y, BLUE);
				//colorbuf[pos]= BLUE;
			else if (y >= ray[x].walluplimit && y <= ray[x].walldownlimit)
				ft_draw_wall(vars, ray, x, y)
			else if (y > ray[x].walldownlimit)
				my_mlx_pixel_put(vars, i, y, GREEN);
				//colorbuf[pos] = GREEN;
			y++;
		}
		x++;
	}
}

void	ft_draw_maze(t_vars *vars)
{
	//printf("colorbuf[%d]\n", vars->win_width * vars->win_height);
	ft_clear_colorbuf_to_color(vars, vars->colorbuf, RED);
	//printf("clearing... done\n");
	ft_fill_colorbuf(vars, vars->rays, vars->colorbuf);
	//printf("filling done\n");
	//ft_display_color_buffer(vars->colorbuf, vars);
	//printf("display done...\n");
}
