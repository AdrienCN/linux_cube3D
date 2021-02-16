/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:54:31 by calao             #+#    #+#             */
/*   Updated: 2021/02/16 14:16:45 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void			ft_draw_minimap(t_cube *cube, t_vars *vars)
{
	int pixel_x;
	int pixel_y;
	int	map_col;
	int map_row;
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
			ft_choose_tile_color(pixel_x, pixel_y, (map[map_row][map_col]), vars);
			map_col = pixel_x / vars->tile_width;
			pixel_x++;
		}
	//	printf("map[%d][%d]\n", map_row, map_col);
		pixel_y++;
		map_row = pixel_y / vars->tile_height;
	}
	printf("max_pixel_X = %d | max_pixel_Y = %d\n", pixel_x, pixel_y);
}

void			ft_draw_player(t_cube *cube, t_vars *vars)
{
	int square_h;
	int square_w;
	int middle_y;
	int middle_x;
	square_h = vars->tile_height;
	square_w = vars->tile_width;
	middle_y = cube->player.y;
	middle_x = cube->player.x;
	ft_draw_square(vars, middle_y, middle_x, square_h, square_w);
}

void			ft_choose_tile_color(int x, int y, char c, t_vars *vars)
{
	if (y % vars->tile_height == 0 || x % vars->tile_width == 0)
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
