/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:15:04 by calao             #+#    #+#             */
/*   Updated: 2021/03/04 12:58:19 by calao            ###   ########.fr       */
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
//	printf("horz->distance = %f\n", horz_hit.distance);
//	printf("vert->distance = %f\n", vert_hit.distance);
	if (vert_hit.distance < horz_hit.distance)
	{
		ray->wallhitx = vert_hit.wallhitx;
		ray->wallhity = vert_hit.wallhity;
		ray->distance = vert_hit.distance;
		ray->hitisvertical = TRUE;
		ray->hitcontent = vert_hit.content;
//		printf("--VERT_HIT--\n");
	}
	else
	{
		ray->wallhitx = horz_hit.wallhitx;
		ray->wallhity = horz_hit.wallhity;
		ray->distance = horz_hit.distance;
		ray->hitisvertical = FALSE;
		ray->hitcontent = horz_hit.content;
//		printf("--HORZ_HIT--\n");
	}
	//printf("player_x = %f | player_y = %f\n", vars->player.x, vars->player.y);
}

void	ft_set_rayprojection_val(t_rays *ray, float screen_dist, t_vars *vars)
{
	// corrige ray.distance	
	ray->fixed_dist = ray->distance *
		cos(ray->angle - vars->player.angle);

	// hauteur du mur (conversion en int ?)
	ray->wallheight = (TILE_SIZE / ray->fixed_dist) * screen_dist;
	
	// limite superieure du mur
	ray->walluplimit = (vars->win_height / 2) -
		(ray->wallheight / 2);
	
	// limite inf du mur
	ray->walldownlimit = (vars->win_height / 2) +
		(ray->wallheight / 2);
	if (ray->walluplimit < 0)
		ray->walluplimit = 0;
	if (ray->walldownlimit > vars->win_height)
		ray->walldownlimit = 0;
}
		

void	ft_cast_all_rays(t_vars *vars)
{
	float ray_angle;
	float screen_dist;
	int i;

	ray_angle = vars->player.angle - ft_radconvert(FOV / 2);
	//ray_angle = vars->player.angle;
	ray_angle = ft_within_twopi(ray_angle);
	screen_dist = (vars->win_width / 2) / tan(ft_radconvert(FOV/2));	
	i = 0;
	while  (i < vars->ray_num)
	{
		ft_set_ray_angle(vars->rays + i, ray_angle);
		ft_set_ray_wallhit(vars->rays + i, vars);
		ft_set_rayprojection_val(vars->rays + i, screen_dist, vars);
		//print_ray_info(vars->rays + i);
		i++;
		// vars->ray_num = decalage d'angle entre chaque rayon
		ray_angle += ft_radconvert(vars->ray_increment);
	}
}
