/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:54:31 by calao             #+#    #+#             */
/*   Updated: 2021/03/14 21:34:27 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

static	int			ft_render_tile_color(char c)
{
	int		color;

	if (c == ' ')
		color = GREEN;
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

static	void		ft_render_player(t_vars *vars, int map_tile)
{
	float	y;
	float	x;
	int		i;
	int		j;
	float	ratio;

	ratio = map_tile / TILE_SIZE;
	y = (vars->player.y * ratio - map_tile / 2);
	x = (vars->player.x * ratio - map_tile / 2);
	i = 0;
	while (i < map_tile)
	{
		j = 0;
		while (j < map_tile)
		{
			my_mlx_pixel_put(vars, x + j,
					y + i, BLUE);
			j++;
		}
		i++;
	}
}

static	void		ft_render_grid(t_cube cube, t_vars *vars,
						char **map, int map_tile)
{
	float	x;
	float	y;
	float	col_count;
	float	row_count;
	int		color;

	y = 0;
	row_count = 0;
	while (row_count < cube.max_row && y < map_tile * cube.max_row)
	{
		x = 0.0;
		col_count = 0.0;
		while (col_count < cube.max_col && x < map_tile * cube.max_col)
		{
			color = ft_render_tile_color(map[(int)row_count][(int)col_count]);
			my_mlx_pixel_put(vars, x, y, color);
			x++;
			col_count = x / map_tile;
		}
		y++;
		row_count = y / map_tile;
	}
	ft_render_player(vars, map_tile);
}

static	void	ft_render_line_gpetit(t_vars *vars, float ray_angle, float x, float y,
				int ratio)
{
	float r;

	r = 0;
	while (!ft_is_maplimit(x, y, vars) && ft_map_content(x, y, vars) != 1)
	{
		my_mlx_pixel_put(vars, x * ratio, y * ratio, ORANGE);
		x = vars->player.x + cos(ray_angle) * r;
		y = vars->player.y - sin(ray_angle) * r;
		r += 0.5;
	}
}

void				ft_render_all_rays(t_vars *vars, int map_tile)
{
	int		i;
	float	x;
	float	y;
	int		ratio;

	i = 0;
	ratio = map_tile / TILE_SIZE;
	x = vars->player.x;
	y = vars->player.y;
	while (i < vars->ray_num)
	{
		ft_render_line_gpetit(vars, vars->rays[i].angle, x, y, ratio);
		i++;
	}
}

void				ft_render_minimap(t_vars *vars)
{
	char	**map;
	int		map_tile;
	int		tile_x;
	int		tile_y;

	tile_x = (vars->win_width / vars->cube.max_col) * MINIMAP_SCALE;
	tile_y = (vars->win_height / vars->cube.max_row) * MINIMAP_SCALE;
	if (tile_x > tile_y)
		map_tile = tile_y;
	else
		map_tile = tile_x;
	map = vars->cube.map;
	ft_render_grid(vars->cube, vars, map, map_tile);
	//ft_render_all_rays(vars, map_tile);
}
