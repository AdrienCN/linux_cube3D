/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:04:58 by calao             #+#    #+#             */
/*   Updated: 2021/03/09 17:05:26 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"


void	ft_render_line_dda(t_vars *vars, t_rays ray, float x1, float y1)
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

void	ft_render_line_gpetit(float x, float y, t_vars *vars, float ray_angle)
{
	float r;
	
	r = 0;
	while (!ft_is_maplimit(x, y, vars) && ft_map_content(x, y, vars) != 1)
		{
			my_mlx_pixel_put(vars, x * MINIMAP_SCALE,
				   	y * MINIMAP_SCALE, ORANGE);
			x = vars->player.x + cos(ray_angle) * r;
			y = vars->player.y - sin(ray_angle) * r;
			r += RAY_STEP;
		}
}

