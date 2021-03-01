/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:15:04 by calao             #+#    #+#             */
/*   Updated: 2021/03/01 14:43:57 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"


/*
void	ft_draw_line(t_vars *vars, float end_x, float end_y, float ray_angle)
{
	float x;
	float y;
	int		r;

	x = vars->player.x;
	y = vars->player.y;
	r = 0;

	while (x <= end_x && y <= end_y)
	{
		my_mlx_pixel_put(vars, x, y, ORANGE);
		x = vars->player.x + cos(ray_angle) * r;
		y = vars->player.y - sin(ray_angle) * r;
		r += RAY_STEP;
	}
}
*/

/*
void	ft_set_rays_values(t_rays *ray, t_vars *vars, float current_angle)
{
	float x;
	float y;
	
	x = vars->player.x;
	y = vars->player.y;


	ray->wallHitX = ft_vertical_intersection();
	ray->wallHitY = ft_horizontal_intersection();
	ray->angle = fov_start;
	ray->distance = distance;
	ray->HitContent = ft_collision_content(x, y, vars);
}
*/

void	ft_cast_single_ray(float x, float y, t_vars *vars, float ray_angle)
{
	int r;
	
	r = 0;
	while (!ft_is_maplimit(x, y, vars) && !ft_collision_content(x, y, vars))
		{
			my_mlx_pixel_put(vars, x, y, ORANGE);
			x = vars->player.x + cos(ray_angle) * r;
			y = vars->player.y - sin(ray_angle) * r;
			r += RAY_STEP;
		}
}

	
void	ft_cast_all_rays(t_vars *vars)
{
	float x;
	float y;
	float ray_angle;
	int i;

	ray_angle = ft_radconvert(vars->player.angle) - ft_radconvert(FOV) / 2;
	// fov_start = pikuma RayAngle ? 
	i = 0;
	while  (i < RAY_NUMBER)
	{
		x = vars->player.x;
		y = vars->player.y;
	
	//	ft_set_rays_values(vars->rays + i, vars, ray_angle);
		ft_cast_single_ray(x, y, vars, vars->player.angle + ray_angle);
	
		i++;

		// RAY_NUMBER = decalage d'angle entre chaque rayon
		ray_angle += ft_radconvert(RAY_ANGLE);
	}
}
