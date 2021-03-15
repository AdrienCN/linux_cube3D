/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:15:04 by calao             #+#    #+#             */
/*   Updated: 2021/03/15 15:14:36 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void	ft_set_ray_angle(t_rays *ray, float ray_angle)
{
	ray->angle = ray_angle;
	if (ray_angle > 0 && ray_angle < M_PI)
		ray->rayisup = TRUE;
	else
		ray->rayisup = FALSE;
	if (ray_angle < M_PI / 2 || ray_angle > (3 * M_PI) / 2)
		ray->rayisright = TRUE;
	else
		ray->rayisright = FALSE;
	ray->rayisdown = !ray->rayisup;
	ray->rayisleft = !ray->rayisright;
}

void	ft_set_ray_wallhit(t_rays *ray, t_vars *vars)
{
	t_inter	vert_hit;
	t_inter horz_hit;

	ft_set_vert_hit(&vert_hit, vars, ray);
	ft_set_horz_hit(&horz_hit, vars, ray);
	ft_find_vert_wallhit(vars, ray, &vert_hit);
	ft_find_horz_wallhit(vars, ray, &horz_hit);
	if (vert_hit.distance < horz_hit.distance)
	{
		ray->wallhitx = vert_hit.wallhitx;
		ray->wallhity = vert_hit.wallhity;
		ray->distance = vert_hit.distance;
		ray->hitisvertical = TRUE;
	}
	else
	{
		ray->wallhitx = horz_hit.wallhitx;
		ray->wallhity = horz_hit.wallhity;
		ray->distance = horz_hit.distance;
		ray->hitisvertical = FALSE;
	}
}

void	ft_set_rayprojection_val(t_rays *ray, float screen_dist, t_vars *vars)
{
	ray->fixed_dist = ray->distance *
		cos(ray->angle - vars->player.angle);
	ray->wallheight = (TILE_SIZE / ray->fixed_dist) * screen_dist;
	ray->wall_start = (vars->win_height / 2) -
		(ray->wallheight / 2);
	ray->wall_end = (vars->win_height / 2) +
		(ray->wallheight / 2);
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	if (ray->wall_end > vars->win_height)
		ray->wall_end = vars->win_height;
}

void	ft_cast_all_rays(t_vars *vars)
{
	float	ray_angle;
	float	screen_dist;
	int		i;

	screen_dist = (vars->win_width / 2) / tan(ft_radconvert(FOV / 2));
	i = 0;
	while (i < vars->ray_num)
	{
		ray_angle = ft_within_twopi(vars->player.angle +
				atan(((vars->ray_num / 2) - i) / screen_dist));
		ft_set_ray_angle(vars->rays + i, ray_angle);
		ft_set_ray_wallhit(vars->rays + i, vars);
		ft_set_rayprojection_val(vars->rays + i, screen_dist, vars);
		ft_render_walls(vars, vars->rays[i], i);
		i++;
	}
}
