/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_hit_algebra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:27:05 by calao             #+#    #+#             */
/*   Updated: 2021/03/09 10:00:15 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"


void	ft_set_vert_hit(t_inter *vert, t_vars *vars, t_rays *ray)
{
	float x;
	float y;

	x = vars->player.x;
	y = vars->player.y;
	// Trouver une parade a INT_MAX
	vert->distance = INT_MAX;
	vert->found_wall = -1;
	vert->x_inter = ((int)(x / TILE_SIZE)) * TILE_SIZE ;
	if (ray->rayisright)
		vert->x_inter += TILE_SIZE;
	vert->y_inter = y - (vert->x_inter - x) * tan(ray->angle);
	vert->x_step = TILE_SIZE;
	if (ray->rayisleft)
		vert->x_step *= -1;
	vert->y_step = TILE_SIZE * tan(ray->angle);
	if (ray->rayisup && vert->y_step > 0)
		vert->y_step *= -1;
	else if (ray->rayisdown && vert->y_step < 0)
		vert->y_step *= -1;
	vert->next_x = vert->x_inter;
	vert->next_y = vert->y_inter;
}

void	ft_set_sprite_to_visible(t_vars *vars, float x, float y)
{
	int row;
	int col;
	int i;

	i = 0;
	row = y / TILE_SIZE;
	col = x / TILE_SIZE;
	while (i < vars->sprite_count)
	{
		if (vars->sprite_tab[i].row == row 
				&& vars->sprite_tab[i].col == col)
		{
			vars->sprite_tab[i].is_visible = 1;
			//Set ray_sprite_dist?
			
			//Set ray_sprite_angle?

			//Set ray_sprite_height ?
			return;
		}
		i++;
	}
}

void	ft_set_horz_hit(t_inter *horz, t_vars *vars, t_rays *ray)
{
	float x;
	float y;

	x = vars->player.x;
	y = vars->player.y;
	// Trouver une parade a INT_MAX
	horz->distance = INT_MAX;
	horz->found_wall = -1;
	horz->y_inter = ((int)(y / TILE_SIZE)) * TILE_SIZE ;
	if (ray->rayisdown)
		horz->y_inter += TILE_SIZE;
	horz->x_inter = x - (horz->y_inter - y) / tan(ray->angle);
	horz->y_step = TILE_SIZE;
	if (ray->rayisup)
		horz->y_step *= -1;
	horz->x_step = TILE_SIZE / tan(ray->angle);
	if (ray->rayisleft && horz->x_step > 0)
		horz->x_step *= -1;
	else if (ray->rayisright && horz->x_step < 0)
		horz->x_step *= -1;
	horz->next_x = horz->x_inter;
	horz->next_y = horz->y_inter;
}

void	ft_find_horz_wallhit(t_vars *vars, t_rays *ray, t_inter *horz)
{
	float tmp;
	float x1;
	float y1;

	x1 = vars->player.x;
	y1 = vars->player.y;
	tmp = 0;
	if (ray->rayisup)
		tmp = -1;
	while (!ft_is_maplimit(horz->next_x, horz->next_y + tmp, vars))
	{
		if (ft_is_sprite(horz->next_x, horz->next_y + tmp, vars))
				ft_set_sprite_to_visible(vars, horz->next_x, horz->next_y + tmp);
		if (ft_is_wall(horz->next_x, horz->next_y + tmp, vars))
		{
			horz->wallhitx = horz->next_x;
			horz->wallhity = horz->next_y;
			horz->distance = ft_get_distance(x1, y1, horz->next_x, horz->next_y);
			horz->found_wall = 1;
			return;
		}
		horz->next_x += horz->x_step;
		horz->next_y += horz->y_step;
	}
}

void	ft_find_vert_wallhit(t_vars *vars, t_rays *ray, t_inter *vert)
{
	float tmp;
	float x1;
	float y1;

	x1 = vars->player.x;
	y1 = vars->player.y;
	tmp = 0;
	if (ray->rayisleft)
		tmp = -1;
	while (!ft_is_maplimit(vert->next_x + tmp, vert->next_y, vars))
	{
		if (ft_is_sprite(vert->next_x + tmp, vert->next_y, vars))
				ft_set_sprite_to_visible(vars, vert->next_x + tmp, vert->next_y);
		if (ft_is_wall(vert->next_x + tmp, vert->next_y, vars))
		{
			vert->wallhitx = vert->next_x;
			vert->wallhity = vert->next_y;
			vert->distance = ft_get_distance(x1, y1, vert->next_x, vert->next_y);
			vert->found_wall = 1;
			return;
		}
		vert->next_x += vert->x_step;
		vert->next_y += vert->y_step;
	}
}
