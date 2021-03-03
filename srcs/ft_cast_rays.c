/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:15:04 by calao             #+#    #+#             */
/*   Updated: 2021/03/03 13:08:12 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void	ft_set_ray_angle(t_rays *ray, float ray_angle)
{
	ray->angle = ray_angle;
	if (ray_angle > 0 && ray_angle < PI)
		ray->rayisup = TRUE;
	else
		ray->rayisup = FALSE;
	if (ray_angle < PI / 2 || ray_angle > (3 * PI) / 2)
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
	printf("horz->distance = %f\n", horz_hit.distance);
	printf("vert->distance = %f\n", vert_hit.distance);
	if (vert_hit.distance < horz_hit.distance)
	{
		ray->wallhitx = vert_hit.wallhitx;
		ray->wallhity = vert_hit.wallhity;
		ray->distance = vert_hit.distance;
		ray->hitisvertical = TRUE;
		ray->hitcontent = vert_hit.content;
		printf("--VERT_HIT--\n");
	}
	else
	{
		ray->wallhitx = horz_hit.wallhitx;
		ray->wallhity = horz_hit.wallhity;
		ray->distance = horz_hit.distance;
		ray->hitisvertical = FALSE;
		ray->hitcontent = horz_hit.content;
		printf("--HORZ_HIT--\n");
	}
	//printf("player_x = %f | player_y = %f\n", vars->player.x, vars->player.y);
}


void	ft_cast_all_rays(t_vars *vars)
{
	float x;
	float y;
	float ray_angle;
	int i;

	//ray_angle = vars->player.angle - ft_radconvert(FOV / 2);
	ray_angle = vars->player.angle;
	ray_angle = ft_within_twopi(ray_angle);
	
	i = 0;
	while  (i < RAY_NUMBER)
	{
		x = vars->player.x;
		y = vars->player.y;
		ft_set_ray_angle(vars->rays + i, ray_angle);
		ft_set_ray_wallhit(vars->rays + i, vars);
		//print_ray_info(vars->rays + i);
		ft_cast_single_ray(x, y, vars, ray_angle);
		i++;
		// RAY_NUMBER = decalage d'angle entre chaque rayon
		ray_angle += ft_radconvert(RAY_ANGLE);
	}
}
