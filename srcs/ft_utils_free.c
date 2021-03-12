/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:27:02 by calao             #+#    #+#             */
/*   Updated: 2021/03/12 22:44:24 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void	ft_free_doublearray(char **tab)
{
	while (*tab)
	{
		free(*tab);
		tab++;
	}
}

void	ft_free_cube(t_cube *element)
{
	if (element->north != NULL)
		free(element->north);
	if (element->east != NULL)
		free(element->east);
	if (element->south != NULL)
		free(element->south);
	if (element->west != NULL)
		free(element->west);
	if (element->sprite != NULL)
		free(element->sprite);
	if (element->map != NULL)
	{
		ft_free_doublearray(element->map);
		free(element->map);
	}
	if (element->gnl_line != NULL)
		free(element->gnl_line);
	if (element->m_line != NULL)
		free(element->m_line);
}

void			ft_free_img(t_img *img)
{
	free(img->img);
	free(img->addr);
}

void			ft_free_game(t_vars *vars)
{
	ft_free_img(&vars->game);
	ft_free_img(&vars->text.north);
	ft_free_img(&vars->text.south);
	ft_free_img(&vars->text.east);
	ft_free_img(&vars->text.west);
	ft_free_img(&vars->text.sprite);
	free(vars->sprite_tab);
	free(vars->rays);
	ft_free_cube(&vars->cube);
}
