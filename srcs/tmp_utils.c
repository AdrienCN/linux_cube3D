/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:56:52 by calao             #+#    #+#             */
/*   Updated: 2021/03/07 14:52:10 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void			ft_print_tab(char **tab)
{
	int row;
	int col;

	row = 0;
		while (tab[row])
		{
			col = 0;
			printf("row:%3d", row);
			while (tab[row][col])
			{
				printf("|%c", tab[row][col]);
				col++;
			}
			printf("||\n");
			row++;
		}
}
void	print_ray_info(t_rays *ray)
{
	printf("ray_distance = %f\n", ray->distance);
	//printf("x_hit = %f || y_hit = %f \n", ray->wallhitx, ray->wallhity);
	ray->rayisup ? printf("*UP*\n") : printf("*DOWN*\n");
	ray->rayisleft ? printf("*LEFT*\n") : printf ("*RIGHT*\n");
	//printf("CONTENT = %d\n", ray->hitcontent);
}
//Fonction a supprimer plus tard. Permet de visualiser les rayons mais coute cher en calcul
void	ft_cast_single_ray(float x, float y, t_vars *vars, float ray_angle)
{
	float r;
	
	r = 0;
	while (!ft_is_maplimit(x, y, vars) && ft_map_content(x, y, vars) != 1)
		{
			my_mlx_pixel_put(vars, x * MINIMAP_SCALE,
				   	y * MINIMAP_SCALE, ORANGE);
			x = vars->player.x + cos(ray_angle) * r;
			y = vars->player.y - sin(ray_angle) * r;
			r += RAY_STEP;
		}
}
