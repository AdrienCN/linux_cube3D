/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:13:14 by calao             #+#    #+#             */
/*   Updated: 2021/03/14 01:06:32 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

static	t_img	*ft_what_is_texture(t_vars *vars, t_rays ray)
{
	if (ray.hitisvertical)
	{
		if (ray.rayisleft)
			return (&vars->text.west);
		else
			return (&vars->text.east);
	}
	else
	{
		if (ray.rayisup)
			return (&vars->text.north);
		else
			return (&vars->text.south);
	}
}

static	float	ft_set_x_text(t_rays ray, t_img *w_text)
{
	float	x_coord;
	int		tronc;

	if (ray.hitisvertical)
	{
		tronc = ray.wallhity / TILE_SIZE;
		if (ray.rayisleft)
			x_coord = (ray.wallhity - (TILE_SIZE * tronc))
			* (w_text->width / TILE_SIZE);
		else
			x_coord = ((-ray.wallhity + (TILE_SIZE * (tronc + 1)))
			* (w_text->width / TILE_SIZE));
	}
	else
	{
		tronc = ray.wallhitx / TILE_SIZE;
		if (ray.rayisdown)
			x_coord = (ray.wallhitx - (TILE_SIZE * tronc))
				* (w_text->width / TILE_SIZE);
		else
			x_coord = ((-ray.wallhitx + (TILE_SIZE * (tronc + 1)))
				* (w_text->width / TILE_SIZE));
	}
	return (x_coord);
}

static	void	ft_xpm_wall_pixel_put(t_vars *vars, t_rays ray,
										int x, int y, int pos_in_wall)
{
	float			x_text;
	float			y_text;
	t_img			*text;
	unsigned int	color;

	if (ray.wallheight > vars->win_height)
		pos_in_wall += (ray.wallheight - vars->win_height) / 2;
	text = ft_what_is_texture(vars, ray);
	x_text = ft_set_x_text(ray, text);
	y_text = (((int)pos_in_wall) / ray.wallheight) * text->height;
	color = ft_get_xpm_pixel_value(text, x_text, y_text);
	my_mlx_pixel_put(vars, x, y, color);
}

void			ft_render_walls(t_vars *vars, t_rays *ray)
{
	int		y;
	int		x;
	float	pos_in_wall;

	x = 0;
	while (x < vars->ray_num)
	{
		y = 0;
		pos_in_wall = 0;
		while (y < ray[x].wall_start)
		{
			my_mlx_pixel_put(vars, x, y, vars->ceil_color);
			y++;
		}
		while (y >= ray[x].wall_start && y <= ray[x].wall_end)
		{
			ft_xpm_wall_pixel_put(vars, ray[x], x, y, pos_in_wall);
			y++;
			pos_in_wall++;
		}
		while (y < vars->win_height)
		{
			my_mlx_pixel_put(vars, x, y, vars->floor_color);
			y++;
		}
		x++;
	}
}
