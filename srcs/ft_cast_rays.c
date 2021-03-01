/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:15:04 by calao             #+#    #+#             */
/*   Updated: 2021/03/01 16:35:23 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void	print_ray_info(t_rays *ray);

void	ft_set_ray_angle(t_rays *ray, float ray_angle)
{
	// avec ou sans le vars.player.angle ?
	ray->angle = ray_angle;
	if (ray_angle > 0 && ray_angle < PI)
		ray->RayIsUp = TRUE;
	else
		ray->RayIsUp = FALSE;
	if (ray_angle < PI / 2 || ray_angle > (3 * PI) / 2)
		ray->RayIsRight = TRUE;
	else
		ray->RayIsRight = FALSE;
	ray->RayIsDown = !ray->RayIsUp;
	ray->RayIsLeft = !ray->RayIsRight;
}

void	ft_cast_single_ray(float x, float y, t_vars *vars, float ray_angle)
{
	int r;
	
	r = 0;
	while (!ft_is_maplimit(x, y, vars) && !ft_map_content(x, y, vars))
		{
			my_mlx_pixel_put(vars, x, y, ORANGE);
			x = vars->player.x + cos(ray_angle) * r;
			y = vars->player.y - sin(ray_angle) * r;
			r += RAY_STEP;
		}
}

float	ft_distance(float x1, float y1, float x2, float y2)
{
	double result;
	double x;
	double y;

	x = (x2 - x1) * (x2 - x1);
	y = (y2 - y1) * (y2 - y1);

	result = sqrt(x + y);
	return ((float)result);
}

void	ft_set_ray_wallhit(t_rays *ray, t_vars *vars, float ray_angle)
{
	float x;
	float y;
	int r;
	int content;

	r = 0;
	x = vars->player.x;
	y = vars->player.y;
	ray_angle += vars->player.angle;
	content = 0;
	while (!ft_is_maplimit(x, y, vars) && content == 0)
		{
			x = vars->player.x + cos(ray_angle) * r;
			y = vars->player.y - sin(ray_angle) * r;
			r += RAY_STEP;
			content = ft_map_content(x, y, vars);
		}
	ray->distance = ft_distance(vars->player.x, vars->player.y, x, y);
	ray->wallHitX = x;
	ray->wallHitY = y;
	ray->HitContent = ft_map_content(x, y, vars);
}

void	ft_cast_all_rays(t_vars *vars)
{
	float x;
	float y;
	float ray_angle;
	int i;
	
	//ray_angle = ft_radconvert(vars->player.angle) - ft_radconvert(FOV) / 2;
	ray_angle = vars->player.angle;
	
	i = 0;
	while  (i < RAY_NUMBER)
	{
		x = vars->player.x;
		y = vars->player.y;
		ft_set_ray_angle(vars->rays + i, ray_angle);
		ft_set_ray_wallhit(vars->rays + i, vars, ray_angle);
		ft_cast_single_ray(x, y, vars, ray_angle);
		print_ray_info(vars->rays + i);
		i++;
		// RAY_NUMBER = decalage d'angle entre chaque rayon
		ray_angle += ft_radconvert(RAY_ANGLE);
	}
}

void	print_ray_info(t_rays *ray)
{
	printf("ray_distance = %f\n", ray->distance);
	ray->RayIsUp ? printf("Ray is *UP*\n") : printf("Ray is *DOWN*\n");
	ray->RayIsLeft ? printf("Ray is *LEFT*\n") : printf ("Ray is *RIGHT*\n");
	printf("Ray HIT CONTENT = %d\n", ray->HitContent);
}

