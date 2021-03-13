/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:57:39 by calao             #+#    #+#             */
/*   Updated: 2021/03/13 16:39:38 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void			ft_draw_square(t_vars *vars, int p_y, int p_x, int hei, int wid,int color)
{
	int i;
	int j;

	i = 0;
	while (i < hei)
	{
		j = 0;
		while (j < wid)
		{
			if (!ft_is_maplimit(p_x + j, p_y + i, vars)
					&& !ft_map_content(p_x + j, p_y + i, vars))
				my_mlx_pixel_put(vars, p_x + j * MINIMAP_SCALE,
					   	p_y + i * MINIMAP_SCALE, color);
			j++;
		}
		i++;
	}
}
