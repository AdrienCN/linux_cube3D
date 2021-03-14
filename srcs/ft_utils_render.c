/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:04:58 by calao             #+#    #+#             */
/*   Updated: 2021/03/14 01:15:16 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"


void	ft_render_line_gpetit(t_vars *vars, float ray_angle, float x, float y)
{
	float r;

	r = 0;
	while (!ft_is_maplimit(x, y, vars) && ft_map_content(x, y, vars) != 1)
	{
		my_mlx_pixel_put(vars, x * MINIMAP_SCALE,
					y * MINIMAP_SCALE, ORANGE);
		x = vars->player.x + cos(ray_angle) * r;
		y = vars->player.y - sin(ray_angle) * r;
		r += 0.5;
	}
}
