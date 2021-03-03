/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:54:31 by calao             #+#    #+#             */
/*   Updated: 2021/03/03 04:54:28 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void			ft_draw_minimap(t_cube *cube, t_vars *vars)
{
	float pixel_x;
	float pixel_y;
	float map_col;
	float  map_row;
	char **map;

	map = cube->map;
	pixel_y = 0.0;
	map_row = 0.0;
	map_col = 0.0;
	while (map_row < cube->max_row && pixel_y < vars->win_height)
	{
		pixel_x = 0.0;
		map_col = 0.0;
		while (map_col < cube->max_col && pixel_x < vars->win_width)
		{
			ft_draw_tile(pixel_x * MINIMAP_SCALE, pixel_y * MINIMAP_SCALE,
				   (map[(int)map_row][(int)map_col]), vars);
			map_col = pixel_x / TILE_SIZE;
			pixel_x++;
		}
		pixel_y++;
		map_row = pixel_y / TILE_SIZE;
	}
}

void			ft_draw_player(t_vars *vars)
{
	int square_h;
	int square_w;
	int start_y;
	int start_x;
	square_h = (TILE_SIZE / 2) * MINIMAP_SCALE;
	square_w = (TILE_SIZE / 2) * MINIMAP_SCALE;
	start_y = (vars->player.y - TILE_SIZE / 4) * MINIMAP_SCALE;
	start_x = (vars->player.x - TILE_SIZE / 4) * MINIMAP_SCALE;
	ft_draw_square(vars, start_y, start_x, square_h, square_w, BLUE);
}

void			ft_draw_tile(float x, float y, char c, t_vars *vars)
{
	int test;

	test = TILE_SIZE * MINIMAP_SCALE;
	if ((int)y % test == 0)
		my_mlx_pixel_put(vars, x, y, BLACK);
	else if ((int)x % test == 0)
		my_mlx_pixel_put(vars, x, y, BLACK);
	else if (c == ' ')
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
