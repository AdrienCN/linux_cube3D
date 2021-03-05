/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_maze.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:13:14 by calao             #+#    #+#             */
/*   Updated: 2021/03/05 16:21:40 by calao            ###   ########.fr       */
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

t_img	*ft_what_is_texture(t_vars *vars, t_rays ray)
{
	if (ray.hitisvertical)
	{
		if (ray.rayisleft)
			return (&vars->text.west);
		else
			return (&vars->text.east);
	}
	else
	{
		if (ray.rayisup)
			return (&vars->text.north);
		else
			return (&vars->text.south);
	}
}

float	ft_set_x_text(t_rays ray, t_img *w_text)
{
	float x_coord;

	if (ray.hitisvertical)
		x_coord = (((int)ray.wallhity % (int)TILE_SIZE) / TILE_SIZE) 
			* w_text->width;
	else
		x_coord = (((int)ray.wallhitx % (int)TILE_SIZE) / TILE_SIZE) 
			* w_text->width;
	return (x_coord);
}

void	tmp_box(t_vars *vars, t_rays ray, int x, int y, int pos_in_wall)
{
	float x_text;
	float y_text;
	t_img	*text;
	unsigned int color;

	if (ray.wallheight > vars->win_height)
		pos_in_wall += (ray.wallheight - vars->win_height) / 2;
	text = ft_what_is_texture(vars, ray);
	x_text = ft_set_x_text(ray, text);	
	y_text = (((int)pos_in_wall) / ray.wallheight) * text->height;
	color = ft_get_xpm_pixel_value(text, x_text, y_text);
	my_mlx_pixel_put(vars, x, y, color);
}

void	ft_fill_colorbuf(t_vars *vars, t_rays *ray, int *colorbuf)
{
	int y;
	int x;
	float pos_in_wall;
//	int pos;

	x = 0;
	colorbuf[1]= BLUE;
	while (x < vars->ray_num)
	{
		y = 0;
		pos_in_wall = 0;
			//pos = y * vars->win_width + x;
			while (y < ray[x].walluplimit)
			{
				my_mlx_pixel_put(vars, x, y, BLUE);
				y++;
			}
			while (y >= ray[x].walluplimit && y <= ray[x].walldownlimit)
			{
				tmp_box(vars, ray[x], x, y, pos_in_wall);
				y++;
				pos_in_wall++;
			}
			while (y < vars->win_height)
			{
				my_mlx_pixel_put(vars, x, y, GREEN);
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
