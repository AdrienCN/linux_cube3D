/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_player_move.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:11:10 by calao             #+#    #+#             */
/*   Updated: 2021/03/15 14:59:08 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

float	ft_calculate_new_x(float x, t_vars *vars)
{
	float x_ref;
	float angle;

	x_ref = vars->player.x;
	angle = vars->player.angle;
	if (vars->player.vert_walk == 1)
		x = x_ref + cos(angle) * vars->move_speed;
	else if (vars->player.vert_walk == -1)
		x = x_ref - cos(angle) * vars->move_speed;
	else if (vars->player.hze_walk == 1)
		x = x_ref + cos(ft_within_twopi(angle + (M_PI / 2)))
			* vars->move_speed;
	else if (vars->player.hze_walk == -1)
		x = x_ref - cos(ft_within_twopi(angle + (M_PI / 2)))
			* vars->move_speed;
	return (x);
}

float	ft_calculate_new_y(float y, t_vars *vars)
{
	float y_ref;
	float angle;

	y_ref = vars->player.y;
	angle = vars->player.angle;
	if (vars->player.vert_walk == 1)
		y = y_ref - sin(angle) * vars->move_speed;
	else if (vars->player.vert_walk == -1)
		y = y_ref + sin(angle) * vars->move_speed;
	else if (vars->player.hze_walk == 1)
		y = y_ref - sin(ft_within_twopi(angle + (M_PI / 2)))
			* vars->move_speed;
	else if (vars->player.hze_walk == -1)
		y = y_ref + sin(ft_within_twopi(angle + (M_PI / 2)))
			* vars->move_speed;
	return (y);
}

int		ft_update_player(t_vars *vars)
{
	float x;
	float y;

	x = 0;
	y = 0;
	if (vars->player.exit)
	{
		mlx_loop_end(vars->mlx);
		return (0);
	}
	vars->player.angle = ft_within_twopi(vars->player.angle
			+ vars->player.turn * vars->rot_speed);
	x = ft_calculate_new_x(x, vars);
	y = ft_calculate_new_y(y, vars);
	if (ft_is_maplimit(x, y, vars) || ft_map_content(x, y, vars))
		return (1);
	vars->player.x = x;
	vars->player.y = y;
	return (0);
}

int		ft_update_move(int keycode, t_vars *vars)
{
	int c;

	c = keycode;
	if (c == A)
		vars->player.hze_walk = 1;
	else if (c == D)
		vars->player.hze_walk = -1;
	else if (c == W)
		vars->player.vert_walk = 1;
	else if (c == S)
		vars->player.vert_walk = -1;
	else if (c == LEFT_ARROW)
		vars->player.turn = 1;
	else if (c == RIGHT_ARROW)
		vars->player.turn = -1;
	else if (c == ESCAPE)
		vars->player.exit = 1;
	return (1);
}
