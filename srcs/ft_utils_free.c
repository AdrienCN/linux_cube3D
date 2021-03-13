/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:27:02 by calao             #+#    #+#             */
/*   Updated: 2021/03/13 12:07:16 by calao            ###   ########.fr       */
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
	if (element->gnl_leak_proof)
		free(element->gnl_leak_proof);
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

void			ft_free_game(t_vars *vars)
{
	if (vars->game.img)
		mlx_destroy_image(vars->mlx, vars->game.img);
	if (vars->text.north.img)
		mlx_destroy_image(vars->mlx, vars->text.north.img);
	if (vars->text.south.img)
		mlx_destroy_image(vars->mlx, vars->text.south.img);
	if (vars->text.east.img)
		mlx_destroy_image(vars->mlx, vars->text.east.img);
	if (vars->text.west.img)
		mlx_destroy_image(vars->mlx, vars->text.west.img);
	if (vars->text.sprite.img)
		mlx_destroy_image(vars->mlx, vars->text.sprite.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	free(vars->sprite_tab);
	free(vars->rays);
	ft_free_cube(&vars->cube);
}
