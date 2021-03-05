/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_maze.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:13:14 by calao             #+#    #+#             */
/*   Updated: 2021/03/05 13:40:31 by calao            ###   ########.fr       */
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

/*
void	ft_what_is_texture(t_vars *vars, t_rays *ray)
{
	//Choisir texture selon: 
		//is hit_vert ou horz?
		//is ray up / down / left / right ?
}
*/

float	ft_get_x_text_coord(t_img *w_text, int x)
{
	float x_val;

	x_val = (x % (int)TILE_SIZE) * w_text->width;
	return (x_val);
}

float	ft_get_y_text_coord(t_img *w_text, int y)
{
	float y_val;

	y_val = (y % (int)TILE_SIZE) * w_text->height;
	return (y_val);
}

void	ft_draw_wall(t_vars *vars, t_rays ray, float x, float y)
{
	float			x_text;
	float			y_text;
	unsigned int	t_pixel_color;
	t_img			*w_text;

	if (ray.rayisup)
		x_text = 1;
	else
		x_text = 1;
	//final_text = ft_what_is_texture(vars, ray);
	w_text = &vars->text.north;
	x_text = ft_get_x_text_coord(w_text, x);
	y_text = ft_get_y_text_coord(w_text, y);
	
	t_pixel_color = ft_get_xpm_pixel_value(w_text, x_text, y_text);
	my_mlx_pixel_put(vars, x, y, t_pixel_color);
	//vars->colorbuf[y * vars->win_width + x] = t_pixel_color;
}


void	tmp_box(t_vars *vars, t_rays ray, int x, int y, int wall)
{
	float x_text;
	float y_text;
	t_img	*text_img;
	unsigned int color;

	if (ray.hitisvertical)
		text_img = &vars->text.north;
	else
		text_img = &vars->text.south;

	//Chaque tuile contient toute l'image mais n'en display qu'une partie
	//x_text = (ray.wallhitx / TILE_SIZE) * text_img->width;
	//y_text = (y / TILE_SIZE) * text_img->height;
	
	//TUILE MONOCOULEUR DE LA BONNE TEXT
	//x_text = (int)ray.wallhitx % (int)TILE_SIZE / text_img->width;
	//y_text = y % (int)TILE_SIZE / text_img->height;

	//++++ MIEUX. Texture + nuance
	x_text = (((int)ray.wallhitx % (int)TILE_SIZE) / TILE_SIZE) * text_img->width;
	y_text = ((int)wall / TILE_SIZE) * text_img->height;
	// Version de Joann
	/*
	int x_hit;
	x_hit = ray.wallhitx;
	x_text = ((x_hit - (TILE_SIZE * (x_hit / TILE_SIZE))) * (text_img->width / TILE_SIZE));	
	y_text =  (((int)y % (int)TILE_SIZE) / TILE_SIZE) * text_img->height;	
	*/
	color = ft_get_xpm_pixel_value(text_img, x_text, y_text);
	my_mlx_pixel_put(vars, x, y, color);
}

void	ft_fill_colorbuf(t_vars *vars, t_rays *ray, int *colorbuf)
{
	float y;
	float x;
	float wallheight;
//	int pos;

	x = 0;
	while (x < vars->ray_num)
	{
		y = 0;
		wallheight = 0;
			//pos = y * vars->win_width + x;
			while (y < ray[(int)x].walluplimit)
			{
				my_mlx_pixel_put(vars, x, y, BLUE);
				colorbuf[1]= BLUE;
				y++;
			}
			while (y >= ray[(int)x].walluplimit 
					&& y <= ray[(int)x].walldownlimit)
			{
					tmp_box(vars, ray[(int)x], x, y, wallheight);
					y++;
					wallheight++;
					//ft_draw_wall(vars, ray[(int)x], x, y);
			}
			while (y > ray[(int)x].walldownlimit && y < vars->win_height)
			{
				my_mlx_pixel_put(vars, x, y, GREEN);
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
