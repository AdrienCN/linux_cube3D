/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:54:31 by calao             #+#    #+#             */
/*   Updated: 2021/03/01 13:54:00 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void			ft_draw_minimap(t_cube *cube, t_vars *vars)
{
	int pixel_x;
	int pixel_y;
	float map_col;
	float  map_row;
	char **map;

	map = cube->map;
	pixel_y = 0;
	map_row = 0;
	map_col = 0;
	while (map_row < cube->max_row && pixel_y < vars->win_height )
	{
		pixel_x = 0;
		map_col = 0;
		while (map_col < cube->max_col && pixel_x < vars->win_width)
		{
			ft_choose_tile_color(pixel_x, pixel_y, (map[(int)map_row][(int)map_col]), vars);
			map_col = (float)pixel_x / (float)vars->tile_width;
			pixel_x++;
		}
	//	printf("map[%d][%d]\n", map_row, map_col);
		pixel_y++;
		map_row = (float)pixel_y / (float)vars->tile_height;
	}
	//printf("max_pixel_X = %d | max_pixel_Y = %d\n", pixel_x, pixel_y);
}

void			ft_draw_player(t_vars *vars)
{
	int square_h;
	int square_w;
	int start_y;
	int start_x;
	square_h = vars->tile_height / 2;
	square_w = vars->tile_width / 2;
	start_y = (vars->player.y - vars->tile_height / 4);
	start_x = (vars->player.x - vars->tile_width / 4);
	/*
	start_y = vars->player.y;
	start_x = vars->player.x;
	*/
	ft_draw_square(vars, start_y, start_x, square_h, square_w);
}

void		ft_draw_ray_projection(t_vars *vars)
{	
	float x;
	float y;
	float r;
	float fov_start;
	int i;

	fov_start = ft_radconvert(vars->player.angle) - ft_radconvert(FOV) / 2;
	// fov_start = pikuma RayAngle ? 
	i = 0;
	while  (i < RAY_NUMBER)
	{
		r = 0;
		x = vars->player.x;
		y = vars->player.y;
		//Draw line if RAY_HIT is IN maplimit AND NOT in WALL
		while (!ft_is_maplimit(x, y, vars) && !ft_map_content(x, y, vars))
		{
			my_mlx_pixel_put(vars, x, y, RED);
			x = vars->player.x + cos(vars->player.angle + fov_start) * r;
			y = vars->player.y - sin(vars->player.angle + fov_start) * r;
			r += RAY_STEP;
		}
		i++;
		// RAY_NUMBER = decalage d'angle entre chaque rayon
		fov_start += ft_radconvert(RAY_ANGLE);
	}
}

void			ft_choose_tile_color(float x, float y, char c, t_vars *vars)
{
	if ((int)y % (int)vars->tile_height == 0 || (int)x % (int)vars->tile_width == 0)
	{
		my_mlx_pixel_put(vars, x, y, BLACK);
		return;
	}
	if (c == ' ')
		my_mlx_pixel_put(vars, x, y, vars->void_color);
	else if (c == '0')
		my_mlx_pixel_put(vars, x, y, vars->floor_color);
	else if (c == '1')
		my_mlx_pixel_put(vars, x, y, vars->wall_color);
	else if (ft_isbase(c, "NESW"))
		my_mlx_pixel_put(vars, x, y, vars->player_color);
	else if (c == '2')
		my_mlx_pixel_put(vars, x, y, vars->sprite_color);
	else
		my_mlx_pixel_put(vars, x, y, vars->void_color);
}
