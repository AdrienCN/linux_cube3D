/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:13:14 by calao             #+#    #+#             */
/*   Updated: 2021/03/04 13:46:08 by calao            ###   ########.fr       */
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

void	ft_fill_colorbuf(t_vars *vars, t_rays *ray, int *colorbuf)
{
	int y;
	int i;

	i = 0;
	// distance ecran aka projectionplane (en radiant?)
	while (i < vars->ray_num)
	{
		//Remplir buffer par colonne
			y = 0;
			while (y < vars->win_height)
			{
				//Remplir couleur de plafond si y < limit sup mur
				if (y <	ray[i].walluplimit)
				{
					//my_mlx_pixel_put(vars, i, y, BLUE);
					colorbuf[y * vars->win_width + i] = BLUE;
				}
				//Remplir couleur de mur si y > limit sup mur && y < limit inf
				else if (y >= ray[i].walluplimit 
						&& y <= ray[i].walldownlimit)
				{
					if (ray[i].hitisvertical)
						colorbuf[y * vars->win_width + i] = WHITE;
						//my_mlx_pixel_put(vars, i, y, WHITE);
					else
						//my_mlx_pixel_put(vars, i, y, GREY);
					colorbuf[y * vars->win_width + i] = GREY;
				}
				else if (y > ray[i].walldownlimit)
				{
					//my_mlx_pixel_put(vars, i, y, GREEN);
					colorbuf[y * vars->win_width + i] = GREEN;
				}
				y++;
			}
		i++;
	}
}

void	ft_draw_maze(t_vars *vars)
{
	//printf("colorbuf[%d]\n", vars->win_width * vars->win_height);
	ft_clear_colorbuf_to_color(vars, vars->colorbuf, RED);
	//printf("clearing... done\n");
	ft_fill_colorbuf(vars, vars->rays, vars->colorbuf);
	//printf("filling done\n");
	ft_display_color_buffer(vars->colorbuf, vars);
	//printf("display done...\n");
}
