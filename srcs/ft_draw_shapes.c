/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_shapes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:57:39 by calao             #+#    #+#             */
/*   Updated: 2021/02/12 17:57:52 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void			ft_print_square(t_vars *vars, int p_y, int p_x, int hei, int wid)
{
	int i;
	int j;

	i = 0;
	while (i < hei)
	{
		j = 0;
		while (j < wid)
		{
			my_mlx_pixel_put(vars, p_x + j, p_y + i, RED);
			j++;
		}
		i++;
	}
}
