/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:56:52 by calao             #+#    #+#             */
/*   Updated: 2021/03/07 13:53:27 by calao            ###   ########.fr       */
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

void	ft_bresenham_line_draw_algo(t_vars *vars, float x1 ,float y1, float x2, float y2)

{
	float dx;
	float dy;
	float x;
	float y;
	float p;
	float end;
    
	dx = x1 - x2;
    dy = y1 - y2;
    p = 2 * dy - dx;

    if (x1 > x2)
    {
        x = x2;
        y = y2;
        end = x1;
    }
    else
    {
        x = x1;
        y = y1;
        end = x2;
    }
    my_mlx_pixel_put(vars, x, y, RED);
    while (x < end)
    {
        x = x + 1;
        if (p < 0)
        {
              p = p + 2 * dy;
        }
        else
        {
              y = y + 1;
              p = p + 2 * (dy - dx);
        }
        my_mlx_pixel_put(vars, x, y, RED);
    }
}	
