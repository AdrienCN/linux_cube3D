/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:15:04 by calao             #+#    #+#             */
/*   Updated: 2021/03/02 11:00:02 by calao            ###   ########.fr       */
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
	float r;
	
	r = 0;
	while (ft_is_maplimit(x, y, vars) == 0 && ft_map_content(x, y, vars) == 0)
		{
			my_mlx_pixel_put(vars, x, y, ORANGE);
			x = vars->player.x + cos(ray_angle) * r;
			y = vars->player.y - sin(ray_angle) * r;
			r += RAY_STEP;
		}
	/*
		my_mlx_pixel_put(vars, x - 1, y, RED);
		my_mlx_pixel_put(vars, x, y, RED);
		my_mlx_pixel_put(vars, x + 1, y, RED);
		my_mlx_pixel_put(vars, x, y + 1, RED);
		my_mlx_pixel_put(vars, x, y - 1, RED);
	*/
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

void	ft_set_ray_wallhit(t_rays *ray, t_vars *vars)
{
	t_inter	vert_hit;
	t_inter horz_hit;

	ft_set_vert_hit(&vert_hit);
	ft_set_horz_hit(&horz_hit);
	ft_find_first_wallhit(ray, vars, &vert_hit);
	ft_find_first_wallhit(ray, vars, &vert_hit);
	if (vert_hit.distance > horz_hit.distance)
	{
		ray->wallhitx = vert_hit.wallhitx;
		ray->wallhity = vert_hit.wallhity;
		ray->distance = vert_hit.distance;
		ray->hitisvertical = TRUE;
		ray->hitcontent = vert_hit.content;
	}
	else
	{
		ray->wallhitx = horz_hit.wallhitx;
		ray->wallhity = horz_hit.wallhity;
		ray->distance = horz_hit.distance;
		ray->hitisvertical = FALSE;
		ray->hitcontent = horz_hit.content;
	}
}

void	ft_find_hit(t_rays *ray, t_vars *vars, t_inter *intersection)
{
	float next_x;
	float next_y;
	float x1;
	float y1;

	x1 = vars->player.x;
	y1 = vars->player.y;
	next_x = intersection->next_x;
	next_y = intersection->next_y;
	while (!ft_is_maplimit(next_x, next_y, vars))
	{
		if (ft_is_wall(next_x, next_y, vars))
		{
			intersection->wallhitx = next_x;
			intersection->wallhity = next_y;
			intersection->content = ft_map_content(next_x, next_y, vars);
			intersection->distance = ft_get_distance(x1, y1, next_x, next_y);
			intersection->found_wall = 1;
			return;
		}
		next_x += intersection->x_step;
		next_y += intersection->y_step;
	}
}
	

void	ft_cast_all_rays(t_vars *vars)
{
	float x;
	float y;
	float ray_angle;
	int i;
	
	ray_angle = ft_radconvert(vars->player.angle) - ft_radconvert(FOV) / 2;
	ray_angle += vars->player.angle;	
	i = 0;
	while  (i < RAY_NUMBER)
	{
		x = vars->player.x;
		y = vars->player.y;
		ft_set_ray_angle(vars->rays + i, ray_angle);
		ft_set_ray_wallhit(vars->rays + i, vars);
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
	printf("x_hit = %f || y_hit = %f \n", ray->wallhitx, ray->wallhity);
	ray->rayisup ? printf("ray is *up*\n") : printf("ray is *down*\n");
	ray->rayisleft ? printf("ray is *left*\n") : printf ("ray is *right*\n");
	printf("ray hit content = %d\n", ray->hitcontent);
}
