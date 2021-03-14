/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:53:00 by calao             #+#    #+#             */
/*   Updated: 2021/03/14 01:37:10 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char *dst;

	dst = vars->game.addr + (y * vars->game.line_len +
			x * (vars->game.bpp / 8));
	*(unsigned int*)dst = color;
}

int		ft_get_xpm_pixel_value(t_img *img, int x, int y)
{
	char *dst;

	dst = img->addr + (y * img->line_len) + (x * 4);
	return (*(unsigned*)dst);
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
