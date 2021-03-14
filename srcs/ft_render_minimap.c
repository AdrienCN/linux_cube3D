/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:54:31 by calao             #+#    #+#             */
/*   Updated: 2021/03/14 12:32:31 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

static	int			ft_render_tile_color(float x, float y, char c)
{
	int		test;
	int		color;

	test = TILE_SIZE * MINIMAP_SCALE;
	if ((int)y % test == 0)
		color = BLACK;
	else if ((int)x % test == 0)
		color = BLACK;
	else if (c == ' ')
		color = WHITE;
	else if (c == '0')
		color = WHITE;
	else if (c == '1')
		color = GREEN;
	else if (ft_isbase(c, "NESW"))
		color = BLUE;
	else if (c == '2')
		color = RED;
	else
		color = GREY;
	return (color);
}

static	void		ft_render_grid(t_cube cube, t_vars *vars, char **map)
{
	float	x;
	float	y;
	float	map_col;
	float	map_row;
	int		color;

	y = 0;
	map_row = 0;
	map_col = 0;
	while (map_row < cube.max_row && y < vars->win_height)
	{
		x = 0.0;
		map_col = 0.0;
		while (map_col < cube.max_col && x < vars->win_width)
		{
			color = ft_render_tile_color(x * MINIMAP_SCALE,
					y * MINIMAP_SCALE,
					(map[(int)map_row][(int)map_col]));
			my_mlx_pixel_put(vars, x * MINIMAP_SCALE, y * MINIMAP_SCALE, color);
			map_col = x / TILE_SIZE;
			x++;
		}
		y++;
		map_row = y / TILE_SIZE;
	}
}

static	void		ft_render_player(t_vars *vars)
{
	float	y;
	float	x;
	int		i;
	int		j;

	y = (vars->player.y - TILE_SIZE / 2) * MINIMAP_SCALE;
	x = (vars->player.x - TILE_SIZE / 2) * MINIMAP_SCALE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(vars, x + j * MINIMAP_SCALE,
					y + i * MINIMAP_SCALE, BLUE);
			j++;
		}
		i++;
	}
}

void				ft_render_all_rays(t_vars *vars)
{
	int		i;
	float	x;
	float	y;

	i = 0;
	x = vars->player.x;
	y = vars->player.y;
	while (i < vars->ray_num)
	{
		ft_render_line_gpetit(vars, vars->rays[i].angle, x, y);
		i++;
	}
}

void				ft_render_minimap(t_vars *vars)
{
	char	**map;

	map = vars->cube.map;
	ft_render_grid(vars->cube, vars, map);
//	ft_render_all_rays(vars);
	ft_render_player(vars);
}
